// Declaration for class solver.
#if !defined(SOLVER_HPP_)
#define SOLVER_HPP_
#include <list>
#include "walkway.hpp"
#include "limak.hpp"
// Class solves problem.
class Solver {
public:
    // Returns the fastest time, which need Limak to get from 0 to L.
    static float GetSolution(const std::list<Walkway>& walkways){
        return 0.0f;
    }
};
#endif
