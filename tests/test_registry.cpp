/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** registry
*/

#include <cassert>
#include <iostream>
#include <optional>

#include "doctest.h"

#include "position.hpp"
#include "registry.hpp"
#include "velocity.hpp"

TEST_CASE("registry register components at once") {
    ecs::registry_t registry;
    registry.register_components<ecs::pos_t, ecs::velocity_t>();

    ecs::entity_t ent1 = registry.spawn_entity();
    registry.emplace_component<ecs::pos_t>(ent1, 2, 2);
    registry.emplace_component<ecs::velocity_t>(ent1, 3, 2);

    ecs::sparse_array<ecs::pos_t> p = registry.get_components<ecs::pos_t>();
    ecs::sparse_array<ecs::velocity_t> v = registry.get_components<ecs::velocity_t>();
    CHECK(p[ent1]->x == 2);
    CHECK(v[ent1]->vx == 3);
}

TEST_CASE("registry manipulate components") {
    ecs::registry_t registry;
    ecs::entity_t ent1 = registry.spawn_entity();
    ecs::entity_t ent2 = registry.spawn_entity();

    REQUIRE(registry.register_component<ecs::pos_t>().size() == 0);
    REQUIRE(registry.register_component<ecs::velocity_t>().size() == 0);

    registry.add_component<ecs::pos_t>(ent1, ecs::pos_t(1.0F, 1.0F));
    registry.add_component<ecs::velocity_t>(ent1, ecs::velocity_t(10, 10));

    auto &positions = registry.get_components<ecs::pos_t>();
    auto &velocities = registry.get_components<ecs::velocity_t>();

    REQUIRE(positions.size() == 1);
    REQUIRE(velocities.size() == 1);

    CHECK(positions[0].value().x == 1);
    CHECK(positions[0].value().y == 1);
    CHECK(velocities[0].value().vx == 10);
    CHECK(velocities[0].value().vy == 10);

    registry.emplace_component<ecs::pos_t>(ent2, 21.0F, 21.0F);
    registry.emplace_component<ecs::velocity_t>(ent2, 42, 42);

    positions = registry.get_components<ecs::pos_t>();
    velocities = registry.get_components<ecs::velocity_t>();

    REQUIRE(positions.size() == 2);
    REQUIRE(velocities.size() == 2);

    CHECK(positions[1].value().x == 21);
    CHECK(positions[1].value().y == 21);
    CHECK(velocities[1].value().vx == 42);
    CHECK(velocities[1].value().vy == 42);

    ecs::entity_t ent3 = registry.entity_from_index(0);
    CHECK(ent3 == 0);

    registry.remove_component<ecs::pos_t>(ent2);
    CHECK(positions[1].has_value() == false);

    registry.kill_entity(ent2);
    CHECK(positions[1].has_value() == false);
    CHECK(velocities[1].has_value() == false);

    CHECK(positions[0].has_value());
    CHECK(velocities[0].has_value());

    registry.kill_entity(ent1);
    CHECK(positions[0].has_value() == false);
    CHECK(velocities[0].has_value() == false);

    registry.kill_entity(ent3);
}