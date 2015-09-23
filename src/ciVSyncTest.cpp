// uncomment ONLY ONE of the below
//#define HOST_OPENFRAMEWORKS
#define HOST_CINDER

#include "common.h"

class VSyncTest : public App {
public:
	void setup() override {
		// init file logging
		ci::log::LogManager::instance()->enableFileLogging(msa::vsynctest::getLogPath());

		msa::vsynctest::init();

		// set any key to toggle fullscreen
		ci::app::getWindow()->getSignalKeyDown().connect(0, [&](ci::app::KeyEvent & event) {
			ci::app::setFullScreen(!ci::app::isFullScreen());
		});
	}

	void draw() override {
		gl::clear(Color::black());
		gl::color(Color::white());

		msa::vsynctest::renderStart();

		// draw text
		TextLayout textLayout;
		textLayout.clear(Color(Color::black()));
		textLayout.setFont(Font("Arial", 18));
		textLayout.setColor(Color::white());
		textLayout.addLine(msa::vsynctest::getAllDisplayStatsStr());
		gl::draw(gl::Texture2d::create(textLayout.render(true, true)), vec2(10, 10));

		msa::vsynctest::logAllStats();

		msa::vsynctest::renderEnd();
	}

};

// This line tells Cinder to actually create and run the application.
CINDER_APP(VSyncTest, RendererGl)