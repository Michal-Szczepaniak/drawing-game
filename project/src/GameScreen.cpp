#include "GameScreen.h"

#include "core/gl/oxgl.h"
#include "Game.h"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace oxygine;
using namespace cv;

GameScreen::GameScreen() {
	level = NULL;

	setupDrawingSpace();
	setupImage();
	setupControls();
}

void GameScreen::setupControls() {
	spSprite finish = initActor(new Sprite,
			arg_resAnim = ::getGameResources()->getResAnim("mainmenu_about_button"),
			arg_attachTo = this,
			arg_size = Vector2(getStage()->getSize().x /40, getStage()->getSize().x /40),
			arg_pos = Vector2(getStage()->getSize().x/2 - getStage()->getSize().x /40/2, getStage()->getSize().y/40)
			);
	finish->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameScreen::finishButtonClicked));
	_finishButton = finish;
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
	df.premultiplied = false;
	frame.init(0, df,
			   RectF(0, 0, size.x / texture->getWidth(), size.y / texture->getHeight()),
			   RectF(Vector2(0, 0), size), size);
	preview->setAnimFrame(frame);


	preview->addEventListener(TouchEvent::MOVE, CLOSURE(this, &GameScreen::onMove));
	preview->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &GameScreen::onDown));
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

void GameScreen::onDown(Event* ev) {
	color = Color(rand() % 255, rand() % 255, rand() % 255, 255);

	TouchEvent* te = (TouchEvent*)ev;
	_oldPos = te->position;

	onMove(ev);
}

void GameScreen::onMove(Event* ev){
	TouchEvent* te = (TouchEvent*)ev;

	if(!te->getPointer()->isPressed()) return;

	STDRenderer& renderer = *STDRenderer::instance;

	renderer.begin(texture);

	ResAnim* brush = ::getGameResources()->getResAnim("brush");
	AnimationFrame frame = brush->getFrame(0);
	const Diffuse& df = frame.getDiffuse();
	renderer.setTexture(df.base, 1);
	renderer.setBlendMode(blend_premultiplied_alpha);

	for(int i = 0; i <= countRepeatTimes(_oldPos, te->position); i++) {
		RectF destRect(Vector2(_oldPos.x - (_oldPos.x - te->localPosition.x)/countRepeatTimes(_oldPos, te->position)*i,
				_oldPos.y - (_oldPos.y - te->localPosition.y)/countRepeatTimes(_oldPos, te->position)*i) - Vector2(16, 16), Vector2(32, 32));
		renderer.draw(color, frame.getSrcRect(), destRect);
	}
	renderer.end();

	_oldPos = te->position;
}

int GameScreen::countRepeatTimes(Vector2 oldV, Vector2 newV) {
	Vector2 diff(oldV.x - newV.x, oldV.y - newV.y);
	int count = sqrt((diff.x*diff.x) + (diff.y*diff.y));
	return count == 0 ? 1 : count;
}

void GameScreen::finishButtonClicked(Event* event) {
	log::messageln("finish");
	dumpToFile(texture, "tmp");

	Mat img_1 = imread( "tmp.ppm", CV_LOAD_IMAGE_GRAYSCALE );
	Mat img_2 = imread( "chapters/tutorial/1/tutorial_1_1.png", CV_LOAD_IMAGE_GRAYSCALE );

	if( !img_1.data || !img_2.data )
	{ log::messageln(" --(!) Error reading images %d %d\n", img_1.data, img_2.data); return; }

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;

	SurfFeatureDetector detector( minHessian );

	std::vector<KeyPoint> keypoints_1, keypoints_2;

	detector.detect( img_1, keypoints_1 );
	detector.detect( img_2, keypoints_2 );

	//-- Step 2: Calculate descriptors (feature vectors)
	SurfDescriptorExtractor extractor;

	Mat descriptors_1, descriptors_2;

	extractor.compute( img_1, keypoints_1, descriptors_1 );
	extractor.compute( img_2, keypoints_2, descriptors_2 );

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match( descriptors_1, descriptors_2, matches );

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < descriptors_1.rows; i++ )
	{ double dist = matches[i].distance;
	if( dist < min_dist ) min_dist = dist;
	if( dist > max_dist ) max_dist = dist;
	}

	printf("-- Max dist : %f \n", max_dist );
	printf("-- Min dist : %f \n", min_dist );

	//-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
	//-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
	//-- small)
	//-- PS.- radiusMatch can also be used here.
	std::vector< DMatch > good_matches;

	for( int i = 0; i < descriptors_1.rows; i++ )
	{ if( matches[i].distance <= max(2*min_dist, 0.02) )
	{ good_matches.push_back( matches[i]); }
	}

	log::messageln( "matches %d", good_matches.size());
}

void GameScreen::setLevel(Json::Value* level) {
	this->level = level;
	log::messageln("image %d", level);
	_image->setResAnim(::getGameResources()->getResAnim(level->asCString()));
	_image->setSize(getStage()->getSize().x/2 - getStage()->getSize().x/20/2, getStage()->getSize().y);
}
