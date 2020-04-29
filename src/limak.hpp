// Class declaration for Limak (walker).
#if !defined(LIMAK_HPP_)
#define LIMAK_HPP_

#include "walkway.hpp"

class Limak {
private:
    double speed_; // Limaks speed.
    double energy_;  // Limaks energy.
public:
    Limak();

    // Speed getter.
    double GetSpeed();

    // Speed setter.
    // s - speed to set.
    void SetSpeed(double s);

    // Energy getter.
    double GetEnergy();

    // Make Limak walk on the path or walkway.
    // walkway - path or walkway to walk.
    // returns how many seconds Limak walks.
    double MakeWalk(const Walkway& walkway);
};
#endif
