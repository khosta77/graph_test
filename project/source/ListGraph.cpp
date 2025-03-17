#include "ListGraph.hpp"

ListGraph::ListGraph( size_t size ) : _graphList(size) {}

ListGraph::ListGraph( const ListGraph& rhs ) : _graphList(rhs.VerticesCount())
{
    for( size_t i = 0; i < _graphList.size(); ++i )
        _graphList[i] = rhs.GetNextVertices(i);
}

ListGraph::~ListGraph()
{
    for( size_t i = 0; i < _graphList.size(); ++i )
        _graphList[i].clear();
    _graphList.clear();
}

void ListGraph::AddEdge( size_t from, size_t to )
{
    if( ( from >= _graphList.size() ) || ( to >= _graphList.size() ) )
        throw OutOfRangeFromTo( from, to, _graphList.size() );
    _graphList[from].push_back(to);
    _graphList[to].push_back(from);
}

size_t ListGraph::VerticesCount() const
{
    return _graphList.size();
}

std::vector<size_t> ListGraph::GetNextVertices( size_t vertex ) const
{
    if( vertex >= _graphList.size() )
        throw OutOfRangeVertex( vertex, _graphList.size() );
    std::vector<size_t> nextVertices = _graphList[vertex];
    return nextVertices;
}

std::vector<size_t> ListGraph::GetPrevVertices( size_t vertex ) const
{
    if( vertex >= _graphList.size() )
        throw OutOfRangeVertex( vertex, _graphList.size() );
    std::vector<size_t> prevVertices;
    for( size_t i = 0, I = _graphList.size(); i < I; ++i )
    {
        for( size_t j = 0, J = _graphList[i].size(); j < J; ++j )
        {
            if( _graphList[i][j] == vertex )
            {
                prevVertices.push_back(i);
                break;
            }
        }
    }
    return prevVertices;
}


