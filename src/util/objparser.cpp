#include "util/objparser.h"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "material/lambertian.h"
#include "surface/triangle.h"
using std::vector;
using std::string;


struct VertexInfo
{
    int vertex_idx;
    int normal_idx;
};


bool parseVertexInfo(std::istream& is, VertexInfo& info)
{
    string token;
    is >> token;
    if(!is) {
        return false;
    }

    int n_bars = std::count(begin(token), end(token), '/');
    if (n_bars = 0) {
        info.vertex_idx = stoi(token);
        info.normal_idx = 0;
    }
    else if (n_bars = 2) {
        sscanf(token.c_str(), "%d//%d", &info.vertex_idx, &info.normal_idx);
        return true;
    }
    else {
        info.vertex_idx = 0;
        info.normal_idx = 0;
        return true;
    }
    return false;
}


bool parseObj(std::string filename, MeshDescription *desc)
{
    std::ifstream in(filename);

    if (!in) {
        std::cerr << "file reading error" << '\n';
        std::cerr << "filename <" << filename << ">\n";

        return false;
    }

    bool smooth = false;
    desc->material = MaterialPtr(new Lambertian { GRAY_TEXTURE });

    string line, token;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> token;
        if (token == "v") {
            Point3 v;
            iss >> v;
            desc->vertices.push_back(v);
        }
        else if (token == "vn") {
            Vec3 vn;
            iss >> vn;
            //vns.push_back(vn);
        }
        else if (token == "f") {
            VertexInfo info;
            parseVertexInfo(iss, info);
            int index1 = info.vertex_idx - 1;
            parseVertexInfo(iss, info);
            int index2 = info.vertex_idx - 1;

            while (parseVertexInfo(iss, info)) {
                int index3 = info.vertex_idx - 1;
                desc->faces.push_back({ index1, index2, index3 });
                index2 = index3;
            }
        }
    }

    return true;
}
