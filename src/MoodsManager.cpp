//
//  MoodsManager.cpp
//  OSCReceiverSendero
//
//  Created by Christian Bouvier on 11/20/16.
//
//

#include "MoodsManager.hpp"

MoodsManagerClass* MoodsManagerClass::_instance = NULL;

MoodsManagerClass::MoodsManagerClass() {}

MoodsManagerClass* MoodsManagerClass::instance() {
    if (_instance == NULL) {
        _instance = new MoodsManagerClass();
    }
    return _instance;
}

void MoodsManagerClass::init(){
    receiver.setup(OSC_PORT_MOODS);
    currentMood = NULL;
    transition = NULL;
}

void MoodsManagerClass::update(){
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // Mood message
        if(m.getAddress() == "/mood"){
            
            if (currentMood == NULL)
                currentMood = new mood();
            
            currentMood->id = m.getArgAsString(0);
            currentMood->hue = m.getArgAsFloat(1);
            currentMood->saturation = m.getArgAsFloat(2);
            currentMood->value = m.getArgAsFloat(3);
            
        // Transition message
        } else if(m.getAddress() == "/moodTransition"){
            
            if (transition == NULL)
                transition = new moodTransition();
            
            transition->id = m.getArgAsString(0);
            transition->remainingTime = m.getArgAsFloat(1);
        }
    }
}

void MoodsManagerClass::draw(){}

void MoodsManagerClass::printStatus(){
    if (currentMood){
        cout << "--- MoodsManager Status ---" << endl;
        cout << "Current Mood: " << currentMood->id << endl;
        cout << "\tHue: " << currentMood->hue << endl;
        cout << "\tSaturation: " << currentMood->saturation << endl;
        cout << "\tValue: " << currentMood->value << endl;
    }
    
    if (transition){
        cout << "Transition:" << transition->id << endl;
        cout << "\tRemaining time:" << transition->remainingTime << endl;
    }
}
