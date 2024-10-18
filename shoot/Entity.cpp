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
