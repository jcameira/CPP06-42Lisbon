#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP
# include <string>
# include <iostream>
# include <limits>
# include <climits>
# include <cstdlib>
# include <cstring>
# include <cctype>

enum    e_type
{
    ERROR = -1,
	NAN_INF,
    CHAR,
    INT,
    FLOAT,
    DOUBLE
};

class ScalarConverter
{
	private:

		ScalarConverter();
		ScalarConverter(const std::string input);
		ScalarConverter(const ScalarConverter &src);

		~ScalarConverter();

		ScalarConverter &operator=(const ScalarConverter &src);

	public:
		static void	convert(const std::string& str);

	class ErrorException : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
};

e_type checkInput(const std::string& str);
void convertInput(void);

void fromChar( e_type type, const std::string& str );
void fromInt( e_type type, const std::string& str );
void fromFloat( e_type type, const std::string& str );
void fromDouble( e_type type, const std::string& str );

void printOutput( e_type type, const std::string& str, char charVar, int intVar, float floatVar, double doubleVar );

#endif