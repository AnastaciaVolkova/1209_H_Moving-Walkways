s definition for Limak (walker).
#include "limak.hpp"

Limak::Limak():speed_(0), energy_(0){};

// Speed getter.
float Limak::GetSpeed(){return speed_;};

// Speed setter.
// ToDo
void Limak::SetSpeed(float s){};

// Energy getter.
float Limak::GetEnergy(){return energy_;};

// Make Limak walk for s seconds.
// t - seconds to walk.
// returns how many seconds Limak walks.
float Limak::MakeWalk(float t){
    // How much energy Limak accumulates/spends per second.
    float d_e = (1-speed_);    
    // How much time Limak can walk with his energy.
    float t_real;
    if (d_e<0){
        t_real = -energy_/(d_e);
        energy_ = 0;
        return t_real;
    } else {
        energy_ += d_e*t;
        return t;
    }
};

