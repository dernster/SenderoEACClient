//
//  MoodsManager.cpp
//  OSCReceiverSendero
//
//  Created by Christian Bouvier on 11/20/16.
//
//

#include "MoodsManager.hpp"
#include "Settings.hpp"
#include "BlobManager.hpp"

MoodsManagerClass* MoodsManagerClass::_instance = NULL;

MoodsManagerClass::MoodsManagerClass() {
    lastMoodId = -1;

    for(int i = 0; i < Settings.MAX_BLOBS; i++) {
        ColorAndBlob colorAndBlob;
        colorAndBlob.color.setHsb(255, 255, 255);
        colorAndBlob.blobId = -1;
        colors.push_back(colorAndBlob);
    }

}

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
    
    currentMood = new Mood();

    currentMood->id = "ruido";
    currentMood->hue = 120;
    currentMood->saturation = 255;
    currentMood->value = 255;
    
    updateColors();
    ofNotifyEvent(moodChanged, *currentMood);
}

void MoodsManagerClass::update(){
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // Mood message
        if(m.getAddress() == "/mood"){
            
            if (currentMood == NULL)
                currentMood = new Mood();
            
            currentMood->id = m.getArgAsString(0);
            currentMood->hue = m.getArgAsFloat(1);
            currentMood->saturation = m.getArgAsFloat(2);
            currentMood->value = m.getArgAsFloat(3);

            int x = 0;
            if (currentMood->id != lastMoodId) {
                // calculate colors for this mood
                lastMoodId = currentMood->id;
                updateColors();
                ofNotifyEvent(moodChanged, *currentMood);
            } else {
                ofNotifyEvent(moodChanged, *currentMood);
            }

        // Transition message
        } else if(m.getAddress() == "/moodTransition"){

            if (transition == NULL)
                transition = new MoodTransition();
            
            transition->id = m.getArgAsString(0);
            transition->remainingTime = m.getArgAsFloat(1);
        }
    }
}

void MoodsManagerClass::updateColors(){
    if (!currentMood)
        return;

    int hueDelta = 255.f / (Settings.MAX_BLOBS + 1);
    int baseHue = currentMood->hue;
    int baseSaturation = currentMood->saturation;
    int baseValue = currentMood->value;

    for(int i = 0; i < Settings.MAX_BLOBS; i++) {
        int hue = (baseHue + ((i+1) * hueDelta)) % 255;
        ColorAndBlob& colorAndBlob = colors[i];
        colorAndBlob.color.setHsb(hue, baseSaturation, baseValue);
    }

//    // notify color changes
//    BlobManager.reassignBlobColors();

}

void MoodsManagerClass::freeColorFromBlobId(int blobId){
    for(int i = 0; i < colors.size(); i++){
        ColorAndBlob& current = colors[i];
        if (current.blobId == blobId){
            current.blobId = -1;
        }
    }
}

ofColor MoodsManagerClass::getColorForBlobId(int blobId){
    int firstAvailableIndex = -1;
    for(int i = 0; i < colors.size(); i++){
        ColorAndBlob& current = colors[i];
        if (current.blobId == -1)
            firstAvailableIndex = i;
        else if (current.blobId == blobId){
            return current.color;
        }
    }

    if (firstAvailableIndex != -1) { // at this point this should always succeed
        ColorAndBlob& available = colors[firstAvailableIndex];
        available.blobId = blobId;
        return available.color;
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
