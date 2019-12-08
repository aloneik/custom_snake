#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "snake.hpp"
#include "food.hpp"
#include "utilites.hpp"


constexpr unsigned WIDTH {400u};
constexpr unsigned HEIGHT{300u};
constexpr unsigned BLOCK_SIZE{20u};


int main()
{
    // Create window
    sf::RenderWindow window{sf::VideoMode{WIDTH, HEIGHT}, "Snake", sf::Style::Default};
    window.setFramerateLimit(60u);

    // Set snake's update time
    float time_to_update = 700.f;

    // Create food
    Food food{sf::Vector2f{7 * BLOCK_SIZE, 7 * BLOCK_SIZE}};

    // Create snake
    Snake snake{sf::Vector2f{10 * BLOCK_SIZE, 7 * BLOCK_SIZE}};
    snake.addSegment(sf::Vector2f{9 * BLOCK_SIZE, 7 * BLOCK_SIZE});
    // snake.addSegment(sf::Vector2f{18 * 20, 15 * 20});
    // snake.addSegment(sf::Vector2f{17 * 20, 15 * 20});
    auto snakeDirection = LEFT;

    sf::Clock timer;

    bool isRunning{true};

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            // Process controls 
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (isRunning) 
                        isRunning = false;
                    else isRunning = true;
                }
                else if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                    snakeDirection = UP;
                else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                    snakeDirection = DOWN;
                else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                    snakeDirection = LEFT;
                else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                    snakeDirection = RIGHT;
            }
        }

        if (isRunning) {
            // Start update block
            if (timer.getElapsedTime().asMilliseconds() >= time_to_update) {
                snake.setDirection(snakeDirection);
                // Check eating
                if (snake.getHeadPosition() + (snake.getDirection() * snake.velocity) == food.getPosition())
                {
                    snake.addSegment(food.getPosition());

                    std::random_device seeder;
                    std::mt19937 rng(seeder());
                    std::uniform_int_distribution<> xDistr(0u, (WIDTH / BLOCK_SIZE) - 1u);
                    std::uniform_int_distribution<> yDistr(0u, (HEIGHT / BLOCK_SIZE) - 1u);
                    float xCoord{xDistr(rng) * static_cast<float>(BLOCK_SIZE)};
                    float yCoord{yDistr(rng) * static_cast<float>(BLOCK_SIZE)};
                    food.setPosition(sf::Vector2f{xCoord, yCoord});
                    while (isIntersectVector2VectorArray(food, getSegments(snake)))
                    {                                 
                        xCoord = xDistr(rng) * static_cast<float>(BLOCK_SIZE);
                        yCoord = yDistr(rng) * static_cast<float>(BLOCK_SIZE);
                        food.setPosition(sf::Vector2f{xCoord, yCoord});
                    }
                    std::cout << "Food Position: " << food.getPosition() << std::endl;

                    if (time_to_update >= 350.f)
                    {
                        time_to_update -= 50.f;
                    }
                }
                std::cout << "print snake BEFORE move" << std::endl;
                for (auto &seg : getSegments(snake))
                {
                    std::cout << seg.getPosition() << " direction: " << seg.direction << std::endl;
                }
                std::cout << "end of print snake BEFORE move" << std::endl;
                snake.move();
                std::cout << "print snake AFTER move" << std::endl;
                for (auto &seg : getSegments(snake))
                {
                    std::cout << seg.getPosition() << " direction: " << seg.direction << std::endl;
                }
                std::cout << "end of print snake AFTER move" << std::endl;
                timer.restart();
            }

            if (snake.isSelfIntersection() || snake.getHeadPosition().x < 0 || snake.getHeadPosition().x  > WIDTH - BLOCK_SIZE || snake.getHeadPosition().y < 0 || snake.getHeadPosition().y  > HEIGHT - BLOCK_SIZE)
            {
                std::cout << "fail!" <<std::endl;
                exit(-1);
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(snake);
        window.draw(food);

        window.display();
    }

    return EXIT_SUCCESS;
}