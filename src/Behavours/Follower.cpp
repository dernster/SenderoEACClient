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
#include "Variables.hpp"

Follower::Follower(string name): Behaviour(name) {
    doubleIntersection = false;
}

void Follower::blend(const vector<Pixel*> & pixels, float alpha){

    for(int b = 0; b < BlobManager.count(); b++){
        Blob* blob = BlobManager.blob(b);
        ofVec3f blobPos = getBlobPos(blob);
        
        if (blobPos.distance(ofVec3f(0)) < Settings.BARCELONA_RADIUS)
            continue;

        Intersection intersection = intersect(blobPos);

        float blobDist = blobDistance(blob, blobPos, intersection.first);
        if (blobDist <= Settings.BLOB_DISTANCE_THRESHOLD){
            drawForBlob(blob, pixels, alpha, blobDist, intersection);
        }
    }

}

float Follower::blobDistance(Blob* blob, const ofVec3f & blobPos, const ofVec3f & intersection){
    return blobPos.distance(intersection);
}

ofVec3f Follower::getBlobPos(Blob* blob){
    ofVec2f pos(blob->x, blob->y);
    auto filtered = blob->posFilter.update(pos);
    return ofVec3f(filtered.x, 0, filtered.y);
}

void Follower::drawForBlob(Blob* blob, const vector<Pixel*> & pixels, float alpha, const float & blobDistance, const Intersection & intersection){

    for(int i = 0; i < pixels.size(); i++){
        Pixel* px = pixels[i];
        ofVec3f pxPosition = px->getPosition();

        float distRadius = ofLerp(Settings.MIN_LIGHTING_RADIUS, Settings.MAX_LIGHTING_RADIUS, blobDistance/Settings.BLOB_DISTANCE_THRESHOLD);
        float dist = pxPosition.distance(intersection.first);
        
        auto alphaVar = Variables.get(V_BLOB_ALPHA, blob);

        if (dist <= distRadius){
            float normalizedDist = 1 - dist/distRadius;
            ofColor c = blob->color;
            px->blendRGBA(c.r,c.g,c.b,255, alphaVar * alpha * ofLerp(0.1,1,normalizedDist));
        }

        if (doubleIntersection){
            float distRadius = ofLerp(Settings.MAX_LIGHTING_RADIUS, Settings.MIN_LIGHTING_RADIUS, blobDistance/Settings.BLOB_DISTANCE_THRESHOLD);
            float dist = pxPosition.distance(intersection.second);

            if (dist <= distRadius){
                float normalizedDist = 1 - dist/distRadius;
                ofColor c = blob->color;
                px->blendRGBA(c.r,c.g,c.b,255, alphaVar * alpha * ofLerp(0.1,1,normalizedDist));
            }
        }
    }
}
