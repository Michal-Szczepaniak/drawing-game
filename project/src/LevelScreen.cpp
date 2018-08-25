/*
 * LevelScreen.cpp
 *
 *  Created on: 4 Feb 2018
 *      Author: foidbgen
 */

#include "LevelScreen.h"
#include "Game.h"
#include "GameScreen.h"
#include "ScreenSwitcher.h"

LevelScreen::LevelScreen() {
	chapter = NULL;

	setupTittle();
	setupLevelButtons();
	setupBackButton();
}

void LevelScreen::setupTittle() {
	spTextField text = new TextField();
	text->attachTo(this);
	text->setPosition(getStage()->getSize().x / 2, getStage()->getSize().y / 18);

	//initialize text style
	TextStyle style = TextStyle(::getGameResources()->getResFont("Roboto-Regular")).withFontSize(100).withColor(Color::White).alignMiddle();
	text->setStyle(style);
	text->setText("Select level");

	_tittle = text;
}

void LevelScreen::setupBackButton() {
    //create button Sprite
    spSprite button = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("back_button"),
			arg_pos = getStage()->getSize()/56,
			arg_attachTo = this,
			arg_size = Vector2(getStage()->getSize().x /12, getStage()->getSize().x /12)
    		);
    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::backButtonClicked));

    _backButton = button;
}

void LevelScreen::setupLevelButtons() {
	Point padding(getStage()->getSize().x/12.2, getStage()->getSize().y/17.1);

    spSprite button = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button->setPosition(getStage()->getSize().x/2 - padding.x*1.5 - button->getSize().x*2, getStage()->getSize().y/2 + getStage()->getSize().y/50 - button->getSize().y);

    spSprite button2 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button2->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button2->setPosition(getStage()->getSize().x/2 - padding.x/2 - button->getSize().x, button->getPosition().y);

    spSprite button3 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button3->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button3->setPosition(getStage()->getSize().x/2 + padding.x/2, button->getPosition().y);

    spSprite button4 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button4->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button4->setPosition(getStage()->getSize().x/2 + padding.x*1.5 + button->getSize().x, button->getPosition().y);

    spSprite button5 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button5->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button5->setPosition(getStage()->getSize().x/2 - padding.x*1.5 - button->getSize().x*2, button->getPosition().y + padding.y + button->getSize().y);

    spSprite button6 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button6->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button6->setPosition(getStage()->getSize().x/2 - padding.x/2 - button->getSize().x, button5->getPosition().y);

    spSprite button7 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button7->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button7->setPosition(getStage()->getSize().x/2 + padding.x/2, button5->getPosition().y);

    spSprite button8 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button8->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button8->setPosition(getStage()->getSize().x/2 + padding.x*1.5 + button->getSize().x, button5->getPosition().y);

    spSprite button9 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button9->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button9->setPosition(getStage()->getSize().x/2 - padding.x*1.5 - button->getSize().x*2, button5->getPosition().y + padding.y + button->getSize().y);

    spSprite button10 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button10->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button10->setPosition(getStage()->getSize().x/2 - padding.x/2 - button->getSize().x, button9->getPosition().y);

    spSprite button11 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button11->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button11->setPosition(getStage()->getSize().x/2 + padding.x/2, button9->getPosition().y);

    spSprite button12 = initActor(new Sprite,
    		arg_resAnim = ::getGameResources()->getResAnim("level_button"),
			arg_attachTo = this
    		);
    button12->addEventListener(TouchEvent::CLICK, CLOSURE(this, &LevelScreen::levelButtonClicked));
	button12->setPosition(getStage()->getSize().x/2 + padding.x*1.5 + button->getSize().x, button9->getPosition().y);

    _levelButtons.push_back(button);
    _levelButtons.push_back(button2);
    _levelButtons.push_back(button3);
    _levelButtons.push_back(button4);
    _levelButtons.push_back(button5);
    _levelButtons.push_back(button6);
    _levelButtons.push_back(button7);
    _levelButtons.push_back(button8);
    _levelButtons.push_back(button9);
    _levelButtons.push_back(button10);
    _levelButtons.push_back(button11);
    _levelButtons.push_back(button12);
}

void LevelScreen::levelButtonClicked(Event* ev) {
	Json::Value* level = (Json::Value*)ev->currentTarget->getUserData();
	((GameScreen*) ScreenSwitcher::getInstance().getScreen("GameScreen"))->setLevel(level);
	ScreenSwitcher::getInstance().switchScreen("GameScreen");
	logs::messageln("level button clicked");
}

void LevelScreen::backButtonClicked(Event* ev) {
	logs::messageln("back button clicked");
	ScreenSwitcher::getInstance().switchScreen("ChapterScreen");
}

void LevelScreen::setChapter(Json::Value* chapter) {
	int i = 0;

	this->chapter = chapter;

	for(auto& button: _levelButtons) {
		button->setUserData(&(*chapter)[i]);
		i++;
	}

	logs::messageln("%s", (*chapter).toStyledString().c_str());
}
