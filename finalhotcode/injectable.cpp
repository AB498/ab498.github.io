#include <cstdarg>
#include <cstdio>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <stdexcept>

std::string __sprecial_print(std::string str, int lineNum, int col)
{
    std::cout << "__res_start__" + std::to_string(lineNum) + "_" + std::to_string(col) + "__";
    std::cout << str << std::endl;
    std::cout << "__res_end__" + std::to_string(lineNum) + "_" + std::to_string(col) + "__";
    return str;
}
std::string ConvToString(const std::string &value, int lineNum, int col)
{
    std::ostringstream os;
    os << value;
    __sprecial_print(os.str(), lineNum, col);
    return value;
}
template <typename T>
T ConvToStringNonPrint(const T &value)
{
    std::ostringstream os;
    os << value;
    return value;
}

template <typename T>
std::vector<T> ConvToString(const std::vector<T> &vec, int lineNum, int col)
{
    std::ostringstream os;
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i > 0)
            os << ", ";
        os << (vec[i]);
    }
    os << "]";
    __sprecial_print(os.str(), lineNum, col);
    return vec;
}

template <typename K, typename V>
std::map<K, V> ConvToString(std::map<K, V> &map, int lineNum, int col)
{
    std::ostringstream os;
    os << "{";
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        if (it != map.begin())
            os << ", ";
        os << ConvToString(it->first) << ": " << ConvToString(it->second);
    }
    os << "}";
    __sprecial_print(os.str(), lineNum, col);
    return map;
}

template <typename T>
T ConvToString(T *arr, size_t N, int lineNum, int col)
{
    std::ostringstream os;
    os << "[";
    for (size_t i = 0; i < N; ++i)
    {
        if (i > 0)
            os << ", ";
        os << ConvToString(arr[i]);
    }
    os << "]";
    __sprecial_print(os.str(), lineNum, col);
    return arr;
}

template <typename T, size_t N>
T *ConvToString(T (&arr)[N], int lineNum, int col)
{
    std::ostringstream os;
    os << "[";
    for (size_t i = 0; i < N; i++)
    {
        os << std::to_string(arr[i]);
        if (i != N - 1)
            os << ", ";
    }
    os << "]";
    __sprecial_print(os.str(), lineNum, col);
    return arr;
}
char *ConvToString(char *value, int lineNum, int col)
{
    __sprecial_print(std::string(value), lineNum, col);
    return value;
}
template <typename T>
T ConvToString(const T &value, int lineNum, int col)
{
    std::ostringstream os;
    os << value;
    __sprecial_print(os.str(), lineNum, col);
    return value;
}
char *ConvToString(const char *value, int lineNum, int col)
{
    std::ostringstream os;
    os << value;
    __sprecial_print(os.str(), lineNum, col);
    return const_cast<char *>(value);
}
void ConvToString()
{
    std::ostringstream os;
    os << "void";
    __sprecial_print(os.str(), 0, 0);
    return;
}
int FormatString(int lineNum, int col, const char *format, ...)
{
    va_list args1, args2;
    va_start(args1, format);

    // Calculate size and format into dynamic buffer
    int size = vsnprintf(nullptr, 0, format, args1) + 1;
    std::unique_ptr<char[]> buffer(new char[size]);
    vsprintf(buffer.get(), format, args1);

    va_end(args1);

    std::string str1 = std::string(buffer.get());
    __sprecial_print(str1, lineNum, col);

    va_start(args2, format);
    int printedChars = vprintf(format, args2); // Print to stdout
    va_end(args2);

    return printedChars;
}
