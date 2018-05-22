/*
 * LevelScreen.h
 *
 *  Created on: 4 Feb 2018
 *      Author: foidbgen
 */

#ifndef LEVELSCREEN_H_
#define LEVELSCREEN_H_

#include "oxygine-framework.h"
#include <functional>
#include <vector>
#include "json/json.h"

using namespace oxygine;

class LevelScreen: public Actor
{
public:
	LevelScreen();

	void setChapter(Json::Value* chapter);


private:
	Json::Value* chapter;
	spTextField _tittle;
	spSprite    _backButton;
	std::vector<spSprite> _levelButtons;

	void setupTittle();
	void setupLevelButtons();
	void setupBackButton();
	void levelButtonClicked(Event* ev);
	void backButtonClicked(Event* ev);
};

typedef oxygine::intrusive_ptr<LevelScreen> spLevelScreen;

#endif /* LEVELSCREEN_H_ */
