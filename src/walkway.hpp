// Class declaration for walkway.
#if !defined(WALKWAY_HPP_)
#define WALKWAY_HPP_
#include <tuple>
#include <iostream>

class Walkway{
private:
    using EndsT=std::tuple<float, float>;
    float speed_; // Speed of walkway.
    EndsT ends_;  // Ends coordinates.
public:
    Walkway(float x, float y, float speed);
    
    // Speed getter.
    float GetSpeed() const;

    // Get length of walkway.
    float GetLength() const;

    // Put to output stream information on object.
    friend std::ostream& operator<<(std::ostream& os, const Walkway& ot);
};
#endif

