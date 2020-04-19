#include <iostream>
#include <list>
#include <vector>
#include <tuple>
#include <memory>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>

#include "walkway.hpp"
#include "solver.hpp"

using namespace std;

using WalkwayL=list<Walkway>;

// Structure for input datum.
struct InputData{
    unsigned int walk_ways_number;
    float distance_to_walk;
    list<tuple<float, float, float>> walkways_parameters;
};

// Parser for input file.
class Parser{
public:
    // Parse input file and fill InputData structure.
    static void Parse(stringstream& in_stream, InputData& in_data){
        string x;
        getline(in_stream, x);
        istringstream iss(x);
        vector<string> x2(istream_iterator<string>{iss}, istream_iterator<string>());
        in_data.walk_ways_number = stoi(x2[0]);
        in_data.distance_to_walk= stof(x2[1]);

        while(getline(in_stream, x)&&(x != "")){
            istringstream iss(x);
            vector<string> x2(istream_iterator<string>{iss}, istream_iterator<string>());
            in_data.walkways_parameters.push_back(make_tuple(stof(x2[0]), stof(x2[1]), stof(x2[2])));
        }
    }
};

// Initializer for Walkway list.
class WalkWaysInitializer{
public:
    // Initialize list of Walkway objects.
    static void Initialize(WalkwayL& ww, const InputData& in_data ){
        float x, y = 0;

        for (auto it: in_data.walkways_parameters){
            x = get<0>(it);
            if (x != y)
                ww.push_back(Walkway(y, x, 0));
            y = get<1>(it);
            ww.push_back(Walkway(x, y, get<2>(it)));
        }
        
        if (get<1>(in_data.walkways_parameters.back()) != in_data.distance_to_walk)
            ww.push_back(Walkway(get<1>(in_data.walkways_parameters.back()), in_data.distance_to_walk, 0));
    }
};


int main(int argc, char* argv[]){
    if (argc > 1) {
        ifstream ifs(argv[1]);
        stringstream in_stream;
        in_stream << ifs.rdbuf();
        ifs.close();
        InputData in_data;
        Parser::Parse(in_stream, in_data);
        WalkwayL walkways;
        WalkWaysInitializer::Initialize(walkways, in_data);
        for (auto i : walkways)
            cout << i << endl;
        cout << Solver::GetSolution(walkways) << endl;
        cout << "Problem \"Moving Walkways\"" << endl;
    }
    return 0;
}
