//
//  Pulse.cpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/25/16.
//
//

#include "Pulse.hpp"
#include "Settings.hpp"
#include "Variables.hpp"
    
#define RANGE (50)
#define SCALER (1.2f)

Pulse::Pulse(string name): Follower(name) {
    offset = 0;
    sign = 1;
}

ofVec3f Pulse::getBlobPos(Blob* blob){
    return Follower::getBlobPos(blob);
}

float Pulse::blobDistance(Blob* blob, const ofVec3f & blobPos, const ofVec3f & intersection){
    float distance = Follower::blobDistance(blob, blobPos, intersection);
    float side = 0;
    if (Variables.isFromSettings(V_BLOB_PULSE_DISTANCE_OFFSET)) {
        offset = offset + sign*1;
        if ((offset == RANGE) || (offset == 0)) {
            sign = -sign;
        }
        side = offset * SCALER;
        float halfSide = (RANGE * SCALER)*.5;
        side = side - halfSide;
    } else {
        // mapping from audio source
        auto audioValue = Variables.get(V_BLOB_PULSE_DISTANCE_OFFSET, blob);
        blob->audioFilter.update(audioValue);
        float offset = blob->audioFilter.value();
        side = offset * Settings.BLOB_PULSE_MAX_OFFSET;
        
        
//        cout << side << endl;
    }

    auto res = distance + side;
    return MIN(MAX(res, 0), Settings.BLOB_DISTANCE_THRESHOLD);
}
