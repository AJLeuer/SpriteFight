//
//  Player.h
//  World
//
//  Created by Adam James Leuer on 5/31/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __GameWorld__Player__
#define __GameWorld__Player__

#include <iostream>
#include <sstream>
#include <chrono>

#include "../Util/Util2.h"
#include "../Util/BoundsCheck.hpp"
#include "../Util/GameRandom.hpp"

#include "../World/GameInterface.h"
#include "../World/PlayerCharacter.h"
#include "../World/GameState.h"

#include "../Control/DefaultConfig.h"
#include "../Control/Input.hpp"

using namespace std ;


class Player /*: public GameInterface*/ {

protected:
	
	static Pos2<float> defaultStartingPosition ;
	static AssetType defaultPCAssetType ; /* change if needed */
	static float defaultSize ;
	
	string name ;
	PlayerCharacter playerCharacter ;
	
	
	/* just for initializing playerCharacter */
	
	
	void registerForCallbacks() ;

public:
	
	/* Players with default settings, for convenience */
	static Player * defaultPlayer0 ;
	static Player * defaultPlayer1 ;
	
	static void initDefaultPlayers() ;
	
	Player() ;
	
	Player(const string & name, const string & playerCharacter_imageFilename,
		   Color playerCharacter_color, float playerCharacter_size, const Pos2<float> & playerCharacter_loc, const string & playerCharacter_name,
		   Reaction playerCharacter_reaction, DoA playerCharacter_alive, CharacterState playerCharacter_state,
		   unsigned playerCharacter_health, unsigned playerCharacter_damage) ;

	/* implementing these just so we're not considered an abstract class */
	void operator()() {}
	
	void update() ;

	
	
	
	
	
	
} ;

#endif /* defined(__GameWorld__Player__) */
