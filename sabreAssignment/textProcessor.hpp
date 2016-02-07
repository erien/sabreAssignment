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
#include <fstream>
#include "commandLineOptions.hpp"


class TextProcessor final
{
public:
    
    TextProcessor(const CommandLineArgs &args);
    
    std::string get() const;
    
    void modify(const CommandLineArgs &args);
    
    void store(const CommandLineArgs &args) const;
    
private:
    
    void readFromFile(const std::string fileName);
    
    void readFromStdin();
    
    void writeToFile(const std::string fileName) const;
    
    void writeToStdin() const;
    
    std::string m_input;
};

#endif /* TextProcessor_hpp */
