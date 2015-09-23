#pragma once

class FrameTimerBase {
public:
	virtual ~FrameTimerBase() {}

	virtual std::string getNameStr() const = 0;
	virtual double getResolutionNS() const = 0;
	virtual void renderStart() = 0;
	virtual void renderEnd() = 0;

	static std::string getTimeStr() {
		std::string s;
		s += "Frame:	" + msaToString(msaGetElapsedFrames()) + "	";
		s += "Time:	" + msaToStringFixedDigits(msaGetElapsedSeconds()) + "	";
		return s;
	}

	std::string getResolutionStr() const {
		return getNameStr() + "	Resolution:	" + msaToStringFixedDigits(getResolutionNS()) + " ns";
	}

	std::string getStatsDetailedStr() const {
		std::string s;
		s += "RAW - ";
		s += "Total  : " + msaToStringFixedDigits(frameMS) + " ms	";
		s += "Render : " + msaToStringFixedDigits(renderMS) + " ms";
		s += "\n";
		s += "AVG - ";
		s += "Total  : " + msaToStringFixedDigits(frameMSAvg) + " ms	";
		s += "Render : " + msaToStringFixedDigits(renderMSAvg) + " ms";
		s += "\n";
		return s;
	}

	std::string getStatsCompactStr() const {
		std::string s;
		s += "Delta:	";
		s += getNameStr() + "	";
		s += "Total:	" + msaToStringFixedDigits(frameMS) + "	";
		s += "Render:	" + msaToStringFixedDigits(renderMS);
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
