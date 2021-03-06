/*
 * SettingsScreen.h
 *
 *  Created on: 7 Feb 2018
 *      Author: foidbgen
 */

#ifndef SETTINGSSCREEN_H_
#define SETTINGSSCREEN_H_

#include "oxygine-framework.h"
#include <functional>
#include "json/json.h"
#include "Game.h"
#include "Helpers/ScreenSwitcher.h"

using namespace oxygine;

class SettingsScreen: public Actor
{
public:
	SettingsScreen(std::shared_ptr<Game> game, ScreenSwitcherPtr screenSwitcherPtr);

private:
	spTextField _tittle, _langsText, _langsLabel, _muteText, _muteLabel;
	spSprite    _backButton, _langsButton, _muteButton;
	std::shared_ptr<Game> game;
	ScreenSwitcherPtr screenSwitcherPtr;

	void setupTittle();
	void setupBackButton();
	void setupLanguagesButton();
	void setupMuteButton();

	void backButtonClicked(Event* ev);
	void languagesButtonClicked(Event* ev);
	void muteButtonClicked(Event* ev);
};

typedef oxygine::intrusive_ptr<SettingsScreen> spSettingsScreen;

#endif /* SETTINGSSCREEN_H_ */
