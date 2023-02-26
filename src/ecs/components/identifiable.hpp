/*
** EPITECH PROJECT, 2023
** workspace
** File description:
** identifiable
*/

#ifndef IDENTIFIABLE_HPP_
#define IDENTIFIABLE_HPP_

#include <sys/types.h>

namespace ecs {
class identifiable_t {
  public:
    identifiable_t(id_t const &id_) : id(id_){};

    operator id_t() { return id; }

    operator id_t() const { return id; }

    id_t id;
};
}  // namespace ecs

#endif /* !IDENTIFIABLE_HPP_ */
