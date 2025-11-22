#include <ScalarConverter.hpp>

ScalarConverter::ScalarConverter() {
}

ScalarConverter::ScalarConverter( const std::string input ) {
	( void )input;
}

ScalarConverter::ScalarConverter( const ScalarConverter &src ) {
	*this = src;
}

ScalarConverter::~ScalarConverter() {
}

ScalarConverter &ScalarConverter::operator=( const ScalarConverter &src ) {
	( void )src;
	return ( *this );
}

e_type	checkInput( const std::string& str ) {
	if ( str.compare( "nan" ) == 0 || str.compare( "nanf" ) == 0 ||
		str.compare( "+inf" ) == 0 || str.compare( "-inf" ) == 0 ||
		str.compare( "+inff" ) == 0 || str.compare( "-inff" ) == 0 ) {
		return ( NAN_INF );
	}
	else if ( str.length() == 1 &&
		( str[0] == '+' || str[0] == '-' ||
		str[0] == 'f' || str[0] == '.' ) ) {
		return ( CHAR );
	}
	else if ( str.find_first_of( "+-" ) != str.find_last_of( "+-" ) )
		return ( ERROR );
	else if ( str.find_first_not_of( "+-0123456789" ) == std::string::npos )
		return (INT);
	else if ( str.find_first_not_of( "+-0123456789." ) == std::string::npos ) {
		if ( str.find_first_of( "." ) != str.find_last_of( "." ) ||
			isdigit( str[ str.find_first_of( "." ) + 1 ] ) == false ||
			str.find_first_of( "." ) == 0 )
			return ( ERROR );
		else
			return ( DOUBLE );
	}
	else if (  str.find_first_not_of(  "+-0123456789.f"  ) == std::string::npos  ) {
		if (  str.find_first_of(  "f"  ) != str.find_last_of(  "f"  ) ||
			str.find_first_of(  "."  ) != str.find_last_of(  "."  ) ||
			str.find_first_of(  "f"  ) - str.find_first_of(  "."  ) == 1 ||
			str.find_first_of(  "."  ) == 0 ||
			str[ str.find_first_of(  "f"  ) + 1 ] != '\0'  )
			return (  ERROR  );
		else
			return (  FLOAT  );
	}
	else if ( ( str.length() == 1 && std::isprint( str[0] ) ) ||
		( str.length() == 1 && std::isalpha( str[0] ) ) ) {
		return ( CHAR );
	}
	else
		return ( ERROR );
}

void fromChar( e_type type, const std::string &str ) {
	char	charVar = str[0];
	int		intVar;
	float	floatVar;
	double	doubleVar;

	charVar = static_cast< unsigned char >( charVar );
	intVar = static_cast< int >( charVar );
	floatVar = static_cast< float >( charVar );
	doubleVar = static_cast< double >( charVar );

	printOutput( type, str, charVar, intVar, floatVar, doubleVar );
}

void fromInt( e_type type, const std::string &str ) {
	char	charVar;
	int		intVar = std::atoi( str.c_str() );
	float	floatVar;
	double	doubleVar;

	charVar = static_cast< int >( intVar );
	floatVar = static_cast< unsigned char >( intVar );
	doubleVar = static_cast< double >( intVar );

	printOutput( type, str, charVar, intVar, floatVar, doubleVar );
}

void fromFloat( e_type type, const std::string &str ) {
	char	charVar;
	int		intVar;
	float	floatVar = std::atof( str.c_str() );
	double	doubleVar;

	charVar = static_cast< float >( floatVar );
	intVar = static_cast< char >( floatVar );
	doubleVar = static_cast< int >( floatVar );

	printOutput( type, str, charVar, intVar, floatVar, doubleVar );
}

void fromDouble( e_type type, const std::string &str ) {
	char	charVar;
	int		intVar;
	float	floatVar;
	double	doubleVar = std::atof( str.c_str() );

	charVar = static_cast< char >( doubleVar );
	intVar = static_cast< int >( doubleVar );
	floatVar = static_cast< float >( doubleVar );

	printOutput( type, str, charVar, intVar, floatVar, doubleVar );
}

void	ScalarConverter::convert( const std::string &str ) {
	void ( *functionPTRS[] )( e_type type, const std::string &str ) = { &fromChar, &fromInt, &fromFloat, &fromDouble };
	int types[] = { CHAR, INT, FLOAT, DOUBLE };

	e_type type = checkInput( str );

	if ( type == NAN_INF )
		printOutput( type, str, 0, 0, 0, 0 );
	int i;
	for ( i = 0; i < 4; i++ ) {
		if ( type == types[ i ] ) {
			( functionPTRS[ i ] )( type, str );
			break ;
		}
	}
	if ( i == 4 )
		throw ScalarConverter::ErrorException();
}

void	printOutput( e_type type, const std::string &str, char charVar, int intVar, float floatVar, double doubleVar ) {
	if ( type != NAN_INF && doubleVar <= UCHAR_MAX && doubleVar >= 0 ) {
		if ( isprint( charVar ) )
			std::cout << "char: '" << charVar << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}
	else
		std::cout << "char: impossible" << std::endl;

	if ( type != NAN_INF && doubleVar >= std::numeric_limits< int >::min() && doubleVar <= std::numeric_limits< int >::max() ) {
		std::cout << "int: " << intVar << std::endl;
	}
	else
		std::cout << "int: impossible" << std::endl;

	if ( type != NAN_INF ) {
		std::cout << "float: " << floatVar;
		if ( floatVar - intVar == 0 )
			std::cout << ".0f" << std::endl;
		else
			std::cout << "f" << std::endl;
	}
	else {
		if ( str == "nan" || str == "nanf" )
			std::cout << "float: nanf" << std::endl;
		else if ( str[0] == '+' )
			std::cout << "float: +inff" << std::endl;
		else
			std::cout << "float: -inff" << std::endl;
	}

	if ( type != NAN_INF ) {
		std::cout << "double: " << doubleVar;
		if ( doubleVar < std::numeric_limits< int >::min() || doubleVar > std::numeric_limits< int >::max() ||
			doubleVar - intVar == 0 )
	 {
			std::cout << ".0" << std::endl;
		}
		else
			std::cout << std::endl;
	}
	else {
		if ( str == "nan" || str == "nanf" )
			std::cout << "double: nan" << std::endl;
		else if ( str[ 0 ] == '+' )
			std::cout << "double: +inf" << std::endl;
		else
			std::cout << "double: -inf" << std::endl;
	}
}

const char *ScalarConverter::ErrorException::what( void ) const throw() {
	return ( "Error: Impossible to print or input not convertable" );
};