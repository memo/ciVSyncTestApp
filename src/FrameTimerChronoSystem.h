#pragma once

#include "FrameTimerBase.h"
#include <chrono>

class FrameTimerChronoSystem : public FrameTimerBase {
public:
	FrameTimerChronoSystem() {
		renderStartTime = std::chrono::system_clock::now();
	}

	std::string getNameStr() const override {
		return "chrono::system_clock";
	}

	double getResolutionNS() const override {
		std::chrono::duration<double, std::nano> ns = std::chrono::system_clock::duration(1);
		return ns.count();
	}

	void renderStart() override {
		auto now = std::chrono::system_clock::now();
		frameMS = 0.000001 * (double)std::chrono::duration_cast<std::chrono::nanoseconds>(now - renderStartTime).count();
		renderStartTime = now;
	}

	void renderEnd() override {
		renderMS = 0.000001 * (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - renderStartTime).count();
		updateAvgs();
	}


private:
	typedef std::chrono::system_clock::time_point	TimePointT;
	TimePointT	renderStartTime;
};
