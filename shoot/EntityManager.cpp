#include<iostream>
#include<map>
#include "EntityManager.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map   <std::string, EntityVec>  EntityMap;

class Entitymanager
{
    EntityVec m_entities;
    EntityVec m_toAdd;
    EntityMap m_entityMap;
    size_t    m_totalEntities = 0;

public:
    Entitymanager();
    ~Entitymanager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
};

Entitymanager::Entitymanager(/* args */)
{
}

Entitymanager::~Entitymanager()
{
}

// called at beginning of each frame by game engine
void Entitymanager::update()
{
    for(auto e:m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();


    // remove dead entities
    for(auto e:m_entities)
    {
        // --remove if-- not alive, safe method
        // https://stackoverflow.com/questions/67710057/how-exactly-remove-if-works
    }
}

// delay vector change until the start of next frame, avoid iteriator problem
std::shared_ptr<Entity> Entitymanager::addEntity(const std::string &tag)
{
    // auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    // private constructor round way
    auto e = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_toAdd.push_back(e);
    return e;
}
