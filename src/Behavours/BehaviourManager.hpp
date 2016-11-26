//
//  BehaviourManager.hpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/24/16.
//
//

#ifndef BehaviourManager_hpp
#define BehaviourManager_hpp

#include <stdio.h>
#include <map>
#include "Behaviour.hpp"
using namespace std;

#define Behaviours (*BehaviourManager::getInstance())

struct BehaviourTime {
    string key;
    float duration;
};

struct BehaviourComposer {
    vector<BehaviourTime> descriptor;
    int currentIndex;
};

class BehaviourManager {
private:
    static BehaviourManager* instance;
    map<string, Behaviour*> behaviour;
    Behaviour* current;
    Behaviour* next;
    BehaviourComposer composer;
    float lastTime;
public:
    static BehaviourManager* getInstance();
    void init();
    void update(const vector<Pixel*> & pixels);
};

#endif /* BehaviourManager_hpp */
