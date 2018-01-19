#include "mainActor.h"
#include "game.h"
#include "core/gl/oxgl.h"
using namespace oxygine;

MainActor::MainActor() {
    //create button Sprite
    spSprite button = new Sprite();


    //setup it:
    //set button.png image. Resource 'button' defined in 'res.xml'
    button->setResAnim(::getGameResources()->getResAnim("button"));

    //centered button at screen
    Vector2 pos = getStage()->getSize() / 2 - button->getSize() / 2;
    button->setPosition(pos);

    //register  click handler to button
    EventCallback cb = CLOSURE(this, &MainActor::buttonClicked);
    button->addEventListener(TouchEvent::CLICK, cb);

#ifdef CLOSURE_FUNCTION //if your compiler supports lambda

    button->addEventListener(TouchEvent::CLICK, [](Event * e)->void
    {
        log::messageln("button clicked");
    });

#endif

    //attach button as child to current actor
    addChild(button);
    _button = button;



    //create TextField Actor
    spTextField text = new TextField();
    //attach it as child to button
    text->attachTo(button);
    //centered in button
    text->setPosition(button->getSize() / 2);

    //initialize text style
    TextStyle style = TextStyle(::getGameResources()->getResFont("main")).withColor(Color::White).alignMiddle();
    text->setStyle(style);
    text->setText("Click\nMe!");

    _text = text;

//    notify("touch to draw", 100000);

	color = Color(255, 255, 255, 32);

	Vector2 size = getStage()->getSize();

	texture = IVideoDriver::instance->createTexture();
	texture->init((int)size.x, (int)size.y, TF_R8G8B8A8, true);

	preview = new Sprite;
	preview->attachTo(getStage());


	AnimationFrame frame;
	Diffuse df;
	df.base = texture;
	df.premultiplied = false;
	frame.init(0, df,
			   RectF(0, 0, size.x / texture->getWidth(), size.y / texture->getHeight()),
			   RectF(Vector2(0, 0), size), size);
	preview->setAnimFrame(frame);


	getStage()->addEventListener(TouchEvent::MOVE, CLOSURE(this, &MainActor::onMove));
	getStage()->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &MainActor::onDown));
}

void MainActor::buttonClicked(Event* event) {
    //user clicked to button

    //animate button by chaning color
//    _button->setColor(Color::White);
//    _button->addTween(Sprite::TweenColor(Color::Green), 500, 1, true);
//
//    //animate text by scaling
//    _text->setScale(1.0f);
//    _text->addTween(Actor::TweenScale(1.1f), 500, 1, true);
//
//    //and change text
//    _text->setText("Clicked!");

	GLubyte *pixels = NULL;
	int width = getStage()->getSize().x;
	int height = getStage()->getSize().y;
	printf("%d %d\n", width, height);
	pixels = (GLubyte*) malloc(3 * width * height);

	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);


    size_t i, j, k, cur;
    enum Constants { max_filename = 256 };
    char filename[max_filename];
    snprintf(filename, max_filename, "%s%d.ppm", "photo", 0);
    FILE *f = fopen(filename, "w");
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

void MainActor::onDown(Event* ev) {
	color = Color(rand() % 255, rand() % 255, rand() % 255, 255);
	onMove(ev);
}

void MainActor::onMove(Event* ev){
	TouchEvent* te = (TouchEvent*)ev;
	bool left = te->getPointer()->isPressed();
	bool right = te->getPointer()->isPressed(MouseButton_Right);
	if (!left && !right)
		return;

	STDRenderer& renderer = *STDRenderer::instance;

	renderer.begin(texture);
	RectF destRect(te->localPosition - Vector2(16, 16), Vector2(32, 32));

	ResAnim* brush = ::getGameResources()->getResAnim(left ? "brush" : "brush_eraser");
	AnimationFrame frame = brush->getFrame(0);
	const Diffuse& df = frame.getDiffuse();
	renderer.setTexture(df.base, 1);
	if (left) {
		renderer.setBlendMode(blend_premultiplied_alpha);
	}
	else
	{
		color = Color::White;
		renderer.setBlendMode(blend_disabled);
	}


	renderer.draw(color, frame.getSrcRect(), destRect);
	renderer.end();
}
