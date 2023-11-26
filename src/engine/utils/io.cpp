#include "io.h"

#include <fstream>
#include <sstream>

std::string read_file(std::string const& filepath) {
    // Open the file
    std::ifstream t(filepath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}