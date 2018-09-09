/*
 * ChapterScreen.cpp
 *
 *  Created on: 3 Feb 2018
 *      Author: foidbgen
 */

#include "ChapterScreen.h"
#include "Helpers/Configuration.h"
#include "Game.h"
#include "Helpers/ScreenSwitcher.h"
#include "Helpers/Theme.h"

ChapterScreen::ChapterScreen() {
	currentChapter = 0;


    // Setup buttons
    setupBackButton();
    setupTittle();
	setupSwitchButtons();

	gridView = new GridView(getStage()->getWidth() - (Theme::getPaddingLarge()*4), getStage()->getHeight()/2, Theme::getPaddingLarge()*2,
							getStage()->getHeight()/4, 2, 4);
	setupChapterButtons();
}

void ChapterScreen::setupBackButton() {
    //create button Sprite
    spSprite button = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("back_button"),
			arg_pos = Vector2(Theme::getPaddingSmall(), Theme::getPaddingSmall()),
			arg_attachTo = this,
			arg_size = Vector2(getStage()->getSize().x /12, getStage()->getSize().x /12)
    		);
    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::backButtonClicked));

    _backButton = button;
}

void ChapterScreen::setupSwitchButtons() {
    spSprite prev = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("chapter_switch_button"),
			arg_attachTo = this,
			arg_visible = false
    		);
    prev->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::prevButtonClicked));
	prev->setX(Theme::getPaddingMedium());
	Theme::centerVerically(prev);
    _prevButton = prev;

    spSprite next = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("chapter_switch_button"),
			arg_attachTo = this
    		);
    next->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::nextButtonClicked));
    next->setX(getStage()->getSize().x - Theme::getPaddingMedium() - next->getSize().x);
    Theme::centerVerically(next);
    _nextButton = next;
}

void ChapterScreen::setupTittle() {

	spTextField text = new TextField();
	text->attachTo(this);
	text->setPosition(getStage()->getSize().x / 2, getStage()->getSize().y / 18);

	//initialize text style
	TextStyle style = TextStyle(::getGameResources()->getResFont("Roboto-Regular")).withFontSize(100).withColor(Color::White).alignMiddle();
	text->setStyle(style);
	text->setText((*Configuration::getInstance().getLevels())[currentChapter]["name"].asCString());

	_title = text;
}

void ChapterScreen::setupChapterButtons() {
    spSprite button = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("chapter_button"),
			arg_attachTo = this,
			arg_userData = &(*Configuration::getInstance().getLevels())[currentChapter]["images"][0]
    		);
    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::chapterButtonClicked));
//	button->setPosition(getStage()->getSize().x/3 - getStage()->getSize().x/23 - button->getSize().x, getStage()->getSize().y/2 - getStage()->getSize().y/14 - button->getSize().y);
    _chapterButton1 = button;
    gridView->addActor(_chapterButton1);

    spSprite button2 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("chapter_button"),
			arg_attachTo = this,
			arg_userData = &(*Configuration::getInstance().getLevels())[currentChapter]["images"][1]
    		);
    button2->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::chapterButtonClicked));
//    button2->setPosition(getStage()->getSize().x/2 - button2->getSize().x/2, getStage()->getSize().y/2 - getStage()->getSize().y/14 - button2->getSize().y);
    _chapterButton2 = button2;
	gridView->addActor(_chapterButton2);

    spSprite button3 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("chapter_button"),
			arg_attachTo = this,
			arg_userData = &(*Configuration::getInstance().getLevels())[currentChapter]["images"][2]
    		);
    button3->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::chapterButtonClicked));
//    button3->setPosition(getStage()->getSize().x/3 * 2 + getStage()->getSize().x/23, getStage()->getSize().y/2 - getStage()->getSize().y/14 - button3->getSize().y);
    _chapterButton3 = button3;
	gridView->addActor(_chapterButton3);

    spSprite button4 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("chapter_button"),
			arg_attachTo = this,
			arg_userData = &(*Configuration::getInstance().getLevels())[currentChapter]["images"][3]
    		);
    button4->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::chapterButtonClicked));
//	button4->setPosition(getStage()->getSize().x/3 - getStage()->getSize().x/23 - button4->getSize().x, getStage()->getSize().y/2 + getStage()->getSize().y/14);
    _chapterButton4 = button4;
	gridView->addActor(_chapterButton4);

    spSprite button5 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("chapter_button"),
			arg_attachTo = this,
			arg_userData = &(*Configuration::getInstance().getLevels())[currentChapter]["images"][4]
    		);
    button5->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::chapterButtonClicked));
//    button5->setPosition(getStage()->getSize().x/2 - button5->getSize().x/2, getStage()->getSize().y/2 + getStage()->getSize().y/14);
    _chapterButton5 = button5;
	gridView->addActor(_chapterButton5);

    spSprite button6 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("chapter_button"),
			arg_attachTo = this,
			arg_userData = &(*Configuration::getInstance().getLevels())[currentChapter]["images"][5]
    		);
    button6->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::chapterButtonClicked));
//    button6->setPosition(getStage()->getSize().x/3 * 2 + getStage()->getSize().x/23, getStage()->getSize().y/2 + getStage()->getSize().y/14);
    _chapterButton6 = button6;
	gridView->addActor(_chapterButton6);

    spSprite button7 = initActor(new Sprite,
            arg_resAnim = ::getGameResources()->getResAnim("chapter_button"),
            arg_attachTo = this,
            arg_userData = &(*Configuration::getInstance().getLevels())[currentChapter]["images"][6]
    );
    button7->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::chapterButtonClicked));
//    button7->setPosition(getStage()->getSize().x/3 * 2 + getStage()->getSize().x/23, getStage()->getSize().y/2 + getStage()->getSize().y/14);
    _chapterButton7 = button7;
	gridView->addActor(_chapterButton7);

    spSprite button8 = initActor(new Sprite,
             arg_resAnim = ::getGameResources()->getResAnim("chapter_button"),
             arg_attachTo = this,
             arg_userData = &(*Configuration::getInstance().getLevels())[currentChapter]["images"][7]
    );
    button8->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ChapterScreen::chapterButtonClicked));
//    button8->setPosition(getStage()->getSize().x/3 * 2 + getStage()->getSize().x/23, getStage()->getSize().y/2 + getStage()->getSize().y/14);
    _chapterButton8 = button8;
	gridView->addActor(_chapterButton8);
}

void ChapterScreen::backButtonClicked(Event* ev) {
	logs::messageln("back button clicked");
	ScreenSwitcher::getInstance().switchScreen("MainMenu");
}

void ChapterScreen::chapterButtonClicked(Event* ev) {
	logs::messageln("chapter button clicked %f %f", _chapterButton1->getX(), _chapterButton2->getY());
	Json::Value* chapter = (Json::Value*)ev->currentTarget->getUserData();
//	((LevelScreen*)ScreenSwitcher::getInstance().getScreen("LevelScreen"))->setChapter(chapter);
//	ScreenSwitcher::getInstance().switchScreen("LevelScreen");
}

void ChapterScreen::nextButtonClicked(Event* ev) {
	if((*Configuration::getInstance().getLevels()).size() <= currentChapter + 1) return;

	Json::Value *chapter;
	currentChapter++;
	chapter = &(*Configuration::getInstance().getLevels())[currentChapter];

    _nextButton->setVisible((*Configuration::getInstance().getLevels()).size() != currentChapter + 1);

    _prevButton->setVisible(currentChapter != 0);

	_title->setText((*chapter)["name"].asCString());

	_chapterButton1->setUserData(&(*chapter)["images"][0]);
	_chapterButton2->setUserData(&(*chapter)["images"][1]);
	_chapterButton3->setUserData(&(*chapter)["images"][2]);
	_chapterButton4->setUserData(&(*chapter)["images"][3]);
	_chapterButton5->setUserData(&(*chapter)["images"][4]);
	_chapterButton6->setUserData(&(*chapter)["images"][5]);
}

void ChapterScreen::prevButtonClicked(Event* ev) {
	if(currentChapter - 1 < 0) return;

	Json::Value *chapter;
	currentChapter--;
	chapter = &(*Configuration::getInstance().getLevels())[currentChapter];

    _nextButton->setVisible((*Configuration::getInstance().getLevels()).size() > currentChapter + 1);

    _prevButton->setVisible(currentChapter != 0);

	_title->setText((*chapter)["name"].asCString());

	_chapterButton1->setUserData(&(*chapter)["images"][0]);
	_chapterButton2->setUserData(&(*chapter)["images"][1]);
	_chapterButton3->setUserData(&(*chapter)["images"][2]);
	_chapterButton4->setUserData(&(*chapter)["images"][3]);
	_chapterButton5->setUserData(&(*chapter)["images"][4]);
	_chapterButton6->setUserData(&(*chapter)["images"][5]);
}