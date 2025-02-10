#pragma once

#include <memory>
#include <string>
#include <stdexcept>

class Matrix2D {
private:
    int width;
    int height;
    int size;
    std::unique_ptr<int[]> data;
public:
    /*
    Construct a matrix given a filepath to a CSV file
    Will compute the requisite width and height
    */
    Matrix2D(const std::string& filepath);

    /*
    Construct a zero-initialized matrix with the given width and height.
    */
    Matrix2D(int width, int height);

    inline int getWidth() const {
        return width;
    }

    inline int getHeight() const {
        return height;
    }

    inline int getValue(int row, int column) {
        int index = row * width + column;
        if (index < 0 || index >= size) {
            throw std::runtime_error("Matrix2D::getValue: index out of bounds");
        }
        return data[index];
    }

    inline void setValue(int row, int column, int value) {
        int index = row * width + column;
        if (index < 0 || index >= size) {
            throw std::runtime_error("Matrix2D::getValue: index out of bounds");
        }
        data[index] = value;
    }
};