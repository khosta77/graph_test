#include "exceptions.hpp"

IGraphException::IGraphException(const std::string &msg) : m_msg(msg) {}

const char* IGraphException::what() const noexcept 
{
    return m_msg.c_str();
}

OutOfRangeFromTo::OutOfRangeFromTo( const int& from, const int& to, const int& size ) : IGraphException(
    std::format( "Indexs for from({}) or to({}) > size({})", from, to, size )
) {}

OutOfRangeVertex::OutOfRangeVertex( const int& vertex, const int& count ) : IGraphException(
    std::format( "Indexs vertex({}) > size({})", vertex, count )
) {}


