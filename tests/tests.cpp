#include <iostream>

#include <SFML/System.hpp>

#include "snake.hpp"
#include "utilites.hpp"


int main()
{
    // Test `isIntersect` 1
    {
        std::cout << "--------------------" << std::endl;
        std::cout << "Test `isIntersect` 1" << std::endl;

        const sf::Vector2f firstObjectPos{0.f, 0.0f};
        const sf::Vector2f firstObjectSize{10.f, 10.0f};

        const sf::Vector2f secondObjectPos{0.f, 0.0f};
        const sf::Vector2f secondObjectSize{10.f, 10.0f};

        // API call
        const bool returnedResult{isIntersect(firstObjectPos, firstObjectSize, secondObjectPos, secondObjectSize)};

        const bool expectedResult{true};
        if (expectedResult == returnedResult)
            std::cout << "Test completed successfully" << std::endl;
        else
            std::cout << "Test failed" << std::endl;

        std::cout << "--------------------" << std::endl;
    }

    // Test `isIntersect` 2
    {
        std::cout << "--------------------" << std::endl;
        std::cout << "Test `isIntersect` 2" << std::endl;

        const sf::Vector2f firstObjectPos{0.f, 0.0f};
        const sf::Vector2f firstObjectSize{10.f, 10.0f};

        const sf::Vector2f secondObjectPos{5.f, 5.0f};
        const sf::Vector2f secondObjectSize{10.f, 10.0f};

        // API call
        const bool returnedResult{isIntersect(firstObjectPos, firstObjectSize, secondObjectPos, secondObjectSize)};

        const bool expectedResult{true};
        if (expectedResult == returnedResult)
            std::cout << "Test completed successfully" << std::endl;
        else
            std::cout << "Test failed" << std::endl;

        std::cout << "--------------------" << std::endl;
    }

    // Test `isIntersect` 3
    {
        std::cout << "--------------------" << std::endl;
        std::cout << "Test `isIntersect` 3" << std::endl;

        const sf::Vector2f firstObjectPos{0.f, 0.f};
        const sf::Vector2f firstObjectSize{10.f, 10.f};

        const sf::Vector2f secondObjectPos{-2.f, -2.f};
        const sf::Vector2f secondObjectSize{1.f, 1.f};

        // API call
        const bool returnedResult{isIntersect(firstObjectPos, firstObjectSize, secondObjectPos, secondObjectSize)};

        const bool expectedResult{false};
        if (expectedResult == returnedResult)
            std::cout << "Test completed successfully" << std::endl;
        else
            std::cout << "Test failed" << std::endl;

        std::cout << "--------------------" << std::endl;
    }

    // Test `Snake.addSegment` 1
    {
        std::cout << "-------------------------" << std::endl;
        std::cout << "Test `Snake.addSegment` 1" << std::endl;

        const sf::Vector2f initPosition{100.f, 100.f};
        Snake snake{initPosition};

        sf::Vector2f nextSegmentPosition{120.f, 100.f};
        
        // API call
        snake.addSegment(nextSegmentPosition);
        
        const sf::Vector2f expectedHeadPosition{100.f, 100.f};
        const sf::Vector2f expectedNextSegPosition{120.f, 100.f};

        const sf::Vector2f expectedDirection{-1.f, 0.f};

        if (snake.getHeadPosition() == expectedHeadPosition &&
            getSegments(snake)[1u].shape.getPosition() == expectedNextSegPosition &&
            getSegments(snake)[0u].direction == expectedDirection &&
            getSegments(snake)[1u].direction == expectedDirection)
            std::cout << "Test completed successfully" << std::endl;
        else
            std::cout << "Test failed" << std::endl;

        std::cout << "--------------------" << std::endl;
    }

    return EXIT_SUCCESS;
}