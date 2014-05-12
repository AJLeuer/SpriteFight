//
//  GraphicalOutput.cpp
//  GameWorld
//
//  Created by Adam James Leuer on 4/26/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//



#include "GraphicalOutput.h"


SDL_Window * GraphicalOutput::window = nullptr ;
SDL_Renderer * GraphicalOutput::renderer = nullptr ;


void GraphicalOutput::init() {
	auto n = SDL_Init(SDL_INIT_EVERYTHING) ;
	
	GraphicalOutput::window = SDL_CreateWindow("SDL 2 window",
														   SDL_WINDOWPOS_CENTERED,     // x position, centered
														   SDL_WINDOWPOS_CENTERED,     // y position, centered
														   (int)GLOBAL_MAX_X,                        // width, in pixels
														   (int)GLOBAL_MAX_Y,                        // height, in pixels
														   (SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL) // flags
														   ) ;
	
	renderer = SDL_CreateRenderer(window, -1, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)) ;
	
	float x_ = 0 ;
	float y_ = 0 ;
	float * x = &x_ ;
	float * y = &y_ ;

	SDL_RenderGetScale(renderer, x, y) ;
	
	SDL_RenderSetLogicalSize(renderer, 3840, 2160);
	
	SDL_RenderGetScale(renderer, x, y) ;

	for (auto i = 0 ; i < SharedGameData::getGameObjects()->size() ; i++) {
		GameObject * temp = SharedGameData::getGameObjects()->at(i) ;
		addSprites(*(temp->getPosition()), temp->getSurface()) ;
	}
}

void GraphicalOutput::addSprites(const Position<long> & pos, SDL_Surface * surface) {
	SDL_Rect * rectangle = static_cast<SDL_Rect *>(malloc(sizeof(*rectangle))) ;
	
	Position<int> tempValueStorage = Position<int>(0, 0, 0) ; //we'll use this Position to store a few different values
															  //for the sake of convenience. Just remember to reset it!
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface) ;
	
	Uint32 * ignored1 = 0 ;
	int * ignored2 = 0 ;
	SDL_QueryTexture(texture, ignored1, ignored2, &(tempValueStorage.x), &(tempValueStorage.y)) ; //we'll temporarily store the w and h
																								  //of our texture in the x and y
																								  //of tempValueStorage
	
	rectangle->x = (int)pos.getX() ;
	rectangle->y = (int)pos.getY() ;
	rectangle->w = tempValueStorage.x ;
	rectangle->h = tempValueStorage.y ;
	
	tempValueStorage.setAllZero() ;
	
		
	SDL_RenderCopy(renderer, texture, NULL, rectangle) ;
}

void GraphicalOutput::update() {
	/* temp code */
	for (auto i = 0 ; i < SharedGameData::getGameObjects()->size() ; i++) {
		GameObject * temp = SharedGameData::getGameObjects()->at(i) ;
		addSprites(*(temp->getPosition()), temp->getSurface()) ;
	}
	/* end temp code */
	
	SDL_RenderPresent(renderer) ;
	SDL_UpdateWindowSurface(window) ; //may need to delete
}

void GraphicalOutput::exit() {
	//todo
}

/**
 * Other useful functions that may come in handy:
 
 SDL_RenderGetScale() ;
 
 SDL_RenderSetLogicalSize();
 
 SDL_GetRendererOutputSize(renderer, &(tempValueStorage.x), &(tempValueStorage.y))
 
 *
 */












