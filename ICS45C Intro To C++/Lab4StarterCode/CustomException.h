#ifndef CUSTOMEXCEPTION_H_
#define CUSTOMEXCEPTION_H_

#include <exception>

class DuplicateMovieException : public std::exception
{
public:
    const char* what();
};

class DuplicateRenterException : public std::exception
{
public:
    const char* what();
};

class EmptyMovieInfoException : public std::exception
{
public:
    const char* what();
};

class EmptyMovieListException : public std::exception
{
public:
    const char* what();
};

class EmptyRenterListException : public std::exception
{
public:
    const char* what();
};

class EmptyRenterNameException : public std::exception
{
public:
    const char* what();
};

class InvalidRenterIDException : public std::exception
{
public:
    const char* what();
};

class MovieLimitException : public std::exception
{
public:
    const char* what();
};

class MovieNotFoundException : public std::exception
{
public:
    const char* what();
};

class RentedMovieException : public std::exception
{
public:
    const char* what();
};

class RenterLimitException : public std::exception
{
public:
    const char* what();
};

class RenterNotFoundException : public std::exception
{
public:
    const char* what();
};

#endif