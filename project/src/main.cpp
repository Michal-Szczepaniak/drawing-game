#include "oxygine/core/oxygine.h"
#include "oxygine/core/file.h"
#include "ox/Stage.hpp"
#include "ox/DebugActor.hpp"
#include "Game.h"
#include "Helpers/Configuration.h"

using namespace oxygine;

namespace oxygine
{
	namespace file
	{
		extern bool _fsInitialized;
	}
}

// This function is called each frame
int mainloop(std::shared_ptr<Game> game)
{
    // Update engine-internal components
    // If input events are available, they are passed to Stage::instance.handleEvent
    // If the function returns true, it means that the user requested the application to terminate
    bool done = core::update();

    // It gets passed to our example game implementation
    game->update();

    // Update our stage
    // Update all actors. Actor::update will also be called for all its children
    getStage()->update();

    if (core::beginRendering())
    {
        Color clearColor(32, 32, 32, 255);
        Point size = core::getDisplaySize();
        Rect viewport(Point(0, 0), size);
        // Render all actors inside the stage. Actor::render will also be called for all its children
        getStage()->render(clearColor, viewport);

        core::swapDisplayBuffers();
    }

    return done ? 1 : 0;
}

// Application entry point
void run()
{
    ObjectBase::__startTracingLeaks();
    std::shared_ptr<Game> game(new Game());

#if RELEASE
    oxygine::file::_fsInitialized = true;
    oxygine::file::wfs().setPath("/usr/share/Graphie");
    oxygine::file::mount(&oxygine::file::wfs());
#endif

    // Initialize Oxygine's internal stuff
    core::init_desc desc;
    desc.title = "Graphie";
#if RELEASE
    desc.companyName = "Mister_Magister";
    desc.appName = "Graphie";
#endif
    desc.vsync = true;

#if OXYGINE_SDL || OXYGINE_EMSCRIPTEN
    // The initial window size can be set up here on SDL builds
    desc.w = 1280;
    desc.h = 720;
    // Marmalade settings can be modified from the emulator's menu
#endif

    game->preInit(game);
    core::init(&desc);

    Json::Value* resolutions = Configuration::getInstance().getResolutions();

    int best = 0,cur = core::getDisplaySize().y;
    for( Json::Value::const_iterator itr = resolutions->begin() ; itr != resolutions->end() ; itr++ ) {
    	if(abs((*resolutions)[itr.index()]["resolutions"][0].asInt() - cur) < abs((*resolutions)[best]["resolutions"][0].asInt() - cur)) best = itr.index();
    }

    logs::messageln("best resolution: %d x %d", (*resolutions)[best]["resolutions"][0].asInt(), (*resolutions)[best]["resolutions"][1].asInt());
    Configuration::getInstance().setResolutions(best);

    // Create the stage. Stage is a root node for all updateable and drawable objects
    Stage::instance = new Stage(true);

    Point size = core::getDisplaySize();
#if __SAILFISHOS__
	size.x = (*resolutions)[best]["resolutions"][0].asInt();
	size.y = (*resolutions)[best]["resolutions"][1].asInt();
    log::messageln("scale %f %f", (float)core::getDisplaySize().x / size.y, (float)core::getDisplaySize().y / size.x);
    getStage()->setScale((float)core::getDisplaySize().x / size.y, (float)core::getDisplaySize().y / size.x);
    getStage()->setPosition((float)core::getDisplaySize().x, 0);
    getStage()->setRotationDegrees(90.0f);
#endif
    getStage()->setSize(size);

    // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff
    DebugActor::show();

    // Initializes our example game. See example.cpp
    game->init();

#ifdef EMSCRIPTEN
    /*
    If you build for Emscripten, mainloop is called automatically and shouldn't be called here.
    See emscripten_set_main_loop in the EMSCRIPTEN section below
    */
    return;
#endif

    // This is the main game loop.
    while (true)
    {
        int done = mainloop(game);
        if (done)
            break;
    }
    /*
     If we get here, the user has requested the Application to terminate.
     We dump and log all our created objects that have not been freed yet
    */
    ObjectBase::dumpCreatedObjects();

    /*
    Let's clean up everything right now and call ObjectBase::dumpObjects() again.
    We need to free all allocated resources and delete all created actors.
    All actors/sprites are smart-pointer objects and don't need to be removed by hand.
    But now we want to delete it by hand.
    */

    // See example.cpp for the shutdown function implementation
    game->destroy();

    //renderer.cleanup();

    // Releases all internal components and the stage
    core::release();

    // The dump list should be empty by now,
    // we want to make sure that there aren't any memory leaks, so we call it again.
    ObjectBase::dumpCreatedObjects();

    ObjectBase::__stopTracingLeaks();
    //end
}

#ifdef OXYGINE_SDL

#include "SDL_main.h"
#include "SDL.h"

extern "C"
{
//    void one(void* param) { mainloop(); }
//    void oneEmsc() { mainloop(); }

    int main(int argc, char* argv[])
    {

#if __SAILFISHOS__
    	SDL_SetHint(SDL_HINT_QTWAYLAND_CONTENT_ORIENTATION, "landscape");
#endif

    	run();

#if EMSCRIPTEN
        emscripten_set_main_loop(oneEmsc, 0, 0);
#endif

        return 0;
    }
};
#endif
