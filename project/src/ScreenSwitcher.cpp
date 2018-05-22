/*
 * screenswitcher.cpp
 *
 *  Created on: 22 Jan 2018
 *      Author: foidbgen
 */

#include "ScreenSwitcher.h"

#include "MainMenu.h"
#include "GameScreen.h"
#include "ChapterScreen.h"
#include "LevelScreen.h"
#include "SettingsScreen.h"

ScreenSwitcher::ScreenSwitcher() {

}

ScreenSwitcher::~ScreenSwitcher() {
}

void ScreenSwitcher::registerScreens() {
	screens.push_back(std::make_pair("MainMenu", new MainMenu()));
	getStage()->addChild(getScreen("MainMenu"));

	screens.push_back(std::make_pair("GameScreen", new GameScreen()));
	getStage()->addChild(getScreen("GameScreen"));
	getScreen("GameScreen")->setVisible(false);

	screens.push_back(std::make_pair("ChapterScreen", new ChapterScreen()));
	getStage()->addChild(getScreen("ChapterScreen"));
	getScreen("ChapterScreen")->setVisible(false);

	screens.push_back(std::make_pair("LevelScreen", new LevelScreen()));
	getStage()->addChild(getScreen("LevelScreen"));
	getScreen("LevelScreen")->setVisible(false);

	screens.push_back(std::make_pair("SettingsScreen", new SettingsScreen()));
	getStage()->addChild(getScreen("SettingsScreen"));
	getScreen("SettingsScreen")->setVisible(false);


	currentScreenName = "MainMenu";
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
