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

map<string, Behaviour*> BehaviourManager::behaviour;

void BehaviourManager::init(){
    behaviour["follower"] = new Follower();
    behaviour["pulse"] = new Pulse();
}
