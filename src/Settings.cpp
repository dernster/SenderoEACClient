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

    BARCELONA_DIAMETER = 1.5;
    METERS_TO_COORD = 160 / BARCELONA_DIAMETER;

    // read from xml
    BARCELONA_DIAMETER = CONVERT(BARCELONA_DIAMETER);
    BARCELONA_BASE = CONVERT(0.4);
    ROOM_WIDTH = CONVERT(4);
    ROOM_DEPTH = CONVERT(4);
    BLOB_DISTANCE_THRESHOLD = CONVERT(2);
    MIN_LIGHTING_RADIUS = CONVERT(0.1);
    MAX_LIGHTING_RADIUS = CONVERT(1);
    MAX_BLOBS = 2;

    // computed
    BARCELONA_RADIUS = BARCELONA_DIAMETER / 2;
}

SettingsManager* SettingsManager::getInstance(){
    if (!instance) {
        instance = new SettingsManager();
    }
    return instance;
}
