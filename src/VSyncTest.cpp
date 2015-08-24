#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "TimingStats.h"

using namespace ci;
using namespace ci::app;

static const std::string kAppName = "VSyncTest";
static const int kVersion = 3;
static const std::string kVersionString = kAppName + " v" + ci::toString(kVersion);

class VSyncTest : public App {
public:
	void setup() override;
	void draw() override;

private:
	std::shared_ptr<TimingStats>	timingStats;
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
	timingStats = std::shared_ptr<TimingStats>(new TimingStats);
	ci::log::LogManager::instance()->enableFileLogging(boost::filesystem::current_path() / boost::filesystem::path(kAppName + "_Logs") / boost::filesystem::path(kAppName + "_" + getCurrentDateTimeString() + ".log"));
	ci::log::LogManager::instance()->enableConsoleLogging();

	CI_LOG_I("Starting " + kVersionString);

	ci::gl::enableVerticalSync(true);
	ci::app::getWindow()->getSignalKeyDown().connect(0, [&](ci::app::KeyEvent & event)
	{
		ci::app::setFullScreen(!ci::app::isFullScreen());
	});
}

void VSyncTest::draw()
{
	gl::clear(ci::Color(0, 0, 0));
	timingStats->renderStart();

	std::string s= kVersionString + "\n" + timingStats->getStatsDetailed();
	ci::gl::drawString(s, ci::vec2(10, 10), ci::Color(1, 1, 1));
	timingStats->renderEnd();
	CI_LOG_I(timingStats->getStatsCompact());
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(VSyncTest, RendererGl)