/*
 * screenswitcher.cpp
 *
 *  Created on: 22 Jan 2018
 *      Author: foidbgen
 */

#include "ScreenSwitcher.h"

#include "../MainMenu.h"
#include "../GameScreen.h"
#include "../ChapterScreen.h"
#include "../SettingsScreen.h"

ScreenSwitcher::ScreenSwitcher(std::shared_ptr<class Game> game) {
	this->game = game;
}

ScreenSwitcher::~ScreenSwitcher() = default;

void ScreenSwitcher::registerScreens(std::shared_ptr<ScreenSwitcher> screenswitcherPtr) {
	screens.emplace_back("MainMenu", new MainMenu(game, screenswitcherPtr));
	getStage()->addChild(getScreen("MainMenu"));

	screens.emplace_back("GameScreen", new GameScreen(game, screenswitcherPtr));
	getStage()->addChild(getScreen("GameScreen"));
	getScreen("GameScreen")->setVisible(false);

	screens.emplace_back("ChapterScreen", new ChapterScreen(game, screenswitcherPtr));
	getStage()->addChild(getScreen("ChapterScreen"));
	getScreen("ChapterScreen")->setVisible(false);

	screens.emplace_back("SettingsScreen", new SettingsScreen(game, screenswitcherPtr));
	getStage()->addChild(getScreen("SettingsScreen"));
	getScreen("SettingsScreen")->setVisible(false);

	currentScreenName = screens.front().first;
}

Actor* ScreenSwitcher::getCurrentScreen() {
	for (auto screen: screens) {
		if(screen.first == currentScreenName)
			return screen.second;
	}
}

Actor* ScreenSwitcher::getScreen(std::string name) {
	for (auto screen: screens) {
		if(screen.first == name)
			return screen.second;
	}
}

Actor* ScreenSwitcher::switchScreen(std::string name) {
	for (auto screen: screens) {
		if(screen.first == name) {
			getCurrentScreen()->setVisible(false);
			currentScreenName = name;
			getCurrentScreen()->setVisible(true);
			return screen.second;
		}
	}
}
