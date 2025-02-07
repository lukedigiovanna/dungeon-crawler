#include "Matrix2D.h"

#include <fstream>
#include <sstream>

#include <iostream>

Matrix2D::Matrix2D(const std::string& filepath) {
    std::fstream file(filepath);

    if (!file) {
        throw std::runtime_error("Matrix2D::Matrix2D: file does not exist: " + filepath);
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string contents = ss.str();

    // Treat `contents` like a well-formed CSV file of bounded integers.
    
    // Count width/height based on number of commas and `\n`
    width = 1;
    height = 0;
    for (int i = 0; i < contents.length() && contents[i] != '\n'; i++)
        width += contents[i] == ',';
    for (int i = 0; i < contents.length(); i++)
        height += contents[i] == '\n';

    size = width * height;

    data = std::make_unique<int[]>(size);

    int ci = 0; // Character Index
    int li = 0; // Last Index
    int i = 0;
    while (ci < contents.length()) {
        // iterate until CSV delimeter
        while (contents[ci] != ',' && contents[ci] != '\n') ci++;
        std::string value_str = contents.substr(li, ci - li);
        data[i] = std::stoi(value_str);
        std::cout << data[i] << " " << std::endl;
        i++;
        ci++;
        li = ci;
    }
}

Matrix2D::Matrix2D(int width, int height) : width(width), height(height) {
    size = width * height;
    data = std::make_unique<int[]>(size);
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}