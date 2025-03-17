#include "exceptions.hpp"

#include <cassert>
#include <iostream>
#include <string>

void test_IGraphException()
{
    IGraphException message( "test" );
    std::string res = std::string( message.what() );
    assert( res == "test" );
}

void test_OutOfRangeFromTo()
{
    OutOfRangeFromTo message( 5, 5, 5 );
    std::string res = std::string( message.what() );
    assert( res == "Indexs for from(5) or to(5) > size(5)" );
}

void test_OutOfRangeVertex()
{
    OutOfRangeVertex message( 5, 5 );
    std::string res = std::string( message.what() );
    assert( res == "Indexs vertex(5) > size(5)" );
}

int main()
{
    test_IGraphException();
    test_OutOfRangeFromTo();
    test_OutOfRangeVertex();
    return 0;
}
