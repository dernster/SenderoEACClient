//
//  Pulse.cpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/25/16.
//
//

#include "Pulse.hpp"
#include "Settings.hpp"

#define RANGE (50)
#define SCALER (0.7f)

Pulse::Pulse(string name): Follower(name) {
    offset = 0;
    sign = 1;
}

ofVec3f Pulse::getBlobPos(Blob* blob){
    return Follower::getBlobPos(blob);
}

float Pulse::blobDistance(const ofVec3f & blobPos, const ofVec3f & intersection){
    float distance = Follower::blobDistance(blobPos, intersection);
    offset = offset + sign*1;
    if ((offset == RANGE) || (offset == 0)) {
        sign = -sign;
    }
    float side = offset * SCALER;
    float halfSide = (RANGE * SCALER)*.5;
    side = side - halfSide;
    auto res = distance + side;
    
    if (distance - halfSide < 0) {
        res += halfSide;
    }

    return MIN(MAX(res, 0), Settings.BLOB_DISTANCE_THRESHOLD);
}
