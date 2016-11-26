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
#include "DoublePulse.hpp"
#include "MoodsManager.hpp"
#include "ofMain.h"

BehaviourManager* BehaviourManager::instance = NULL;

BehaviourManager* BehaviourManager::getInstance(){
    if (instance == NULL){
        instance = new BehaviourManager();
    }
    return instance;
}

void BehaviourManager::init(){

    // subscribe to events
    ofAddListener(MoodsManager.moodChanged, this, &BehaviourManager::onMoodChange);
//    ofAddListener(MoodsManager.moodChanged, this, &BehaviourManager::onMoodChange);

    behaviour["follower"] = new Follower("follower");
    behaviour["pulse"] = new Pulse("pulse");
    behaviour["doublePulse"] = new DoublePulse("doublePulse");

    next = NULL;
    current = NULL;

//    // default composer
//    BehaviourTime ftime = {"follower", 3};
//    BehaviourTime ptime = {"pulse", 5};
//    BehaviourTime dtime = {"doublePulse", 5};
//    composer.descriptor = {ftime, ptime, dtime};
//    composer.currentIndex = 0;
//    current = behaviour["follower"];
    lastTime = -1;

}

void BehaviourManager::update(const vector<Pixel*> & pixels){
    if (!current)
        return;
    
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

void BehaviourManager::onMoodChange(Mood & mood){
    // set behaviour
    composer = Settings.getComposerWithMood(mood.id);
    current = behaviour[composer.descriptor[0].key];
    cout << current->name << endl;
}

