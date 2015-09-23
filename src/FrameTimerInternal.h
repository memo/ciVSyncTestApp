#pragma once

#include "FrameTimerBase.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
#include <windows.h>
#endif

class FrameTimerInternal : public FrameTimerBase {
public:
	FrameTimerInternal() {
		renderStartTime = msaGetElapsedSeconds();
	}

	std::string getNameStr() const override {
		return "QueryPerformanceCounter";
	}

	double getResolutionNS() const override {
#if defined( __WIN32__ ) || defined( _WIN32 )
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		return 1000000000. / freq.QuadPart;
#else
		return 0;
#endif
	}

	void renderStart() override {
		auto now = msaGetElapsedSeconds();
		frameMS = (now - renderStartTime) * 1000;
		renderStartTime = now;
	}

	void renderEnd() override {
		renderMS = (msaGetElapsedSeconds() - renderStartTime) * 1000;
		updateAvgs();
	}


private:
	double	renderStartTime;
};
