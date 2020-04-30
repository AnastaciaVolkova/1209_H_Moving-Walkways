// Class declaration for Limak (walker).
#if !defined(LIMAK_HPP_)
#define LIMAK_HPP_

#include "walkway.hpp"
#include <stdexcept>

class Limak {
private:
    double speed_; // Limaks speed.
    double energy_; // Limaks energy.
    const double k_epsi_ = 1e-12; // Epsilon to compare floating point values.
public:
    Limak() noexcept;

    // Speed getter.
    double GetSpeed() const noexcept;

    // Speed setter.
    // s - speed to set.
    void SetSpeed(double s);

    // Energy getter.
    double GetEnergy() const noexcept;

    // Make Limak walk on the path or walkway.
    // walkway - path or walkway to walk.
    // returns how many seconds Limak walks.
    double MakeWalk(const Walkway& walkway);
};
#endif
