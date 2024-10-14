#include"EntityManager.cpp"

class GameEngine
{
private:
    /* data */
    Entitymanager m_entityManager;
    int m_currentFrame = 0;
public:
    GameEngine(/* args */);
    ~GameEngine();
    void mainLoop();
};

GameEngine::GameEngine(/* args */)
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::mainLoop()
{
    // first step: update entities
    m_entityManager.update();

    // step by step
    //
    //
    // sUserInput();
    // sMovement();
    // sCollision();
    // sRender();
    m_currentFrame++;
}
