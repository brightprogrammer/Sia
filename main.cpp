#include "Config.hpp"
#include <CommandLine/ArgumentParser.hpp>
#include <Lexer/Token.hpp>
#include <Loggers/Log.hpp>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>

std::vector<Token> tokens;

class FileReader{
    std::ifstream file;
public:
    FileReader() = default;
    FileReader(const char* filename);

    /**
     * @brief load file for reading
     * 
     * @param filename 
     */
    void LoadFile(const char* filename);

    /**
     * @brief get next character in argument passed
     * 
     * @param c : reference to char to store next character in
     * @return true continue reading
     * @return false end of file reached
     */
    bool Next(char& c);
};

// constructor
FileReader::FileReader(const char* filename){
    file.open(filename);
}

// load file
void FileReader::LoadFile(const char *filename){
    file.open(filename);
}

// get next character
bool FileReader::Next(char& c){
    file.get(c); // get next character
    return !file.eof();
}

void LexFile(const char* filename){
    LOG(INFO, "lexing %s ...", filename)
    FileReader file(filename);
    char c;
    while(file.Next(c)){
        
    }
    LOG(INFO, "lexing %s ... done", filename)
}

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

    Option* sources = cmdLineParser.GetOption("source");
    if(sources){
        const char* filename;
        sources->GetNextValue(&filename);
        LexFile(filename);
    }else{
        LOG(ERROR, "no sources were provided to compile");
        std::quick_exit(-1);
    }
}