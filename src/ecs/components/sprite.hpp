/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** sprite
*/

#ifdef SFML_PLUGIN
#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <exception>

#include "SFML/Graphics.hpp"

#include "position.hpp"

namespace ecs {
class sprite_t {
  public:
    sprite_t(std::string const &path, sf::Color const &color = sf::Color::White) {
        if (!_texture.loadFromFile(path)) {
            throw std::invalid_argument("Invalid path");
        }
        sf_sprite.setTexture(_texture);
        sf_sprite.setColor(color);
    };
    sprite_t(sprite_t const &sprite) : sf_sprite(sprite.sf_sprite), _texture(sprite._texture) {
        sf_sprite.setTexture(_texture);
    }
    ~sprite_t() = default;

    void set_texture_rect(sf::IntRect const &rect) { sf_sprite.setTextureRect(rect); };
    void set_color(sf::Color const &color) { sf_sprite.setColor(color); };
    void set_scale(sf::Vector2f scale) { sf_sprite.setScale(scale); };

    sf::Sprite sf_sprite;

  private:
    sf::Texture _texture;
};
}  // namespace ecs

#endif /* !SPRITE_HPP_ */
#endif