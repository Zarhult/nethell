#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include <memory>
#include <SDL.h>
#include "texture.hpp"

class Game
{
    public:
	explicit Game() {}
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
	~Game();

	bool init(int winWidth, int winHeight);
	bool loadTexture(std::string path);
	void eventHandle();
	void render();
	void clean();

	bool getRunStatus();

    private:
	SDL_Window* window { nullptr };
	SDL_Renderer* renderer { nullptr };
	std::vector<Texture::TexturePtr> textureVec;
	SDL_Event event;
	bool isRunning { false };
};

#endif
