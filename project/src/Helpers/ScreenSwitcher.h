/*
 * screenswitcher.h
 *
 *  Created on: 22 Jan 2018
 *      Author: foidbgen
 */

#ifndef SCREENSWITCHER_H_
#define SCREENSWITCHER_H_

#include "oxygine-framework.h"
#include "../Game.h"

using namespace oxygine;

class ScreenSwitcher
{
public:
    ScreenSwitcher(std::shared_ptr<class Game> game);
    ~ScreenSwitcher();

public:

    void registerScreens(std::shared_ptr<ScreenSwitcher> screenSwitcherPtr);
    Actor* getCurrentScreen();
    Actor* getScreen(std::string name);
    Actor* switchScreen(std::string name);

private:
    std::vector<std::pair<std::string, Actor*>> screens;
    std::string currentScreenName;
    std::shared_ptr<class Game> game;
};
typedef std::shared_ptr < ScreenSwitcher > ScreenSwitcherPtr;

#endif /* SCREENSWITCHER_H_ */
