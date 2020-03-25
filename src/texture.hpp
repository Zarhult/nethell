#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "sdlw.hpp"

class Texture
{
    public:
	Texture(sdlw::RendererShPtr renderer);
	bool loadFromFile(const std::string &path);
	void render(int xPos = 0, int yPos = 0, SDL_Rect* clip = nullptr);    // If clip is nullptr, full texture is rendered

	sdlw::RendererShPtr texRenderer;    // Pointer to the renderer associated with this texture

	int getWidth()	const;
	int getHeight()	const;

    protected:
	sdlw::TextureShPtr texture {nullptr};

    private:
	int width   {0};
	int height  {0};
};

#endif
