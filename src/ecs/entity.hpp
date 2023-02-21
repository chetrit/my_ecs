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
    explicit entity_t(size_t const& id) : _id(id){};
    ~entity_t() = default;

    operator size_t() { return _id; }

    operator size_t() const { return _id; }

  private:
    size_t _id;

    // size_t _version = 0;
};
};  // namespace ecs

#endif /* !ENTITY_HPP_ */
