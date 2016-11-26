//
//  Follower.hpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/24/16.
//
//

#ifndef Follower_hpp
#define Follower_hpp

#include <stdio.h>
#include "Behaviour.hpp"
#include "BlobManager.hpp"

class Follower: public Behaviour {
protected:
    void drawForBlob(Blob* blob, const vector<Pixel*> & pixels, float alpha, const float & blobDistance, const ofVec3f & intersection);
public:
    Follower(string name);
    virtual void blend(const vector<Pixel*> & pixels, float alpha);
    virtual ofVec3f getBlobPos(Blob* blob);
    virtual float blobDistance(const ofVec3f & blobPos, const ofVec3f & intersection);
};

#endif /* Follower_hpp */
