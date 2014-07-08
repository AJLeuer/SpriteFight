//
//  WorldController.cpp
//  World
//
//  Created by Adam James Leuer on 3/11/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//


#include "WorldController.h"

using namespace std ;


vector<GameObject*> * WorldController::gameObjects  = nullptr ;
thread WorldController::mainThread ;
thread WorldController::checkDelThread ;
const GameMap<GameObject> * WorldController::map = nullptr ;

WorldController::WorldController() {}


void WorldController::init() {

	WorldController::gameObjects = GameObject::getAllGameObjects() ;
	WorldController::map = GameObject::getMap() ;

	FastRand<int> posModifier(-100, 100) ;

	VectrVel<float> test(-11, 1.5, 0, nullptr) ;
	
	/* Init enemies */
	/*
	new Enemy(AssetType::character, AssetFileIO::getRandomImageFilename(AssetType::character),
              0.50, Pos2<float>(globalMaxX() - 200, (startingYAreaHi + posModifier()), 0, defaultCheck<float>())) ;

	new Enemy(AssetType::character, AssetFileIO::getRandomImageFilename(AssetType::character),
              0.50, Pos2<float>(globalMaxX() - 200, (startingYAreaLo + posModifier()), 0, defaultCheck<float>())) ;
	*/
	/* Init obstacles */
	FastRand<float>randomSizeModifier(0.25, 1.0) ;
	
	AssetType atype = AssetType::asteroid ;
	
	for (auto i = 0 ; i < 10 ; i++) {
		/*
		new GameObject(Colors::blue, atype, AssetFileIO::getRandomImageFile(atype), randomSizeModifier(),
					   Pos2<float>(*FastRand<float>::randPositionSetter, BoundsCheck<float>::defaultCheck)) ; */
	}
	
	/* Init game state */
	GameState::initData(GameObject::getAllGameObjects(), GameObject::getMap()) ;
	
}

void WorldController::begin_main() {
	mainThread = thread(&WorldController::main) ;  //runWorldSimulation()
	checkDelThread = thread(&GameObject::checkForMarkedDeletions) ;
}

void WorldController::main() {
	
	auto rt = refreshTime ; //debug symbol
    
    /* start the gameobjects moving */
    for (auto i = 0 ; i < gameObjects->size() ; i++) {
        if (gameObjects->at(i) != nullptr) {
            gameObjects->at(i)->moveRandomDirection();
            
            /* do any other stuff with GameObjects */
            
            /* always call update at the end */
            gameObjects->at(i)->update() ;
        }
    }
	
	bool * cont = &GLOBAL_CONTINUE_SIGNAL ; //debug variable - rm
	
	while (GLOBAL_CONTINUE_SIGNAL) {
		auto startTime = GameState::mainGameClock->checkTimeElapsed() ;
		
		/* Do stuff */
		for (auto i = 0 ; i < gameObjects->size() ; i++) {
			if (gameObjects->at(i) != nullptr) {
				gameObjects->at(i)->defaultBehaviors() ;
                
                /* do any stuff with GameObjects */
                
                /* always call update at the end */
                gameObjects->at(i)->update() ;
			}
		}
		
		auto * wloop = &worldLoopCount ; //debug var, delete
		
		auto time2 = GameState::mainGameClock->checkTimeElapsed() ;
		auto timeElapsed = time2 - startTime ;
		
		auto sleepTime = refreshTime - timeElapsed ;
		worldLoopCount++ ;
		this_thread::sleep_for(sleepTime) ;
        
       /* Sync loops */
		while (worldLoopCount > mainGameLoopCount) {
           /* wait */
		}
	}
}



void WorldController::exit() {
	
	GameState::sharedMutex.lock() ; //we don't want our Adapter thinking its safe to read our GameObjects any more
	
	checkDelThread.join() ;
	
	GameObject::joinThreads() ;
	
	for (auto i = 0 ; i < gameObjects->size() ; i++) {
		if (gameObjects->at(i) != nullptr) {
			//delete gameObjects->at(i) ;
		}
	}

	delete gameObjects ;
	delete map ; 
	gameObjects = nullptr ;
	
	GameState::sharedMutex.unlock() ;
}






