#include "ofApp.h"
using namespace glm;

ofVec2f circlePosition;
vector<ofVec2f> pastPos;
ofVec2f pastPosition;
bool isDragging = false;

ofVec2f objPos;
int counter = 0;

bool flip = false;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::purple);
    circlePosition.set(ofGetWidth() / 2, ofGetHeight() / 2);
    objPos.set(ofGetWidth() / 3, ofGetHeight() / 3);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float speed = 0.05;
    float thresh = 10;
    
    if (!flip) {
        
        if (pastPos.size() > 1) {
            if (counter < pastPos.size() - 1)
            {
                objPos.x = ofLerp(objPos.x, pastPos[counter + 1].x, speed);
                objPos.y = ofLerp(objPos.y, pastPos[counter + 1].y, speed);
                
                if (objPos.distance(pastPos[counter + 1]) < thresh)
                {
                    counter += 1;
                    objPos = pastPos[counter];
                }
            }
            
            else {
                objPos.x = ofLerp(objPos.x, pastPos[0].x, speed);
                objPos.y = ofLerp(objPos.y, pastPos[0].y, speed);
                
                if (objPos.distance(pastPos[0]) < thresh)
                {
                    objPos = pastPos[0];
                    counter = 0;
                }
            }
        }
    }
    
    else {
        
        if (pastPos.size() > 1) {
            if (counter > 0)
            {
                objPos.x = ofLerp(objPos.x, pastPos[counter - 1].x, speed);
                objPos.y = ofLerp(objPos.y, pastPos[counter - 1].y, speed);
                
                if (objPos.distance(pastPos[counter - 1]) < thresh)
                {
                    counter -= 1;
                    objPos = pastPos[counter];
                }
            }
            
            else {
                objPos.x = ofLerp(objPos.x, pastPos[pastPos.size()-1].x, speed);
                objPos.y = ofLerp(objPos.y, pastPos[pastPos.size()-1].y, speed);
                
                if (objPos.distance(pastPos[pastPos.size()-1]) < thresh)
                {
                    objPos = pastPos[pastPos.size()-1];
                    counter = pastPos.size()-1;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::yellow);
    for (int i = 1; i < pastPos.size(); ++i) {
        ofDrawLine(pastPos[i - 1], pastPos[i]);
    }
    
    if (pastPos.size() > 1) {
        ofDrawLine(pastPos[pastPos.size()-1], pastPos[0]);
    }
    
    ofSetColor(ofColor::red);
    ofNoFill();
    ofDrawCircle(circlePosition, 15);
    
    ofSetColor(ofColor::cyan);
    ofFill();
    ofDrawBox(objPos.x, objPos.y, 0, 60, 60, 0);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'x' && pastPos.size() > 0) {
        pastPos.pop_back();
        circlePosition = pastPos[pastPos.size()-1];
    }
    
    else if (key == 'c' && pastPos.size() > 0) {
        pastPos.erase(pastPos.begin());
        circlePosition = pastPos[pastPos.size()-1];
    }
    
    if (key == 'f' && pastPos.size() > 0) {
        flip = !flip;
        if (flip) {
            counter += 1;
        }
        else {
            counter -= 1;
        }
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
    if (isDragging) {
            circlePosition.x = x;
            circlePosition.y = y;
        }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (ofDist(x, y, circlePosition.x, circlePosition.y) < 20) {
            isDragging = true;
        }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    pastPos.push_back(circlePosition);
    isDragging = false;
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
