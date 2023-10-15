#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include<string>
#include<unordered_map>

#include<SDL2/SDL.h>

class ResourceManager
{
    private:
    ResourceManager();
    ResourceManager(const ResourceManager&);
    ResourceManager& operator= (const ResourceManager&)= delete;

    std::unordered_map<std::string, SDL_Surface *> m_surfaces;

    public:
        static ResourceManager& GetInstance();

        SDL_Surface* GetSurface(const std::string& filepath);
};

#endif