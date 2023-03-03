/*
** EPITECH PROJECT, 2023
** workspace
** File description:
** human
*/

#ifndef HUMAN_HPP_
#define HUMAN_HPP_

namespace ecs {
class human_t {
  public:
    human_t(id_t const &id_) : id(id_){};

    operator id_t() { return id; }

    operator id_t() const { return id; }

    id_t id;
};
}  // namespace ecs

#endif /* !HUMAN_HPP_ */
