//
//  TextProcessor.cpp
//  sabreAssignment
//
//  Created by magda on 06/02/2016.
//  Copyright © 2016 Magdalena Glanowska. All rights reserved.
//

#include "textProcessor.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <utility>

TextProcessor::TextProcessor(const CommandLineArgs &args)
: m_input(), m_args(args)
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

bool TextProcessor::isRangeSpecified() const
{
    if(!m_args.findOption(RANGE_FROM) != !m_args.findOption(RANGE_TO))
    {
        throw std::invalid_argument{"Unknown range. One of range options skipped."};
    }
    if(m_args.findOption(RANGE_FROM) && m_args.findOption(REPLACE_TEXT))
    {
        return true;
    }
    return false;
}

bool TextProcessor::isNumber(const std::string range) const
{
    return !range.empty() &&
            std::find_if(range.begin(), range.end(), [](char c){ return !std::isdigit(c); }) == range.end();
}

std::pair<size_t, size_t> TextProcessor::parseRange() const
{
//    if(isNumber(m_args.getValue(RANGE_FROM)) && isNumber(m_args.getValue(RANGE_TO)))
//    {
    
    size_t from = std::stoi(m_args.getValue(RANGE_FROM));
    size_t to = std::stoi(m_args.getValue(RANGE_TO));

    return std::make_pair(from, to);
//    }
//    else
//    {
//        throw std::invalid_argument{"Unknown range. Should be positive number."};
//    }
}

void TextProcessor::readInput(std::istream &input)
{
    if(!isRangeSpecified())
    {
        m_input.assign((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
    }
    else
    {
        std::pair<unsigned, unsigned> range = parseRange();
        std::string line;
        size_t lineCounter = 0;
        while(std::getline(input, line))
        {
            lineCounter++;
            if(lineCounter >= range.first && lineCounter <= range.second)
            {
                m_input += line + '\n';
            }
        }
    }

}

void TextProcessor::readFromFile(const std::string fileName)
{
    std::ifstream inputFile(fileName);
    
    if (!inputFile.is_open())
    {
        throw std::ios_base::failure("Unable to open file: " + fileName);
    }
    
    readInput(inputFile);
    inputFile.close();
}

void TextProcessor::readFromStdin()
{
    readInput(std::cin);
}

std::string TextProcessor::get() const
{
    return m_input;
}

void TextProcessor::modify()
{
    if(!m_args.findOption(MATCH_TEXT) || !m_args.findOption(REPLACE_TEXT))
    {
        throw std::invalid_argument{"Unknown text to modify."};
    }
    
    std::string matchText = m_args.getValue(MATCH_TEXT);
    std::string replaceText = m_args.getValue(REPLACE_TEXT);
    
    if(matchText.empty() || replaceText.empty())
    {
        throw std::invalid_argument{"Empty text to modify."};
    }
    
    size_t pos = 0;
    while((pos = m_input.find(matchText, pos)) != std::string::npos)
    {
        m_input.replace(pos, matchText.length(), replaceText);
        pos += replaceText.length();
    }
}

void TextProcessor::store() const
{
    if(m_args.findOption(OUTPUT_FILE))
    {
        writeToFile(m_args.getValue(OUTPUT_FILE));
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

