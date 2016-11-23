//
//  SettingsManager.hpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/22/16.
//
//

#ifndef SettingsManager_hpp
#define SettingsManager_hpp

#define Settings (*SettingsManager::getInstance())

#include <stdio.h>

class SettingsManager {
private:
    SettingsManager();
    static SettingsManager* instance;
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
    // end xml

    float METERS_TO_COORD;
    float BARCELONA_RADIUS;
};

#endif /* SettingsManager_hpp */
