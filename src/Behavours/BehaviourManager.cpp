//
//  BehaviourManager.cpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/24/16.
//
//

#include "BehaviourManager.hpp"
#include "Follower.hpp"
#include "Pulse.hpp"

BehaviourManager* BehaviourManager::instance = NULL;

BehaviourManager* BehaviourManager::getInstance(){
    if (instance == NULL){
        instance = new BehaviourManager();
    }
    return instance;
}

void BehaviourManager::init(){
    behaviour["follower"] = new Follower("follower");
    behaviour["pulse"] = new Pulse("pulse");

    next = NULL;
    
    // default composer
    BehaviourTime ftime = {"follower", 10};
    BehaviourTime ptime = {"pulse", 10};
    composer.descriptor = {ftime, ptime};
    composer.currentIndex = 0;
    current = behaviour["follower"];
    lastTime = -1;
}

void BehaviourManager::update(const vector<Pixel*> & pixels){
    if (lastTime == -1) {
        lastTime = ofGetElapsedTimef();
    }
    auto currentTime = ofGetElapsedTimef();
    
    if (next == NULL) {

        auto currentKey = composer.descriptor[composer.currentIndex].key;
        auto currentDuration = composer.descriptor[composer.currentIndex].duration;

        if ((currentTime - lastTime) > currentDuration) {
            auto nextIndex = (composer.currentIndex + 1) % composer.descriptor.size();
            auto nextKey = composer.descriptor[nextIndex].key;
            composer.currentIndex = nextIndex;
            next = behaviour[nextKey];
        }

        current->blend(pixels, 1);
            
    } else { // transition
        
        lastTime = currentTime;
        current = next;
        next = NULL;

        current->blend(pixels, 1);
    }

}

