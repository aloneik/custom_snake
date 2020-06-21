#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "snake.hpp"
#include "food.hpp"
#include "utilites.hpp"
#include "random.hpp"


constexpr unsigned WINDOW_WIDTH      {500u};
constexpr unsigned WINDOW_HEIGHT     {400u};

constexpr unsigned GAME_FIELD_HEIGHT {400u};
constexpr unsigned GAME_FIELD_WIDTH  {400u};

constexpr unsigned BLOCK_SIZE        {20u};

constexpr unsigned MAX_FOODS         {10u};


int main()
{
    sf::Font gameScoreFont{};
    if (!gameScoreFont.loadFromFile("../assets/fonts/Ubuntu-M.ttf"))
        std::cout << "Font has not ben loaded!" << std::endl;

    // Create window
    sf::RenderWindow window{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Snake", sf::Style::Default};
    window.setFramerateLimit(60u);

    sf::RectangleShape gameFieldTexture{sf::Vector2f{GAME_FIELD_WIDTH, GAME_FIELD_WIDTH}};
    gameFieldTexture.setFillColor(sf::Color{25u, 25u, 25u});

    // Set snake's update time
    float time_to_update = 700.f;

    sf::Rect<std::size_t> gameFieldBounds{0u,
                                          0u,
                                          (GAME_FIELD_WIDTH / BLOCK_SIZE) - 1u, 
                                          (GAME_FIELD_HEIGHT / BLOCK_SIZE) - 1u};

    // Create food vector
    std::vector<Food> foodObjects{};
    foodObjects.reserve(MAX_FOODS);
    unsigned foodIdx{0u};

    // Create initial food
    foodObjects.emplace_back(sf::Vector2f{7 * BLOCK_SIZE, 7 * BLOCK_SIZE}, sf::Vector2f{BLOCK_SIZE, BLOCK_SIZE});
    foodObjects.emplace_back(sf::Vector2f{3 * BLOCK_SIZE, 2 * BLOCK_SIZE}, sf::Vector2f{BLOCK_SIZE, BLOCK_SIZE});

    // Create snake
    Snake snake{sf::Vector2f{10 * BLOCK_SIZE, 7 * BLOCK_SIZE}};
    snake.addSegment(sf::Vector2f{9 * BLOCK_SIZE, 7 * BLOCK_SIZE});
    // snake.addSegment(sf::Vector2f{18 * 20, 15 * 20});
    // snake.addSegment(sf::Vector2f{17 * 20, 15 * 20});
    auto snakeDirection = LEFT;

    std::size_t gameScore{0u};
    sf::Text scoreLabel{};
    scoreLabel.setFillColor(sf::Color::Green);
    scoreLabel.setFont(gameScoreFont);
    scoreLabel.setPosition(sf::Vector2f{410u, 10u});
    scoreLabel.setCharacterSize(24u);
    scoreLabel.setString(std::to_string(gameScore));

    sf::Clock timer{};

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
                for (auto& food : foodObjects)
                {
                    if (snake.getHeadPosition() + (snake.getDirection() * snake.velocity) == food.getPosition())
                    {
                        updateGameScore(&gameScore, food);
                        snake.addSegment(food.getPosition());

                        // Generate food position until it don't intersect with snake
                        food.setPosition(generateNewFoodPos(gameFieldBounds, snake, food));
                        std::cout << "Food Position: " << food.getPosition() << std::endl;
                        
                        const int pseudoRandomNumber = UniformRandomNumber::getClosed(1, 11);
                        if (pseudoRandomNumber < 2)
                        {
                            food.setType(FoodType::Valuable);
                        }
                        else if (pseudoRandomNumber < 4)
                        {
                            food.setType(FoodType::Aggressive);
                            // Create additional food
                            // TODO: Move additional food create out of eating cycle
                            Food newFood{sf::Vector2f{0 * BLOCK_SIZE, 0 * BLOCK_SIZE}, sf::Vector2f{BLOCK_SIZE, BLOCK_SIZE}};
                            newFood.setPosition(generateNewFoodPos(gameFieldBounds, snake, newFood));
                            foodObjects.push_back(newFood);
                        }
                        else 
                        {
                            food.setType(FoodType::Neutral);
                        }

                        if (time_to_update >= 350.f)
                        {
                            time_to_update -= 50.f;
                        }
                    }
                }
                // std::cout << "print snake BEFORE move" << std::endl;
                // for (const auto &seg : getSegments(snake))
                // {
                //     std::cout << seg.getPosition() << " direction: " << seg.direction << std::endl;
                // }
                // std::cout << "end of print snake BEFORE move" << std::endl;
                snake.move();
                // std::cout << "print snake AFTER move" << std::endl;
                // for (const auto &seg : getSegments(snake))
                // {
                //     std::cout << seg.getPosition() << " direction: " << seg.direction << std::endl;
                // }
                // std::cout << "end of print snake AFTER move" << std::endl;
                timer.restart();
            }

            if (snake.isSelfIntersection() ||
                snake.getHeadPosition().x < 0 || snake.getHeadPosition().x  > GAME_FIELD_WIDTH - BLOCK_SIZE ||
                snake.getHeadPosition().y < 0 || snake.getHeadPosition().y  > GAME_FIELD_HEIGHT - BLOCK_SIZE)
            {
                std::cout << "fail!" <<std::endl;
                exit(-1);
            }
        }

        scoreLabel.setString(std::to_string(gameScore));

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(gameFieldTexture);
        window.draw(scoreLabel);
        window.draw(snake);
        for (const auto& food : foodObjects)
            window.draw(food);
        window.display();
    }

    return EXIT_SUCCESS;
}
