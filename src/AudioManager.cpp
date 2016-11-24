//
//  AudioManager.cpp
//  SenderoEACClient
//
//  Created by Christian Bouvier on 11/23/16.
//
//

#include "AudioManager.hpp"
#include "BlobManager.hpp"

AudioManagerClass* AudioManagerClass::_instance = NULL;

AudioManagerClass::AudioManagerClass(){}

AudioManagerClass* AudioManagerClass::instance(){
    if (_instance == NULL){
        _instance = new AudioManagerClass();
    }
    return _instance;
}

void AudioManagerClass::init(){
    backgroundValue = 1.0f;
    receiver.setup(OSC_PORT_AUDIO);
}

void AudioManagerClass::update(){
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // Blob sound message
        if(m.getAddress() == "/blobAudio"){
            int id = m.getArgAsInt32(0);
            float value = m.getArgAsFloat(1);
            BlobManager.setAudioValue(id, value);
        // Background sound message
        } else if(m.getAddress() == "/backgroundAudio"){
            backgroundValue = m.getArgAsFloat(0);
        }
    }
}

void AudioManagerClass::draw(){}

void AudioManagerClass::printStatus(){}
