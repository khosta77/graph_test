#ifndef PROJECT_INCLUDE_GRAPHTEST_HPP_
#define PROJECT_INCLUDE_GRAPHTEST_HPP_

#include <sstream>
#include <limits>
#include <set>

#include "ListGraph.hpp"

class GraphTest
{
private:
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
    size_t Dijkstra( const IGraph& graph, const size_t& from, const size_t& to );

public:
    GraphTest() = default;
    ~GraphTest() = default;

    /*
     * @brief функтор выполненния задачи класс
     * @param in  входные данные
     * @param out выходные данные
     * */
    void operator()( std::istream& in, std::ostream& out );

};

#endif  // PROJECT_INCLUDE_GRAPHTEST_HPP_
