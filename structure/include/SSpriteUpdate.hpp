#include <utility>
#include <stdexcept>

#include "Component.hpp"
#include "CCollider.hpp"
#include "System.hpp"
#include "GameEntity.hpp"
#include "CResources.hpp"
#include "CPhysics.hpp"


using std::pair;

class SpriteUpdate:System{
public:
    void setPosition(int x, int y);
    pair<int,int>& getPosition();
    bool isColliding(const Collider* ,size_t m_collider, size_t collider, bool isPixelPerfect);


    void updateSize(GameEntity* entity, int w, int h);
    void createMask(GameEntity*);

};