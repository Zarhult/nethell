// Defines smart pointer wrappers around SDL structs
// Thanks to https://swarminglogic.com/jotting/2015_05_smartwrappers 

#ifndef SDLW_HPP
#define SDLW_HPP

#include <memory>
#include <SDL2/SDL.h>

namespace sdlw
{
    struct SDL_Deleter
    {
	void operator() (SDL_Window*	window)	    const { if (window)	    { SDL_DestroyWindow(window);	} }
	void operator() (SDL_Texture*	texture)    const { if (texture)    { SDL_DestroyTexture(texture);  	} }
	void operator() (SDL_Renderer*	renderer)   const { if (renderer)   { SDL_DestroyRenderer(renderer);	} }
	void operator() (SDL_Surface*	surface)    const { if (surface)    { SDL_FreeSurface(surface);		} }
	void operator() (SDL_RWops*	rwops)	    const { if (rwops)	    { SDL_RWclose(rwops);		} }
    };

    template<class T, class D = std::default_delete<T>>
    struct shared_ptr_sdl_deleter : public std::shared_ptr<T>
    {
	explicit shared_ptr_sdl_deleter(T* t = nullptr) : std::shared_ptr<T>(t, D()) {}
	
	void reset(T* t = nullptr) 
	{
	  std::shared_ptr<T>::reset(t, D());
	}
    };

    using WindowShPtr   = shared_ptr_sdl_deleter<SDL_Window,   SDL_Deleter>;
    using TextureShPtr  = shared_ptr_sdl_deleter<SDL_Texture,  SDL_Deleter>;
    using RendererShPtr = shared_ptr_sdl_deleter<SDL_Renderer, SDL_Deleter>;
    using SurfaceShPtr  = shared_ptr_sdl_deleter<SDL_Surface,  SDL_Deleter>;
    using RWopsShPtr    = shared_ptr_sdl_deleter<SDL_RWops,    SDL_Deleter>;
}

#endif
