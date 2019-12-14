#include <iostream>

#include "food.hpp"


Food::Food() : _type(FoodType::Neutral), _shape(sf::Vector2f(20.f, 20.f))
{
    _shape.setPosition(sf::Vector2f{});
    _shape.setFillColor(sf::Color::White); 
}

Food::Food(const sf::Vector2f position, const sf::Vector2f size) : _type(FoodType::Neutral), _shape(size)
{
    _shape.setPosition(position);
    _shape.setFillColor(sf::Color::White);
}

Food::Food(const sf::Vector2f position, const sf::Vector2f size, const FoodType type) :
    _type(FoodType::Neutral), _shape(size)
{
    _shape.setPosition(position);
    _shape.setFillColor(sf::Color::White);
}

void Food::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(_shape, states);
}

void Food::setType(const FoodType type)
{
    _type = type;
    switch (_type)
    {
        case FoodType::Neutral:
            _shape.setFillColor(sf::Color::White);
            break;
        case FoodType::Aggressive:
            _shape.setFillColor(sf::Color::Red);
            break;
        case FoodType::Valuable:
            _shape.setFillColor(sf::Color::Magenta);
            break;
        default:
            std::cout << "Unknown food type!!" << std::endl;
    }
}
