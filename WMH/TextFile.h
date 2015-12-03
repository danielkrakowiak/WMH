#pragma once

#include <vector>
#include <memory>

class TextFile
{
    public:

    static std::shared_ptr< std::vector<char> > load( const std::string& path );

    static int   parseInt( std::vector<char>::const_iterator& it, const std::vector<char>::const_iterator& endIt );
    static float parseFloat( std::vector<char>::const_iterator& it, const std::vector<char>::const_iterator& endIt );
    static void  skipSpaces( std::vector<char>::const_iterator& it, const std::vector<char>::const_iterator& endIt );
    static void  skipSpacesAndNewlines( std::vector<char>::const_iterator& it, const std::vector<char>::const_iterator& endIt );
};

