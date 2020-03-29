// Class definition for walkway.
#include "walkway.hpp"

using namespace std;

Walkway::Walkway(float x, float y, float speed):speed_(speed){ends_=make_tuple(x, y);};

// Speed getter.
float Walkway::GetSpeed(){return speed_;};

// Speed setter.
// ToDo
void Walkway::SetSpeed(float s){};

