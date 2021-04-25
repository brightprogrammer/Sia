/**
 * @file Option.hpp
 * @author Siddharth Mishra
 * @date 2021-04-25
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

#ifndef SIA_UTILS_COMMAND_LINE_OPTION_HPP
#define SIA_UTILS_COMMAND_LINE_OPTION_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <cstring>

// parsed option
struct Option{
    // name of option
    const char* name = nullptr;
    // values are value type cast compatible string values
    std::vector<const char*> values;

    /**
     * @brief reset option to clear state
     * 
     */
    void Reset(){
        name = nullptr;
        values.clear();
        nextIdx = 0;
    }

    /**
     * @brief Get string value
     * 
     * @param value is pointer to string in which value will be stored.
     *        if idx is greater than the number of values then nullptr is
     *        stored in value
     * @param idx of value of get. It is automatically increated by one on each call
     */
    void GetValue(const char** value, size_t& idx){
        if(idx < values.size()){
            *value = values[idx];
            idx++;
        }
        else *value = nullptr;
    }

    /**
     * @brief Get integer value
     * 
     * @param value is pointer to integer in which value will be stored
     *        if idx is greater than the number of values then nullptr is
     *        stored in value
     * @param idx of value to get. It is automatically increated by one on each call
     */
    void GetValue(int* value, size_t& idx){
        if(idx < values.size()){
            *value = atoi(values[idx]);
            idx++;
        }
        else value = nullptr;
    }

    /**
     * @brief Get float value
     * 
     * @param value is pointer to float in which value will be stored
     *        if idx is greater than the number of values then nullptr is
     *        stored in value
     * @param idx of value to get. It is automatically increated by one on each call
     */
    void GetValue(float* value, size_t& idx){
        if(idx < values.size()){
            *value = atof(values[idx]);
            idx++;
        }
        else value = nullptr;
    }

    /**
     * @brief Get boolean value
     * 
     * @param value is pointer to boolean in which value will be stored
     *        if idx is greater than the number of values then nullptr is
     *        stored in value
     * @param idx of value to get. It is automatically increated by one on each call
     */
    void GetValue(bool* value, size_t& idx){
        if(idx < values.size()){
            // if false
            if(strcmp(values[idx], "0") == 0){
                *value = false;
            }else *value = true;
            idx++;
        }
        else value = nullptr;
    }

    /// get next value
    void GetNextValue(const char** value){
        GetValue(value, nextIdx);
    }

    /// get next value
    void GetNextValue(int* value){
        GetValue(value, nextIdx);
    }

    /// get next value
    void GetNextValue(float* value){
        GetValue(value, nextIdx);
    }

    /// get next value
    void GetNextValue(bool* value){
        GetValue(value, nextIdx);
    }
private : 
    size_t nextIdx = 0;
};

// type of value
enum class ValueType : uint{
    Integer     = 0,
    Float       = 1,
    String      = 2,
    Bool        = 3
};

// get ValueType string
inline const char* GetTypeString(const ValueType& type){
    if(type==ValueType::Integer){
        return "int";
    }else if(type==ValueType::Float){
        return "float";
    }else if(type== ValueType::String){
        return "string";
    }else{
        return "bool";
    }
}

/**
 * @brief use this struct for describing about the
 *        options that are accepted by the parser.
 * 
 */
struct OptionDescription{
    /**
     * @brief Construct a new Option Description object
     * 
     * @param name name of option
     * @param helpString help string for option
     * @param valueType what type of value to accept
     * @param valueCount number of values to be accepted for option (-1 means infinite values)
     */
    OptionDescription(const char* name, const char* helpString, const ValueType& valueType = ValueType::String, int valueCount = -1)
    : name(name), helpString(helpString), valueType(valueType), valueCount(valueCount){
        // short hand is initial of help string until unless explicitly stated
        shortHand = name[0];
    }
    
    /// option name
    const char* name;
    
    /// option help string
    const char* helpString;
    
    /**
     * @brief option short hand notation, for eg : for --source it will be -s
     *        argument parser won't check conflicting shorthand notations
     */
    char shortHand;

    /**
     * @brief Type of value this option must have
     *        the values are stored as string
     *        but they are loaded in such a way that
     *        they can be easily typecasted to their
     *        desired types
     */
    ValueType valueType;

    ///exact number of values the option will take
    int valueCount;
};

#endif//SIA_UTILS_COMMAND_LINE_OPTION_HPP