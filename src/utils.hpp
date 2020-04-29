// Declaration of util classes.
#if !defined(UTILS_HPP_)
#define UTILS_HPP_

#include <list>
#include <tuple>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>

#include "walkway.hpp"

using WalkwayL = std::list<Walkway>;

enum class ErrorCodes {
    OK = 0,
    FILE_ERROR = -1,
    CL_ERROR = -2
};

// Structure for input datum.
struct InputData {
    unsigned int walk_ways_number;
    double distance_to_walk;
    std::list<std::tuple<double, double, double>> walkways_parameters;
};

// Parser for input file.
class Parser {
public:
    // Parse input file and fill InputData structure.
    static void Parse(std::stringstream& in_stream, InputData& in_data);
};


// Initializer for Walkway list.
class WalkWaysInitializer {
public:
    // Initialize list of Walkway objects.
    static void Initialize(WalkwayL& ww, const InputData& in_data);
};

#endif