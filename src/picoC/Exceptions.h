#pragma once
#include <exception> 
#include <string>


namespace PicoC
{

    class Exception : public std::exception
    {
    protected:
    public:
        virtual std::string GetMessage() = 0;

    };

    class TokenizerOutOfRangeException : public std::exception
    {
    public:
        std::string GetMessage();
    };




}