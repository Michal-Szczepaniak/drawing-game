/*
 * GameScreen.h
 *
 *  Created on: 15 Jan 2018
 *      Author: foidbgen
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include "oxygine-framework.h"
#include <functional>
#include "json/json.h"
#include "Game.h"
#include "Helpers/ScreenSwitcher.h"

using namespace oxygine;

class GameScreen: public Actor
{
public:
	GameScreen(std::shared_ptr<Game> game, ScreenSwitcherPtr screenSwitcherPtr);

	void setLevel(Json::Value* level);

private:
	spTextField _text;
	spSprite _image, _finishButton;
	spNativeTexture texture;
	Color color;
	spSprite preview;
	Vector2 _oldPos;
	Json::Value* level;
	std::shared_ptr<Game> game;
	ScreenSwitcherPtr screenSwitcherPtr;

	void setupDrawingSpace();
	void setupImage();
	void setupControls();

	int countRepeatTimes(Vector2 oldV, Vector2 newV);
	void dumpToFile(spNativeTexture texture, std::string filename);
};

typedef oxygine::intrusive_ptr<GameScreen> spGameScreen;

#endif /* GAMESCREEN_H_ */
