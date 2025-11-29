#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {
}

ScalarConverter::ScalarConverter( const ScalarConverter &obj ) {
	(void)obj;
}

ScalarConverter::~ScalarConverter() {
}

ScalarConverter &ScalarConverter::operator=( const ScalarConverter &obj ) {
	(void)obj;
	return *this;
}

static bool isPseudoLiteral( const std::string& str )
{
    return (
        str == "nan" || str == "nanf" ||
        str == "+inf" || str == "+inff" ||
        str == "-inf" || str == "-inff"
    );
}

static bool isInt( const std::string& str )
{
    size_t i = 0;
    if ( str[ i ] == '+' || str[ i ] == '-' )
		i++;

    if ( i == str.size() )
		return ( false );
    for ( ; i < str.size(); i++ )
        if ( !std::isdigit( str[ i ] ) )
            return ( false );
    return ( true );
}

static bool isFloat( const std::string& str )
{
    if ( str == "+inff" || str == "-inff" || str == "nanf" )
        return ( true );

    size_t i = 0;
    bool dot = false;

    if ( str[ i ] == '+' || str[ i ] == '-' )
		i++;

    if ( i == str.size() )
		return ( false );

    for ( ; i < str.size(); i++ )
    {
        if ( str[ i ] == '.' && !dot )
            dot = true;
        else if ( str[ i ] == 'f' && i == str.size() - 1 )
            return ( dot );
        else if ( !std::isdigit( str[ i ] ) )
            return ( false );
    }

    return ( false );
}

static bool isDouble( const std::string& str )
{
    if ( str == "+inf" || str == "-inf" || str == "nan" )
        return ( true );

    size_t i = 0;
    bool dot = false;

    if ( str[ i ] == '+' || str[ i ] == '-' )
		i++;

    if ( i == str.size() )
		return ( false );

    for ( ; i < str.size(); i++ )
    {
        if ( str[ i ] == '.' && !dot )
            dot = true;
        else if ( !std::isdigit( str[ i ] ) )
            return ( false );
    }
    return ( dot );
}

static void  printChar( double value )
{
    std::cout << "char: ";
    if ( value != value || value < 0 || value > 127 )
        std::cout << "impossible" << std::endl;
    else if ( !std::isprint( static_cast< int >( value ) ) )
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast< char >( value ) << "'" << std::endl;
}

static void printInt( double value )
{
    std::cout << "int: ";
    if ( value != value ||
        value < std::numeric_limits< int >::min() ||
        value > std::numeric_limits< int >::max() )
        std::cout << "impossible" << std::endl; 
    else
        std::cout << static_cast< int >( value ) << std::endl;
}

static void printFloat( double value )
{
    std::cout << "float: ";
    float valuef = static_cast< float >( value );

    if ( value != value )
        std::cout << "nanf" << std::endl;
    else if ( value == std::numeric_limits< double >::infinity() )
        std::cout << "+inff" << std::endl;
    else if ( value == -std::numeric_limits< double >::infinity() )
        std::cout << "-inff" << std::endl;
    else
    {
        std::cout << valuef;
        if ( valuef == static_cast< int >( valuef ) )
            std::cout << ".0";
        std::cout << "f" << std::endl;
    }
}

static void printDouble( double value )
{
    std::cout << "double: ";
    if ( value != value )
        std::cout << "nan" << std::endl;
    else if ( value == std::numeric_limits<double>::infinity() )
        std::cout << "+inf" << std::endl;
    else if ( value == -std::numeric_limits<double>::infinity() )
        std::cout << "-inf" << std::endl;
    else
    {
        std::cout << value;
        if ( value == static_cast< int >( value ) )
            std::cout << ".0";
        std::cout << std::endl;
    }
}

void ScalarConverter::convert( const std::string& str )
{
    double value = 0.0;

    if ( isPseudoLiteral( str ) )
    {
        if ( str[ 0 ] == '+' ) 
			value = std::numeric_limits< double >::infinity();
        else if ( str[ 0 ] == '-' ) 
			value = -std::numeric_limits< double >::infinity();
        else 
			value = std::numeric_limits< double >::quiet_NaN();
    }
    else if ( str.size() == 1 && std::isprint( str[ 0 ] ) && !std::isdigit( str[ 0 ] ) )
        value = static_cast< double >( str[ 0 ] );
    else if ( isInt( str ) )
        value = std::strtol( str.c_str(), NULL, 10 );
    else if ( isFloat( str ) )
        value = std::strtod( str.c_str(), NULL );
    else if ( isDouble( str ) )
        value = std::strtod( str.c_str(), NULL );
    else
    {
        std::cout << "Error: invalid input" << std::endl;
        return;
    }

    printChar( value );
    printInt( value );
    printFloat( value );
    printDouble( value );
}

const char *ScalarConverter::ErrorException::what() const throw()
{
    return "Error: impossible to convert";
}