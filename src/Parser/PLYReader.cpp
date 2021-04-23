#include "PLYReader.hpp"
#include "happly.h"
#include <fstream>
#include <iostream>

namespace Parser {
PLYReader::MeshData
PLYReader::readMesh(std::string fileName)
{
    happly::PLYData plyIn;
    try {
        plyIn = happly::PLYData(fileName);
    } catch (std::exception e) {
        std::cout << "Could not open PLY file " << fileName << std::endl;
        exit(1);
    }
    auto positions = plyIn.getVertexPositions();
    auto indices = plyIn.getFaceIndices();

    // convert arrays to 3-vectors
    std::vector<LinearAlgebra::Vec3> positionsConverted;
    positionsConverted.reserve(positions.size());
    for (auto& pos : positions)
        positionsConverted.push_back(
          { (FloatT)pos[0], (FloatT)pos[1], (FloatT)pos[2] });

    // flatten the index array
    std::vector<int> indicesConverted;
    indicesConverted.reserve(indices.size() * 3);
    for (auto& ind : indices) {
        indicesConverted.push_back(ind[0]);
        indicesConverted.push_back(ind[1]);
        indicesConverted.push_back(ind[2]);
    }

    return { std::move(indicesConverted), std::move(positionsConverted) };
}
}