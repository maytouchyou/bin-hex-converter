#include "converter.h"
#include "string.h"
#include <iostream>


Converter::Converter(const char *originStr, int defaultBase) :
    alphabet("0123456789abcdef"),
    base(defaultBase),
    number(-1),
    valid(false)
{
    prefixes[2] = "b";
    prefixes[10] = "";
    prefixes[16] = "0x";

    if (originStr)
        numstr = strdup(originStr);

    for (size_t i = 0; i < strlen(alphabet); i++)
    {
        orders.insert(pair<char,int>(alphabet[i], i));
    }
}

Converter::Converter() : Converter(nullptr)
{}

bool Converter::isValid()
{
    return valid;
}

int Converter::getBase()
{
    return base;
}

bool Converter::validateString(const char *str)
{
    if (!numstr)
        delete [] numstr;

    numstr = strdup(str);
    size_t prefixlen = 0;

    for (auto it = prefixes.begin(); it != prefixes.end(); ++it)
    {
        prefixlen = strlen((*it).second);

        if ((*it).first == 10)
            continue;

        if (!strncmp(str, (*it).second, prefixlen))
            base = (*it).first;
    }

    prefixlen = strlen(prefixes[base]);

    if (prefixlen == strlen(str)) // empty string
        return false;

    for (size_t i = prefixlen; i < strlen(str); i++)
    {
        if ((str[i] < alphabet[0]) || (str[i] > alphabet[base-1]))
        {
            return false;
        }
    }

    return (valid = true);
}

int Converter::toInt()
{
    if (valid)
    {
        int sum = 0, basepow = 1;
        int prefixlen = strlen(prefixes[base]);

        for (int i = strlen(numstr) - 1; i >= prefixlen; i--)
        {
            sum += basepow * orders[numstr[i]];
            basepow *= base;
        }

        number = sum;
    }
    return number;
}

char* Converter::converToBaseString(int tobase)
{
    int bodylen = 1, num = number;

    do { bodylen++; } while ((num /= tobase) > 0);

    int prefixlen = strlen(prefixes[tobase]);
    int len = prefixlen + bodylen;

    char *strconv = new char[len];
    strcpy(strconv, prefixes[tobase]);

    int i;
    for (num = number, i = len - 2; i >= prefixlen; i--)
    {
        int div = num % tobase;
        strconv[i] = alphabet[div];
        num = num / tobase;
    }

    strconv[len-1] = '\0';
    return strconv;
}

void Converter::printAllBases()
{
    if (valid)
    {
        for (auto it = prefixes.begin(); it != prefixes.end(); ++it)
        {
            if ((*it).first == base)
                continue;

            char *res = converToBaseString((*it).first);
            std::cout << "Number in " << (*it).first << " base: " << res << std::endl;

            delete [] res;
        }
    }
}
