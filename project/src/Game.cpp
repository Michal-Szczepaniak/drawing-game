#include "Helpers/ScreenSwitcher.h"
#include "ResFontFT.h"
#include "Helpers/Configuration.h"
#include "sound/SoundPlayer.h"
#include "sound/SoundSystem.h"
#include "MusicPlayer.h"

//it is our resources
//in real project you would have more than one Resources declarations.
//It is important on mobile devices with limited memory and you would load/unload them
Resources gameResources;
MusicPlayer* musicPlayer;

Resources* getGameResources() {
	return &gameResources;
}

MusicPlayer* getMusicPlayer() {
	return musicPlayer;
}

void game_preinit() {}

//called from main.cpp
void game_init() {
	ResFontFT::initLibrary();

	SoundSystem::create()->init(1);
	SoundPlayer::initialize();

    //load xml file with resources definition
    gameResources.loadXML("res_" + (*Configuration::getInstance().getResolution())["name"].asString() + ".xml");
    gameResources.loadXML("images.xml");
    gameResources.loadXML("music.xml");

    musicPlayer = new MusicPlayer();

    //lets create our client code simple actor
    //spMainActor was defined above as smart intrusive pointer (read more: http://www.boost.org/doc/libs/1_60_0/libs/smart_ptr/intrusive_ptr.html)
    //spMainActor actor = new MainActor;

    //and add it to Stage as child
    ScreenSwitcher::getInstance().registerScreens();
}


//called each frame from main.cpp
void game_update() {
	musicPlayer->update();
}

//called each frame from main.cpp
void game_destroy() {
    //free previously loaded resources
	SoundPlayer::free();
	SoundSystem::free();
    gameResources.free();
    ResFontFT::freeLibrary();
}
