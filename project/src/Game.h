/*
 * game.h
 *
 *  Created on: 15 Jan 2018
 *      Author: foidbgen
 */
#include "oxygine-framework.h"
#include <functional>
#include "MusicPlayer.h"

using namespace oxygine;

#ifndef GAME_H_
#define GAME_H_

void game_preinit();
void game_init();
void game_destroy();
void game_update();

Resources* getGameResources();
MusicPlayer* getMusicPlayer();

#endif /* GAME_H_ */