#include<iostream>

class Entity
{
    const size_t    m_id = 0;
    std::string     m_tag = "Default";
    bool            m_alive = true;
public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CName> cName;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CBBox> cBBox;
    Entity(const std::string& tag, size_t id);
    std::string tag(){return m_tag;};
    void destroy() { m_alive = false};
};

Entity::Entity(/* args */)
{
}

Entity::~Entity()
{
}
