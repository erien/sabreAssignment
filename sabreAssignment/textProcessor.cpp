//
//  TextProcessor.cpp
//  sabreAssignment
//
//  Created by magda on 06/02/2016.
//  Copyright © 2016 Magdalena Glanowska. All rights reserved.
//

#include "TextProcessor.hpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <streambuf>


TextProcessor::TextProcessor(const CommandLineArgs &args) : m_input()
{
    if(args.findOption(INPUT_FILE))
    {
        readFromFile(args.getValue(INPUT_FILE));
    }
    else
    {
        readFromStdin();
    }
}

void TextProcessor::readFromFile(const std::string fileName)
{
    std::ifstream inputFile (fileName);
    
    if (!inputFile.is_open())
    {
        throw std::ios_base::failure("Unable to open file: " + fileName);
    }
    
    m_input.assign((std::istreambuf_iterator<char>(inputFile)), (std::istreambuf_iterator<char>()));
    inputFile.close();
}

void TextProcessor::readFromStdin()
{
    m_input.assign((std::istreambuf_iterator<char>(std::cin)), (std::istreambuf_iterator<char>()));
}

std::string TextProcessor::get() const
{
    return m_input;
}

void TextProcessor::modify(const CommandLineArgs &args) 
{
    if(!args.findOption(MATCH_TEXT) || !args.findOption(REPLACE_TEXT))
    {
        throw std::invalid_argument{"Unknown text to modify."};
    }
    
    std::string matchText = args.getValue(MATCH_TEXT);
    std::string replaceText = args.getValue(REPLACE_TEXT);
    size_t pos = 0;
    
    while((pos = m_input.find(matchText, pos)) != std::string::npos)
    {
        m_input.replace(pos, matchText.length(), replaceText);
        pos += replaceText.length();
    }
}

void TextProcessor::store(const CommandLineArgs &args) const
{
    if(args.findOption(OUTPUT_FILE))
    {
        writeToFile(args.getValue(OUTPUT_FILE));
    }
    else
    {
        writeToStdin();
    }
}

void TextProcessor::writeToFile(const std::string fileName) const
{
    std::ofstream outputFile (fileName);
    
    if (!outputFile.is_open())
    {
        throw std::ios_base::failure("Unable to open file: " + fileName);
    }
    
    outputFile << m_input;
    outputFile.close();
}

void TextProcessor::writeToStdin() const
{
    std::cout << m_input;
}

