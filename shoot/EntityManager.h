#include "Entity.h"

class EntityManager
{
private:
    /* data */
public:
    EntityManager(/* args */);
    ~EntityManager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
};

EntityManager::EntityManager(/* args */)
{
}

EntityManager::~EntityManager()
{
}
