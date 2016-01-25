#pragma once

class Solution;
class Graph;

namespace TestHelper
{
    bool solutionHasUniqueAndCorrectVertices( const Solution& solution );

    bool areSolutionsSame( const Solution& solution1, const Solution& solution2 );
}