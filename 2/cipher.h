#pragma once
#include <string>
#include <locale>
#include <iostream>
#include <map>
#include <stdexcept>
#include <cmath>
using namespace std;

class cipher_error : public std::invalid_argument
{
public:
    explicit cipher_error(const std::string& what_arg): 
    std::invalid_argument(what_arg){}
    explicit cipher_error(const char* what_arg): 
    std::invalid_argument(what_arg){}
};

class cipher {
private:
    int stolb;
    int isValidKey(int key,string s); 
    bool isPlusKey(int key);
    bool isValidText(const string& text);
    string getValidOpenText(const std::string& s);
    
public:
    cipher(int key);
    cipher() = delete;
    string encrypt(string text);
    string decrypt(string text);
};
