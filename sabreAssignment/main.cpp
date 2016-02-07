//
//  main.cpp
//  sabreAssignment
//
//  Created by magda on 06/02/2016.
//  Copyright © 2016 Magdalena Glanowska. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>      // std::stringstream
#include <exception>

#include "textProcessor.hpp"

void printUsage()
{
    std::cout << "help" <<std::endl;
}

int main(int argc, const char **argv) {
    
    try
    {
        CommandLineArgs args(argc, argv);
        if(args.findOption(HELP) || args.count() == 0)
        {
            printUsage();
            return 0;
        }
        
        try
        {
            TextProcessor text(args);
            text.modify(args);
            text.store(args);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error cuured: ";
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unable to parse command-line arguments: ";
        std::cerr << e.what() << std::endl;
        printUsage();
        return 1;
    }
    return 0;
}
