#include<iostream>
#include "Entity.h"

bool Entity::isActive() const
{
    return m_alive;
}

const std::string &Entity::tag() const
{
    return m_tag;
}

const size_t Entity::id() const
{
    return m_id;
}

void Entity::destroy()
{
    m_alive = false;
}
