/*
 * SettingsScreen.cpp
 *
 *  Created on: 7 Feb 2018
 *      Author: foidbgen
 */

#include "SettingsScreen.h"
#include "Game.h"
#include "Helpers/ScreenSwitcher.h"
#include "Helpers/Configuration.h"

SettingsScreen::SettingsScreen(std::shared_ptr<Game> game, ScreenSwitcherPtr screenSwitcherPtr) {
	this->game = game;
	this->screenSwitcherPtr = screenSwitcherPtr;

	setupTittle();
	setupBackButton();
	setupLanguagesButton();
	setupMuteButton();
}

void SettingsScreen::setupTittle() {
	Json::Value* translations = Configuration::getInstance().getTranslations();

	spTextField text = new TextField();
	text->attachTo(this);
	text->setPosition(getStage()->getSize().x / 2, getStage()->getSize().y / 5.5);

	//initialize text style
	TextStyle style = TextStyle(game->getResources()->getResFont("Roboto-Bold")).withFontSize(160).withColor(Color::White).alignMiddle();
	text->setStyle(style);
	text->setText((*translations)["settings"].asString());

	_tittle = text;
}

void SettingsScreen::setupBackButton() {
    spSprite button = initActor(new Sprite,
    		arg_resAnim = game->getResources()->getResAnim("back_button"),
			arg_pos = getStage()->getSize()/56,
			arg_attachTo = this,
			arg_size = Vector2(getStage()->getSize().x /12, getStage()->getSize().x /12)
    		);
    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &SettingsScreen::backButtonClicked));

    _backButton = button;
}

void SettingsScreen::setupLanguagesButton() {
	Json::Value* settings = Configuration::getInstance().getSettings();
	Json::Value* languages = Configuration::getInstance().getLanguages();
	Json::Value* translations = Configuration::getInstance().getTranslations();

    spSprite langsButton = initActor(new Sprite,
    		arg_resAnim = game->getResources()->getResAnim("settings_button"),
			arg_attachTo = this
    		);
    langsButton->setPosition(Vector2(getStage()->getSize().x/2 - langsButton->getSize().x/2, getStage()->getSize().y/2.12));
    langsButton->addEventListener(TouchEvent::CLICK, CLOSURE(this, &SettingsScreen::languagesButtonClicked));

	spTextField langsText = new TextField();
	langsText->attachTo(langsButton);
    langsText->setPosition(langsButton->getSize().x / 2, (langsButton->getSize().y / 2) - (langsButton->getSize().y / 7));

	TextStyle style = TextStyle(game->getResources()->getResFont("Roboto-Regular")).withFontSize(60).withColor(Color::Black).alignMiddle();
	langsText->setStyle(style);

	if(!settings->isMember("language") || !languages->isMember((*settings)["language"].asString())) {
		(*settings)["language"] = "en";
	}

	langsText->setText((*languages)[(*settings)["language"].asString()].asString());

	spTextField langsLabel= new TextField();
	langsLabel->attachTo(this);
	langsLabel->setPosition(Vector2(getStage()->getSize().x/2, langsButton->getPosition().y - getStage()->getSize().y/15));

	TextStyle labelStyle = TextStyle(game->getResources()->getResFont("Roboto-Bold")).withFontSize(54).withColor(Color::Black).alignMiddle();
	langsLabel->setStyle(labelStyle);
	langsLabel->setText((*translations)["languages"].asString());

    _langsButton = langsButton;
    _langsText = langsText;
    _langsLabel = langsLabel;
}

void SettingsScreen::setupMuteButton() {
	Json::Value* settings = Configuration::getInstance().getSettings();
	Json::Value* translations = Configuration::getInstance().getTranslations();

    spSprite muteButton = initActor(new Sprite,
    		arg_resAnim = game->getResources()->getResAnim("settings_button"),
			arg_attachTo = this
    		);
    muteButton->setPosition(Vector2(getStage()->getSize().x/2 - muteButton->getSize().x/2, getStage()->getSize().y/1.37));
    muteButton->addEventListener(TouchEvent::CLICK, CLOSURE(this, &SettingsScreen::muteButtonClicked));

	spTextField muteText = new TextField();
	muteText->attachTo(muteButton);
    muteText->setPosition(muteButton->getSize().x / 2, (muteButton->getSize().y / 2) - (muteButton->getSize().y / 7));

	TextStyle style = TextStyle(game->getResources()->getResFont("Roboto-Regular")).withFontSize(60).withColor(Color::Black).alignMiddle();
	muteText->setStyle(style);

	if(!settings->isMember("muted")) {
		(*settings)["muted"] = false;
	}

	if((*settings)["muted"].asBool())
		muteText->setText((*translations)["muted"].asString());
	else
		muteText->setText((*translations)["unmuted"].asString());

	spTextField muteLabel= new TextField();
	muteLabel->attachTo(this);
	muteLabel->setPosition(Vector2(getStage()->getSize().x/2, muteButton->getPosition().y - getStage()->getSize().y/15));

	TextStyle labelStyle = TextStyle(game->getResources()->getResFont("Roboto-Bold")).withFontSize(54).withColor(Color::Black).alignMiddle();
	muteLabel->setStyle(labelStyle);
	muteLabel->setText((*translations)["sound"].asString());

    _muteButton = muteButton;
    _muteText = muteText;
    _muteLabel = muteLabel;
}

void SettingsScreen::backButtonClicked(Event* ev) {
	logs::messageln("back button clicked");
	screenSwitcherPtr->switchScreen("MainMenu");
}

void SettingsScreen::languagesButtonClicked(Event* ev) {
	logs::messageln("settings button clicked");
	Json::Value* languages = Configuration::getInstance().getLanguages();

	if(languages->size() < 2) return;

	Json::Value* settings = Configuration::getInstance().getSettings();

	Json::Value::Members languages_index = languages->getMemberNames();

	for(Json::Value::Members::iterator it = languages_index.begin(); it != languages_index.end(); ++it) {
		if(strcmp(it->data(), (*settings)["language"].asCString()) == 0) {
			if(it+1 == languages_index.end()) (*settings)["language"] = languages_index.begin()->data();
			else (*settings)["language"] = (it+1)->data();
			break;
		}
	}

	_langsText->setText((*languages)[(*settings)["language"].asString()].asString());

	Configuration::getInstance().save();
}

void SettingsScreen::muteButtonClicked(Event* ev) {
	logs::messageln("mute button clicked");

	Json::Value* settings = Configuration::getInstance().getSettings();
	Json::Value* translations= Configuration::getInstance().getTranslations();

	if(!settings->isMember("muted")) {
		(*settings)["muted"] = false;
	} else {
		(*settings)["muted"] = !(*settings)["muted"].asBool();
	}

	if((*settings)["muted"].asBool())
		_muteText->setText((*translations)["muted"].asString());
	else
		_muteText->setText((*translations)["unmuted"].asString());

	game->getMusicPlayer()->setMuted((*settings)["muted"].asBool());

	Configuration::getInstance().save();
}
