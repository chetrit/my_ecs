/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include <iostream>

#ifdef SFML_PLUGIN
#include "SFML/Graphics.hpp"
#endif

namespace ecs {
class velocity_t {
  public:
#ifdef SFML_PLUGIN
    velocity_t(sf::Vector2i const &v) : vx(v.x), vy(v.y){};
#endif
    velocity_t(int32_t const &vx_ = 0, int32_t const &vy_ = 0) : vx(vx_), vy(vy_){};

    velocity_t(velocity_t const &velocity) : vx(velocity.vx), vy(velocity.vy){};

    velocity_t &operator=(velocity_t const &velocity) {
        vx = velocity.vx;
        vy = velocity.vy;
        return *this;
    };

#ifdef SFML_PLUGIN
    operator sf::Vector2i() { return {vx, vy}; }
    operator sf::Vector2i() const { return {vx, vy}; }
#endif
    int32_t vx;
    int32_t vy;
};

inline std::ostream &operator<<(std::ostream &stream, velocity_t const &velocity) {
    stream << "(" << static_cast<int>(velocity.vx) << "," << static_cast<int>(velocity.vy) << ")";
    return stream;
}
}  // namespace ecs

#endif /* !VELOCITY_HPP_ */
