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
    float ex = rand() % m_window.getSize().y;
    // record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{

}

void Game::sRender()
{
    m_window.clear();
    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);
    // player rotation
    m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(m_player->cTransform->angle);

    m_window.draw(m_player->cShape->circle);

    m_window.display();
}

void Game::sEnemySpawner()
{

    spawnEnemy();
}