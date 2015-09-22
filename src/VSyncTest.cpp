#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "FrameTimerChronoHigh.h"
#include "FrameTimerChronoSystem.h"

using namespace ci;
using namespace ci::app;

static const std::string kAppName = "VSyncTest";
static const int kVersion = 5;
static const std::string kVersionString = kAppName + " v" + ci::toString(kVersion);

class VSyncTest : public App {
public:
	void setup() override;
	void draw() override;

private:
	std::vector< std::shared_ptr<FrameTimerBase> >	timers;
};


const std::string getCurrentDateTimeString()
{
	time_t timeSinceEpoch = time(NULL);
	struct tm *now = localtime(&timeSinceEpoch);

	char result[100];
	strftime(result, sizeof(result), "%Y-%m-%d-%H-%M-%S", now);

	return result;
}


void VSyncTest::setup() {
	ci::log::LogManager::instance()->enableFileLogging(boost::filesystem::current_path() / boost::filesystem::path(kAppName + "_Logs") / boost::filesystem::path(kAppName + "_" + getCurrentDateTimeString() + ".log"));
	ci::log::LogManager::instance()->enableConsoleLogging();

	CI_LOG_I("Starting " + kVersionString);

	ci::gl::enableVerticalSync(true);
	ci::app::getWindow()->getSignalKeyDown().connect(0, [&](ci::app::KeyEvent & event)
	{
		ci::app::setFullScreen(!ci::app::isFullScreen());
	});

	timers.push_back(std::make_shared<FrameTimerChronoSystem>());
	timers.push_back(std::make_shared<FrameTimerChronoHigh>());

	for(auto t : timers) CI_LOG_I(t->getPrecisionStr());
}

void VSyncTest::draw()
{
	// start all timers
	for(auto t : timers) {
		t->renderStart();
	}


	gl::clear(Color::black());
	gl::color(Color::white());

	std::string str;
	str += kVersionString + "\n";
	str += FrameTimerBase::getTimeDetailedStr() + "\n";
	str += "\n";

	// add all text
	for(auto t : timers) {
		str += t->getPrecisionStr()+ "\n";
		str += t->getStatsDetailedStr() + "\n";
		str += "\n";
	}

	// draw text
	TextLayout textLayout;
	textLayout.clear(Color(Color::black()));
	textLayout.setFont(Font("Arial", 18));
	textLayout.setColor(Color::white());
	textLayout.addLine(str);
	gl::draw( gl::Texture2d::create( textLayout.render( true, true) ), vec2( 10, 10 ) );


	// log
	CI_LOG_I(FrameTimerBase::getTimeCompactStr());
	for(auto t : timers) {
		CI_LOG_I(t->getStatsCompactStr());
	}


	// end all timers
	for(auto t : timers) {
		t->renderEnd();
	}
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(VSyncTest, RendererGl)