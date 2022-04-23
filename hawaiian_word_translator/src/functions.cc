#include "functions.hpp"
#include <string>
#include <vector>
#include <iostream>
// Your function definitions should go in this source file.

bool CheckValid(std::string word) {
    bool valid = true;
    std::vector<char> vect = {' ', 'a', 'e', 'i', 'o', 'u', 'p', 'k', 'h', 'l', 'm', 'n', 'w', '\''};
    for (unsigned i = 0; i < word.length(); i++) {
        int a = 0;
        for (unsigned j = 0; j < vect.size(); j++) {
            if (word[i] == vect[j]) {
                a = 1;
            }
        }
        if (a == 0) {
            valid = false;
        }
    }
    return valid;
}

std::string Transform(std::string word) {
    std::string output;
    for (unsigned i = 0; i < word.length(); i++) {
        char c = word[i];
        if (c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n'
        || c == ' ' || c == '\'') {
            output += c;  
        } else if (c == 'o') {
            std::string o = TransformO(word, i);
            output += o;
            if (o == "oy" || o == "ow" || o == "ow-" || o == "oy-") {
                i++;}
        } else if (c == 'u') {
            std::string u = TransformU(word, i);
            output += u;
            if (u == "ooey" || u == "ooey-") {
                i++;}
        } else if (c == 'i') {
            std::string wordi = TransformI(word, i);
            output += wordi;
            if (wordi == "ew" || wordi == "ew-") {
                i++;}
        } else if (c == 'e') {
            std::string worde = TransformE(word, i);
            output += worde;
            if (worde == "ay" || worde == "ay-" || worde == "eh-oo" || worde == "eh-oo-" ) {
                i++;}
        } else if (c == 'a') {
            std::string worda = TransformA(word, i);
            output += worda;
            if (worda == "eye" || worda == "eye-" || worda == "ow" || worda == "ow-" ) {
                i++;}
        } else if (c == 'w') {
            std::string wordw = TransformW(word, i);
            output += wordw;
        }
    }
    return output;
}

std::string TransformW(std::string word, unsigned index) {
    std::string out;
    if (index == 0 || word[index-1] == 'a' || word[index-1] == 'u' || word[index-1] == 'o') {
        out += 'w';
    } else if (word[index-1] == 'i' || word[index-1] == 'e') {
        out += 'v';
    }
    return out;
}

std::string TransformA(std::string word, unsigned index) {
    std::string out;
    if (index + 1 < word.length()) {
        if (word[index+1] == 'i' || word[index+1] == 'e') {
            out += "eye";
            if (index != word.length() - 1) {
                out += '-';
            }
        } else if (word[index+1] == 'o' || word[index+1] == 'u') {
            out += "ow";
            if (index != word.length() - 1) {
                out += '-';
            }
        } else {
            out += "ah";
            if (word[index+1] != ' ' && word[index+1] != '\'') {
                out += '-';
            }
        }
    } else {
        out += "ah";
    }
    return out;
}

std::string TransformE(std::string word, unsigned index) {
    std::string out;
    if (index + 1 < word.length()) {
        if (word[index+1] == 'i') {
            out += "ay";
            if (index != word.length() - 1) {
                out += '-';
            }
        } else if (word[index+1] == 'u') {
            out += "eh-oo";
            if (index != word.length() - 1) {
                out += '-';
            }
        } else {
            out += "eh";
            if (word[index+1] != ' ' && word[index+1] != '\'') {
                out += '-';
            }
        }
    } else {
        out += "eh";
    }
    return out;   
}

std::string TransformI(std::string word, unsigned index) {
    std::string out;
    if (index + 1 < word.length()) {
        if (word[index+1] == 'u') {
            out += "ew";
            if (index != word.length() - 1) {
                out += '-';
            }
        } else {
            out += "ee";
            if (word[index+1] != ' ' && word[index+1] != '\'') {
                out += '-';
            }
        }
    } else {
        out += "ee";
    }
    return out;
}

std::string TransformU(std::string word, unsigned index) {
    std::string out;
    if (index + 1 < word.length()) {
        if (word[index+1] == 'i') {
            out += "ooey";
            if (index != word.length() - 1) {
                out += '-';
            }
        } else {
            out += "oo";
            if (word[index+1] != ' ' && word[index+1] != '\'') {
                out += '-';
            }
        }
    } else {
        out += "oo";
    }
    return out;
}

std::string TransformO(std::string word, unsigned index) {
    std::string out;
    if (index + 1 < word.length()) {
        if (word[index + 1] == 'i') {
            out += "oy";
            if (index != word.length() - 1) {
                out += '-';
            }
        } else if (word[index + 1] == 'u') {
            out += "ow";
            if (index != word.length() - 1) {
                out += '-';
            }
        } else {
            out += "oh";
            if (word[index+1] != ' ' && word[index+1] != '\'') {
                out += '-';
            }
        }
    } else {
        out += "oh";
    }
    return out;
}