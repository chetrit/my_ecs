/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** registry
*/

#include <cassert>
#include <iostream>
#include <optional>
#include <sstream>

#include "doctest.h"

#include "velocity.hpp"

TEST_CASE("test velocity component") {
    ecs::velocity_t v1(2, 3);
#ifdef SFML_PLUGIN
    ecs::velocity_t v2(sf::Vector2i(2, 3));
#endif
    ecs::velocity_t v3(7);
    ecs::velocity_t v4;
    ecs::velocity_t v5(v3);
    ecs::velocity_t v6 = v5;

#ifdef SFML_PLUGIN
    ecs::velocity_t const v7(v2);
    sf::Vector2i vec1 = v7;
#endif

    std::ostringstream oss;
    oss << v6;

    CHECK(v1.vx == 2);
    CHECK(v1.vy == 3);
    CHECK(v3.vx == 7);
    CHECK(v3.vy == 0);
    CHECK(v4.vx == 0);
    CHECK(v4.vy == 0);
    CHECK(v5.vx == v3.vx);
    CHECK(v5.vy == v3.vy);
    CHECK(oss);
    CHECK(oss.str() == "(7,0)");
#ifdef SFML_PLUGIN
    CHECK(v2.vx == 2);
    CHECK(v2.vy == 3);
    CHECK(v7.vx == v2.vx);
    CHECK(v7.vy == v2.vy);
    CHECK(vec1.x == v7.vx);
    CHECK(vec1.y == v7.vy);
#endif
}