#ifndef PROJECT_INCLUDE_IGRAPH_HPP_
#define PROJECT_INCLUDE_IGRAPH_HPP_

#include <vector>
#include <cstddef>
#include <ostream>

#include "exceptions.hpp"

/*
 * @brief Интерфейсный класс
 * */
struct IGraph
{
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge( size_t from, size_t to ) = 0;

    virtual size_t VerticesCount() const = 0;

    virtual std::vector<size_t> GetNextVertices( size_t vertex ) const = 0;
    virtual std::vector<size_t> GetPrevVertices( size_t vertex ) const = 0;
};

#endif  // PROJECT_INCLUDE_IGRAPH_HPP_
