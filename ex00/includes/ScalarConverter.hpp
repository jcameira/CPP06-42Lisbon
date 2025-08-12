#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP
# include <string>
# include <iostream>
# include <limits>
# include <climits>
# include <cstdlib>
# include <cstring>
# include <cctype>

# define NAN_INF 1
# define ERROR 2
# define CHAR 3
# define INT 4
# define FLOAT 5
# define DOUBLE 6

class ScalarConverter
{
	private:
		const std::string _input;
		int _type;
		char _char;
		int _int;
		float _float;
		double _double;

		ScalarConverter();

		int checkInput(void);
		void convertInput(void);

		void fromChar(void);
		void fromInt(void);
		void fromFloat(void);
		void fromDouble(void);

		void printOutput(void)const;

		std::string getInput(void)const;
		int getType(void)const;
		char getChar(void)const;
		int getInt(void)const;
		float getFloat(void)const;
		double getDouble(void)const;

	public:

		ScalarConverter(const std::string input);
		ScalarConverter(const ScalarConverter &src);

		~ScalarConverter();

		ScalarConverter &operator=(const ScalarConverter &src);

	class ErrorException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif