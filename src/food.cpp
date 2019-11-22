#include "food.hpp"


Food::Food(const sf::Vector2f position) : _shape(size)
{
    _shape.setPosition(position);
    _shape.setFillColor(_color);
}

void Food::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(_shape, states);
}