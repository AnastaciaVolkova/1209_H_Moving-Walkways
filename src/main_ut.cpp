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
    double distance_to_walk;
    list<tuple<double, double, double>> walkways_parameters;
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
        double x, y = 0;

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

// Test case
class TestCase {
private:
    WalkwayL walkways_;
    double ref_;
    double dut_;
public:
    TestCase(stringstream& in_test, const char* gold_ref):dut_(0) {
        InputData in_data;
        Parser::Parse(in_test, in_data);
        WalkWaysInitializer::Initialize(walkways_, in_data);
        ref_ = stof(gold_ref);
    }
    bool Test() {
        dut_ = Solver::GetSolution(walkways_);
        return abs(dut_ - ref_) < 1e-3;
    }

    friend class TestCasePool;
};

class TestCasePool {
private:
    vector<TestCase> test_cases_;
public:
    TestCasePool() {
        stringstream in_data_stream;
        in_data_stream << "1 5\n0 2 2.0";
        test_cases_.push_back(TestCase(in_data_stream, "3.0"));
        in_data_stream.clear();
        in_data_stream << "1 5\n2 4 0.91";
        test_cases_.push_back(TestCase(in_data_stream, "3.808900523560"));
        in_data_stream.clear();
        in_data_stream << "3 1000\n0 990 1.777777\n995 996 1.123456789\n996 1000 2.0";
        test_cases_.push_back(TestCase(in_data_stream, "361.568848429553"));
    }

    bool RunTestPool() {
        bool all_passed = true;
        for (auto tc : test_cases_) {
            bool test_res = tc.Test();
            all_passed &= test_res;
            if (!test_res) {
                cout << "Failed: reference=" << tc.ref_ << " dut=" << tc.dut_ << endl;
                for (auto w : tc.walkways_)
                    cout << w << endl;
            }
        }
        return all_passed;
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
    else {
        TestCasePool test_pool;
        cout << boolalpha << test_pool.RunTestPool() << endl;
    }
    return 0;
}
