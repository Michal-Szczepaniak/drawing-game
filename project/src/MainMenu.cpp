#include "MainMenu.h"
#include "ScreenSwitcher.h"

#include "core/gl/oxgl.h"
#include "Game.h"
using namespace oxygine;

MainMenu::MainMenu() {
	setupStartButton();
	setupSettingsButton();
	setupHelpButton();
	setupAboutButton();
}

void MainMenu::setupStartButton() {
    spSprite button = new Sprite();
    button->setResAnim(::getGameResources()->getResAnim("mainmenu_button"));

//    button->setSize(getStage()->getSize().x / 3.31, getStage()->getSize().y / 8.5);
    log::messageln("button scale: %f", getStage()->getScale().x);
//    button->setScale(getStage()->getScale());
    Vector2 pos(getStage()->getSize().x / 2 - button->getSize().x / 2, getStage()->getSize().y / 2 - button->getSize().y / 2 - getStage()->getSize().y / 35);
    button->setPosition(pos);

    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MainMenu::startButtonClicked));

    addChild(button);
    _startButton = button;

    spTextField text = new TextField();

    text->attachTo(button);

    text->setPosition(button->getSize().x / 2, (button->getSize().y / 2) - (button->getSize().y / 8));


    TextStyle style = TextStyle(::getGameResources()->getResFont("Roboto-Regular")).withFontSize(30).withColor(Color::Black).alignMiddle();
    text->setStyle(style);
    text->setText("start");

    _startText = text;
}

void MainMenu::setupSettingsButton() {
    //create button Sprite
    spSprite button = new Sprite();

    //setup it:
    //set button.png image. Resource 'button' defined in 'res.xml'
    button->setResAnim(::getGameResources()->getResAnim("mainmenu_button"));

    //centered button at screen
//    button->setSize(_startButton->getSize());
    Vector2 pos(_startButton->getPosition().x, _startButton->getPosition().y + _startButton->getSize().y + getStage()->getSize().y / 14.5);
    button->setPosition(pos);

    //register  click handler to button
    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MainMenu::settingsButtonClicked));

    //attach button as child to current actor
    addChild(button);
    _optionsButton = button;

    //create TextField Actor
    spTextField text = new TextField();
    //attach it as child to button
    text->attachTo(button);
    //centered in button
    text->setPosition(button->getSize().x / 2, (button->getSize().y / 2) - (button->getSize().y / 8));

    //initialize text style
    TextStyle style = TextStyle(::getGameResources()->getResFont("Roboto-Regular")).withFontSize(30).withColor(Color::Black).alignMiddle();
    text->setStyle(style);
    text->setText("opcje");

    _optionsText = text;
}

void MainMenu::setupHelpButton() {
    //create button Sprite
    spSprite button = new Sprite();

    //setup it:
    //set button.png image. Resource 'button' defined in 'res.xml'
    button->setResAnim(::getGameResources()->getResAnim("mainmenu_button"));

    //centered button at screen
//    button->setSize(_startButton->getSize());
    Vector2 pos(_startButton->getPosition().x, _optionsButton->getPosition().y + _startButton->getSize().y + getStage()->getSize().y / 14.5);
    button->setPosition(pos);

    //register  click handler to button
    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MainMenu::buttonClicked));

    //attach button as child to current actor
    addChild(button);
    _helpButton = button;

    //create TextField Actor
    spTextField text = new TextField();
    //attach it as child to button
    text->attachTo(button);
    //centered in button
    text->setPosition(button->getSize().x / 2, (button->getSize().y / 2) - (button->getSize().y / 8));

    //initialize text style
    TextStyle style = TextStyle(::getGameResources()->getResFont("Roboto-Regular")).withFontSize(30).withColor(Color::Black).alignMiddle();
    text->setStyle(style);
    text->setText("help");

    _helpText = text;
}

void MainMenu::setupAboutButton() {
    //create button Sprite
    spSprite button = new Sprite();

    //setup it:
    //set button.png image. Resource 'button' defined in 'res.xml'
    button->setResAnim(::getGameResources()->getResAnim("mainmenu_about_button"));

    //centered button at screen
    button->setSize(getStage()->getSize().x / 7, getStage()->getSize().y / 13);
    Vector2 pos(getStage()->getSize().x - button->getSize().x, getStage()->getSize().y - button->getSize().y);
    button->setPosition(pos);

    //register  click handler to button
    button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MainMenu::buttonClicked));

    //attach button as child to current actor
    addChild(button);
    _aboutButton = button;

    //create TextField Actor
    spTextField text = new TextField();
    //attach it as child to button
    text->attachTo(button);
    //centered in button
    text->setPosition(button->getSize().x / 2, (button->getSize().y / 2) - (button->getSize().y / 8));

    //initialize text style
    TextStyle style = TextStyle(::getGameResources()->getResFont("Roboto-Regular")).withFontSize(30).withColor(Color::Black).alignMiddle();
    text->setStyle(style);
    text->setText("about");

    _aboutText = text;
}

void MainMenu::startButtonClicked(Event* event) {
	log::messageln("start button clicked");
	ScreenSwitcher::getInstance().switchScreen("ChapterScreen");
}

void MainMenu::settingsButtonClicked(Event* event) {
	log::messageln("settings button clicked");
	ScreenSwitcher::getInstance().switchScreen("SettingsScreen");
}

void MainMenu::buttonClicked(Event* event) {
	log::messageln("button clicked");
}
