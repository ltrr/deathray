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


ObjParserResult parseObj(std::string filename)
{
    ObjParserResult result;
    std::ifstream in(filename);

    if (!in) {
        std::cerr << "file reading error" << '\n';
        std::cerr << "filename <" << filename << ">\n";

        result.ok = false;
        return result;
    }

    vector<Point3> vs;
    vector<Vec3> vns;
    bool smooth = false;

    MaterialPtr mat(new Lambertian { Vec3(0.5, 0.5, 0.5) });

    string line, token;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> token;
        if (token == "v") {
            Point3 v;
            iss >> v;
            vs.push_back(v);
        }
        else if (token == "vn") {
            Vec3 vn;
            iss >> vn;
            vns.push_back(vn);
        }
        else if (token == "f") {
            VertexInfo info;
            parseVertexInfo(iss, info);
            Vec3 vertex1 = vs.at(info.vertex_idx - 1);
            Vec3 normal1 = vns.at(info.normal_idx - 1);
            parseVertexInfo(iss, info);
            Vec3 vertex2 = vs.at(info.vertex_idx - 1);

            while (parseVertexInfo(iss, info)) {
                Vec3 vertex3 = vs.at(info.vertex_idx - 1);
                result.surfaces.push_back(
                    SurfacePtr(new Triangle(vertex1, vertex2, vertex3, normal1, mat))
                );

                vertex2 = vertex3;
            }
        }
    }

    result.ok = true;
    return result;
}
