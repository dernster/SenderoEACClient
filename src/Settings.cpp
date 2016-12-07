//
//  SettingsManager.cpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/22/16.
//
//

#include "Settings.hpp"

#define CONVERT(x) ((x) * METERS_TO_COORD)

SettingsManager* SettingsManager::instance = NULL;

SettingsManager::SettingsManager(){
    
    settingsParser.loadFile("settings.xml");
    
    // -----------------------------------------------------------------------------------------------------
    // Common
    // -----------------------------------------------------------------------------------------------------
    BARCELONA_DIAMETER = settingsParser.getValue("settings:common:barcelonaDiameter", 1.5);
    int metersToCoordTemp = settingsParser.getValue("settings:common:metersToCoord", 160);
    METERS_TO_COORD = metersToCoordTemp / BARCELONA_DIAMETER;
        
    BARCELONA_DIAMETER = CONVERT(BARCELONA_DIAMETER);

    BARCELONA_BASE = CONVERT(settingsParser.getValue("settings:common:barcelonaBase", 0.4));
    ROOM_WIDTH = CONVERT(settingsParser.getValue("settings:common:roomWidth", 4));
    ROOM_DEPTH = CONVERT(settingsParser.getValue("settings:common:roomDepth", 4));
    BLOB_DISTANCE_THRESHOLD = CONVERT(settingsParser.getValue("settings:common:blobDistanceThreshold", 1));
    MIN_LIGHTING_RADIUS = CONVERT(settingsParser.getValue("settings:common:minLightingRadius", 0.2));
    MAX_LIGHTING_RADIUS = CONVERT(settingsParser.getValue("settings:common:maxLightingRadius", 1.2));
    MAX_BLOBS = settingsParser.getValue("settings:common:maxBlobs", 2);

    BLOB_PULSE_MAX_OFFSET = settingsParser.getValue("settings:common:blobPulseMaxOffset", 120);

    float audioAlphaScaler = settingsParser.getValue("settings:audioAlpha:scaler", 1.f);
    float audioAlphaOffset = settingsParser.getValue("settings:audioAlpha:offset", 0.f);
    AUDIO_ALPHA = {audioAlphaScaler, audioAlphaOffset};

    float audioRadiusScaler = settingsParser.getValue("settings:audioRadius:scaler", 1.f);
    float audioRadiusOffset = settingsParser.getValue("settings:audioRadius:offset", 0.f);
    AUDIO_RADIUS = {audioRadiusScaler, audioRadiusOffset};

    BLOB_POSITION_FC = settingsParser.getValue("settings:blobPositionFilter", 0.1f);
    BLOB_AUDIO_FC = settingsParser.getValue("settings:blobAudioFilter", 0.1f);

    // not used
    BLOB_PULSE_DISTANCE_OFFSET = 50;
    BLOB_ALPHA = 1;
    BLOB_PULSE_VELOCITY = 1;

    // Computed
    BARCELONA_RADIUS = BARCELONA_DIAMETER / 2;
    
    // -----------------------------------------------------------------------------------------------------
    // Moods
    // -----------------------------------------------------------------------------------------------------
    settingsParser.pushTag("settings");
    settingsParser.pushTag("moods");
    
    int numberOfMoods = settingsParser.getNumTags("mood");
    for(int i = 0; i < numberOfMoods; i++){
        
        // Get mood name
        string name = settingsParser.getAttribute("mood", "name", "", i);
        settingsParser.pushTag("mood", i);
        
        // Create behaviourComposer
        settingsParser.pushTag("behaviourComposer");
        BehaviourComposer composer;
        
        // Iterate behaviourTime
        int numberBehaviourTime = settingsParser.getNumTags("behaviourTime");
        for (int j=0; j<numberBehaviourTime; j++){
            BehaviourTime b;
            b.key = settingsParser.getAttribute("behaviourTime", "key", "", j);
            b.duration = settingsParser.getAttribute("behaviourTime", "duration", 0.0, j);
            composer.descriptor.push_back(b);
        }
        
        cout << name << endl;
        cout << composer.descriptor[0].key << endl;
        moods.insert(std::pair<string,BehaviourComposer>(name, composer));
        
        settingsParser.popTag(); // behaviourComposer
        settingsParser.popTag(); // mood i
    }
    settingsParser.popTag(); // moods
    settingsParser.popTag(); // settings
}

SettingsManager* SettingsManager::getInstance(){
    if (!instance) {
        instance = new SettingsManager();
    }
    return instance;
}

BehaviourComposer SettingsManager::getComposerWithMood(string mood){

    BehaviourTime time = { "follower", 120};
    vector<BehaviourTime> descriptor = {time};
    BehaviourComposer comp = {descriptor, 0};
    return comp;
    //std::map<string, BehaviourComposer>::iterator it;
    
    //it = moods.find(mood);
    
    //if (it != moods.end())
    //    return (BehaviourComposer) it->second;
}
