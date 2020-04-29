#include "utils.hpp"

using namespace std;

// Parse input file and fill InputData structure.
void Parser::Parse(stringstream& in_stream, InputData& in_data) {
    string x;
    getline(in_stream, x);
    istringstream iss(x);
    vector<string> x2(istream_iterator<string>{iss}, istream_iterator<string>());
    in_data.walk_ways_number = stoi(x2[0]);
    in_data.distance_to_walk = stof(x2[1]);

    while (getline(in_stream, x) && (x != "")) {
        istringstream iss(x);
        vector<string> x2(istream_iterator<string>{iss}, istream_iterator<string>());
        in_data.walkways_parameters.push_back(make_tuple(stof(x2[0]), stof(x2[1]), stof(x2[2])));
    }
}

// Initialize list of Walkway objects.
void WalkWaysInitializer::Initialize(WalkwayL& ww, const InputData& in_data) {
    double x, y = 0;

    for (auto it : in_data.walkways_parameters) {
        x = get<0>(it);
        if (x != y)
            ww.push_back(Walkway(y, x, 0));
        y = get<1>(it);
        ww.push_back(Walkway(x, y, get<2>(it)));
    }

    if (get<1>(in_data.walkways_parameters.back()) != in_data.distance_to_walk)
        ww.push_back(Walkway(get<1>(in_data.walkways_parameters.back()), in_data.distance_to_walk, 0));
}