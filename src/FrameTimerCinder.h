#pragma once

#include "FrameTimerBase.h"

#if (defined( CINDER_MSW ) || defined( CINDER_WINRT))
	#include <windows.h>
#endif

class FrameTimerCinder : public FrameTimerBase {
public:
	FrameTimerCinder() {
		renderStartTime = ci::app::getElapsedSeconds();
	}

	std::string getNameStr() const override {
		return "cinder internal (QueryPerformanceCounter)";
	}

	double getResolutionNS() const override {
#if (defined( CINDER_MSW ) || defined( CINDER_WINRT))
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		return 1000000000./freq.QuadPart;
#else
		return 0;
#endif
	}

	void renderStart() override {
		auto now = ci::app::getElapsedSeconds();
		frameMS = (now - renderStartTime) * 1000;
		renderStartTime = now;
	}

	void renderEnd() override {
		renderMS = (ci::app::getElapsedSeconds() - renderStartTime) * 1000;
		updateAvgs();
	}


private:
	double	renderStartTime;
};
