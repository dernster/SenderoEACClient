//
//  Variables.cpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/27/16.
//
//

#include "Variables.hpp"
#include "Settings.hpp"

VariablesClass* VariablesClass::instance = NULL;

VariablesClass* VariablesClass::getInstance(){
    if (instance == NULL)
        instance = new VariablesClass();
    return instance;
}

void VariablesClass::init(){
    connectors[V_BLOB_PULSE_DISTANCE_OFFSET] = {
        S_SETTINGS,
        1,
        1,
        Settings.BLOB_PULSE_DISTANCE_OFFSET
    };
    
//    connectors[V_BLOB_PULSE_DISTANCE_OFFSET] = {
//        S_BLOB_AUDIO_VALUE,
//        1,
//        1,
//        1,
//    };
}

float VariablesClass::get(const string & key, Blob* blob){
    Connector& connector = connectors[key];
    if (connector.sourceId == S_BLOB_AUDIO_VALUE){
        return blob->audioValue * connector.scaler + connector.offset;
    } else {
        return connector.defaultValue;
    }
}

bool VariablesClass::isFromSettings(const string & key){
    Connector& connector = connectors[key];
    return (connector.sourceId == S_SETTINGS);
}
