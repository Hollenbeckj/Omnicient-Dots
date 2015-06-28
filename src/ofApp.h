#pragma once

#include "ofMain.h"
#include "Circle.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector <Circle> circles;       //Create a vector of particles. Similar to our Java ArrayList
    
    
    
        //forces
        ofPoint wind;   //ofPoint for the wind force
        ofPoint gravity;    //ofPoint for some fake gravity
        //end of forces
    
        int counter;    //counter to set when we have a random event
        int maxcircles;   //maximum number of particles
        int circleAlpha;
        int circleSize;
    
        void particleSizeChecker();     //Function to check the size of our particle array
        void createNewParticle();       //Function to create new particles for our vector of BasicParticle objects
        void deleteCircle();
        void getSize();
    
        void audioIn(float * input, int bufferSize, int nChannels);
    
        vector <float> left;
        vector <float> right;
        vector <float> volHistory;
    
        int 	bufferCounter;
        int 	drawCounter;
    
        float smoothedVol;
        float scaledVol;
    
        ofSoundStream soundStream;
     
    

		
};
