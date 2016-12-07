//
//  BlobManager.hpp
//  OSCReceiverSendero
//
//  Created by Christian Bouvier on 11/20/16.
//
//

#ifndef BlobManager_hpp
#define BlobManager_hpp

#include <stdio.h>
#include "ofxOsc.h"
#include "ofxBiquadFilter.h"
#include "MoodsManager.hpp"

#define EXPIRATION_TIME 0.1
#define OSC_PORT_BLOBS 12346

#define BlobManager (*BlobManagerClass::instance())

struct Blob {
    int id;
    float x;
    float y;
    float size;
    float time;
    float startAlpha;
    ofColor color;
    float audioValue;
    
    // filters
    ofxBiquadFilter1f audioFilter;
    ofxBiquadFilter2f posFilter;

};

class BlobManagerClass {
private:
    static BlobManagerClass* _instance;
    BlobManagerClass();
    
    // Blobs current list
    vector<Blob*> blobs;
    
    // OSC channel for Blobs
    ofxOscReceiver receiver;
    
    // When a new OSC message with blob information
    // arrives, this method will be invoked to
    // create a new blob or update an existing one.
    void addOrUpdateBlob(Blob *b);
    void asignColorTo(Blob *b);
    void printBlob(Blob *b);
    void printBlobs();
    void drawBlobs();
    void removeExpiredBlobs();
    
public:
    static BlobManagerClass* instance();

    int count();
    Blob* blob(int i);
    void init();
    void update();
    void draw();
    void reassignBlobColors();
    void printStatus();
    void setAudioValue(int id, float value);
    void onMoodUpdate(Mood & mood);
};

#endif /* BlobManager_hpp */
