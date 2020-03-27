// Class declaration for walkway.
#if !defined(WALKWAY_HPP_)
#define WALKWAY_HPP_
#include <tuple>

class Walkway{
private:
    using EndsT=std::tuple<float, float>;
    float speed_; // Speed of walkway.
    EndsT ends_;  // Ends coordinates.
public:
    Walkway();
    
    // Speed getter.
    float GetSpeed();

    // Speed setter.
    // s - speed to set for walkway.
    void SetSpeed(float s);
};
#endif

