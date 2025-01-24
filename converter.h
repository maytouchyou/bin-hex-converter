#ifndef CONVERTER_H
#define CONVERTER_H

#include <map>

using namespace std;

class Converter
{
public:
    Converter();
    Converter(const char *originStr, int defaultBase = 10);

    bool isValid();
    bool validateString(const char *str);
    int toInt();
    int getBase();
    char* converToBaseString(int tobase);
    void printAllBases();
private:
    const char * const alphabet;
    map<char, int> orders;
    map<int, const char*> prefixes;
    int base;
    int number;
    char *numstr;
    bool valid;
};

#endif // CONVERTER_H
