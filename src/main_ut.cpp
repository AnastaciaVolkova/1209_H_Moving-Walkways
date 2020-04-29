#include <iostream>
#include <iomanip>
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
    int id_;
public:
    TestCase(int id, stringstream& in_test, double gold_ref) :dut_(0) {
        InputData in_data;
        Parser::Parse(in_test, in_data);
        WalkWaysInitializer::Initialize(walkways_, in_data);
        ref_ = gold_ref;
        id_ = id;
    }
    bool Test() {
        dut_ = Solver::GetSolution(walkways_);
        return (abs(dut_ - ref_) < 1e-9) || (dut_ < ref_);
    }

    friend class TestCasePool;
};

class TestCasePool {
private:
    vector<TestCase> test_cases_;
public:
    TestCasePool(std::stringstream& str_stream) {
        string x;
        int line_num = 0;
        while (getline(str_stream, x)) {
            istringstream iss(x);
            vector<double> x2(istream_iterator<double>{iss}, istream_iterator<double>());
            stringstream in_data_stream;
            in_data_stream << setiosflags(ios_base::fixed) << setprecision(10) << "2 " << x2[0] + x2[2] << "\n"
                << "0 " << x2[0] << " " << x2[1] << "\n"
                << x2[0] << " " << x2[0] + x2[2] << " " << x2[3];
            test_cases_.push_back(TestCase(line_num++, in_data_stream, x2[4]));
        }
    }

    bool RunTestPool() {
        bool all_passed = true;
        int num_failed = 0;        
        for (auto tc : test_cases_) {
            bool test_res = tc.Test();
            all_passed &= test_res;
            if (!test_res) {
                cout << fixed << setfill('0') << setprecision(10) << 
                    "Failed #" <<  tc.id_ << ": reference=" << tc.ref_ << " dut=" << tc.dut_ << endl;
                num_failed++;
            }
        };
        cout << "Total failed number: " << num_failed << " out of " << test_cases_.size() << endl;
        return all_passed;
    }
};

int main(int argc, char* argv[]) {
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
        if (!test_case_pool.RunTestPool()) {
            cout << "Solver failed." << endl;
        }
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
