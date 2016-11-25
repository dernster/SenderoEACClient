//
//  AudioManager.hpp
//  SenderoEACClient
//
//  Created by Christian Bouvier on 11/23/16.
//
//

#ifndef AudioManager_hpp
#define AudioManager_hpp

#define OSC_PORT_AUDIO 12347

#include <stdio.h>
#include "ofxOsc.h"

using namespace std;

#define AudioManager (*AudioManagerClass::instance())

class AudioManagerClass {
private:
    static AudioManagerClass* _instance;
    AudioManagerClass();
    ofxOscReceiver receiver;
    
    float backgroundValue;
public:
    static AudioManagerClass* instance();
    
    void init();
    void update();
    void draw();
    void printStatus();
};

#endif /* AudioManager_hpp */
