/*
** EPITECH PROJECT, 2023
** workspace
** File description:
** limited
*/

#ifndef LIMITED_HPP_
#define LIMITED_HPP_

#include <algorithm>
#include <iostream>

#include "ecs/components/position.hpp"

namespace ecs {
class limited_t {
  public:
    limited_t(int32_t left_, int32_t top_, int32_t width_, int32_t height_)
        : left(left_), top(top_), width(width_), height(height_){};

    limited_t(limited_t const &limited)
        : left(limited.left), top(limited.top), width(limited.width), height(limited.height){};

    limited_t &operator=(limited_t const &limited) {
        left = limited.left;
        top = limited.top;
        width = limited.width;
        height = limited.height;
        return *this;
    };

    inline bool contains(int32_t x, int32_t y) const {
        return (x >= left && x <= width && y >= top && y <= height);
    }

    inline bool intersects(limited_t const &limited) const {
        int x1 = std::max(left, limited.left);
        int y1 = std::max(top, limited.top);
        int x2 = std::min(width, limited.width);
        int y2 = std::min(height, limited.height);

        return (x1 >= x2 || y1 >= y2);
    }

    friend inline std::ostream &operator<<(std::ostream &stream, limited_t const &limited) {
        stream << "(" << static_cast<int>(limited.left) << "," << static_cast<int>(limited.top)
               << "," << static_cast<int>(limited.width) << "," << static_cast<int>(limited.height)
               << ")";
        return stream;
    }

    int32_t left;
    int32_t top;
    int32_t width;
    int32_t height;
};

}  // namespace ecs

#endif /* !LIMITED_HPP_ */
