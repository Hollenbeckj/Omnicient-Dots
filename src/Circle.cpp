//
//  Circle.cpp
//  Agario_Visualizer
//
//  Created by Joshua Hollenbeck on 6/21/15.
//
//

#include "Circle.h"

Circle::Circle()
{
    location = ofPoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));    //generate a random location to start from within the sketch window
    
    velocity = ofPoint(ofRandom(-4,4),ofRandom(-4,4));    //this may overcome our forces
    //velocity = ofPoint(2,2);                                //starting with 0 instead
    
    acceleration = ofPoint(0.0,0.0);      //set acceleration to nothing to start so rely purely on incoming forces
    
    s = 5;     //scalar of our mass
    
    mass = ofRandom(1,20);  //init mass as a random between 1-19.999...
    
    particleAlpha = 220;
    
    size = 10;
    
    circleR = 255;
    circleG = 255;
    circleB = 255;
    
    randomizeColor();
    


}

void Circle::update(){
    
    
    velocity = velocity+acceleration; //add acceleration to velocity to change over time
    
    velocity.limit(50); //limit velocity to 10. If our velocity hits 10 it will stay at 10.
    
    location = location+velocity;     //add velocity to location to move at a constant velocity.
    
    edgeCheck();    //if past the screen edge reset to opposite end of x or y
    
    acceleration*=0;    //scale acceleration by 0 and assign back to itself so forces do not continue to stack
    
}

//Method to apply force
void Circle::applyForce(ofPoint f){
    ofPoint force = f/mass;  //create/init ofPoint force which is set to the incoming force/mass per
    
    acceleration+=force;    //add and assign our force to acceleration, per accumulation of forces
}


void Circle::display(){
    
    setCircleColor();
    ofEllipse(location, size, size);      //draw our particle
    
}


void Circle::edgeCheck(){
    
    //do a bounds check for x. reset to opposite side of screen if out of bounds
    if(location.x > ofGetWidth()){
        location.x = ofGetWidth();
        velocity.x *= -1;       //flip our velocity if at left edge
    }else if(location.x < 0){
        location.x = 0;
        velocity.x *= -1;       //flip our velocity if at right edge
    }
    
    //do a bounds check for y. reset to opposite side of screen if out of bounds
    if(location.y > ofGetHeight()){
        location.y = ofGetHeight();
        velocity.y *= -1;      //flip our velocity if we hit the bottom edge
    }else if(location.y < 0){
        location.y = 0;
        velocity.y *= -1;       //flip our velocity if we hit the top edge
    }
    
}

void Circle::reduceAlpha()
{
    particleAlpha--;
    
    if(particleAlpha == 0)
    {
        particleAlpha = 0;
        
    }
}

void Circle::setCircleColor()
{
    ofSetColor(circleR, circleG, circleB,particleAlpha);
}

void Circle::randomizeColor()
{
    circleR = ofRandom(255);
    circleG = ofRandom(255);
    circleB = ofRandom(255);
}

void Circle::expandCircle()
{
    size+=1;
}
