//
//  MoodsManager.hpp
//  OSCReceiverSendero
//
//  Created by Christian Bouvier on 11/20/16.
//
//

#ifndef MoodsManager_hpp
#define MoodsManager_hpp

#include <stdio.h>
#include "ofxOsc.h"
#include "ofEventUtils.h"

using namespace std;

#define OSC_PORT_MOODS 12345

#define MoodsManager (*MoodsManagerClass::instance())

struct Mood {
    string id;
    float hue;
    float saturation;
    float value;
};

struct MoodTransition {
    string id;
    float remainingTime;
};

struct ColorAndBlob {
    ofColor color;
    int blobId;
};

class MoodsManagerClass {
private:
    static MoodsManagerClass* _instance;
    vector<ColorAndBlob> colors;
    ofxOscReceiver receiver;
    MoodTransition* transition;
    string lastMoodId;
    
    

    MoodsManagerClass();
    void updateColors();
public:
    static MoodsManagerClass* instance();
    Mood* currentMood;
    ofEvent<Mood> moodChanged;
    ofEvent<Mood> moodUpdate;
    
    ofColor getColorForBlobId(int blobId);
    void freeColorFromBlobId(int blobId);
    void init();
    void update();
    void draw();
    void printStatus();

};

#endif /* MoodsManager_hpp */
