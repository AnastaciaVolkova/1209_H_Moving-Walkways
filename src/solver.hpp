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
    static std::tuple<float, float> GetDeltasWP(const Walkway& w, const Walkway& p){
        float d = p.GetLength();
        float s = w.GetSpeed();
        float l = w.GetLength();

        // Limak's speed delta on the walkway.
        float d_w = std::min(1.0f, (d*(s+1))/(2*l+d));

        // Limak's speed delta on the path.
        float d_p = -(l*d_w)/((l+d)*(d_w-((d*(s+1))/(l+d))));

        return std::make_tuple(d_w, d_p);
    }

    // Get Limak's speed deltas in situation walkway-walkway.
    static std::tuple<float, float> GetDeltasWW(const Walkway& w1, const Walkway& w2){
        float l_1 = w1.GetLength();
        float l_2 = w2.GetLength();
        float s_1 = w1.GetSpeed();
        float s_2 = w2.GetSpeed();
        float delta_w1, delta_w2;
        if (s_1 < s_2)
            delta_w1 = 0;
        else
            delta_w1 = std::min(1.0f, (l_2*(s_1+1))/(2*l_1+s_2*l_1+l_2));

        delta_w2 = ((l_1*(1+s_2))/(l_1+l_2))*((delta_w1)/((l_2*(s_1+1))/(l_1+l_2)-delta_w1));
        return std::make_tuple(delta_w1, delta_w2);
    }

public:
    // Returns the fastest time, which need Limak to get from 0 to L.
    static float GetSolution(const std::list<Walkway>& walkways){
        float t = 0.0; // Time for Limak to travel along the distance.
        Limak limak;
        auto w_it = walkways.cbegin();

        while(w_it != walkways.cend()){
            if (w_it->GetSpeed() == 0){
                limak.SetSpeed(1);
                t += limak.MakeWalk(*w_it);
            } else {
                auto w_it_1 = w_it++;
                auto w_it_2 = w_it;

                if (w_it_2 == walkways.cend()){
                    limak.SetSpeed(1);
                    t += limak.MakeWalk(*w_it_1);
                } else {
                    {
                        float delta_w, delta_p;
                        if (w_it_2->GetSpeed() == 0)
                            std::tie(delta_w, delta_p) = GetDeltasWP(*w_it_1, *w_it_2);
                        else
                            std::tie(delta_w, delta_p) = GetDeltasWW(*w_it_1, *w_it_2);

                        // Go on the walkway.
                        limak.SetSpeed(1-delta_w);
                        t += limak.MakeWalk(*w_it_1);

                        // Go on the path.
                        limak.SetSpeed(1+delta_p);
                        t += limak.MakeWalk(*w_it_2);
                    }
                }
            }
            w_it++;
        }
        return t;
    }
};
#endif
