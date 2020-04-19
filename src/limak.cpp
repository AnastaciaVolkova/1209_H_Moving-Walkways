// definition for Limak (walker).
#include "limak.hpp"

Limak::Limak():speed_(0), energy_(0){};

// Speed getter.
double Limak::GetSpeed(){return speed_;};

// Speed setter.
// ToDo
void Limak::SetSpeed(double s) { speed_ = s; };

// Energy getter.
double Limak::GetEnergy(){return energy_;};

// Make Limak walk on the path or walkway.
// walkway - path or walkway to walk.
// returns how many seconds Limak walks.
double Limak::MakeWalk(const Walkway& walkway){
    // How much energy Limak accumulates/spends per second.
    double d_e = (1-speed_);

    // How much time Limak needs to walk.
    double dt = walkway.GetLength()/(speed_+walkway.GetSpeed());

    energy_ += (dt*d_e);

    if ((energy_ < 0) && (abs(energy_)<1e-15))
        throw "Out of energy";
    return dt;
};

