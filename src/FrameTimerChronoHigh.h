#pragma once

#include "FrameTimerBase.h"
#include <chrono>

class FrameTimerChronoHigh : public FrameTimerBase {
public:
	FrameTimerChronoHigh() {
		renderStartTime = std::chrono::high_resolution_clock::now();
	}

	std::string getNameStr() const override {
		return "chrono::high_resolution_clock";
	}

	double getPrecisionNS() const override {
		std::chrono::duration<double, std::nano> ns = std::chrono::high_resolution_clock::duration(1);
		return ns.count();
	}

	void renderStart() override {
		auto now = std::chrono::high_resolution_clock::now();
		frameMS = (double)std::chrono::duration_cast<std::chrono::milliseconds>(now - renderStartTime).count();
		renderStartTime = now;
	}

	void renderEnd() override {
		renderMS = (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - renderStartTime).count();
		updateAvgs();
	}


private:
	typedef std::chrono::high_resolution_clock::time_point	TimePointT;
	TimePointT	renderStartTime;
};
