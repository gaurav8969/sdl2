#include <string>
#include <SDL2/SDL.h>

class TexturedRectangle{
    public:
            //pass as constructor argument what you only have one copy of in your program
        TexturedRectangle( SDL_Renderer* rendererPtr, std::string fn);

        //constructor for when have a commmon surface and texture made from it
        TexturedRectangle(SDL_Surface* surface, SDL_Texture* texture, SDL_Renderer* renderer);

        //compiler-generated copy constructor works, shallow copy is desired

        ~TexturedRectangle();

        void setRectangleProperties(int, int, int, int);
        void update();
        void render();

    private:
    SDL_Rect m_rectangle;
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;

};