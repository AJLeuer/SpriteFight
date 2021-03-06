#pragma once

#include <unistd.h>

#include <iostream>
#include <thread>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../Util/Debug.h"
#include "../Util/Util.hpp"
#include "../Util/Vect.hpp"

#include "GraphicsData.hpp"
#include "TextOutput.hpp"
#include "GameColor.h"


#include "../World/GameState.hpp"
#include "../World/GameObject.h"

#include "../Control/Configuration.h"

using namespace std ;

/**
 * Controller class for all graphics output.
 */
class GraphicalOutput {
	
protected:
	
	static Window * window ;
	static Renderer * renderer ;
	static RenderInfo renderInfo ;
	static unsigned framesRendered ;
	
	/**
	 * Handles rendering.
	 */
	static void render() ;
	
	/**
	 * Renders the given texture at the desired position and size.
	 */
	template<typename M, typename N>
	static void render(GraphicsData<M, N> * output) ;
	
	
	GraphicalOutput() ; //private to prevent instantiation
	
public:
	
	static void init() ;
	static void update() ;
	static void drawFPS() ;
	static void exit() ;
	
} ;


template<typename M, typename N>
void GraphicalOutput::render(GraphicsData<M, N> * output) {
	
    auto tempShape = Util::convertToSDL_Rect(output->getPosition(), output->getSize()) ;
	
	int sdlrend_error = 0 ;
	
	/* texture will sometimes be null, e.g. when game objects are invisible their
	   getTexture() method returns a nullptr */
	if ((output != nullptr) && (output->isVisible())) {
		if (output->getTexture() != nullptr) {
			sdlrend_error = SDL_RenderCopyEx(renderer, output->getTexture(), NULL, &tempShape, output->copyOrientation(), NULL, SDL_FLIP_NONE) ;
		}
	}
	
	if (sdlrend_error == -1) {
		stringstream ss ;
		ss << "SDL_RenderCopy() failed." << '\n' ;
		ss << SDL_GetError() << '\n' ;
		cerr << ss.rdbuf() ;
		throw exception() ;
	}
}
