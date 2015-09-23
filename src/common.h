/*
	trying to unify code to be agnostic of openframeworks or cinder (or any other platform host)
	#define HOST_CINDER or HOST_OPENFRAMEWORKS before including this
*/

#pragma once

#include "utils.h"

#include "FrameTimerInternal.h"
#include "FrameTimerChronoHigh.h"
#include "FrameTimerChronoSystem.h"

namespace msa {
	namespace vsynctest {

		// init app name and version
		const std::string kAppName = std::string(msaHostPrefix) + "VSyncTest";
		const int kVersion = 9;
		const std::string kVersionString = kAppName + " v" + msaToString(kVersion);

		std::vector< std::shared_ptr<FrameTimerBase> >	timers;


		//--------------------------------------------------------------
		const std::string getLogPath() {
			return (boost::filesystem::current_path() / boost::filesystem::path(kAppName + "_Logs") / boost::filesystem::path(kAppName + "_" + getCurrentDateTimeString() + ".log")).string();
		}

		//--------------------------------------------------------------
		void init() {
			msaLog("Starting: " + kVersionString);

			msaEnableVSync(true);

			timers.push_back(std::make_shared<FrameTimerInternal>());
			timers.push_back(std::make_shared<FrameTimerChronoSystem>());
			timers.push_back(std::make_shared<FrameTimerChronoHigh>());

			for (auto t : timers) msaLog(t->getResolutionStr());
		}

		//--------------------------------------------------------------
		void renderStart() {
			for (auto t : timers) t->renderStart();
		}

		//--------------------------------------------------------------
		std::string getAllDisplayStatsStr() {
			std::string str;
			str += kVersionString + "\n";
			str += FrameTimerBase::getTimeStr() + "\n";
			str += "--------------------------------------------------------------------------------------------------------\n";

			// add all text
			for (auto t : timers) {
				str += t->getResolutionStr() + "\n";
				str += t->getStatsDetailedStr() + "\n";
				str += "\n";
			}
			return str;
		}

		//--------------------------------------------------------------
		void logAllStats() {
			//msaLog(FrameTimerBase::getTimeStr());
			for (auto t : timers) {
				msaLog(t->getStatsCompactStr());
			}
		}

		//--------------------------------------------------------------
		void renderEnd() {
			for (auto t : timers) t->renderEnd();
		}
	}
}