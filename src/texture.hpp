#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <memory>
#include <SDL2/SDL.h>

class Texture
{
    public:
	typedef std::unique_ptr<Texture> TexturePtr;

    public:
	explicit Texture(int width, int height) : width(width), height(height) {} 
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
	~Texture();

	bool loadFromFile(SDL_Renderer* renderer, std::string path);
	void render(SDL_Renderer* renderer);
	void free();

	int getWidth();
	int getHeight();

    private:
	SDL_Texture* texture = nullptr;

	int width { 0 };
	int height { 0 };
};

#endif
