#include "TextFile.h"

#include <fstream>

std::shared_ptr< std::vector<char> > TextFile::load( const std::string& path )
{

    std::ifstream file;
    std::vector<char> fileData;

    // Open the file.
    file.open( path.c_str(), std::ifstream::in | std::ifstream::binary );

    // Check if open succeeded.
    if ( !file.is_open() )	throw std::exception( "TextFile::load - Failed to open file." );

    try {
        // Check file size.
        std::streamoff fileSize = 0;
        file.seekg( 0, std::ios::end ); // Move cursor to the end of the file.
        fileSize = file.tellg(); // Save cursor position.

        // Allocate memory for the file.
        fileData.reserve( fileSize + 1 );
        fileData.resize( fileSize + 1 );

        // Read the file.
        file.seekg( 0, std::ios::beg );  // Move cursor to the beginning of the file.
        file.read( reinterpret_cast<char*>(fileData.data()), fileSize );

        // Trim the data vector to the real number of characters read (on Windows multiple bytes can be read as one character - ex: LF CR -> '\n').
        fileData.resize( file.gcount() + 1 );

        // Set last character in the buffer to 0.
        fileData.at( file.gcount() ) = 0;

        // Close the file.
        file.close();

        return std::make_shared< std::vector<char> >( fileData );

    } catch ( ... ) {
        // In case of errors - close the file.
        file.close();

        throw std::exception( "TextFile::loadText - Error occured." );
    }
}

int TextFile::parseInt( std::vector<char>::const_iterator& it, const std::vector<char>::const_iterator& endIt )
{
    std::vector<char>::const_iterator beginIt = it;

    while ( it != endIt && *it != ' ' )
        ++it;

    std::string text( beginIt, it );

    const char* startPtr = text.c_str();
    char*       endPtr = nullptr;
    const int result = std::strtol( startPtr, &endPtr, 10 );

    if ( endPtr != startPtr )
        return result;
    else
        throw std::exception( "TextFile::parseInt - failed to read int." );
}

float TextFile::parseFloat( std::vector<char>::const_iterator& it, const std::vector<char>::const_iterator& endIt )
{
    std::vector<char>::const_iterator beginIt = it;

    while ( it != endIt && *it != ' ' )
        ++it;

    std::string text( beginIt, it );

    const char* startPtr = text.c_str();
    char*       endPtr = nullptr;
    const float result = std::strtof( startPtr, &endPtr );

    if ( endPtr != startPtr )
        return result;
    else
        throw std::exception( "TextFile::parseFloat - failed to read float." );
}

void TextFile::skipSpaces( std::vector<char>::const_iterator& it, const std::vector<char>::const_iterator& endIt )
{
    while ( it != endIt && *it == ' ' )
        ++it;
}

void TextFile::skipSpacesAndNewlines( std::vector<char>::const_iterator& it, const std::vector<char>::const_iterator& endIt )
{
    while ( it != endIt && (*it == ' ' || *it == '\n' || *it == '\r' || *it == 0) )
        ++it;
}
