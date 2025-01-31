#ifndef CONVERTER_H
#define CONVERTER_H

#include <map>


class Converter
{
public:
    Converter();
    explicit Converter(const std::string &originStr, int base = 10);

    bool isValid();
    bool validateString(const std::string &str);
    int toInt();
    int getBase();
    std::string convertToBase(int base);
    void printAllBases();
private:
    int base {0};
    int number;
    bool valid {false};
    std::string numstr;
    const std::string alphabet {"0123456789abcdef"};
    std::map<char, int> orders;
    std::map<int, std::string> prefixes;

};

#endif // CONVERTER_H
