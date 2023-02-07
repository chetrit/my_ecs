/*
** EPITECH PROJECT, 2023
** workspace
** File description:
** human
*/

#ifndef HUMAN_HPP_
#define HUMAN_HPP_

#include <cstddef>

namespace ecs {
class human_t {
    human_t(size_t const &id_) : id(id_){};
    // ~human_t() = default;

    operator size_t() { return id; }

    operator size_t() const { return id; }

    size_t id;
};
}  // namespace ecs

#endif /* !HUMAN_HPP_ */
