#include "GraphTest.hpp"

/*
 * @brief Решение для данной задачи ялвется алгоритм Дейкстры. Вынес его в приватное поле, так как
 *        алогоритм расчитан на то, что время прохождения меж узлами будет различным, а в задаче оно 1
 *        и граф тоже расчитан на то, что время меж вершинами равно const -> короче о универсальности
 *        речь не идет, класс решает только поставленную задачу. Это не очень хорошо, но в тоже время
 *        если добавить в граф и время, то тогда для данной задачи был бы излишний перегруз, что мне
 *        кажется было бы излишне.
 *
 *        В целом расширить данный класс быдет просто, надо в паре.. мест поменить size_t на std::pair<>
 * @param graph сам граф
 * @param from  откуда
 * @param to    в
 * */
size_t GraphTest::Dijkstra( const IGraph& graph, const size_t& from, const size_t& to )
{
    std::vector<size_t> optimalTime( graph.VerticesCount(), std::numeric_limits<size_t>::max() );
    optimalTime[from] = 0;

    std::multiset<std::pair<size_t, size_t>> times;
    times.insert( { 0, from } );

    while( !times.empty() )
    {
        size_t current = times.begin()->second;
        times.erase( times.begin() );
        for( size_t neighbor : graph.GetNextVertices(current) )
        {
            const size_t new_time = optimalTime[current] + 1;

            if( new_time < optimalTime[neighbor] )
            {
                optimalTime[neighbor] = new_time;
                times.insert( { new_time, neighbor } );
            }
        }
    }

    return optimalTime[to];
}

/*
 * @brief функтор выполненния задачи класс
 * @param in  входные данные
 * @param out выходные данные
 * */
void GraphTest::operator()( std::istream& in, std::ostream& out )
{
    size_t size = 0, from = 0, to = 0;
    in >> size;
    ListGraph graph(size);
    in >> size;

    // Так вообще по условию у нас не сказано, будли все вершины графа в порядке от 0 до size,
    // по этому на всякий случай я добавил set который будет хранить все вершины
    std::set<size_t> points;
    for( size_t i = 0; ( ( i < size ) && ( in >> from >> to ) ); ++i )
    {
        graph.AddEdge( from, to );
        points.insert( from );
        points.insert( to );
    }
    in >> from;

    for( auto& point : points )
    {
        out << Dijkstra( graph, from, point ) << std::endl;
    }
}


