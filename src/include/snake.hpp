#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


const sf::Vector2f UP    { 0.f, -1.f};
const sf::Vector2f DOWN  { 0.f,  1.f};
const sf::Vector2f RIGHT { 1.f,  0.f};
const sf::Vector2f LEFT  {-1.f,  0.f};


struct Segment {
  Segment(const sf::RectangleShape& shape, sf::Vector2f direction) : shape(shape), direction(direction) {}

  Segment(const Segment& other) = default;

  const sf::Vector2f getPosition() const {return shape.getPosition();}

  const sf::Vector2f getSize() const {return shape.getSize();}

  sf::RectangleShape shape;
  sf::Vector2f direction;
};

using Segments = std::vector<Segment>;

class Snake : public sf::Drawable {
  public:
    explicit Snake(const sf::Vector2f initPosition);

    void addSegment(const sf::Vector2f position);

    void setDirection(const sf::Vector2f direction);

    const sf::Vector2f getDirection() const {return _segments[0u].direction;}

    void move(float timedelta = 1.f);

    const sf::Vector2f getHeadPosition() const {return _segments[0U].shape.getPosition();}

    bool isSelfIntersection() const;
  
  public:
    sf::Vector2f size     {20.f, 20.f};
    sf::Color    color    {sf::Color::Green};
    float        velocity {20.f}; // pixels per second

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    friend const Segments& getSegments(const Snake& snake);

  private:
    Segments _segments;
};
