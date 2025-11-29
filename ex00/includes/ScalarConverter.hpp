#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cctype>

class ScalarConverter
{
	private:
	    ScalarConverter();
	    ScalarConverter( const ScalarConverter &obj );
	    ScalarConverter& operator=( const ScalarConverter &obj );
	    ~ScalarConverter();

	public:
	    static void convert( const std::string& input );

		class ErrorException : public std::exception
	    {
	    	public:
	    	    virtual const char *what() const throw();
	    };
};

#endif