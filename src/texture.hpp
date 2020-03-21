#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "sdlw.hpp"

class Texture
{
    public:
	using TexturePtr = std::unique_ptr<Texture>;

    public:
	explicit Texture(const int &xPos, const int &yPos) : xPos(xPos), yPos(yPos) {} 

	bool loadFromFile(sdlw::RendererShPtr renderer, const std::string &path);
	void render(sdlw::RendererShPtr renderer, SDL_Rect* clip = nullptr, const int &x = 0, const int &y = 0);

	const int& getWidth()	const;
	const int& getHeight()	const;
	const int& getXPos()	const;
	const int& getYPos()	const;

    private:
	sdlw::TextureShPtr texture {nullptr};

	int width   {0};
	int height  {0};
	int xPos    {0};
	int yPos    {0};
};

#endif
