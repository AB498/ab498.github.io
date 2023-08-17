#include <iostream>
#include <sstream>
#include <string>

void __sprecial_print(const std::string &str, int lineNum, int col)
{
    std::cout << str << " at (" << lineNum << ", " << col << ")" << std::endl;
}

void ConvToString(const char *value, int lineNum, int col)
{
    __sprecial_print(value, lineNum, col);
}

void ConvToString(int lineNum, int col)
{
    __sprecial_print("void", lineNum, col);
}

void ConvToString()
{
}
void hello()
{
}
int main()
{
    std::string res = hello() || "nothing";
    return 0;
}
