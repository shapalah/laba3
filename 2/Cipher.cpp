#include "cipher.h"

#include <limits>
#include <stdexcept>
cipher::cipher(int key)
{
    string z = to_string(key);
    if(z.empty()) {
        throw cipher_error("Введите ключ");
    }
    for(char c : z) {
        if(!isdigit(c)) {
            throw cipher_error("Ключ не должен содежать буквы");
        }
    }
    if(!isPlusKey(key)) {
        throw cipher_error("Ключ некорректный");
    }
    stolb = key;
}
string cipher::encrypt(string text)
{
    text = getValidOpenText(text);
    if(!isValidText(text)) {
        throw cipher_error("Текст не корректный");
    }
    stolb = isValidKey(stolb, text);
    int s = text.length();
    int str = ceil(double(s) / stolb);
    char table[str][stolb] = { ' ' };
    string res;
    int index = 0;
    for(int a = 0; a < str; ++a) {
        for(int b = 0; b < stolb; ++b) {
            table[a][b] = text[index];
            index++;
        }
    }
    for(int i = stolb - 1; i >= 0; --i) {
        for(int j = 0; j < str; ++j) {
            if(table[i][j] != ' ') {
                res += table[j][i];
            }
        }
    }
    return res;
}
string cipher::decrypt(string text)
{
    text = getValidOpenText(text);
    stolb = isValidKey(stolb, text);
    if(!isValidText(text)) {
        throw cipher_error("Text nekorrekten");
    }

    int s = text.length();
    int p = s;
    string res;
    int str = ceil(double(s) / stolb);
    char table[str][stolb];
    for(int x = 0; x < s; x++) {
        if(p % stolb != 0) {
            p++;
        } else {
            break;
        }
    }
    int n = p - s;
    int h = str - 1;
    int z = 0;
    for(int j = stolb - 1; j >= 0; --j) {
        if(z < n) {
            table[h][j] = ' ';
            z++;
        } else {
            break;
        }
    }
    int index = 0;
    for(int i = stolb - 1; i >= 0; --i) {
        for(int j = 0; j < str; ++j) {
            if(index < s and table[j][i] != ' ') {
                table[j][i] = text[index];
                index++;
            }
        }
    }
    for(int a = 0; a < str; ++a) {
        for(int b = 0; b < stolb; ++b) {
            if(table[a][b] != ' ') {
                res += table[a][b];
            }
        }
    }
    return res;
}
bool cipher::isPlusKey(int key) { return key > 0; }
inline int cipher::isValidKey(int key, string s)
{
    int z = s.size();
    if(key > (ceil(z / 2) + 3)) {
        key = (ceil(z / 2) + 3);
    }
    return key;
}
bool cipher::isValidText(const string& text)
{
    for(char c : text) {
        if(!isalpha(c)) {
            return false;
        }
    }
    return true;
}

inline std::string cipher::getValidOpenText(const std::string& s)
{
    std::string tmp;
    for(auto c : s) {
        if(isalpha(c)) {
            if(islower(c))
                tmp.push_back(toupper(c));
            else
                tmp.push_back(c);
        }
    }
    if(tmp.empty())
        throw cipher_error("Пусто");
    return tmp;
}
