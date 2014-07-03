//
//  Player.cpp
//  World
//
//  Created by Adam James Leuer on 5/31/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Player.h"

using namespace std ;

Player::Player() :
	name("Player 1")
{
    auto x = (globalMaxX() / 2) ;
    auto y = (globalMaxY() - (globalMaxY() * 0.25)) ;
	playerCharacter = PlayerCharacter(pcAssetType, AssetFileIO::getRandomImageFilename(pcAssetType), size, Pos2<float>(x, y, 0), /* Pos2<float>(randPositionSetter<float>(), defaultCheck<float>()) */ name, Reaction::friendly, DoA::alive, CharacterState::normal,
        500, 100) ;
	
	registerForCallbacks() ;
}

Player::Player(const string & name, const string & imageFile) :
	name(name)
{
    auto x = (globalMaxX() / 2) ;
    auto y = (globalMaxY() - (globalMaxY() * 0.25)) ;
	playerCharacter = PlayerCharacter(pcAssetType, imageFile, size,
								Pos2<float>(x, y, 0), name, Reaction::friendly, DoA::alive, CharacterState::normal, 500, 100) ;
	registerForCallbacks() ;
}

void Player::update() {
	//todo
}

void Player::printPositition() {
	stringstream ss ;
	ss << this->name << "'s current world position is: " << playerCharacter.getPosition() ;
	auto screenPosition = translateToWindowCoords(*playerCharacter.getPosition()) ;
	ss << this->name << "'s current screen position is: " << screenPosition << '\n' ;
	DebugOutput << ss.rdbuf() ;
}

void Player::registerForCallbacks() {
	
	KeyInputRegister * moveUpKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveUp), MOVE_UP, SDLK_UP) ;
	KeyInputRegister * moveDownKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveDown), MOVE_UP, SDLK_DOWN) ;
	KeyInputRegister * moveLeftKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveLeft), MOVE_LEFT, SDLK_LEFT) ;
	KeyInputRegister * moveRightKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveRight), MOVE_RIGHT, SDLK_RIGHT) ;
	
	KeyInputRegister * jumpKey = new KeyInputRegister(this, (&GameInterface::jump), SDLK_SPACE) ;

	InputController::registerForKeypress(moveUpKey) ;
	InputController::registerForKeypress(moveDownKey) ;
	InputController::registerForKeypress(moveLeftKey) ;
	InputController::registerForKeypress(moveRightKey) ;
	
	InputController::registerForKeypress(jumpKey) ;
}

void Player::jump() {
	playerCharacter.jump() ;
	playerCharacter.timedTurnInvisible(std::chrono::nanoseconds(64000000)) ;
	
	#ifdef DEBUG_MODE
	printPositition() ;
	#endif
}