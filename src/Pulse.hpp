//
//  Pulse.hpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/25/16.
//
//

#ifndef Pulse_hpp
#define Pulse_hpp

#include <stdio.h>
#include "Follower.hpp"

class Pulse: public Follower {
private:
    int offset;
    int sign;
public:
    Pulse(string name);
    virtual ofVec3f getBlobPos(Blob* blob);
    virtual float blobDistance(Blob* blob, const ofVec3f & blobPos, const ofVec3f & intersection);
};

#endif /* Pulse_hpp */
