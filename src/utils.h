/*
trying to unify code to be agnostic of openframeworks or cinder (or any other platform host)
#define HOST_CINDER or HOST_OPENFRAMEWORKS before including this
*/

#pragma once


// map defines for basic openframeworks and cinder functions
#if defined(HOST_OPENFRAMEWORKS)
#include "ofMain.h"
#define msaHostPrefix			"of"
#define msaToString				ofToString
#define msaGetElapsedFrames		ofGetFrameNum
#define msaGetElapsedSeconds	ofGetElapsedTimef
#define msaLog(s)				ofLog() << s
#define msaEnableVSync			ofSetVerticalSync



#elif defined(HOST_CINDER)
#include "cinder/Utilities.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

using namespace ci;
using namespace ci::app;
#define msaHostPrefix			"ci"
#define msaToString				toString
#define msaGetElapsedFrames		getElapsedFrames
#define msaGetElapsedSeconds	getElapsedSeconds
#define msaLog					CI_LOG_I
#define msaEnableVSync			ci::gl::enableVerticalSync
#endif


//--------------------------------------------------------------
const std::string getCurrentDateTimeString() {
	time_t timeSinceEpoch = time(NULL);
	struct tm *now = localtime(&timeSinceEpoch);
	char result[100];
	strftime(result, sizeof(result), "%Y-%m-%d-%H-%M-%S", now);
	return result;
}

//--------------------------------------------------------------
const std::string msaToStringFixedDigits(double v) {
	static char sz[255];
	sprintf_s(sz, "%.3f", v);
	return sz;
}