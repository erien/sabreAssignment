//
//  CommandLineArgs.cpp
//  sabreAssignment
//
//  Created by magda on 06/02/2016.
//  Copyright © 2016 Magdalena Glanowska. All rights reserved.
//

#include "commandLineArgs.hpp"
#include <algorithm>
#include <iostream>


void CommandLineArgs::fillValidOptions()
{
    // TODO: m_validOptions - vector should hold args constants with descriptions
    m_validOptions = {HELP, INPUT_FILE, OUTPUT_FILE, MATCH_TEXT, REPLACE_TEXT, RANGE_FROM, RANGE_TO};
}

void CommandLineArgs::printUsage() const
{
    std::cout << "Valid command line options:" << std::endl;
    // TODO: m_validOptions - vector should hold args constants with descriptions
    for(std::vector<std::string>::const_iterator it = m_validOptions.begin() ; it != m_validOptions.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "Usage: [OPTION]=[OPTION_VALUE]" << std::endl;
}

std::string CommandLineArgs::getValue(const std::string &name) const
{
    std::string ret;
    auto pos = m_optionsMap.find(name);
    
    if(pos != std::end(m_optionsMap))
    {
        ret = pos->second;
    }
    return ret;
}

bool CommandLineArgs::findOption(const std::string &name) const
{
    return (m_optionsMap.find(name)) != std::end(m_optionsMap);
}

CommandLineArgs::CommandLineArgs(int argc, const char **argv)
{
    std::deque<std::string> intermediateValues(argv + 1, argv + argc);
    fillValidOptions();
    
    while(!intermediateValues.empty())
    {
        auto argument = intermediateValues.front();
        checkIfCommand(argument);
        intermediateValues.pop_front();
        
        auto optionPair = handleOption(argument);
        checkIfValidOption(optionPair.first);
        m_optionsMap.insert({optionPair.first, optionPair.second});
    }
}

void CommandLineArgs::checkIfCommand(const std::string &option) const
{
    if(option.compare(0, 2, "--") != 0)
    {
        throw std::invalid_argument{"Invalid argument (" + option + ")"};
    }
}

std::pair<std::string, std::string>
CommandLineArgs::handleOption(std::string argument) const
{
    std::string optionValue;
    auto prefixedOption = parsePrefix(argument);
    
    if(!prefixedOption.first.empty())
    {
        argument = prefixedOption.first;
        optionValue = prefixedOption.second;
    }

    return {argument, optionValue};
}

std::pair<std::string, std::string>
CommandLineArgs::parsePrefix(const std::string &val) const
{
    std::pair<std::string, std::string> optionPair;
    
    for(const auto &option : m_validOptions)
    {
        auto prefix = std::string(option).append("=");

        if(!val.compare(0, prefix.size(), prefix))
        {
            optionPair = {option, val.substr(prefix.size())};
            break;
        }
    }
    return optionPair;
}

void CommandLineArgs::checkIfValidOption(const std::string &argument) const
{
    if(std::find(m_validOptions.begin(), m_validOptions.end(), argument) == m_validOptions.end())
    {
        throw std::invalid_argument{"Unknown argument (" + argument + ")"};
    }
}

size_t CommandLineArgs::count() const
{
    return m_optionsMap.size();
}


