#include <iostream>
#include "converter.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Please run as: " << argv[0]
                  << " <number_to_convert>" << std::endl;
        std::cout << "Example: " << argv[0] <<
                     " 254" << std::endl;
        return 0;
    }

    Converter cc{};
    if (!cc.validateString(argv[1]))
    {
        std::cout << "Input correct number " << std::endl;
        return 0;
    }
    std::cout << "Original base is: " << cc.getBase() << std::endl;
    std::cout << "Original value: " << argv[1] << std::endl;

    cc.toInt();
    cc.printAllBases();

    return 0;
}
