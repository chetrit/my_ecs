/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include <any>
#include <functional>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "entity.hpp"
#include "sparse_array.hpp"

template <typename...>
struct is_one_of;

template <typename F>
struct is_one_of<F> {
    static constexpr bool value = false;
};

template <typename F, typename S, typename... T>
struct is_one_of<F, S, T...> {
    static constexpr bool value = std::is_same<F, S>::value || is_one_of<F, T...>::value;
};

template <typename...>
struct is_unique;

template <>
struct is_unique<> {
    static constexpr bool value = true;
};

template <typename F, typename... T>
struct is_unique<F, T...> {
    static constexpr bool value = is_unique<T...>::value && !is_one_of<F, T...>::value;
};

namespace ecs {
class registry_t {
  public:
    template <class Component>
    /**
     * @brief Register a new component
     */
    sparse_array<Component> &register_component() {
        _components_arrays.emplace(std::type_index(typeid(Component)), sparse_array<Component>());
        _erase_component_funcs.push_back(
            [](entity_t const &e, registry_t &r) { r.remove_component<Component>(e); });
        return std::any_cast<sparse_array<Component> &>(
            _components_arrays[std::type_index(typeid(Component))]);
    };

    template <class... Components>
    void register_components() {
        constexpr bool unique_types = is_unique<Components...>::value;

        if (!unique_types) {
            throw std::out_of_range("Components are not unique");
        }
        std::call_once(_init_flag, [=] {
            (_components_arrays.emplace(std::type_index(typeid(Components)),
                                        sparse_array<Components>()),
             ...);
            _erase_component_funcs.push_back(
                [](entity_t const &e, registry_t &r) { (r.remove_component<Components>(e), ...); });
        });
    };

    /**
     * @brief Obtain sparse array of a component
     */
    template <class Component>
    sparse_array<Component> &get_components() {
        return std::any_cast<sparse_array<Component> &>(
            _components_arrays[std::type_index(typeid(Component))]);
    };

    /**
     * @brief Obtain constant sparse array of a component
     */
    template <class Component>
    sparse_array<Component> const &get_components() const {
        return std::any_cast<sparse_array<Component> &>(
            _components_arrays.at(std::type_index(typeid(Component))));
    };

    /**
     * @brief Create and return an Entity
     */
    entity_t spawn_entity() {
        entity_t entity(_index);
        _index++;
        return entity;
    };

    /**
     * @brief Create and return an Entity with a given index
     */
    entity_t entity_from_index(size_t const &idx) { return entity_t(idx); };

    /**
     * @brief Kill an entity
     */
    void kill_entity(entity_t const &entity) {
        _killed_entities.push_back(entity);
        for (auto _erase_component_func : _erase_component_funcs) {
            _erase_component_func(entity, *this);
        }
    };

    /**
     * @brief Add a component to a given entity
     */
    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(entity_t const &to,
                                                                   Component &&c) {
        get_components<Component>().insert_at(to, c);
        return get_components<Component>()[to];
    };

    /**
     * @brief Add the list of components to the registry
     */
    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(entity_t const &to,
                                                                       Params &&...p) {
        get_components<Component>().emplace_at(to, std::forward<Params>(p)...);
        return get_components<Component>()[to];
    };

    /**
     * @brief Remove a component of a given entity
     */
    template <typename Component>
    void remove_component(entity_t const &from) {
        sparse_array<Component> &components = get_components<Component>();
        if (from < components.size() && components[from]) {
            components.erase(from);
        }
    };

    template <class... Components, typename Callable>
    void add_system(Callable &&f) {
        _run_system_funcs.push_back([f = std::forward<Callable>(f)](registry_t &r) {
            f(r, r.get_components<Components>()...);
        });
    };

    template <class... Components, typename Callable>
    void add_system(Callable const &f) {
        _run_system_funcs.push_back(
            [&f](registry_t &r) { f(r, r.get_components<Components>()...); });
    }

    void run_systems() {
        for (auto &run_system_func : _run_system_funcs) {
            run_system_func(*this);
        }
    }

  private:
    size_t _index = 0;
    std::once_flag _init_flag;

    std::unordered_map<std::type_index, std::any> _components_arrays;

    std::vector<size_t> _killed_entities;
    std::vector<std::function<void(entity_t const &entity, registry_t &registry)>>
        _erase_component_funcs;
    std::vector<std::function<void(registry_t &)>> _run_system_funcs;
};
}  // namespace ecs

#endif /* !REGISTRY_HPP_ */
