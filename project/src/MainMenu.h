/*
 * mainActor.h
 *
 *  Created on: 15 Jan 2018
 *      Author: foidbgen
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "oxygine-framework.h"
#include <functional>

using namespace oxygine;

class MainMenu: public Actor
{
public:
    spTextField _startText, _optionsText, _helpText, _aboutText;
    spSprite    _startButton, _optionsButton, _helpButton, _aboutButton;
    spNativeTexture texture;
	Color color;
	spSprite preview;

    MainMenu();

    void buttonClicked(Event* event);
    void onDown(Event* ev);
    void onMove(Event* ev);

    void dumpToFile(spNativeTexture texture, std::string filename);

private:
    void setupStartButton();
    void setupSettingsButton();
    void setupHelpButton();
    void setupAboutButton();
    void startButtonClicked(Event* event);
    void settingsButtonClicked(Event* event);
};
//declare spMainActor as intrusive_ptr holder of MainActor
typedef oxygine::intrusive_ptr<MainMenu> spMainMenu;
//you could use DECLARE_SMART preprocessor definition it does the same:
//DECLARE_SMART(MainActor, spMainActor)

#endif /* MAINMENU_H_ */