#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


enum class FoodType : std::size_t 
{
    Neutral = 0U,
    Aggressive,
    Valuable
};


class Food : public sf::Drawable {
  public:
    explicit Food();

    explicit Food(const sf::Vector2f position, const sf::Vector2f size);

    Food(const sf::Vector2f position, const sf::Vector2f size, const FoodType type);

    const sf::Vector2f getPosition() const {return _shape.getPosition();}

    const sf::Vector2f getSize() const {return _shape.getSize();}

    const FoodType getType() const {return _type;}

    void setPosition(const sf::Vector2f& position) {_shape.setPosition(position);}

    void setType(const FoodType type);


  private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    friend const sf::Shape& getShape(const Food& food);

  private:
    FoodType           _type;
    sf::RectangleShape _shape;
};
