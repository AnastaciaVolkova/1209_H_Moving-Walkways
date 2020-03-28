#include <iostream>
#include <list>
#include <vector>
#include <tuple>
#include <memory>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>

#include "limak.hpp"
#include "walkway.hpp"


using namespace std;

using WalkWays=list<Walkway>;

// Structure for input datum.
struct InputData{
    unsigned int walk_ways_number;
    unsigned int distance_to_walk;
    list<tuple<float, float, float>> walkways_parameters;
};

// Parser for input file.
class Parser{
public:
    // Parse input file and fill InputData structure.
    static void Parse(int argc, char* argv[], InputData& in_data){
        ifstream ifs(argv[1]);
        stringstream in_stream;
        in_stream << ifs.rdbuf();
        ifs.close();
        
        string x;
        getline(in_stream, x);
        istringstream iss(x);
        vector<string> x2(istream_iterator<string>{iss}, istream_iterator<string>());
        in_data.walk_ways_number = stof(x2[0]);
        in_data.walk_ways_number = stof(x2[1]);

        while(getline(in_stream, x)&&(x != "")){
            istringstream iss(x);
            vector<string> x2(istream_iterator<string>{iss}, istream_iterator<string>());
            in_data.walkways_parameters.push_back(make_tuple(stof(x2[0]), stof(x2[1]), stof(x2[2])));
        }
    }
};

int main(int argc, char* argv[]){
    InputData in_data;
    Parser::Parse(argc, argv, in_data);
    cout << "Problem \"Moving Walkways\"" << endl;
}
