//
//  SettingsManager.hpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/22/16.
//
//

#ifndef SettingsManager_hpp
#define SettingsManager_hpp

#include <stdio.h>
#include "ofxXmlSettings.h"

#define Settings (*SettingsManager::getInstance())

struct BehaviourTime {
    string key;
    float duration;
};

struct BehaviourComposer {
    vector<BehaviourTime> descriptor;
    int currentIndex;
};

class SettingsManager {
private:
    SettingsManager();
    static SettingsManager* instance;
    
    ofxXmlSettings settingsParser;
    map<string, BehaviourComposer> moods;
public:
    static SettingsManager* getInstance();

    // xml
    float BARCELONA_DIAMETER;
    float BARCELONA_BASE;
    float ROOM_WIDTH;
    float ROOM_DEPTH;
    float BLOB_DISTANCE_THRESHOLD;
    float MIN_LIGHTING_RADIUS;
    float MAX_LIGHTING_RADIUS;
    int MAX_BLOBS;

    // news
    float BLOB_PULSE_MAX_OFFSET;
    
    //---- INPUTS
    float BLOB_PULSE_DISTANCE_OFFSET;
    float BLOB_ALPHA;
    float BLOB_PULSE_VELOCITY;

    // end xml

    float METERS_TO_COORD;
    float BARCELONA_RADIUS;
    
    BehaviourComposer getComposerWithMood(string mood);
};

#endif /* SettingsManager_hpp */
