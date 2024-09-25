#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
    // same speed on every screen
    window.setFramerateLimit(60);

    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(300.0f, 300.0f);
    float circleMoveSpeed = 0.01f;

    sf::Font myfont;

    if(!myfont.loadFromFile("fonts/tech.ttf"))
    {
        std::cerr << "Could not load font!\n";
        exit(-1);
    }

    sf::Text text("Sample Text", myfont, 24);

    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    // main loop - continues for each frame while window is open
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key pressed with code = " << event.key.code << "\n";
            }
        }
        // animation
        circle.setPosition(circle.getPosition().x + circleMoveSpeed, circle.getPosition().y + circleMoveSpeed);

        // rendering function calls
        window.clear();
        window.draw(circle);
        window.draw(text);
        window.display();
    }
    return 0;
}