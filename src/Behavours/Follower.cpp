//
//  Follower.cpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/24/16.
//
//

#include "Follower.hpp"
#include "Settings.hpp"
#include "BlobManager.hpp"

void Follower::blend(vector<Pixel*>* pixels, float alpha){

    for(int b = 0; b < BlobManager.count(); b++){
        Blob* blob = BlobManager.blob(b);
        ofVec3f blobPos = getBlobPos(blob);
        
        if (blobPos.distance(ofVec3f(0)) < Settings.BARCELONA_RADIUS)
            continue;
        
        ofVec3f intersection = intersect(blobPos);

        float blobDist = blobDistance(blobPos, intersection);
        if (blobDist < Settings.BLOB_DISTANCE_THRESHOLD){
            drawForBlob(blob, pixels, alpha, blobDist, intersection);
        }
    }

}

float Follower::blobDistance(const ofVec3f & blobPos, const ofVec3f & intersection){
    return blobPos.distance(intersection);
}

ofVec3f Follower::getBlobPos(Blob* blob){
    return ofVec3f(blob->x, 0, blob->y);
}

void Follower::drawForBlob(Blob* blob, vector<Pixel*>* pixels, float alpha, const float & blobDistance, const ofVec3f & intersection){

    for(int i = 0; i < pixels->size(); i++){
        Pixel* px = (*pixels)[i];
        ofVec3f pxPosition = px->getPosition();
        
        float distRadius = ofLerp(Settings.MIN_LIGHTING_RADIUS, Settings.MAX_LIGHTING_RADIUS, blobDistance/Settings.BLOB_DISTANCE_THRESHOLD);
        float dist = pxPosition.distance(intersection);
        
        if (dist < distRadius){
            float normalizedDist = 1 - dist/distRadius;
            ofColor c = blob->color;
            px->blendRGBA(c.r,c.g,c.b,255,ofLerp(0.1,1,normalizedDist));
        }
    }
}
