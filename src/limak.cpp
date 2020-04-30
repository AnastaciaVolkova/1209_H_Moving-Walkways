// definition for Limak (walker).
#include "limak.hpp"

Limak::Limak() noexcept :speed_(0.0), energy_(0.0) {};

// Speed getter.
double Limak::GetSpeed() const noexcept { return speed_; };

// Speed setter.
void Limak::SetSpeed(double s) {
    if (s < -k_epsi_)
        throw std::invalid_argument("Speed must not be negative");
    speed_ = s;
};

// Energy getter.
double Limak::GetEnergy() const noexcept { return energy_; };

// Make Limak walk on the path or walkway.
// walkway - path or walkway to walk.
// returns how many seconds Limak walks.
double Limak::MakeWalk(const Walkway& walkway) {
    // How much energy Limak accumulates/spends per second.
    double d_e = (1.0 - speed_);

    // How much time Limak needs to walk.
    double dt = walkway.GetLength() / (speed_ + walkway.GetSpeed());

    energy_ += (dt * d_e);

    if (energy_ < 0.0) {
        energy_ -= (dt * d_e); // Return back wasted energy.
        double t1 = energy_ / (speed_ - 1);

        // Distance to walk with current speed.
        double l1 = t1 * (speed_ + walkway.GetSpeed());

        // Distance to walk with decreased speed.
        double l2 = walkway.GetLength() - l1;

        if (l2 < 0.0)
            throw std::exception("Negative distance to walk");

        SetSpeed(1);
        double t2 = l2 / (walkway.GetSpeed() + GetSpeed());

        dt = t1 + t2;
    }

    return dt;
};

