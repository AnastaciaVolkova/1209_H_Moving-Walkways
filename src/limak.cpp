// definition for Limak (walker).
#include "limak.hpp"

Limak::Limak():speed_(0), energy_(0){};

// Speed getter.
float Limak::GetSpeed(){return speed_;};

// Speed setter.
// ToDo
void Limak::SetSpeed(float s){};

// Energy getter.
float Limak::GetEnergy(){return energy_;};

// Make Limak walk on the path or walkway.
// walkway - path or walkway to walk.
// returns how many seconds Limak walks.
float Limak::MakeWalk(const Walkway& walkway){
    // How much energy Limak accumulates/spends per second.
    float d_e = (1-speed_);

    // How much time Limak needs to walk.
    float dt = walkway.GetLength()/(speed_+walkway.GetSpeed());

    energy_ += (dt*d_e);

    if (energy_ < 0)
        throw "Out of energy";
    return dt;
};

