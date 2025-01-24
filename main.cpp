#include <iostream>
#include "converter.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Please run as: " << argv[0] << " <number_to_convert>" << endl;
        cout << "Example: " << argv[0] << " 254" << endl;
        return 0;
    }

    Converter conv;
    cout << "Original value: " << argv[1] << endl;

    if (!conv.validateString(argv[1]))
    {
        cout << "Input correct number " << endl;
        return 0;
    }

    conv.toInt();
    conv.printAllBases();

    return 0;
}
