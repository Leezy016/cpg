#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class Shape{
    int type;
    int color;

public:
    void draw();

};


int main()
{
    std::vector<Shape> vec;
    std::string infoline;
    std::fstream ConfigFile("config.txt");


    
    

    //read window info
    //
    //
    int wWidth, wHeight;
    int flag = 0;
    std::string fontPath="";

    while (std::getline(ConfigFile, infoline, ' '))
    {
        flag++;
        std::cout<<flag<<" "<<infoline<<"\n";
        if(flag==2)
            wWidth=std::stoi(infoline);
        if(flag == 3)
            wHeight=std::stoi(infoline);
        if(flag  == 4)
            fontPath=infoline;
    }
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
    // same speed on every screen
    window.setFramerateLimit(60);

    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(300.0f, 300.0f);
    float circleMoveSpeed = 0.01f;

    // read font info
    //
    //
    sf::Font myfont;

    if(!myfont.loadFromFile("./"+fontPath))
    {
        std::cerr << "Could not load font!\n";
        exit(-1);
    }

    sf::Text text("I did it!!!!!", myfont, 30);

    text.setPosition(wWidth/2, wHeight/2 - (float)text.getCharacterSize());

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
        // animations for every shape
        //
        //
        circle.setPosition(circle.getPosition().x + circleMoveSpeed, circle.getPosition().y + circleMoveSpeed);

        // rendering function calls
        window.clear();
        window.draw(circle);
        window.draw(text);
        window.display();
    }
    return 0;
}