#ifndef PROJECT_INCLUDE_EXCEPTIONS_H_
#define PROJECT_INCLUDE_EXCEPTIONS_H_

#include <exception>
#include <string>
#include <format>

class IGraphException : public std::exception
{
private:
    std::string m_msg;

public:
    explicit IGraphException(const std::string &msg);
    const char* what() const noexcept override;
};

class OutOfRangeFromTo : public IGraphException
{
public:
    explicit OutOfRangeFromTo( const int& from, const int& to, const int& size );
};

class OutOfRangeVertex : public IGraphException
{
public:
    explicit OutOfRangeVertex( const int& vertex, const int& count );
};

#endif  // PROJECT_INCLUDE_EXCEPTIONS_H_
