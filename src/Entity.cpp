#include<iostream>

class Entity
{
    std::string tag;
    bool alive = true;
public:
    
    Entity(/* args */);
    ~Entity();
    std::string tag(){return tag;};
};

Entity::Entity(/* args */)
{
}

Entity::~Entity()
{
}
