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
    std::string input;
    int windowWidth, windowHeight, windowFrameLimit,fontSize,fontR,fontG,fontB,soomeint;
    bool windowFullScreen;
    fin
        >>input>>windowWidth>>windowHeight>>windowFrameLimit>>windowFullScreen
        >>input>>m_fontConfig.fontPath>>m_fontConfig.fontSize>>m_fontConfig.fontColorR>>m_fontConfig.fontColorG>>m_fontConfig.fontColorB
        >>input>>m_playerConfig.shapeRadius>>m_playerConfig.collisionRadius>>m_playerConfig.speed>>m_playerConfig.fillColorR>>m_playerConfig.fillColorG>>m_playerConfig.fillColorB>>m_playerConfig.outlineColorR>>m_playerConfig.outlineColorG>>m_playerConfig.outlineColorB>>m_playerConfig.outlineThickness>>m_playerConfig.shapeVertices
        >>input>>m_enemyConfig.shapeRadius>>m_enemyConfig.collisionRadius>>m_enemyConfig.speedMin>>m_enemyConfig.speedMax>>m_enemyConfig.outlineColorR>>m_enemyConfig.outlineColorG>>m_enemyConfig.outlineColorB>>m_enemyConfig.outlineThickness>>m_enemyConfig.minVertices>>m_enemyConfig.maxVertices>>m_enemyConfig.smallLifespan>>m_enemyConfig.spawnInterval
        >>input>>m_bulletConfig.shapeRadius>>m_bulletConfig.collisionRadius>>m_bulletConfig.speed>>m_bulletConfig.fillColorR>>m_bulletConfig.fillColorG>>m_bulletConfig.fillColorB>>m_bulletConfig.outlineColorR>>m_bulletConfig.outlineColorG>>m_bulletConfig.outlineColorB>>m_bulletConfig.outlineThickness>>m_bulletConfig.shapeVertices>>m_bulletConfig.lifeSpan;
    

    // window setup
    m_window.create(sf::VideoMode(windowWidth, windowHeight), "shoot");
    m_window.setFramerateLimit(windowFrameLimit);


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
    entity->cShape = std::make_shared<CShape>(m_playerConfig.shapeRadius, m_playerConfig.shapeVertices, sf::Color(m_playerConfig.fillColorR, m_playerConfig.fillColorG, m_playerConfig.fillColorB), sf::Color(m_playerConfig.outlineColorR, m_playerConfig.outlineColorG, m_playerConfig.outlineColorB), m_playerConfig.outlineThickness);

    entity->cInput = std::make_shared<CInput>();

    m_player = entity;
}

void Game::spawnEnemy()
{
    if(m_currentFrame-m_lastEnemySpawnTime==m_enemyConfig.spawnInterval)
    {
        auto entity = m_entities.addEntity("enemy");
        float ex = rand() % m_window.getSize().x;
        float ey = rand() % m_window.getSize().y;
        float enemySides = rand() % m_enemyConfig.maxVertices + m_enemyConfig.minVertices;
        float enemyColorR = rand() % 255;
        float enemyColorG = rand() % 255;
        float enemyColorB = rand() % 255;

        float enemySpeed = rand() % (int)m_enemyConfig.speedMax + m_enemyConfig.speedMin;
        entity->cTransform = std::make_shared<CTransform>(Vec2(ex,ey),Vec2(enemySpeed, enemySpeed), 0.0);
        entity->cShape = std::make_shared<CShape>(m_enemyConfig.shapeRadius, enemySides, sf::Color(enemyColorR, enemyColorG, enemyColorB), sf::Color(m_enemyConfig.outlineColorR, m_enemyConfig.outlineColorG, m_enemyConfig.outlineColorB), m_enemyConfig.outlineThickness);
        
        
        // record when the most recent enemy was spawned
        m_lastEnemySpawnTime = m_currentFrame;
    }
    
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{

}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos)
{
    auto bullet = m_entities.addEntity("bullet");
    // calculate bullet velocity use mousePos and playerPos
    float dist= entity->cTransform->pos.dist(mousePos);
    float bulletVelX= (mousePos.x-entity->cTransform->pos.x)/dist*m_bulletConfig.speed;
    float bulletVelY= (mousePos.y-entity->cTransform->pos.y)/dist*m_bulletConfig.speed;
    bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos, Vec2(bulletVelX,bulletVelY), 0);
    bullet->cShape = std::make_shared<CShape>(m_bulletConfig.shapeRadius, m_bulletConfig.collisionRadius, sf::Color(m_bulletConfig.fillColorR,m_bulletConfig.fillColorG,m_bulletConfig.fillColorB), sf::Color(m_bulletConfig.outlineColorR,m_bulletConfig.outlineColorG,m_bulletConfig.outlineColorB), m_bulletConfig.outlineThickness);

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
        m_player->cTransform->velocity.y = -m_playerConfig.speed;
    }
    if (m_player->cInput->down)
    {
        m_player->cTransform->velocity.y = m_playerConfig.speed;
    }
    if (m_player->cInput->left)
    {
        m_player->cTransform->velocity.x = -m_playerConfig.speed;
    }
    if (m_player->cInput->right)
    {
        m_player->cTransform->velocity.x = m_playerConfig.speed;
    }

    // enemy movement
    


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


    // font setup
    sf::Font myfont;
    if(!myfont.loadFromFile("./"+m_fontConfig.fontPath))
    {
        std::cerr << "Could not load font!\n";
        exit(-1);
    }
    sf::Text text("Score: ", myfont, m_fontConfig.fontSize);
    
    text.setFillColor(sf::Color(m_fontConfig.fontColorR,m_fontConfig.fontColorG,m_fontConfig.fontColorB));
    text.setPosition(20, 20);
    m_window.draw(text);

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
