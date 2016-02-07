//
//  commandLineOptions.hpp
//  sabreAssignment
//
//  Created by magda on 06/02/2016.
//  Copyright © 2016 Magdalena Glanowska. All rights reserved.
//

#ifndef commandLineOptions_hpp
#define commandLineOptions_hpp

#include <stdio.h>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include "commandLineArgsConstants.hpp"


class CommandLineArgs final
{
public:
    
    CommandLineArgs(int argc, const char **argv);
    
    bool findOption(const std::string &name) const;
    
    std::string getValue(const std::string &name) const;
        
    size_t count() const;
    
private:
    
    std::pair<std::string, std::string> parsePrefix(const std::string &val) const;

    void checkIfValidOption(const std::string &argument) const;
   
    void checkIfCommand(const std::string &option) const;

    std::pair<std::string, std::string> handleOption(std::string argument) const;
    
    void fillValidOptions();
    
    std::vector<std::string> m_validOptions;

    std::map<std::string, std::string> m_optionsMap;
};


#endif /* commandLineOptions_hpp */
