#include <iostream>
#include <fstream>

#include "color.hpp"
#include "image.hpp"

int main(int argc, char** argv) {
    int rows = 100;
    int cols = 200;

    Image im(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            im(i, j) = Color4f(j/float(cols), 1 - i/float(rows), 0.0);
        }
    }

    if (argc >= 2) {
        std::string filename(argv[1]);
        std::ofstream out(filename, std::ofstream::out | std::ofstream::binary);
        im.write_ppm(out);
        out.close();
    }
    else {
        im.write_ppm(std::cout);
    }
}
