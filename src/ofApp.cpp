#include "ofApp.h"

using namespace ofxCv;

//You commented out undeclared functiond in ofxFaceTracker.cpp after line 140
//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    
    cam.initGrabber(640, 480);
    
    tracker.setup();
    ofSetFrameRate( 60 );
    
    redBlueCam.setPosition( 0, 0, 10 );
    redBlueCam.lookAt( ofVec3f(0,0,0));
    
    boxes.assign( 10, ofBoxPrimitive() );
    
    for( int i = 0; i < boxes.size(); i++ ) {
        // boxes.push_back( ofBoxPrimitive() ); // ofBoxPrimitive() instantiates new instances of boxes
        ofBoxPrimitive& box = boxes[i];
        box.set( ofRandom(0.3, 0.75) );
        box.roll( ofRandom(0, 180));
        box.tilt( ofRandom(0, 180));
        float tx = ofRandom( -5, 5 ); //distance from center?
        float ty = ofRandom( -5, 5 ); //distance from center?
        float tz = ofRandom( -5, 5 ); //distance from center?
        box.setPosition( tx, ty, tz ); // This is how you can set the position of the box based off of face
        colors.push_back( ofColor( ofRandom(0,50), ofRandom(0, 255), ofRandom(0, 50))); //Sets RGB of blocks kind of?
    }
    
    redBlueCam.enableStereo();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()) {
        tracker.update(toCv(cam));
        position = tracker.getPosition();
        scale = tracker.getScale();
        orientation = tracker.getOrientation();
        rotationMatrix = tracker.getRotationMatrix();
    }
    
    redBlueCam.eyeSeparation   = ofMap( ofGetMouseX(), 0, ofGetWidth(), 0, 1., true );
    redBlueCam.focalLength     = ofMap( ofGetMouseY(), 0, ofGetHeight(), 0, 100, true );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    cam.draw(0, 0);
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    ofDrawBitmapString("Scale: "+ofToString( tracker.getScale()), 40, 60 );
    ofDrawBitmapString("Position: "+ofToString( tracker.getPosition()), 40, 90 );
    ofDrawBitmapString("Orientation: "+ofToString( ofRadToDeg(tracker.getOrientation().x))+ "  " +ofToString( ofRadToDeg(tracker.getOrientation().y))+"  "+ ofToString( ofRadToDeg(tracker.getOrientation().z)), 40, 120 );
    ofDrawBitmapString("Rotation Matrix: "+ofToString( tracker.getRotationMatrix()), 40, 150 );
    ofDrawBitmapString("Eye Separation: "+ofToString( redBlueCam.eyeSeparation, 3), 40, 300 );
    ofDrawBitmapString("Eye Focal Length: "+ofToString( redBlueCam.focalLength, 3), 40, 300 );
    if(tracker.getFound()) {
        ofSetLineWidth(1);
        tracker.draw();
        
        //easyCam.begin();
        ofSetupScreenOrtho(640, 480, -1000, 1000);
        ofTranslate(640 / 2, 480 / 2);
        
        ofPushMatrix();
        ofScale(5,5,5);
        tracker.getObjectMesh().drawWireframe();
        ofPopMatrix();
        
        applyMatrix(rotationMatrix);
        ofScale(5,5,5);
        tracker.getObjectMesh().drawWireframe();
        //easyCam.end();
    }
    
    
    ofEnableDepthTest();
    if( redBlueCam.isStereo() ) {
        redBlueCam.beginLeft();
    } else {
        redBlueCam.begin();
    }
    
    for( int i = 0; i < boxes.size(); i++ ) {
        ofSetColor( colors[i] );
        boxes[i].draw();
        ofSetColor(30, 30, 30);
        //ofLine( ofPoint(0,0,0), boxes[i].getPosition() ); //this draws the lines to the boxes
    }
    
    // draw again into the right eye //
    if( redBlueCam.isStereo() ) {
        redBlueCam.beginRight();
        for( int i = 0; i < boxes.size(); i++ ) {
            ofSetColor( colors[i] );
            boxes[i].draw();
            ofSetColor(30, 30, 30);
            // ofLine( ofPoint(0,0,0), boxes[i].getPosition() ); //this draws the lines to the boxes
        }
    }
    
    if( redBlueCam.isStereo() ) {
        redBlueCam.endStereo();
    } else {
        redBlueCam.end();
    }
    ofDisableDepthTest();
    
    ofSetColor(30, 30, 30 );
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r') {
        tracker.reset();
    }
    if( key == ' ' ) {
        if( redBlueCam.isStereo() ) redBlueCam.disableStereo();
        else redBlueCam.enableStereo();
    }
    if( key == 'f' ) {
        ofToggleFullscreen();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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


