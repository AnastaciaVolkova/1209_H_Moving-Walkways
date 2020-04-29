#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

#include "walkway.hpp"
#include "solver.hpp"
#include "utils.hpp"

using namespace std;


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
        InputData in_data;
        Parser::Parse(in_stream, in_data);
        WalkwayL walkways;
        WalkWaysInitializer::Initialize(walkways, in_data);
        cout << fixed << setfill('0') << setprecision(9) << Solver::GetSolution(walkways) << endl;
        return static_cast<int>(ErrorCodes::OK);
    }
    else {
        cout << "Wrong command line is used." << endl;
        cout << "Proper call:" << endl;
        cout << argv[0] << " <file_name>" << endl;
        return static_cast<int>(ErrorCodes::CL_ERROR);
    }
}