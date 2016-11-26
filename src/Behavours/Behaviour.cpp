//
//  Behaviour.cpp
//  SenderoEACClient
//
//  Created by Diego Ernst on 11/24/16.
//
//

#include "Behaviour.hpp"
#include "Settings.hpp"

Intersection Behaviour::intersect(ofVec3f src){
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
    
    Intersection intersection = {ofVec3f(0), ofVec3f(0)};

    if (discriminante > 0){
        double t1 = (-b - sqrt(discriminante))/2;
        double t2 = ((-b + sqrt(discriminante))/2);

        if (t1 > 0){
            intersection.first = src + direction * t1;
        }
        
        if (t2 > 0){
            intersection.second = src + direction * t2;
        }
    }

    return intersection;
}

Behaviour::Behaviour(string name){
    this->name = name;
}
