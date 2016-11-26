//
//  Behaviour.cpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/24/16.
//
//

#include "Behaviour.hpp"
#include "Settings.hpp"

ofVec3f Behaviour::intersect(ofVec3f src){
    /*Las posiciones relativas entre un rayo y una esfera son:
     *1. No se intersectan
     *2. El rayo es tangente a la esfera (Interseccion en 1 punto)
     *3. El rayo atraviesa la esfera (Interseccion en 2 puntos)
     *
     * Para averiguar esto, sustituyo en la ecuacion de la esfera la del rayo
     * y mediante la obtencion de las raices determino los puntos de interseccion
     */
    ofVec3f direction = ofVec3f(0) - src;
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
    
    // Por vector normal, dX¬≤ + dY¬≤ + dZ¬≤ = 1
    double a = 1;
    double b = 2*(x_dir*(x_src - centro.x)) + 2*((y_dir*(y_src - centro.y))) + 2*(z_dir*(z_src - centro.z));
    double c = pow(x_src - centro.x,2) + pow(y_src - centro.y,2) + pow(z_src - centro.z,2) - pow(radio,2);
    
    double discriminante = pow(b,2) - 4*(a*c);
    double t;
    
    if (discriminante < 0){
        //No hubo interseccion
        return ofVec3f(0); // should never happen
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
            return ofVec3f(0); // should never happen
        }
    }
    
    ofVec3f punto = src + direction*t;
    return punto;
}

Behaviour::Behaviour(string name){
    this->name = name;
}
