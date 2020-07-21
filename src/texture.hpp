#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "sdlw.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <memory>

class Texture
{
public:
    Texture(sdlw::RendererShPtr renderer) : texRenderer(renderer) {}
    void loadFromFile(const std::string &path);
    void loadFromRenderedText(const std::string &text, TTF_Font* textFont, SDL_Color textColor =  {0, 0, 0, 255});
    void render(int xPos = 0, int yPos = 0, SDL_Rect* clip = nullptr); // If clip is nullptr, full texture is rendered
    
    int getWidth()  const;
    int getHeight() const;
    
protected:
    sdlw::TextureShPtr mTexture {nullptr};
    
private:
    sdlw::RendererShPtr texRenderer; // Pointer to the renderer associated with this texture
    int mWidth   {0};
    int mHeight  {0};
};

#endif
