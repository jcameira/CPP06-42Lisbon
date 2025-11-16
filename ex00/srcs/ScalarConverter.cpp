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
	if ( str.compare( "nan" ) == 0 || str.compare( "+inf" ) == 0 ||
		str.compare( "-inf" ) == 0 || str.compare( "+inff" ) == 0 ||
		str.compare( "-inff" ) == 0 ) {
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

void fromChar( const ScalarConverter &src ) {
	this->_char = static_cast< unsigned char >( this->getInput()[0] );
	this->_int = static_cast< int >( this->getChar() );
	this->_float = static_cast< float >( this->getChar() );
	this->_double = static_cast< double >( this->getChar() );
}

void fromInt( const ScalarConverter &src ) {
	this->_int = static_cast< int >( this->getDouble() );
	this->_char = static_cast< unsigned char >( this->getInt() );
	this->_float = static_cast< float >( this->getDouble() );
}

void fromFloat( const ScalarConverter &src ) {
	this->_float = static_cast< float >( this->getDouble() );
	this->_char = static_cast< char >( this->getFloat() );
	this->_int = static_cast< int >( this->getFloat() );
}

void fromDouble( const ScalarConverter &src ) {
	this->_char = static_cast< char >( this->getDouble() );
	this->_int = static_cast< int >( this->getDouble() );
	this->_float = static_cast< float >( this->getDouble() );
}

void	ScalarConverter::convert( const std::string &str ) {
	void ( *functionPTRS[] )( void ) = { &fromChar, &fromInt, &fromFloat, &fromDouble };
	int types[] = { CHAR, INT, FLOAT, DOUBLE };

	e_type type = checkInput( str );

	if ( type == NAN_INF )
		return ;
	int i;
	for ( i = 0; i < 4; i++ ) {
		if ( type == types[ i ] ) {
			( functionPTRS[ i ] )();
			break ;
		}
	}
	if ( i == 4 )
		throw ScalarConverter::ErrorException();
}

void	ScalarConverter::printOutput( void )const {
	if ( this->getType() != NAN_INF && this->getDouble() <= UCHAR_MAX && this->getDouble() >= 0 ) {
		if ( isprint( this->getChar() ) )
			std::cout << "char: '" << this->getChar() << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}
	else
		std::cout << "char: impossible" << std::endl;

	if ( this->getType() != NAN_INF && this->getDouble() >= std::numeric_limits< int >::min() && this->getDouble() <= std::numeric_limits< int >::max() ) {
		std::cout << "int: " << this->getInt() << std::endl;
	}
	else
		std::cout << "int: impossible" << std::endl;

	if ( this->getType() != NAN_INF ) {
		std::cout << "float: " << this->getFloat();
		if ( this->getFloat() - this->getInt() == 0 )
			std::cout << ".0f" << std::endl;
		else
			std::cout << "f" << std::endl;
	}
	else {
		if ( this->getInput() == "nan" || this->getInput() == "nanf" )
			std::cout << "float: nanf" << std::endl;
		else if ( this->getInput()[0] == '+' )
			std::cout << "float: +inff" << std::endl;
		else
			std::cout << "float: -inff" << std::endl;
	}

	if ( this->getType() != NAN_INF ) {
		std::cout << "double: " << this->getDouble();
		if ( this->getDouble() < std::numeric_limits< int >::min() || this->getDouble() > std::numeric_limits< int >::max() ||
			this->getDouble() - this->getInt() == 0 )
	 {
			std::cout << ".0" << std::endl;
		}
		else
			std::cout << std::endl;
	}
	else {
		if ( this->getInput() == "nan" || this->getInput() == "nanf" )
			std::cout << "double: nan" << std::endl;
		else if ( this->getInput()[ 0 ] == '+' )
			std::cout << "double: +inf" << std::endl;
		else
			std::cout << "double: -inf" << std::endl;
	}
}

const char *ScalarConverter::ErrorException::what( void ) const throw() {
	return ( "Error: Impossible to print or input not convertable" );
};