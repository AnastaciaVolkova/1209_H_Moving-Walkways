// Class definition for walkway.
#include "walkway.hpp"
#include <stdexcept>

using namespace std;

Walkway::Walkway(double x, double y, double speed) :speed_(speed) {
    if (x > y)
        throw invalid_argument("Left point must be greater than right point");
    ends_ = make_tuple(x, y);
};

// Speed getter.
double Walkway::GetSpeed() const noexcept { return speed_; };

// Get length of walkway.
double Walkway::GetLength() const noexcept {
    return get<1>(ends_) - get<0>(ends_);
};

// Put to output stream information on object.
ostream& operator<<(ostream& os, const Walkway& ot) noexcept {
    os << get<0>(ot.ends_) << " " << get<1>(ot.ends_) << " " << ot.speed_;
    return os;
}

