#include <iostream>

#include "snake.hpp"


Snake::Snake(const sf::Vector2f initPosition) : _segments()
{
    sf::RectangleShape headShape {size};
    headShape.setFillColor(color);
    headShape.setPosition(initPosition);
    _segments.push_back(Segment{headShape, LEFT});
}

void Snake::addSegment(const sf::Vector2f position)
{
    _segments.push_back(Segment(*_segments.rbegin()));
    _segments.rbegin()->direction = (_segments.rbegin() + 1u)->direction;
    _segments.rbegin()->shape.setPosition((_segments.rbegin() + 1u)->getPosition() - (_segments.rbegin()->direction * velocity));
}

void Snake::setDirection(const sf::Vector2f direction)
{
    if (direction ==  _segments.front().direction)
        return;
    // Check what directions is not opposite
    auto dirSum = direction + _segments.front().direction; 
    if (!(dirSum.x == 0.f && dirSum.y == 0.f))
        _segments.front().direction = direction;
}

void Snake::move(float timedelta)
{
    sf::Vector2f headPositionDelta{_segments.front().direction * velocity * timedelta};
    // std::cout << "head position delta: " << headPositionDelta << std::endl;
    _segments.insert(_segments.cbegin(), _segments.front());
    _segments.front().shape.setPosition(_segments[1u].shape.getPosition() + headPositionDelta);
    if (_segments.size() > 1u)
        _segments.pop_back();
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& segment: _segments)
        target.draw(segment.shape, states);
}


bool Snake::isSelfIntersection() const
{
    bool intersection{false};
    for (auto iter = _segments.cbegin() + 1u; iter != _segments.cend(); ++iter)
    {
        if (iter->getPosition() == getHeadPosition())
        {
            intersection = true;
            break;
        }
    }

    return intersection;
}