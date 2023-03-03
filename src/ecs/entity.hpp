/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cstddef>

namespace ecs {
class entity_t {
  public:
    explicit entity_t(size_t const& id_) : id(id_){};
    ~entity_t() = default;

    operator size_t() { return id; }

    operator size_t() const { return id; }

    size_t version = 1;
    size_t id;
};
};  // namespace ecs

#endif /* !ENTITY_HPP_ */
