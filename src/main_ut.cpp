#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>

#include "walkway.hpp"
#include "solver.hpp"
#include "utils.hpp"

using namespace std;


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
        return (abs(dut_ - ref_) < 1e-3) || (dut_ < ref_);
    }

    friend class TestCasePool;
};

class TestCasePool {
private:
    vector<TestCase> test_cases_;
public:
    TestCasePool(std::stringstream& str_stream) {
        string x;
        while (getline(str_stream, x)) {
            istringstream iss(x);
            vector<double> x2(istream_iterator<double>{iss}, istream_iterator<double>());
            stringstream in_data_stream;
            in_data_stream << "2 " << x2[0] + x2[2] << "\n"
                << "0 " << x2[0] << " " << x2[1] << "\n"
                << x2[0] << " " << x2[0] + x2[2]  << " " << x2[3];
            test_cases_.push_back(TestCase(in_data_stream, to_string(x2[4]).c_str()));
        }
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
    if (argc == 2) {
        ifstream ifs(argv[1]);
        if (!ifs.is_open()) {
            cout << "Error: unable to open file." << endl;
            return static_cast<int>(ErrorCodes::FILE_ERROR);
        }
        stringstream in_stream;
        in_stream << ifs.rdbuf();
        ifs.close();
        TestCasePool test_case_pool(in_stream);
        cout << boolalpha << test_case_pool.RunTestPool() << endl;        
        return static_cast<int>(ErrorCodes::OK);
    }
    else {
        cout << "Wrong command line is used." << endl;
        cout << "Proper call:" << endl;
        cout << argv[0] << " <file_name>" << endl;
        return static_cast<int>(ErrorCodes::CL_ERROR);
    }
    return 0;
}
