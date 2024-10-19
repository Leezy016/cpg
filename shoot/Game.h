#pragma once

#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Entity.h"

struct FontConfig {std::string fontPath; int fontSize, fontColorR, fontColorG, fontColorB;};
struct PlayerConfig { int shapeRadius, collisionRadius, fillColorR, fillColorG, fillColorB, outlineColorR, outlineColorG, outlineColorB, outlineThickness, shapeVertices; float speed;};
struct EnemyConfig { int shapeRadius, collisionRadius, outlineColorR, outlineColorG, outlineColorB, outlineThickness, minVertices, maxVertices, smallLifespan, spawnInterval; float speedMin, speedMax;};
struct BulletConfig { int shapeRadius, collisionRadius, fillColorR, fillColorG, fillColorB, outlineColorR,outlineColorG, outlineColorB, outlineThickness, shapeVertices, lifeSpan; float speed;};

class Game
{
    sf::RenderWindow m_window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text;
    FontConfig m_fontConfig;
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;
    bool m_paused = false;
    bool m_running = true;

    std::shared_ptr<Entity> m_player;

    void init(const std::string & config);
    void setPaused(bool paused);

    void sMovement();
    void sUserInput();
    void sLifeSpan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    Game(const std::string & config);
    void run();
};
