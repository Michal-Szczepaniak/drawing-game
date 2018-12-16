/*
 * game.h
 *
 *  Created on: 15 Jan 2018
 *      Author: foidbgen
 */
#ifndef GAME_H_
#define GAME_H_

#include "oxygine-framework.h"
#include <functional>
#include <memory>
#include "MusicPlayer.h"
#include "Helpers/ScreenSwitcher.h"

using namespace oxygine;

typedef std::shared_ptr<Resources> ResourcesPtr;

class Game {
public:
    Game();

    void preInit(std::shared_ptr<Game> game);
    void init();
    void update();
    void destroy();

    ResourcesPtr getResources();
    MusicPlayerPtr getMusicPlayer();

private:
    ResourcesPtr resourcesPtr;
    MusicPlayerPtr musicPlayerPtr;
    std::shared_ptr<class ScreenSwitcher> screenSwitcherPtr;
    std::shared_ptr<Game> game;
};
#endif /* GAME_H_ */