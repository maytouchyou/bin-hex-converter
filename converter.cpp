#include "converter.h"
#include <iostream>


Converter::Converter() : Converter(std::string{})
{}

Converter::Converter(const std::string &originStr, int base) :
    base{base},
    numstr{originStr},
    prefixes{{2, "b"}, {8, "0o"}, {5, "5x"},
             {10, ""}, {16, "0x"}}
{
    for (size_t i = 0; i < alphabet.length(); i++)
    {
        orders.insert(std::pair<char,int>(alphabet[i], i));
    }

    valid = validateString(numstr);
}

/**
 * Validness of passed numerical value in class
*/
bool Converter::isValid() const
{
    return valid;
}

/**
 * Base of passed numerical value in class
*/
int Converter::getBase() const
{
    return base;
}

/**
 * Check of alphabet consistency & number's base
*/
bool Converter::validateString(const std::string &origNum)
{
    auto setValid(
                [this](auto n, auto v){ numstr = n, valid = v; }
    );
    setValid("", false);

    for (auto it = prefixes.begin(); it != prefixes.end(); ++it)
    {
        if ((*it).first == 10)
            continue;

        if (origNum.find((*it).second) != origNum.npos)
        {
            base = (*it).first;
            break;
        }
    }

    for (auto i = prefixes[base].length(); i < origNum.length(); i++)
    {
        if ((origNum[i] < alphabet[0]) || (origNum[i] > alphabet[base-1]))
        {
            return false;
        }
    }
    setValid(origNum, true);
    return true;
}

/**
 * Decimal storage value of number as INT
*/
int Converter::toInt()
{
    if (valid)
    {
        int sum = 0, basepow = 1;
        int prefixlen = prefixes[base].length();

        for (int i = numstr.length() - 1; i >= prefixlen; i--)
        {
            sum += basepow * orders[numstr[i]];
            basepow *= base;
        }
        number = sum;
    }
    return number;
}

/**
 * Numerical representation of number in fixed base
*/
std::string Converter::convertToBase(int base) const
{
    int num = number;
    const auto &prefix = prefixes.at(base);
    std::string res;

    while (num > 0)
    {
        int div = num % base;
        res.insert(begin(res), alphabet[div]);
        num = num / base;
    }
    res.insert(begin(res), begin(prefix), end(prefix));
    return res;
}

/**
 * Print number in all registered numerical systems
*/
void Converter::printAllBases() const
{
    if (valid)
    {
        for (auto it = prefixes.begin(); it != prefixes.end(); ++it)
        {
            if ((*it).first == base)
                continue;

            std::string res = convertToBase((*it).first);
            std::cout << "Number in " << (*it).first
                      << " base: " << res << std::endl;
        }
    }
    else {
        std::cout << "Incorrect passed value: " << numstr << std::endl;
    }
}
