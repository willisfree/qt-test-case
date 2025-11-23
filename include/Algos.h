#ifndef ALGOS_H
#define ALGOS_H

#include<string>
#include<iostream>

namespace Algos {

inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

inline int firstIntFromStr(const char* c_str) {
    if (!c_str) return -1;

    std::string numberOnly;
    
    for (int i=0; c_str[i] != '\0'; ++i) {
        while (isDigit(c_str[i])) {
            numberOnly += c_str[i];
            ++i;
        }
        if (numberOnly.size()) break;
    }

    std::cout << "DEBUG: " << numberOnly << '\n';
    return numberOnly.size() ? std::stoi(numberOnly) : -1;
}
}

#endif