#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Food : public sf::Drawable {
  public:
    Food();

    Food(const sf::Vector2f position);

    const sf::Vector2f getPosition() const {return _shape.getPosition();}

    const sf::Vector2f getSize() const {return _shape.getSize();}

    void setPosition(const sf::Vector2f& position) {_shape.setPosition(position);}

  private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  public:
    sf::Vector2f size{20.f, 20.f};

  private:
    sf::Color          _color {sf::Color::Red};
    sf::RectangleShape _shape;
};