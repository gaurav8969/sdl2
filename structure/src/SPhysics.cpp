#include "SPhysics.hpp"

bool Physics::isColliding(GameEntity* f_entity, GameEntity* s_entity,size_t f_collider, size_t s_collider, bool isPixelPerfect){
    auto& f_resources{f_entity->getComponent<Resources>()};
    auto& s_resources{s_entity->getComponent<Resources>()};
    
    auto f_size = f_resources.m_colliderComponents->size();
    auto s_size = s_resources.m_colliderComponents->size();

    auto& f_colliders{*f_resources.m_colliderComponents};
    auto& s_colliders{*s_resources.m_colliderComponents};

    if(f_collider < f_size && s_collider < s_size){
        Collider* p_fcollider = f_colliders[f_collider].get();
        Collider* p_scollider = s_colliders[s_collider].get();
        SDL_Rect* f_collidingRect = &p_fcollider->colliderRect;
        SDL_Rect* s_collidingRect = &p_scollider->colliderRect;
        SDL_Rect* f_outline = &f_colliders[0].get()->colliderRect;
        SDL_Rect* s_outline = &s_colliders[0].get()->colliderRect;
        
        SDL_Rect m_intersection;
        bool isColliding = SDL_IntersectRect(f_collidingRect,s_collidingRect,&m_intersection);
        
        if(isPixelPerfect && isColliding){
            
            //first assume there's no pixel perfect collision
            isColliding = false;
            //the origin
            int xintersection = m_intersection.x;
            int yintersection = m_intersection.y;
            
            int f_xcolliding = xintersection - f_outline->x;
            int f_ycolliding = yintersection - f_outline->y;

            int s_xcolliding = xintersection - s_outline->x;
            int s_ycolliding = yintersection - s_outline->y;

            int width = abs(m_intersection.w);
            int height = abs(m_intersection.h);

            int f_surfaceWidth = f_resources.m_surface->w;
            int s_surfaceWidth = s_resources.m_surface->w;

            auto& f_mask{*f_resources.m_mask};
            auto& s_mask{*s_resources.m_mask};
            
            for(int y = 0; y < height; y++){
                for(int x = 0; x < width; x++){
                    int f_xoffset = f_xcolliding + x;
                    int s_xoffset = s_xcolliding + x;
                    int f_yoffset = f_ycolliding + y;
                    int s_yoffset = s_ycolliding + y;

                    int f_index = f_xoffset + f_surfaceWidth*(f_yoffset);
                    int s_index = s_xoffset + s_surfaceWidth*(s_yoffset);
                    int m_bitValue = f_mask[f_index];
                    int bitValue = s_mask[s_index];

                    if(m_bitValue && bitValue){
                        return true;
                    }
                }
            }
        }
        return isColliding;
    }
    throw(std::out_of_range("The collider index(s) is(are) out of range"));
}