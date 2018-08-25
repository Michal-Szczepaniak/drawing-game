#include "GameScreen.h"

#include "oxygine/core/gl/oxgl.h"
#include "Game.h"

using namespace oxygine;

GameScreen::GameScreen() {
	level = NULL;

	setupDrawingSpace();
	setupImage();
	setupControls();
}

void GameScreen::setupControls() {
//	spSprite finish = initActor(new Sprite,
//			arg_resAnim = ::getGameResources()->getResAnim("mainmenu_about_button"),
//			arg_attachTo = this,
//			arg_size = Vector2(getStage()->getSize().x /40, getStage()->getSize().x /40),
//			arg_pos = Vector2(getStage()->getSize().x/2 - getStage()->getSize().x /40/2, getStage()->getSize().y/40)
//			);
//	finish->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameScreen::finishButtonClicked));
//	_finishButton = finish;
}

void GameScreen::setupDrawingSpace() {
	color = Color(255, 255, 255, 32);

	Vector2 size(getStage()->getSize().x/2 - getStage()->getSize().x/20/2, getStage()->getSize().y);

	texture = IVideoDriver::instance->createTexture();
	texture->init((int)size.x, (int)size.y, TF_R8G8B8A8, true);

	preview = new Sprite;
	preview->attachTo(this);
	preview->setPosition(getStage()->getSize().x/2 + getStage()->getSize().x/20/2, 0);

	AnimationFrame frame;
	Diffuse df;
	df.base = texture;
//	df.premultiplied = false;
	frame.init(0, df,
			   RectF(0, 0, size.x / texture->getWidth(), size.y / texture->getHeight()),
			   RectF(Vector2(0, 0), size), size);
	preview->setAnimFrame(frame);
}

void GameScreen::setupImage() {
	_image = initActor(new Sprite,
			arg_attachTo = this
    		);
}

void GameScreen::dumpToFile(spNativeTexture texture, std::string filename) {
	GLubyte *pixels = NULL;

#if __SAILFISHOS__
	int width = preview->getSize().y*getStage()->getScaleY();
	int height = preview->getSize().x*getStage()->getScaleX();
#else
	int width = preview->getSize().x*getStage()->getScaleX();
	int height = preview->getSize().y*getStage()->getScaleY();
#endif
//	printf("%d %d\n", width, height);
	pixels = (GLubyte*) malloc(3 * width * height);

#if __SAILFISHOS__
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
#else
	glReadPixels(preview->getPosition().x, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
#endif


    size_t i, j, k, cur;
    enum Constants { max_filename = 256 };
    char destfilename[max_filename];
    snprintf(destfilename, max_filename, "%s.ppm", filename.c_str());
    FILE *f = fopen(destfilename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            cur = 3 * ((height - i - 1) * width + j);
            fprintf(f, "%3d %3d %3d ", pixels[cur], pixels[cur + 1], pixels[cur + 2]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
	free(pixels);
}

int GameScreen::countRepeatTimes(Vector2 oldV, Vector2 newV) {
	Vector2 diff(oldV.x - newV.x, oldV.y - newV.y);
	int count = sqrt((diff.x*diff.x) + (diff.y*diff.y));
	return count == 0 ? 1 : count;
}

void GameScreen::setLevel(Json::Value* level) {
	this->level = level;
	logs::messageln("image %d", level);
	_image->setResAnim(::getGameResources()->getResAnim(level->asCString()));
	_image->setSize(getStage()->getSize().x/2 - getStage()->getSize().x/20/2, getStage()->getSize().y);
}
