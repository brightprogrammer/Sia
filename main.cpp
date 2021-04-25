#include <Config.hpp>
#include <CommandLine/ArgumentParser.hpp>
#include <Loggers/Log.hpp>
#include <ios>
#include <iostream>

int main(int argc, char** argv){
    // create an argument parser for parsing command line arguments
    ArgumentParser cmdLineParser;
    
    // add options to check for
    cmdLineParser.AddOption(OptionDescription("source", "list of sources to compile to one file"));
    cmdLineParser.AddOption(OptionDescription("optimization", "optimization level to be used in optimization stage", ValueType::Integer, 1));
    
    // need atleast 3 arguments
    cmdLineParser.SetMinimumArgumentCount(3);

    // parse arguments
    cmdLineParser.ParseArguments(argc, argv);

    // get sources
    const char* value = "s";
    std::vector<const char*> values;
    Option *source = cmdLineParser.GetOption("source");
    while(value){
        source->GetNextValue(&value);
        if(value) values.push_back(value);
    }
}