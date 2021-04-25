/**
 * @file ArgumentParser.cpp
 * @author Siddharth Mishra
 * @date 2021-04-24
 * 
 * @copyright Copyright (c) 2021 Siddharth Mishra
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "ArgumentParser.hpp"
#include "../Loggers/Log.hpp"
#include <cstdlib>
#include <ios>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <utility>

// constructor
ArgumentParser::ArgumentParser(){
    AddOption(OptionDescription("help", "show this help message"));
}

// check whether given value is integer or not
bool IsInteger(const char* value){
    const char validChars[] = {'1','2','3','4','5','6','7','8','9','0'};
    for(size_t i=0; i<strlen(value); i++){
        bool found = false;
        for(const auto& j : validChars){
            if(value[i]==j){
                found = true;
                break;
            }
        }
        if(!found) return false;
    }
    return true;
}

// check if a given value is float or not, checks for double values too
// integers will pass this test too
bool IsFloat(const char* value){
    const char validChars[] = {'1','2','3','4','5','6','7','8','9','0','.'};
    size_t decimalCount = 0;
    for(size_t i=0; i<strlen(value); i++){
        bool found = false;
        for(const auto& j : validChars){
            if(value[i] == j) found = true;
            if(value[i] == '.') decimalCount++;
        }
        if(decimalCount>1) return false;
        if(!found) return false;
    }
    return true;
}

// check if a given value is 0 or 1
bool IsBool(const char* value){
    if(strcmp(value, "0") == 0 || strcmp(value, "1") == 0) return true;
    return false;
}

// check whether a given string is a valid option name
bool ArgumentParser::IsOption(const char* optionName){
    std::string opt(optionName);
    // check if option format is correct or not
    if(opt.find("--") == 0 && opt.size()>3){
        return true;
    }else if(opt[0]=='-' && opt.size()==2){
        return true;
    }else{
        return false;
    }
}

// check valid value type from the given value string and type
bool ArgumentParser::CheckValidValue(const char* value, const ValueType& type){
    if(type == ValueType::Integer){
        return IsInteger(value);
    }else if(type == ValueType::Float){
        return IsFloat(value);
    }else if(type == ValueType::Bool){
        return IsBool(value);
    }else{
        return true;
    }
}

OptionDescription ArgumentParser::GetOptionDescription(const char* name){
    for(const auto& option : validOptions){
        if(strcmp(name, option.name) == 0) return option;
    }
    LOG(ERROR, "Failed to find queried option (%s) type. OPTION NOT IN OPTION DESCRIPTIONS", name)
    exit(-1);
}

// parse the arguments
void ArgumentParser::ParseArguments(const uint &argc, char **argv){
    // check if argc is greater than 2
    // if not then print the help string
    if(argc < minArgumentCount){
        PrintHelpMessage();
        LOG(ERROR, "need atleast %i argument(s)", minArgumentCount)
        std::quick_exit(-1);
    }

    // stores the last option that we found and the corresponding values
    Option lastOption;
    lastOption.name = nullptr;

    // start from 1 as we don't want to include the executable name
    for(uint i=1; i<argc; i++){
        // get argument
        char* arg = argv[i];

        // check if argument is an option
        if(IsOption(arg)){
            // if we have a name then store it as option
            // else store the option name and let the loop get the option values
            if(lastOption.name != nullptr){
                parsedArgs.push_back(lastOption);
                lastOption.name = nullptr;
                lastOption.values.clear();
            }

            // if arg is an option then store it
            // if shorthand was used
            if(strlen(arg)==2){
                // get the full name
                for(const auto& option : validOptions){
                    if(arg[1]==option.shortHand){
                        lastOption.name = option.name;
                    }
                }
            }else{
                // if full form was used
                // then just skip the first two characters (--)
                lastOption.name = arg + 2;
            }

        }else{
            // if arg is not an option then it is a value
            lastOption.values.push_back(arg);
        } // end of if-else
    } // end of for loop

    // don't forget to add the last parsed option
    parsedArgs.push_back(lastOption);

    // now check whether the arguments given were valid or not
    size_t invalidArgCount = 0;
    for(const auto& option : parsedArgs){
        bool bFound = false;
        for(const auto& validOption : validOptions){
            if(strcmp(validOption.name, option.name) == 0) bFound = true;
        }
        
        // if not found
        if(!bFound){
            LOG(ERROR, "\"%s\" argument name is unknown", option.name);
            invalidArgCount++;
        }
    }

    // check whether the given values to options are valid or not
    size_t invalidValueCount = 0;
    // check for valid number of values for a given option
    size_t invalidNumberOfValuesCount = 0;
    // go through all options
    for(const auto& option : parsedArgs){
        // get option description
        OptionDescription description = GetOptionDescription(option.name);

        // check for valid value type
        for(const auto& value : option.values){
            if(!CheckValidValue(value, description.valueType)){
                LOG(ERROR, "\"%s\" given value is not of valid value type (%s)", value, GetTypeString(description.valueType))
            }
        }

        // check valid number of values
        if((option.values.size() != description.valueCount) && description.valueCount!=-1){
            LOG(ERROR, "\"%s\" option takes only %i argument(s) : %lu given", option.name, description.valueCount, option.values.size())
            invalidNumberOfValuesCount++;
        }
    }

    // check whether argument list contains -h or --help
    // if it does, then print help message and exit
    for(const auto& option : parsedArgs){
        if(strcmp(option.name, "help") == 0){
            PrintHelpMessage();
            std::quick_exit(-1);
        }
    }

    // if alteast one invalid argument is found then print the help message
    if(invalidArgCount > 0 || invalidValueCount > 0 || invalidNumberOfValuesCount > 0){
        PrintHelpMessage();
        LOG(ERROR, "invalid arguments were given")
        std::quick_exit(-1);
    }
}

// print the parsed argument with their values
void ArgumentParser::PrintArguments(){
    LOG(PRINT ARGUMENTS, "Below are detected values")
    for(const auto& option : parsedArgs){
        printf("\t%s \t : ", option.name);
        for(const auto& value : option.values){
            printf("%s ", value);
        }
        printf("\n");
    }
}

// add a valid option to check for
void ArgumentParser::AddOption(const OptionDescription& description){
    validOptions.push_back(description);
}

// print help message for all options
void ArgumentParser::PrintHelpMessage(){
    printf("\n\tList of valid options :\n");
    for(const auto& validOption : validOptions){
        if(strcmp(validOption.name, "help") == 0){
            printf("\t--help \t\t show this help message\n");
        }else{
            printf("\t--%s \t (%s) %s\n", validOption.name, GetTypeString(validOption.valueType), validOption.helpString);
        }
    }
    printf("\n");
}

// set minimum argument count to check for in ParseArguments function
void ArgumentParser::SetMinimumArgumentCount(const uint &n){
    minArgumentCount = n;
}

// get option from option name
Option* ArgumentParser::GetOption(const char *name){
    for(auto& option : parsedArgs){
        if(strcmp(option.name, name) == 0) return &option;
    }
    return nullptr;
}