//
//  SpecificBehaviour.h
//  GenericClient
//
//  Created by Christian Clark on 3/26/13.
//  Copyright (c) 2013 chachi.clark@gmail.com. All rights reserved.
//

#ifndef GenericClient_SpecificBehaviour_h
#define GenericClient_SpecificBehaviour_h

#include "ofMain.h"
#include "Pixel.h"
#include "DTFrame.h"
#include "DTPixel.h"
#include <map>
#include <vector>


class SpecificBehaviour {
    
public:
        
    SpecificBehaviour();
    ~SpecificBehaviour(void);
    
    void setup(map<int,Pixel*>* pixels, vector<Pixel*>* pixelsFast);
    void update();
    void draw();
    
    void keyPressed(int key); 
    
    void exit();

private:
    
    map<int, Pixel*>* pixels;
    vector<Pixel*>* pixelsFast;
    
};

#endif
