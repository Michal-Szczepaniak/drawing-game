#include "Game.h"
#include "ResFontFT.h"
#include "Helpers/Configuration.h"
#include "sound/SoundPlayer.h"
#include "sound/SoundSystem.h"

Game::Game() = default;

void Game::preInit(std::shared_ptr<Game> game) {
    this->game = game;
}

void Game::init() {
    ResFontFT::initLibrary();

    SoundSystem::create()->init(1);
    SoundPlayer::initialize();

    resourcesPtr = std::make_shared<Resources>();
    //load xml file with resources definition
    getResources()->loadXML("res_" + (*Configuration::getInstance().getResolution())["name"].asString() + ".xml");
    getResources()->loadXML("images.xml");
    getResources()->loadXML("music.xml");

    musicPlayerPtr = std::make_shared<MusicPlayer>(resourcesPtr);

    screenSwitcherPtr = std::make_shared<ScreenSwitcher>(game);

    //lets create our client code simple actor
    //spMainActor was defined above as smart intrusive pointer (read more: http://www.boost.org/doc/libs/1_60_0/libs/smart_ptr/intrusive_ptr.html)
    //spMainActor actor = new MainActor;

    //and add it to Stage as child
    screenSwitcherPtr->registerScreens(screenSwitcherPtr);
}

//called each frame from main.cpp
void Game::update() {
    getMusicPlayer()->update();
}

void Game::destroy() {
    //free previously loaded resources
    SoundPlayer::free();
    SoundSystem::free();
    getResources()->free();
    ResFontFT::freeLibrary();
}

ResourcesPtr Game::getResources() {
    return resourcesPtr;
}

MusicPlayerPtr Game::getMusicPlayer() {
    return musicPlayerPtr;
}
