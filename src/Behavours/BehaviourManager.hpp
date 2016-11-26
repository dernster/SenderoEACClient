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
#include "MoodsManager.hpp"
#include "Settings.hpp"
using namespace std;

#define Behaviours (*BehaviourManager::getInstance())

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
    void onMoodChange(Mood & mood);
};

#endif /* BehaviourManager_hpp */
