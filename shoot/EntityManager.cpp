#include<iostream>
#include<map>
#include "EntityManager.h"

EntityVec &EntityManager::getEntities()
{
    return m_entities;
}

EntityVec &EntityManager::getEntities(const std::string &tag)
{
    return m_entityMap[tag];
}

void EntityManager::removeDeadEntities(EntityVec &vec)
{
    for(auto e:vec)
    {
        if(!e->isActive())
        {
            // remove for vec safely
            // std::remove_if
        }
    }
}

void EntityManager::update()
{
    for(auto e:m_entitiesToAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_entitiesToAdd.clear();


    // remove dead entities from two places
    removeDeadEntities(m_entities);
    for(auto& [tag, entityVec]:m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

// delay vector change until the start of next frame, avoid iteriator problem

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    // auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    // private constructor round way
    auto e = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_entitiesToAdd.push_back(e);
    return e;
}
