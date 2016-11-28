//
//  SpecificBehaviour.cpp
//  GenericClient
//
//  Created by Christian Clark on 3/26/13.
//  Copyright (c) 2013 chachi.clark@gmail.com. All rights reserved.
//

#include <iostream>
#include "SpecificBehaviour.h"
#include "BlobManager.hpp"
#include "MoodsManager.hpp"
#include "AudioManager.hpp"
#include "Settings.hpp"
#include "BehaviourManager.hpp"
#include "Variables.hpp"

SpecificBehaviour::SpecificBehaviour(){
    
}

SpecificBehaviour::~SpecificBehaviour(void){
    
}

void SpecificBehaviour::setup(map<int,Pixel*>* iPixels, vector<Pixel*>* iPixelsFast){
    //this class shares the same collections as the generic client manager. BE CAREFUL
    
    this->pixels=iPixels;
    this->pixelsFast=iPixelsFast;

    sphere.setRadius(Settings.BARCELONA_RADIUS);
    sphere.setPosition(0,0,0);
    
    movingSphere.setRadius(2);

    Behaviours.init();
    BlobManager.init();
    MoodsManager.init();
    AudioManager.init();
    Variables.init();

}

ofVec3f* SpecificBehaviour::intersect(ofVec3f src, ofVec3f direction){
    /*Las posiciones relativas entre un rayo y una esfera son:
     *1. No se intersectan
     *2. El rayo es tangente a la esfera (Interseccion en 1 punto)
     *3. El rayo atraviesa la esfera (Interseccion en 2 puntos)
     *
     * Para averiguar esto, sustituyo en la ecuacion de la esfera la del rayo
     * y mediante la obtencion de las raices determino los puntos de interseccion
     */
    double radio = Settings.BARCELONA_RADIUS;
    
    ofVec3f centro(0,0,0);
    direction = direction.getNormalized();
    //Obtengo las partes del rayo para mayor simplicidad de las cuentas
    double x_src = src.x;
    double y_src = src.y;
    double z_src = src.z;
    
    double x_dir = direction.x;
    double y_dir = direction.y;
    double z_dir = direction.z;
    
    //Terminos de la ecuacion cuadratica
    
    // Por vector normal, dX² + dY² + dZ² = 1
    double a = 1;
    double b = 2*(x_dir*(x_src - centro.x)) + 2*((y_dir*(y_src - centro.y))) + 2*(z_dir*(z_src - centro.z));
    double c = pow(x_src - centro.x,2) + pow(y_src - centro.y,2) + pow(z_src - centro.z,2) - pow(radio,2);
    
    double discriminante = pow(b,2) - 4*(a*c);
    double t;

    if (discriminante < 0){
        //No hubo interseccion
        return NULL;
    } else {
        //Hubo interseccion, determino si fue una o dos
        double t1 = (-b - sqrt(discriminante))/2;
        //std::cout << "t1: " << t1 << std::endl;
        double t2 = ((-b + sqrt(discriminante))/2);
        //Caso de interseccion doble, devuelvo la mas cercana al rayo
        
        if (t1 > 0){ //&& (t1 <= Constantes::UMBRAL_DOUBLE) && (objRef == this)){
            t = t1;
        } else if (t2 > 0){
            t = t2;
        }else{
            return NULL;
        }
    }
    
    
    ofVec3f* punto = new ofVec3f(0,0,0);
    
    *punto = src + direction*t;
    return punto;
}

ofVec3f inters;

void SpecificBehaviour::update(){
    
    static int alph = 0;

    vector<Pixel*>::iterator it = this->pixelsFast->begin();
    
    while (it!=this->pixelsFast->end())
    {
        Pixel* px = *it;
        px->blendRGBA(0, 0, 0, 255, 0.1f);
        it++;
    }

    BlobManager.update();
    MoodsManager.update();
    AudioManager.update();

    alph = (alph + 1) % 255;
    
    float b = alph / 255.f;

    Behaviours.update(*pixelsFast);
}

void SpecificBehaviour::calculatePixelColorsForBlob(Blob* blob, const float & blobDistance, const ofVec3f & intersection){

    for(int i = 0; i < pixelsFast->size(); i++){
        Pixel* px = (*pixelsFast)[i];
        ofVec3f pxPosition = px->getPosition();

        float distRadius = ofLerp(Settings.MIN_LIGHTING_RADIUS, Settings.MAX_LIGHTING_RADIUS, blobDistance/Settings.BLOB_DISTANCE_THRESHOLD);
        float dist = pxPosition.distance(intersection);
        
        if (dist < distRadius){
            float normalizedDist = 1 - dist/distRadius;
            ofColor c = blob->color;
            px->blendRGBA(c.r,c.g,c.b,255,ofLerp(0.1,1,normalizedDist));
        }
    }
}

void SpecificBehaviour::draw(){
    //custom draw here.
    ofSetColor(255);
    ofDrawSphere(inters, 5);
    BlobManager.draw();
    MoodsManager.draw();
    AudioManager.draw();
    ofSetColor(0, 255, 0, 20);
    ofDrawBox(
        0,
        -Settings.BARCELONA_BASE/2,
        0,
        Settings.ROOM_WIDTH,
        Settings.BARCELONA_DIAMETER + Settings.BARCELONA_BASE,
        Settings.ROOM_DEPTH
    );
}

void SpecificBehaviour::keyPressed(int key){
    //sample -> paint every pixel with red at key pressed and blend with black at update
    vector<Pixel*>::iterator it = this->pixelsFast->begin();
    
    while (it!=this->pixelsFast->end())
    {
        Pixel* px = *it;
        px->blendRGBA(255, 0, 0, 255, 1.0f);
        it++;
    }
    //end of sample
    
}


void SpecificBehaviour::exit(){
    
}
