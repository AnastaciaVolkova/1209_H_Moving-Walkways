// Class declaration for Limak (walker).
#if !defined(LIMAK_HPP_)
#define LIMAK_HPP_

#include "walkway.hpp"

class Limak{
private:
    float speed_; // Limaks speed.
    float energy_;  // Limaks energy.
public:
    Limak();

    // Speed getter.
    float GetSpeed();

    // Speed setter.
    // s - speed to set.
    void SetSpeed(float s);

    // Energy getter.
    float GetEnergy();

    // Make Limak walk on the path or walkway.
    // walkway - path or walkway to walk.
    // returns how many seconds Limak walks.
    float MakeWalk(const Walkway& walkway);
};
#endif
