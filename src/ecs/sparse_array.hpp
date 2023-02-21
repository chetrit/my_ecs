/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** sparse_array
*/

#ifndef SPARSE_ARRAY_HPP_
#define SPARSE_ARRAY_HPP_

#include <iostream>
#include <map>
#include <optional>
#include <vector>

namespace ecs {
template <typename Component>
class sparse_array {
  public:
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;

    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    /**
     * @brief Construct a new sparse_array object by default
     *
     */
    sparse_array() = default;
    /**
     * @brief Construct a new sparse_array object by copie
     *
     * @param old
     */
    sparse_array(sparse_array const &arr) : _data(arr._data){};
    /**
     * @brief Construct a new sparse_array object by move
     *
     * @param arr_ref arr reference
     */
    sparse_array(sparse_array &&arr_ref) noexcept : _data(std::move(arr_ref._data)){};
    /**
     * @brief Destroy the sparse_array object
     *
     */
    ~sparse_array() = default;

    /**
     * @brief Overload the assignement operator by copy
     *
     * @param array
     * @return sparse_array&
     */

    sparse_array &operator=(sparse_array const &arr) {
        _data = arr._data;
        return *this;
    };

    /**
     * @brief Overload the assignement operator by move
     *
     * @param array
     * @return sparse_array&
     */
    sparse_array &operator=(sparse_array &&arr_ref) noexcept {
        _data = std::move(arr_ref._data);
        return *this;
    };

    /**
     * @brief Overload the [] operator
     *
     * @param idx
     * @return reference_type
     */
    reference_type operator[](size_t idx) { return _data[idx]; };

    /**
     * @brief Overload the [] operator
     *
     * @param idx
     * @return const reference_type
     */
    const_reference_type operator[](size_t idx) const { return _data.at(idx); };

    /**
     * @brief Returns a read/write iterator that points to the first
     * element in the array. Iteration is done in ordinary
     * element order
     *
     * @return iterator
     */
    iterator begin() { return _data.begin(); };

    /**
     * @brief Returns a read/write iterator that points to the first
     * element in the array. Iteration is done in ordinary
     * element order
     *
     * @return const_iterator
     */
    const_iterator begin() const { return _data.begin(); };

    /**
     * @brief Returns a read-only (constant) iterator that points to the
     * first element in the array. Iteration is done in ordinary
     * element order
     *
     * @return const_iterator
     */
    const_iterator cbegin() const { return _data.cbegin(); };

    /**
     * @brief Returns a read/write iterator that points one past the last
     * element in the array. Iteration is done in ordinary
     * element order
     *
     * @return iterator
     */
    iterator end() { return _data.end(); };

    /**
     * @brief Returns a read/write iterator that points one past the last
     * element in the array. Iteration is done in ordinary
     * element order
     * @return const_iterator
     */
    const_iterator end() const { return _data.end(); };

    /**
     * @brief Returns a read-only (constant) iterator that points one past
     * the last element in the array. Iteration is done in
     * ordinary element order
     *
     * @return const_iterator
     */
    const_iterator cend() const { return _data.cend(); };

    /**
     * @brief Returns the number of elements in the array
     *
     * @return size_type
     */
    size_type size() const { return _data.size(); };

    /**
     * @brief Insert a copy component at the given position in the array, and
     * resize the array if needed
     *
     * @param pos
     * @param component
     * @return reference_type
     */
    reference_type insert_at(size_type pos, Component const &component) {
        if (pos >= size()) {
            _data.resize(pos + 1);
        }
        _data[pos] = std::make_optional(component);
        return _data[pos];
    };

    /**
     * @brief Insert a move component at the given position in the array, and
     * resize the array if needed
     *
     * @param pos
     * @param component_ref
     * @return reference_type
     */
    reference_type insert_at(size_type pos, Component &&component_ref) {
        if (pos >= this->size()) {
            _data.resize(pos + 1);
        }
        _data[pos] = std::move(component_ref);
        return _data[pos];
    }

    /**
     * @brief Insert a list of params given as parameters in the array
     *
     * @tparam Params
     * @param pos
     * @param params
     * @return reference_type
     */
    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...args) {
        using allocator_t = decltype(_data.get_allocator());
        if (pos >= this->size()) {
            _data.resize(pos + 1);
        }
        allocator_t alloc = _data.get_allocator();
        std::allocator_traits<allocator_t>::destroy(alloc, &_data[pos]);
        std::allocator_traits<allocator_t>::construct(alloc, &_data[pos], std::in_place,
                                                      std::forward<Params>(args)...);
        return _data[pos];
    };

    /**
     * @brief Erase the the component at the given value
     *
     * @param pos
     */
    void erase(size_type pos) { _data[pos] = std::nullopt; };

    /**
     * @brief Get the index object given
     *
     * @param value
     * @return size_type
     */
    size_type get_index(value_type const &component) const {
        if (component == std::nullopt) {
            throw std::out_of_range("no component given");
        }
        for (const_iterator it = this->begin(); it != this->end(); ++it) {
            if (std::addressof(*it) == std::addressof(component)) {
                return std::distance(_data.begin(), it);
            }
        }
        throw std::out_of_range("component not found");
    };

  private:
    container_t _data;
};
};  // namespace ecs

#endif /* !SPARSE_ARRAY_HPP_ */
