#ifndef STRINGOP_H
#define STRINGOP_H

#include <iostream>
#include <cctype>

using std::string;
using namespace std;
class StringOp{
public:
    StringOp();
    string toUpperCase(string toMod);
    string toLowCase(string toMod);
    string validateNumber(string toValidate);
    string validateString(string toValidate);
    string reverse(string toMod);

    bool equalsNotSensible(string string1, string string2);
};

StringOp::StringOp() {};

string StringOp::toUpperCase(string toMod){
    for (int i = 0; i < toMod.length(); i++) toMod[i] = toupper(toMod[i]);
    return toMod;
}

string StringOp::toLowCase(string toMod){
    for (int i = 0; i < toMod.length(); i++) toMod[i] = tolower(toMod[i]);
    return toMod;
}

//Validar que todos sean digitos [0-9]
string StringOp::validateNumber(string toValidate){
    for(int i=0; i<toValidate.length(); i++){
        if (toValidate[i]<48 || toValidate[i]>57) throw invalid_argument("Not_Correct");
    }
    return toValidate;
}

//Validar que todos sean del alfabeto [A-Z] - [a-z]
string StringOp::validateString(string toValidate){
    for(int i=0; i<toValidate.length();i++) {
        if (!((toValidate[i]>=65 && toValidate[i]<=90)|| (toValidate[i]>=97 && toValidate[i]<=122)))
            throw invalid_argument("Not_Correct");
    }
    return  toValidate;
}

//Compares two given strings ignoring the capital letters
bool StringOp::equalsNotSensible(std::string string1, std::string string2) {
    if(toUpperCase(string1)== toUpperCase(string2)){
        return true;
    } else {
        return false;
    }
}

//Reverse a given string
string StringOp::reverse(std::string toMod) {
    string toReturn;
    for (int i = toMod.size()-1; i >=0; --i) {
        toReturn += toMod[i];
    }
    return toReturn;
}

#endif