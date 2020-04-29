// Declaration for class solver.
#if !defined(SOLVER_HPP_)
#define SOLVER_HPP_
#include <list>
#include <tuple>
#include <algorithm>
#include "walkway.hpp"
#include "limak.hpp"

// Class solves problem.
class Solver {
private:
    // Get Limak's speed deltas in situation walkway-path.
    static std::tuple<double, double> GetDeltasWP(const Walkway& w, const Walkway& p);

    // Get Limak's speed deltas in situation walkway-walkway.
    static std::tuple<double, double> GetDeltasWW(const Walkway& w1, const Walkway& w2);

public:
    // Returns the fastest time, which need Limak to get from 0 to L.
    static double GetSolution(const std::list<Walkway>& walkways); 
};
#endif
