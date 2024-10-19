#include "Game.h"

#include<iostream>
#include<fstream>

Game::Game(const std::string & config)
{
    init(config);
}

void Game::init(const std::string & path)
{
    std::ifstream fin(path);

    // need read from file
    //
    //
    fin>>m_playerConfig.SR>>m_playerConfig.CR;
    m_window.create(sf::VideoMode(1280, 720), "shoot shape");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}

void Game::run()
{
    // TODO: add pause
    // some systems should function while pause (rendering), others not(movement / input)
    while (m_running)
    {
        m_entities.update();

        if(!m_paused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
        }
        
        sUserInput();
        sRender(); // always rendering

        m_currentFrame++;
    }
}

void Game::setPaused(bool paused)
{
    paused = true;
}

void Game::spawnPlayer()
{
    // TODO: add all properties from config

    auto entity = m_entities.addEntity("player");

    float midX = m_window.getSize().x/2;
    float midY = m_window.getSize().y/2;

    entity->cTransform = std::make_shared<CTransform>(Vec2(midX, midY), Vec2(1.0f, 1.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

    entity->cInput = std::make_shared<CInput>();

    m_player = entity;
}

void Game::spawnEnemy()
{
    // TODO: use m_enemyConfig
    //       must be within window
    auto entity = m_entities.addEntity("enemy");
    float ex = rand() % m_window.getSize().x;
    float ey = rand() % m_window.getSize().y;

    entity->cTransform = std::make_shared<CTransform>(Vec2(ex,ey),Vec2(1.0f, 1.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);

    // record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{

}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos)
{
    auto bullet = m_entities.addEntity("bullet");
    bullet->cTransform = std::make_shared<CTransform>(mousePos, Vec2(0,0), 0);
    bullet->cShape = std::make_shared<CShape>(10, 8, sf::Color(255,255,255), sf::Color(255,0,0), 2);

}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
}

void Game::sMovement()
{
    // player movement
    m_player->cTransform->velocity = {0,0};
    if(m_player->cInput->up)
    {
        m_player->cTransform->velocity.y = -5;
    }
    if (m_player->cInput->down)
    {
        m_player->cTransform->velocity.y = 5;
    }
    if (m_player->cInput->left)
    {
        m_player->cTransform->velocity.x = -5;
    }
    if (m_player->cInput->right)
    {
        m_player->cTransform->velocity.x = 5;
    }

    // update every entity's position
    for(auto& e: m_entities.getEntities())
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }

}

void Game::sRender()
{
    m_window.clear();

    for(auto& e: m_entities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
        // rotation
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);

        m_window.draw(e->cShape->circle);
    }

    m_window.display();
}

void Game::sUserInput()
{
    // TODO
    // the movement system will read the variables set in here
    //
    //
    sf::Event event;

    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        if(event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
            case sf::Keyboard::W:
                m_player->cInput->up = true;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = true;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = true;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = true;
                break;
            default:
                break;
            }
        }

        if(event.type == sf::Event::KeyReleased)
        {
            switch(event.key.code)
            {
            case sf::Keyboard::W:
                m_player->cInput->up = false;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = false;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = false;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = false;
                break;
            default:
                break;
            }
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                spawnBullet(m_player, Vec2(event.mouseButton.x,event.mouseButton.y));
            }
        }
    }
}

void Game::sLifeSpan()
{
}

void Game::sEnemySpawner()
{

    spawnEnemy();
}

void Game::sCollision()
{
    // use collision radius
    for(auto b : m_entities.getEntities("bullet"))
    {
        for(auto e : m_entities.getEntities("enemy"))
        {

        }
    }
}
