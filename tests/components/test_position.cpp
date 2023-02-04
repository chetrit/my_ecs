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

#include "position.hpp"

TEST_CASE("test position component") {
    ecs::pos_t p1(2, 3);
#ifdef SFML_PLUGIN
    ecs::pos_t p2(sf::Vector2f(2, 3));
#endif
    ecs::pos_t p3(1.0f);
    ecs::pos_t p4;
    ecs::pos_t p5(p3);
    ecs::pos_t p6 = p5;

#ifdef SFML_PLUGIN
    ecs::pos_t const p7(p2);
    sf::Vector2f v1 = p7;
#endif

    std::ostringstream oss;
    oss << p6;

    CHECK(p1.x == 2);
    CHECK(p1.y == 3);
    CHECK(p3.x == 1);
    CHECK(p3.y == 0);
    CHECK(p4.x == 0);
    CHECK(p4.y == 0);
    CHECK(p5.x == p3.x);
    CHECK(p5.y == p3.y);
    CHECK(oss);
    CHECK(oss.str() == "(1,0)");
#ifdef SFML_PLUGIN
    CHECK(p2.x == 2);
    CHECK(p2.y == 3);
    CHECK(p7.x == p2.x);
    CHECK(p7.y == p2.y);
    CHECK(v1.x == p7.x);
    CHECK(v1.y == p7.y);
#endif
}