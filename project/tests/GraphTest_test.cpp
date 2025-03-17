#include <iostream>
#include <sstream>
#include <cassert>

#include "GraphTest.hpp"

// Тест из примера
void test_example()
{
    std::stringstream in, out, truth;
    in << "5" << std::endl;
    in << "4" << std::endl;
    in << "0 1" << std::endl;
    in << "0 4" << std::endl;
    in << "1 2" << std::endl;
    in << "1 3" << std::endl;
    in << "4" << std::endl;
    GraphTest()( in, out );
    truth << "1" << std::endl;
    truth << "2" << std::endl;
    truth << "3" << std::endl;
    truth << "3" << std::endl;
    truth << "0" << std::endl;
    assert( out.str() == truth.str() );
}

// Тест на "равнобедренный" треугольник, там немного другая фигура, но похожая на треугольник
void test_isosceles()
{
    std::stringstream in, out, truth;
    in << "5" << std::endl;
    in << "5" << std::endl;
    in << "0 1" << std::endl;
    in << "0 2" << std::endl;
    in << "1 3" << std::endl;
    in << "2 4" << std::endl;
    in << "3 4" << std::endl;
    in << "1" << std::endl;
    GraphTest()( in, out );
    truth << "1" << std::endl;
    truth << "0" << std::endl;
    truth << "2" << std::endl;
    truth << "1" << std::endl;
    truth << "2" << std::endl;
    assert( out.str() == truth.str() );
}

// Тест большой фигуры, до которой несколькими путями добратся можно
void test_big()
{
    std::stringstream in, out, truth;
    in << "8" << std::endl;
    in << "9" << std::endl;
    in << "0 3" << std::endl;
    in << "0 7" << std::endl;
    in << "1 2" << std::endl;
    in << "1 7" << std::endl;
    in << "2 3" << std::endl;
    in << "3 4" << std::endl;
    in << "3 5" << std::endl;
    in << "4 5" << std::endl;
    in << "5 6" << std::endl;
    in << "7" << std::endl;
    GraphTest()( in, out );
    truth << "1" << std::endl;
    truth << "1" << std::endl;
    truth << "2" << std::endl;
    truth << "2" << std::endl;
    truth << "3" << std::endl;
    truth << "3" << std::endl;
    truth << "4" << std::endl;
    truth << "0" << std::endl;
    assert( out.str() == truth.str() );
}

int main()
{
    test_example();
    test_isosceles();
    test_big();
    return 0;
}
