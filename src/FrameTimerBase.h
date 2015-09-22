#pragma once

#include "cinder/Utilities.h"

class FrameTimerBase {
public:
	virtual ~FrameTimerBase() {}

	virtual std::string getNameStr() const = 0;
	virtual double getPrecisionNS() const = 0;
	virtual void renderStart() = 0;
	virtual void renderEnd() = 0;

	static std::string getTimeDetailedStr() {
		std::string s;
		s += "Time:	" + ci::toString(ci::app::getElapsedSeconds()) + "\n";
		s += "Frame: " + ci::toString(ci::app::getElapsedFrames()) + "\n";
		return s;
	}

	static std::string getTimeCompactStr() {
		std::string s;
		s += "Time:	" + ci::toString(ci::app::getElapsedSeconds()) + "	";
		s += "Frame:	" + ci::toString(ci::app::getElapsedFrames()) + "	";
		return s;
	}


	std::string getPrecisionStr() const {
		return getNameStr() + " precision: " + ci::toString(getPrecisionNS()) + " ns";
	}

	std::string getStatsDetailedStr() const {
		std::string s;
		s += "RAW - ";
		s += "Total  : " + ci::toString(frameMS) + " ms, ";
		s += "Render : " + ci::toString(renderMS) + " ms";
		s += "\n";
		s += "AVG - ";
		s += "Total  : " + ci::toString(frameMSAvg) + " ms, ";
		s += "Render : " + ci::toString(renderMSAvg) + " ms";
		s += "\n";
		return s;
	}

	std::string getStatsCompactStr() const {
		std::string s;
		s += getNameStr() + "	";
		s += "Total:	" + ci::toString(frameMS) + "	";
		s += "Render:	" + ci::toString(renderMS);
		return s;
	}

	void updateAvgs() { 
		frameMSAvg += (frameMS - frameMSAvg) * 0.1;
		renderMSAvg = (renderMS - renderMSAvg) * 0.1;
	}




protected:
	double		frameMSAvg = 0;
	double		renderMSAvg = 0;

	double		frameMS = 0;
	double		renderMS = 0;

};
