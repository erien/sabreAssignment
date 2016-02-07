//
//  TextProcessor.hpp
//  sabreAssignment
//
//  Created by magda on 06/02/2016.
//  Copyright © 2016 Magdalena Glanowska. All rights reserved.
//

#ifndef TextProcessor_hpp
#define TextProcessor_hpp

#include <cstdio>
#include "commandLineOptions.hpp"


class TextProcessor final
{
public:
    
    TextProcessor(const CommandLineArgs &args);
    
    std::string get() const;
    
    void modify();
    
    void store() const;
    
private:
    
    void readFromFile(const std::string fileName);
    
    void readFromStdin();
    
    void writeToFile(const std::string fileName) const;
    
    void writeToStdin() const;
    
    void readInput(std::istream &input);
    
    bool isRangeSpecified() const;
    
    bool isNumber(const std::string s) const;
    
    std::pair<size_t, size_t> parseRange() const;

    std::string m_input;
        
    CommandLineArgs m_args;
};

#endif /* TextProcessor_hpp */
