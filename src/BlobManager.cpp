//
//  BlobManager.cpp
//  OSCReceiverSendero
//
//  Created by Christian Bouvier on 11/20/16.
//
//

#include "BlobManager.hpp"
#include "Settings.hpp"
#include "MoodsManager.hpp"

void init();
void update();
void draw();

BlobManagerClass* BlobManagerClass::_instance = NULL;

BlobManagerClass::BlobManagerClass() { }

BlobManagerClass* BlobManagerClass::instance() {
    if (_instance == NULL) {
        _instance = new BlobManagerClass();
    }
    return _instance;
}

void BlobManagerClass::init() {
    // OSC receiver for Blobs
    receiver.setup(OSC_PORT_BLOBS);
}

#define normalize(x) (MIN(MAX((x), 0),1))

void BlobManagerClass::update() {
    // Check for waiting messages
    // on blobs OSC channel
    while(receiver.hasWaitingMessages()){
        
        // Get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // Check for blob messages
        if(m.getAddress() == "/blob/updated"){
            Blob *newBlobData =  new Blob();
            newBlobData->id = m.getArgAsInt32(0);
            newBlobData->x = m.getArgAsFloat(1);
            newBlobData->y = m.getArgAsFloat(2);
            newBlobData->size = 0.3;//m.getArgAsFloat(3);
            newBlobData->time = ofGetElapsedTimef();
            newBlobData->startAlpha = 0.0f;
            newBlobData->audioValue = 1.0f;

            // convert to coord space
            newBlobData->x = (normalize(newBlobData->x) - .5) * Settings.ROOM_WIDTH;
            newBlobData->y = ((1 - normalize(newBlobData->y)) - .5) * Settings.ROOM_DEPTH;
            newBlobData->size = normalize(newBlobData->size);

            addOrUpdateBlob(newBlobData);
        }
    }
    
    // Clean expired blobs
    removeExpiredBlobs();
}

void BlobManagerClass::draw() {
    ofSetColor(255,0,0);
    drawBlobs();
}

void BlobManagerClass::addOrUpdateBlob(Blob *b){
    int i = 0;
    while (i<blobs.size() and blobs[i]->id != b->id)
        i++;
    
    if (i < blobs.size()){
        b->startAlpha = blobs[i]->startAlpha;
        b->color = blobs[i]->color;
        delete blobs[i];
        blobs[i] = b;
    } else {
        asignColorTo(b);
        blobs.push_back(b);
    }
}

void BlobManagerClass::printBlobs(){
    for(int i=0; i<blobs.size(); i++)
        printBlob(blobs[i]);
}

void BlobManagerClass::printBlob(Blob *b){
    cout << "ID: " << b->id << " x: " << b->x << "- y:" << b->y << "- size:" << b->size << endl;
}

void BlobManagerClass::drawBlobs(){
    for(int i=0; i<blobs.size(); i++)
        ofDrawSphere(blobs[i]->x, 0, blobs[i]->y, blobs[i]->size*100.0f);
}

int BlobManagerClass::count(){
    return blobs.size();
}

Blob* BlobManagerClass::blob(int i){
    return blobs[i];
}

void BlobManagerClass::removeExpiredBlobs(){
    if (blobs.size() > 0){
        float now = ofGetElapsedTimef();
        
        for (int i=0; i<blobs.size(); i++) {
            if (now - blobs[i]->time > EXPIRATION_TIME){
                Blob* b = blobs[i];
                MoodsManager.freeColorFromBlobId(b->id);
                blobs[i] = blobs.back();
                blobs.pop_back();
                delete b;
                i--;
            }
        }
    }
}

void BlobManagerClass::printStatus(){
    printBlobs();
}

void BlobManagerClass::asignColorTo(Blob *b){
    b->color = MoodsManager.getColorForBlobId(b->id);
}

void BlobManagerClass::reassignBlobColors(){
    for(int i = 0; i < blobs.size(); i++) {
        Blob* blob = blobs[i];
        blob->color = MoodsManager.getColorForBlobId(blob->id);
    }
}

void BlobManagerClass::setAudioValue(int id, float value){
    int i = 0;
    while (i<blobs.size() and blobs[i]->id != id)
        i++;
    
    if (i < blobs.size())
        blobs[i]->audioValue = value;
}
