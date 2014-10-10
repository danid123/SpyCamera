#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//PIR sensor setup
    wiringPiSetup();
    
    sensorRead = 15;
    timesMoved = 0;
    sensorValue = 0;
    snapCounter = 0;
   
    
    pinMode(15,INPUT);
    ofSleepMillis(2500);
    
    //camera setup
    camWidth 		= 320;	// try to grab at this size.
	camHeight 		= 240;
	
    //we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl; 
        }
	}
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);	
	ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void ofApp::update(){
    
    //PIR update
    //int sensorValue = 0;
    //int snapCounter = 0;
    sensorValue = digitalRead(15);
    ofLog() << sensorValue;

    //ofSleepMillis(5);
    
	//video update
	ofBackground(255,255,255);
	
	vidGrabber.update();
	//vidGrabber.isFrameNew() && sensorValue==1
        if (sensorValue==1 && vidGrabber.isFrameNew()){
            vidImage.grabScreen(0,0,1000,1000);
            
            string fileName = "snapshot_"+ofToString(10000+snapCounter)+".png";
            vidImage.saveImage(fileName);
            sprintf(snapString, "saved %s", fileName.c_str());
            snapCounter++;
            sensorValue = 0;
            
        }
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(20,20);
	videoTexture.draw(20+camWidth,20,camWidth,camHeight);
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
