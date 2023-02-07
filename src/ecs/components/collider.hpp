/*
** EPITECH PROJECT, 2023
** my_ecs
** File description:
** collider
*/

#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_

#include <algorithm>
#include <iostream>

#include "../entity.hpp"
#include "../registry.hpp"
#include "position.hpp"

namespace ecs {
class collider_t {
public:
  collider_t(int32_t width_, int32_t height_)
      : width(width_), height(height_){};

  collider_t(collider_t const &collider)
      : width(collider.width), height(collider.height){};

  collider_t &operator=(collider_t const &collider) {
    width = collider.width;
    height = collider.height;
    return *this;
  };

  pos_t get_top_left(pos_t const &point) const {
    return ecs::pos_t(point.x - (width / 2), point.y - (height / 2));
  }

  pos_t get_bottom_right(pos_t const &point) const {
    return ecs::pos_t(point.x + (width / 2), point.y + (height / 2));
  }

  friend inline std::ostream &operator<<(std::ostream &stream,
                                         collider_t const &collider) {
    stream << "(" << static_cast<int>(collider.width) << ","
           << static_cast<int>(collider.height) << ")";
    return stream;
  }

  uint32_t width;
  uint32_t height;
};
} // namespace ecs

#endif /* !COLLIDER_HPP_ */
