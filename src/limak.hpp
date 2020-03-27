// Class declaration for Limak (walker).
#if !defined(LIMAK_HPP_)
#define LIMAK_HPP_
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

    // Make Limak walk for m meters with speed s.
    // m - meters to walk.
    void MakeWalk(float m);
};
#endif
