#ifndef PROJECT_INCLUDE_LISTGRAPH_HPP_
#define PROJECT_INCLUDE_LISTGRAPH_HPP_

#include "IGraph.hpp"

class ListGraph : public IGraph
{
    std::vector<std::vector<size_t>> _graphList;

public:
    ListGraph( size_t size );
    ListGraph( const ListGraph& rhs );
    ~ListGraph();

    void AddEdge( size_t from, size_t to ) override;

    size_t VerticesCount() const override;

    std::vector<size_t> GetNextVertices( size_t vertex ) const override;
    std::vector<size_t> GetPrevVertices( size_t vertex ) const override;
};

#endif  // PROJECT_SOURCE_LISTGRAPH_HPP_
