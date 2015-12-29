#pragma once

#include <utility>
#include <memory>
#include <string>
#include <vector>

class Solution;

class Graph
{
    public:

    static std::shared_ptr<Graph> loadFromFile( std::string path );

    Graph();
    ~Graph();
    
    int   getVertexCount() const;
    float getWeight( int vertexFrom, int vertexTo ) const;

    private:

    int vertexCount;

    std::vector<float> weightsMatrix;
};

