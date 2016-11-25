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

class BehaviourManager {
public:
    static map<string, Behaviour*> behaviour;
    static void init();
};

#endif /* BehaviourManager_hpp */
