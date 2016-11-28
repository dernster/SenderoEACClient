//
//  Variables.hpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/27/16.
//
//

#ifndef Variables_hpp
#define Variables_hpp

#include <stdio.h>
#include <string>
#include <map>
#include "BlobManager.hpp"

#define Variables (*VariablesClass::getInstance())

// Variables Keys

#define V_BLOB_PULSE_DISTANCE_OFFSET "BLOB_DISTANCE_OFFSET"
#define V_BLOB_ALPHA "BLOB_ALPHA"
#define V_BLOB_PULSE_VELOCITY "PULSE_VELOCITY"

// Source Ids

#define S_BLOB_AUDIO_VALUE "BLOB_AUDIO_VALUE"
#define S_SETTINGS "SETTINGS"

using namespace std;

struct Connector {
    string sourceId;
    float offset;
    float scaler;
    float defaultValue;
};

class VariablesClass {
private:
    static VariablesClass* instance;
    map<string, Connector> connectors;
public:
    static VariablesClass* getInstance();
    void init();
    float get(const string & key, Blob* blob);
    bool isFromSettings(const string & key);
};

#endif /* Variables_hpp */
