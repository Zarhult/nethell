#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <memory>
#include <SDL2/SDL.h>

class Texture
{
    public:
	using TexturePtr = std::unique_ptr<Texture>;

    public:
	explicit Texture(const int &xPos, const int &yPos) : xPos(xPos), yPos(yPos) {} 
	~Texture();

	bool loadFromFile(SDL_Renderer* renderer, const std::string &path);
	void render(SDL_Renderer* renderer, const int &x, const int &y);
	void free();

	const int &getWidth() const;
	const int &getHeight() const;
	const int &getXPos() const;
	const int &getYPos() const;

    private:
	SDL_Texture* texture {nullptr};

	int width {0};
	int height {0};
	int xPos {0};
	int yPos {0};
};

#endif
