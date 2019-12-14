#pragma once

#include <random>
#include <iostream>
#include <vector>

#include <boost/geometry.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "food.hpp"


using point_t = boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian>;
using box_t = boost::geometry::model::box<point_t>;


bool isIntersect(const sf::Vector2f &firstObjectPos, const sf::Vector2f &firstObjectSize,
                 const sf::Vector2f &secondObjectPos, const sf::Vector2f &secondObjectSize)
{
    box_t firstObj{point_t{firstObjectPos.x, firstObjectPos.y},
                   point_t{firstObjectPos.x + firstObjectSize.x, firstObjectPos.y + firstObjectSize.y}};
    box_t secondObj{point_t{secondObjectPos.x, secondObjectPos.y},
                    point_t{secondObjectPos.x + secondObjectSize.x, secondObjectPos.y + secondObjectSize.y}};
    return boost::geometry::intersects(firstObj, secondObj);
}

template<class ShapeAT, class ShapeBT>
bool isIntersectShape2Shape(const ShapeAT& firstShape, const ShapeBT& secondShape)
{
    return isIntersect(firstShape.getHeadPosition(), firstShape.getSize(), secondShape.getPosition(), secondShape.getSize());
}

std::ostream& operator<<(std::ostream &os, const sf::Vector2f &vector)
{
    os << "x: " << vector.x << ", y: " << vector.y;
    return os;
}

const Segments& getSegments(const Snake& snake) 
{
    return snake._segments;
}

template <class ShapeT, class VectorShapeT>
bool isIntersectVector2VectorArray(const ShapeT& shape, const VectorShapeT& shapeArray)
{
    bool intersection{false};
    for (const auto& shapeIdx: shapeArray)
    {
        if (isIntersect(shapeIdx.getPosition(), shapeIdx.getSize(), shape.getPosition(), shape.getSize()))
        {
            intersection = true;
            break;
        }
    }
    return intersection;
}

inline void updateGameScore(std::size_t* gameScore, const Food& food)
{
    switch (food.getType())
    {
        case FoodType::Neutral:
            *gameScore += 5u;
            break;
        case FoodType::Aggressive:
            if (*gameScore > 30u)
                *gameScore -= 30u;
            else
                *gameScore = 0u;
            break;
        case FoodType::Valuable:
            *gameScore += 30u;
            break;
        default:
            std::cout << "Unknown food type!" << std::endl;
            break;
    }
}

sf::Vector2f generatePosition(const sf::Rect<std::size_t>& bounds)
{
    static std::random_device seeder;
    static std::mt19937 rng{seeder()};
   
    std::uniform_int_distribution<> xDistr(bounds.left, bounds.left + bounds.width);
    std::uniform_int_distribution<> yDistr(bounds.top, bounds.top + bounds.height);

    return sf::Vector2f{static_cast<float>(xDistr(rng)), static_cast<float>(yDistr(rng))};
}

const sf::Shape& getShape(const Food& food)
{
    return food._shape;
} 
