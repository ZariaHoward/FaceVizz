#pragma once

#include "ofMain.h"

#include "ofxCv.h"
using namespace ofxCv;
using namespace cv;

#include "ofxFaceTracker.h"
#include "ofxCameraAnaglyph.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofVideoGrabber cam;
        ofxFaceTracker tracker;
        ofVec2f position;
        float scale;
        ofVec3f orientation;
        ofMatrix4x4 rotationMatrix;
        
        Mat translation, rotation;
        ofMatrix4x4 pose;
        
        ofEasyCam easyCam;
    
        ofxCameraAnaglyph redBlueCam;
        
        vector< ofBoxPrimitive > boxes;
        vector< ofColor > colors;
		
};
