#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(1920, 1080);
    ofSetFrameRate(60);
    ofSetFullscreen(true);
    ofSetCircleResolution(80);
    ofBackground(255);
    
    Circle tempP = Circle();  //create a local Circle to pass into our vector which will store Circle objects
    circles.push_back(tempP);   //add a new Circle to the rear of our vector
    
    //initializing our forces
    wind = ofPoint(0.2,0.0);
    gravity = ofPoint(0.0,0.1);
    
    counter = 0;    //counter used to trigger wind events
    maxcircles = 4000; //set our max amount of circles
    
    
    ofSoundStreamListDevices();
    soundStream.setDeviceID(3);
    int bufferSize = 256;
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);


}

//--------------------------------------------------------------
void ofApp::update(){
    
    //p.update();     //calculate our Circle object's new position
    
    if(circles.size()<maxcircles){
        createNewParticle();
        particleSizeChecker();
    }
    
    for(int i = 0; i < circles.size(); i++){      //iterate through our vector to update our Circle Objects
        //circles[i].applyForce(wind);      //pass our wind ofPoint and apply it on our particle via the applyForces method
        circles[i].applyForce(gravity);   //same for gravity
        circles[i].reduceAlpha();
        circles[i].update();  //update our particle at location i within our vector
        circles[i].expandCircle();
    }
    
    //cout<<"CURRENT NUMBER OF circles = "<<circles.size()<<endl;
    
    //ADD RANDOM WIND EVENT
    
     if (counter == 500) {
     wind.x = ofRandom(-2.0,2.0);
     wind.y = ofRandom(-2.0,2.0);
     counter++;
     cout<<"RANDOM WIND EVENT"<<endl;
     cout<<"WIND = "<<wind.x<<","<<wind.y<<endl;
     }else if(counter > 1000){
     wind.x = 0.2;
     wind.y = 0.0;
     counter = 0;
     cout<<"WIND RESET"<<endl;
     }else{
     counter++;
     }
    
    
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
    cout<<scaledVol<<endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    for(int i = 0; i < circles.size(); i++)
    {
        circles[i].size = circleSize;
        circles[i].display();  //display our particle
    }
    
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15); //display fps
    
    //frameNum++; //increment the frame number
    
    //recordIMGSeq();


}

void ofApp::particleSizeChecker(){
    
    if(circles.size() > 200){
        circles.erase(circles.begin());
    }
}

void ofApp::createNewParticle(){
    Circle tempP = Circle();  //create a local Circle to pass into our vector which will store Circle objects
    
    circles.push_back(tempP);   //add a new Circle to the rear of our vector
}

void ofApp::deleteCircle()
{
    
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
    getSize();
    
}

void ofApp::getSize()
{
    circleSize = scaledVol * ofRandom(180.0f,195.0f);
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
