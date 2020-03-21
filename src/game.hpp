#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "texture.hpp"
#include "sdlw.hpp"

class Game
{
    public:
	Game(const int &winWidth, const int &winHeight);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	bool loadTexture(const std::string &path, const int &xPos, const int &yPos);
	void eventHandle();
	void render();

	const bool& getRunStatus() const;

    private:
	sdlw::WindowShPtr window {nullptr};
	sdlw::RendererShPtr renderer {nullptr};
	std::vector<Texture::TexturePtr> textureVec;
	SDL_Event event;
	bool isRunning {false};
};

#endif
