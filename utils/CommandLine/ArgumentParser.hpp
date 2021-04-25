/**
 * @file ArgumentParser.hpp
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

#ifndef SIA_UTILS_ARGUMENT_PARSER_HPP
#define SIA_UTILS_ARGUMENT_PARSER_HPP

#include "Option.hpp"

/**
 * @brief parses arguments from given command line arguments
 * 
 */
class ArgumentParser{
    // parsed arguments
    std::vector<Option> parsedArgs;

    // check whether given option name is valid
    bool IsOption(const char* optionName);

    // check whether given value matches with the value type
    bool CheckValidValue(const char* value, const ValueType& valueType);

    // get option description for given option name
    OptionDescription GetOptionDescription(const char* name);

    // valid option names
    std::vector<OptionDescription> validOptions;

    // minimum number of arguments
    uint minArgumentCount = 0;
public:
    ArgumentParser();

    /**
     * @brief add an option for argument parser to detect.
     *        Only added options will be allowed. If argument
     *        parser detects some other arguments then it will
     *        print help string and call std::quick_exit(-1)
     * 
     * @param description is OptionDescription
     */
    void AddOption(const OptionDescription& description);

    /**
     * @brief Parse the given arguments from argument vector
     * 
     * @param argc argument count (accepted in main)
     * @param argv argument vector(accepted in main)
     */
    void ParseArguments(const uint& argc, char** argv);

    /**
     * @brief Prints the help string for valid arguments
     * 
     */
    void PrintHelpMessage();

    /**
     * @brief print the detected arguments and values
     * 
     */
    void PrintArguments();

    /**
     * @brief Reset this parser.
     *        By resetting you clear all the previous data
     *        stored in argument parser 
     * 
     */
    void Reset();

    /**
     * @brief Set the minimum argument count to check against.
     *        If argc is less than n in ParseArguments then
     *        an error message will be shown, help message will
     *        printed and program will call std::quick_exit(-1)
     *         
     *
     * @param n is minimum number of arguments parser must accept 
     */
    void SetMinimumArgumentCount(const uint& n);

    /**
     * @brief Get option by name.
     * 
     * @param name of option
     * @return Option pointer, nullptr is returned if option was not found.
     */
    Option* GetOption(const char* name);
};

#endif//SIA_UTILS_ARGUMENT_PARSER_HPP