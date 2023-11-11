#include<iterator>

#include "ResourceManager.hpp"
//the empty functions below are needed for a singleton
ResourceManager::ResourceManager(){
}

ResourceManager::ResourceManager(const ResourceManager&){
}

ResourceManager::~ResourceManager(){
    std::unordered_map<std::string,SDL_Surface*>::iterator it;
    for(it = m_surfaces.begin();it != m_surfaces.end(); it++){
        SDL_FreeSurface(it->second);
    }
}

ResourceManager& ResourceManager::GetInstance(){
    //ResourceManager pointer below is initialized only once in program, so only one allocation
    //is made, thus only one instance of ResourceManager is created, and thus a singleton class
    static ResourceManager* s_instance = new ResourceManager();
    return *s_instance; //hoping they don't take its address and call delete on it
}

SDL_Surface* ResourceManager::GetSurface(const std::string& filepath){
    //look through our m_surfaces, an unordered map, to see if a file exists
    auto search = m_surfaces.find(filepath);
    if (search != m_surfaces.end()){
        return m_surfaces[filepath];
    }else{
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        m_surfaces.insert(std::make_pair(std::move(filepath.c_str()),surface));
        return surface;
    }
}