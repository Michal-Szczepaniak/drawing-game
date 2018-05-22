/*
 * screenswitcher.h
 *
 *  Created on: 22 Jan 2018
 *      Author: foidbgen
 */

#ifndef SCREENSWITCHER_H_
#define SCREENSWITCHER_H_

#include "oxygine-framework.h"

using namespace oxygine;

class ScreenSwitcher
{
    public:
        static ScreenSwitcher& getInstance()
        {
            static ScreenSwitcher instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
    private:
        ScreenSwitcher();

        ~ScreenSwitcher();

        std::vector<std::pair<std::string, Actor*>> screens;
        std::string currentScreenName;

    public:
        ScreenSwitcher(ScreenSwitcher const&) = delete;
        void operator=(ScreenSwitcher const&) = delete;

        void registerScreens();
        Actor* getCurrentScreen();
        Actor* getScreen(std::string name);
        Actor* switchScreen(std::string name);


};

#endif /* SCREENSWITCHER_H_ */
