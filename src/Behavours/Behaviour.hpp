//
//  Behaviour.hpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/24/16.
//
//

#ifndef Behaviour_hpp
#define Behaviour_hpp

#include <stdio.h>
#include "Pixel.h"
#include <vector>

class Behaviour {
public:
    string name;
    Behaviour(string name);
    virtual void blend(const vector<Pixel*> & pixels, float alpha) = 0;
    virtual ofVec3f intersect(ofVec3f src);
};

#endif /* Behaviour_hpp */
