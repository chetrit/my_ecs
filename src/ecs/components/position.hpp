/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <iostream>

#ifdef SFML_PLUGIN
#include "SFML/Graphics.hpp"
#endif

namespace ecs {
class position_t {
  public:
#ifdef SFML_PLUGIN
    position_t(sf::Vector2f const &v) : x(v.x), y(v.y){};
#endif

    position_t(float const &x_ = 0.0F, float const &y_ = 0.0F) : x(x_), y(y_){};

    position_t(position_t const &pos) : x(pos.x), y(pos.y){};

    position_t &operator=(position_t const &pos) {
        x = pos.x;
        y = pos.y;
        return *this;
    };

#ifdef SFML_PLUGIN
    operator sf::Vector2f() { return {x, y}; }

    operator sf::Vector2f() const { return {x, y}; }
#endif

    float x;
    float y;
};

using pos_t = position_t;

inline std::ostream &operator<<(std::ostream &stream, pos_t const &pos) {
    stream << "(" << static_cast<int>(pos.x) << "," << static_cast<int>(pos.y) << ")";
    return stream;
}
}  // namespace ecs

#endif /* !POSITION_HPP_ */
