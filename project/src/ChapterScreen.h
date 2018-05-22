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

using namespace oxygine;

class ChapterScreen: public Actor
{
public:
	ChapterScreen();

private:
	int currentChapter;
	spSprite    _backButton, _nextButton, _prevButton, _randomButton;
	spSprite    _chapterButton1, _chapterButton2, _chapterButton3, _chapterButton4, _chapterButton5, _chapterButton6;
	spTextField _tittle;

	void setupBackButton();
	void setupChapterButtons();
	void setupTittle();
	void setupSwitchButtons();
	void setupRandomButton();

	void backButtonClicked(Event* ev);
	void nextButtonClicked(Event* ev);
	void prevButtonClicked(Event* ev);
	void chapterButtonClicked(Event* ev);
	void randomButtonClicked(Event* ev);
};

typedef oxygine::intrusive_ptr<ChapterScreen> spChapterScreen;

#endif /* CHAPTERSCREEN_H_ */
