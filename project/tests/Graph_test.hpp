#ifndef TESTS_GRAPH_TEST_HPP_
#define TESTS_GRAPH_TEST_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <exception>
#include <cassert>

const std::string TEST_RESULT_01 = "0, 1\n0, 2\n0, 3\n1, 0\n1, 3\n2, 0\n2, 3\n2, 4\n3, 0\n3, 1\n3, 2\n4, 2\n";

const std::vector<size_t> TEST_RESULT_02 = { 1, 2, 3 };
const std::vector<size_t> TEST_RESULT_03 = { 0, 3 };
const std::vector<size_t> TEST_RESULT_04 = { 0, 3, 4 };

const std::vector<size_t> TEST_RESULT_05 = { 0, 3 };
const std::vector<size_t> TEST_RESULT_06 = { 0, 3, 4 };
const std::vector<size_t> TEST_RESULT_07 = { 0, 1, 2 };
const std::vector<size_t> TEST_RESULT_08 = { 2 };

void printVector( const std::vector<size_t>& vector )
{
    for( const size_t it : vector )
        std::cout << it << ' ';
    std::cout << std::endl;
}

template <typename T>
std::string readStringStream( T& graph )
{
    std::stringstream ss;
    for( size_t i = 0, I = graph.VerticesCount(); i < I; ++i )
        for( auto j : graph.GetNextVertices(i) )
            ss << i << ", " << j << "\n";
    return ss.str();
}

/*
 * @brief универсальная функция для того, чтобы можно было протестировать различные реализации интефейса
 *        графа
 * */
template <typename T>
void testAddEdge()
{
    T graph(5);

    // Тест на вывод ошибки в VerticesCount и конструктор
    assert( 5 == graph.VerticesCount() );

    graph.AddEdge( 0, 1 );
    graph.AddEdge( 0, 2 );
    graph.AddEdge( 0, 3 );
    graph.AddEdge( 1, 3 );
    graph.AddEdge( 2, 3 );
    graph.AddEdge( 2, 4 );

    // Тест на вывод ошибки в AddEdge
    try
    {
        graph.AddEdge( 5, 5 );
    }
    catch( const std::exception& emsg )
    {
        std::string msg = emsg.what();
        assert( msg == "Indexs for from(5) or to(5) > size(5)" );
    }

    // Данный тест не учитывает состояние когда у нас в принципе не прописана проверка на на большие входные 
    // данные. предполагается, что хотя бы какая-то уже есть, котороая возвращает ошибку, чтобы не городить
    // код. В дальнейшем это будет учитыватся и в других тестах

    // Тест на вывод ошибки в VerticesCount
    // Данный тест еще нужен чтобы уточнить, что после добавления размер не менялся
    assert( 5 == graph.VerticesCount() );

    // Тест на вывод ошибки в VerticesCount
    assert( graph.GetNextVertices(0) == TEST_RESULT_02 );
    assert( graph.GetNextVertices(1) == TEST_RESULT_03 );
    assert( graph.GetNextVertices(2) == TEST_RESULT_04 );
    try
    {
        graph.GetNextVertices(5);
    }
    catch( const std::exception& emsg )
    {
        std::string msg = emsg.what();
        assert( msg == "Indexs vertex(5) > size(5)" );
    }

    // Тест на вывод ошибки в VerticesCount
    assert( graph.GetPrevVertices(1) == TEST_RESULT_05 );
    assert( graph.GetPrevVertices(2) == TEST_RESULT_06 );
    assert( graph.GetPrevVertices(3) == TEST_RESULT_07 );
    assert( graph.GetPrevVertices(4) == TEST_RESULT_08 );
    try
    {
        graph.GetPrevVertices(5);
    }
    catch( const std::exception& emsg )
    {
        std::string msg = emsg.what();
        assert( msg == "Indexs vertex(5) > size(5)" );
    }

    // Тест конструктора копирования
    T graphCopy(graph);
    std::string resultCopy = readStringStream<T>(graphCopy);
    assert( TEST_RESULT_01 == resultCopy );
}

#endif  // TESTS_GRAPH_TEST_HPP_
