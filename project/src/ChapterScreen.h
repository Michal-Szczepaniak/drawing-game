/*
 * ChapterScreen.h
 *
 *  Created on: 3 Feb 2018
 *      Author: foidbgen
 */

#ifndef CHAPTERSCREEN_H_
#define CHAPTERSCREEN_H_

#include "oxygine-framework.h"
#include <functional>
#include "Helpers/GridView.h"
#include "Game.h"
#include "Helpers/ScreenSwitcher.h"

using namespace oxygine;

class ChapterScreen: public Actor
{
public:
	ChapterScreen(std::shared_ptr<Game> game, ScreenSwitcherPtr screenSwitcherPtr);

private:
	int currentChapter;
	spSprite    _backButton, _nextButton, _prevButton;
	spSprite    _chapterButton1, _chapterButton2, _chapterButton3, _chapterButton4, _chapterButton5, _chapterButton6, _chapterButton7, _chapterButton8;
	spTextField _title;
        GridView*	gridView;
        std::shared_ptr<Game> game;
        ScreenSwitcherPtr screenSwitcherPtr;

	void setupBackButton();
	void setupChapterButtons();
	void setupTittle();
	void setupSwitchButtons();

	void backButtonClicked(Event* ev);
	void nextButtonClicked(Event* ev);
	void prevButtonClicked(Event* ev);
	void chapterButtonClicked(Event* ev);
};

typedef oxygine::intrusive_ptr<ChapterScreen> spChapterScreen;

#endif /* CHAPTERSCREEN_H_ */
