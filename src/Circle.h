//
//  Circle.h
//  Agario_Visualizer
//
//  Created by Joshua Hollenbeck on 6/21/15.
//
//

#ifndef __Agario_Visualizer__Circle__
#define __Agario_Visualizer__Circle__

//#include <iostream>
#include "ofMain.h"

class Circle{
    
public:     //public vars
    Circle();        //default constructor
    
    ofPoint location;       //ofPoint to describe location
    ofPoint velocity;       //ofPoint to describe velocity
    ofPoint acceleration;   //ofPoint to describe acceleration
    
    float accelerationScaler;   //used to scale our direciton unit vector to increase/decrease steering capability
    float mass;                 //mass of our particle aka a scalar
    int particleAlpha;
    
    int s;                  //scalar for our mass
    int size;
    int circleR;
    int circleG;
    int circleB;
    ofColor circleColor;
    
    
    void update();          //update method for movement calculations
    void display();         //draw method
    void edgeCheck();       //check if the particle has gone offscreen
    void applyForce(ofPoint);      //receives a force as a ofPoint and applies it to our acceleration
    void reduceAlpha();
    void expandCircle();
    void setCircleColor();
    void randomizeColor();
};
#endif /* defined(__Agario_Visualizer__Circle__) */
