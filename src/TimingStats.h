#pragma once

#include "cinder/Utilities.h"
#include <chrono>

inline double lerpDown(double newValue, double oldValue, double dropSpeed = 1, double snapThresh = 100) {
	return (newValue > oldValue) || (fabs(newValue - oldValue) > snapThresh) ? newValue : oldValue - dropSpeed;
}

class TimingStats {
public:
	TimingStats() {
		renderStartTime = std::chrono::high_resolution_clock::now();
	}

	std::string getPrecisionStr() const {
		std::chrono::duration<double, std::nano> ns = std::chrono::high_resolution_clock::duration(1);
		return ci::toString(ns.count()) + " ns";
//		return ci::toString(1000000000.0 * std::chrono::high_resolution_clock::period::num / std::chrono::high_resolution_clock::period::den) + " ns";
	}

	std::string getStatsDetailedStr() const {
		std::string s;
		s += "Time:	" + ci::toString(ci::app::getElapsedSeconds()) + "\n";
		s += "Frame: " + ci::toString(ci::app::getElapsedFrames()) + "\n";
		s += "RAW         - ";
		s += "Total  : " + ci::toString((int)frameMS) + " ms, ";
		s += "Render : " + ci::toString((int)renderMS) + " ms";
		s += "\n";
		s += "SMOOTH - ";
		s += "Total  : " + ci::toString((int)frameMSSmooth) + " ms, ";
		s += "Render : " + ci::toString((int)renderMSSmooth) + " ms";
		s += "\n";
		return s;
	}

	std::string getStatsCompactStr() const {
		std::string s;
		s += "Time:	" + ci::toString(ci::app::getElapsedSeconds()) + "	";
		s += "Frame:	" + ci::toString(ci::app::getElapsedFrames()) + "	";
		s += "RAW:	";
		s += "Total:	" + ci::toString((int)frameMS) + "	";
		s += "Render:	" + ci::toString((int)renderMS);
		return s;
	}


	void renderStart() {
		auto now = std::chrono::high_resolution_clock::now();
		frameMS = (double)std::chrono::duration_cast<std::chrono::milliseconds>(now - renderStartTime).count();
		frameMSSmooth = lerpDown(frameMS, frameMSSmooth);
		renderStartTime = now;
	}

	void renderEnd() {
		renderMS = (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - renderStartTime).count();
		renderMSSmooth = lerpDown(renderMS, renderMSSmooth);
	}


private:
	typedef std::chrono::high_resolution_clock::time_point	TimePointT;
	TimePointT	updateStartTime;
	TimePointT	renderStartTime;
	double		frameMSSmooth = 0;
	double		renderMSSmooth = 0;

	double		frameMS = 0;
	double		renderMS = 0;

};
