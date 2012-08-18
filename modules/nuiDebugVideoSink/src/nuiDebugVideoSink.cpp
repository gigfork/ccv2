/////////////////////////////////////////////////////////////////////////////
// Name:        modules/nuiDebugVideoSink.cpp
// Purpose:     Sink to display video
// Author:      Scott Halstvedt
// Copyright:   (c) 2012 NUI Group
/////////////////////////////////////////////////////////////////////////////

#include "nuiDebugVideoSink.h"

MODULE_DECLARE(DebugVideoSink, "native", "Sink to display video");

nuiDebugVideoSink::nuiDebugVideoSink() : nuiModule() {
    MODULE_INIT();

	this->input = new nuiEndpoint(this);
    this->input->setTypeDescriptor(std::string("IplImage"));
    this->setInputEndpointCount(1);
    this->setInputEndpoint(0,this->input);

	dispFrame = NULL;
}

nuiDebugVideoSink::~nuiDebugVideoSink() {
}

void nuiDebugVideoSink::update() {    
	//LOG(NUI_DEBUG, "module update called");
	void* data;
	nuiDataPacket* packet = this->input->getData();
	if(packet == NULL) return;
	packet->unpackData(data);
	IplImage* frame = (IplImage*)data;
	dispFrame = cvCloneImage(frame);
	cvShowImage((this->property("id")).asString().c_str(), dispFrame);
	cv::waitKey(1);
	cvReleaseImage(&dispFrame);
	//delete frame;
}

void nuiDebugVideoSink::start() {
	nuiModule::start();
	LOG(NUI_DEBUG,"starting video sink");
}