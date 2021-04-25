#ifndef SIA_UTILS_LOGGERS_HPP
#define SIA_UTILS_LOGGERS_HPP

// for conversion to string
#define TEXT(x) #x

// for logging
#define LOG(severity, ...) { \
    printf("[%s] : ", #severity); \
    printf(__VA_ARGS__); \
    printf("\n"); \
}

#endif//SIA_UTILS_LOGGERS_HPP