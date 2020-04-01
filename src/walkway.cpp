// Class definition for walkway.
#include "walkway.hpp"

using namespace std;

Walkway::Walkway(float x, float y, float speed):speed_(speed){ends_=make_tuple(x, y);};

// Speed getter.
float Walkway::GetSpeed() const {return speed_;};

// Get length of walkway.
float Walkway::GetLength() const {
    return get<1>(ends_) - get<0>(ends_);
};

// Put to output stream information on object.
ostream& operator<<(ostream& os, const Walkway& ot){
    os << get<0>(ot.ends_) << " " << get<1>(ot.ends_) << " " << ot.speed_;
    return os;
}

