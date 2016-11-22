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

using namespace std;

#define EXPIRATION_TIME 5
#define OSC_PORT_MOODS 12346

#define MoodsManager (*MoodsManagerClass::instance())

struct mood {
    string id;
    float hue;
    float saturation;
    float value;
};

struct moodTransition {
    string id;
    float remainingTime;
};

class MoodsManagerClass {
private:
    static MoodsManagerClass* _instance;
    MoodsManagerClass();
    ofxOscReceiver receiver;
    
    mood* currentMood;
    moodTransition* transition;
public:
    static MoodsManagerClass* instance();
    
    void init();
    void update();
    void draw();
    void printStatus();
};

#endif /* MoodsManager_hpp */
