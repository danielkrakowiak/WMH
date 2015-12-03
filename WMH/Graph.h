#pragma once

#include <utility>
#include <memory>
#include <string>
#include <vector>

class Graph
{
    public:

    static std::shared_ptr<Graph> loadFromFile( std::string path );

    Graph();
    ~Graph();

    float getWeight( int vertexFrom, int vertexTo );

    private:

    int vertexCount;

    std::vector<float> weightsMatrix;
};

