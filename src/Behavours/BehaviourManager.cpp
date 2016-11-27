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

    lastTime = -1;

}

void BehaviourManager::update(const vector<Pixel*> & pixels){
    static float alp = 0;
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
            alp = 0;
        }

        current->blend(pixels, 1);
            
    } else { // transition

        next->blend(pixels, alp);
        current->blend(pixels, 1 - alp);

        alp += 0.2;

        if (alp >= 1) {
            lastTime = currentTime;
            current = next;
            next = NULL;
        }
    }

}

void BehaviourManager::onMoodChange(Mood & mood){
    // set behaviour
    composer = Settings.getComposerWithMood(mood.id);
    current = behaviour[composer.descriptor[0].key];
}

