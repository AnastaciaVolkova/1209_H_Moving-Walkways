// Class declaration for walkway.
#if !defined(WALKWAY_HPP_)
#define WALKWAY_HPP_
#include <tuple>
#include <iostream>

class Walkway {
private:
    using EndsT = std::tuple<double, double>;
    double speed_; // Speed of walkway.
    EndsT ends_;  // Ends coordinates.
public:
    Walkway(double x, double y, double speed);

    // Speed getter.
    double GetSpeed() const noexcept;

    // Get length of walkway.
    double GetLength() const noexcept;

    // Put to output stream information on object.
    friend std::ostream& operator<<(std::ostream& os, const Walkway& ot) noexcept;
};
#endif

