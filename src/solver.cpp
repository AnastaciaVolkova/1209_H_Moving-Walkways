// Definition for class solver.
#include "solver.hpp"

    // Get Limak's speed deltas in situation walkway-path.
std::tuple<double, double> Solver::GetDeltasWP(const Walkway& w, const Walkway& p) {
    double d = p.GetLength();
    double s = w.GetSpeed();
    double l = w.GetLength();

    // Limak's speed delta on the walkway.
    double d_w = std::min(1.0, (d * (s + 1)) / (2 * l + d));

    // Limak's speed delta on the path.
    double d_p = 1;

    return std::make_tuple(d_w, d_p);
}

// Get Limak's speed deltas in situation walkway-walkway.
std::tuple<double, double> Solver::GetDeltasWW(const Walkway& w1, const Walkway& w2) {
    double l_1 = w1.GetLength();
    double l_2 = w2.GetLength();
    double s_1 = w1.GetSpeed();
    double s_2 = w2.GetSpeed();
    double delta_w1, delta_w2;
    if (s_1 < s_2) {
        delta_w1 = 0;
        delta_w2 = 0;
    }
    else {
        delta_w1 = std::min(1.0, l_2 * (s_1 + 1) / (2 * l_1 + l_1 * s_2 + l_2));
        delta_w2 = 1;
    }

    return std::make_tuple(delta_w1, delta_w2);
}

// Returns the fastest time, which need Limak to get from 0 to L.
double Solver::GetSolution(const std::list<Walkway>& walkways) {
    double t = 0.0; // Time for Limak to travel along the distance.
    Limak limak;
    auto w_it = walkways.cbegin();

    while (w_it != walkways.cend()) {
        if (w_it->GetSpeed() == 0) {
            limak.SetSpeed(1);
            t += limak.MakeWalk(*w_it);
        }
        else {
            auto w_it_1 = w_it++;
            auto w_it_2 = w_it;

            if (w_it_2 == walkways.cend()) {
                limak.SetSpeed(1);
                t += limak.MakeWalk(*w_it_1);
            }
            else {
                {
                    double delta_w_1, delta_w_2;

                    if (w_it_2->GetSpeed() == 0)
                        std::tie(delta_w_1, delta_w_2) = GetDeltasWP(*w_it_1, *w_it_2);
                    else
                        std::tie(delta_w_1, delta_w_2) = GetDeltasWW(*w_it_1, *w_it_2);

                    // Go on the walkway.
                    limak.SetSpeed(1 - delta_w_1);
                    t += limak.MakeWalk(*w_it_1);

                    // Go on the path.
                    limak.SetSpeed(1 + delta_w_2);
                    t += limak.MakeWalk(*w_it_2);
                }
            }
        }
        w_it++;
    }
    return t;
}
