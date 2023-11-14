#include <set>
#include <stack>
#include <queue>
#include <cstdarg>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>

std::string _special_print(std::string str, int lineNum, int col)
{
    std::cout << "__res_start__" + std::to_string(lineNum) + "_" + std::to_string(col) + "__";
    std::cout << str;
    std::cout << "__res_end__" + std::to_string(lineNum) + "_" + std::to_string(col) + "__";
    return str;
}

template <typename T>
auto strinfigy_auto(const T &obj, typename std::enable_if<!std::is_convertible<T, std::string>::value>::type * = nullptr)
{
    return "[Object]";
}

std::string strinfigy_auto(const std::string obj)
{
    return obj;
}
std::string strinfigy_auto(char obj)
{
    return std::string(1, obj);
}
std::string strinfigy_auto(int obj)
{
    return std::to_string(obj);
}
std::string strinfigy_auto(float obj)
{
    return std::to_string(obj);
}
std::string strinfigy_auto(double obj)
{
    return std::to_string(obj);
}
std::string strinfigy_auto(short obj)
{
    return std::to_string(obj);
}
std::string strinfigy_auto(long obj)
{
    return std::to_string(obj);
}
std::string strinfigy_auto(long long obj)
{
    return std::to_string(obj);
}
std::string strinfigy_auto(unsigned int obj)
{
    return std::to_string(obj);
}
std::string strinfigy_auto(unsigned long obj)
{
    return std::to_string(obj);
}

template <typename... Args>
std::string strinfigy_auto(std::map<Args...> obj);
template <typename... Args>
std::string strinfigy_auto(std::vector<Args...> obj);

template <typename... Args>
std::string strinfigy_auto(std::vector<Args...> obj)
{
    std::ostringstream os;
    os << "[";
    for (auto it = obj.begin(); it != obj.end(); it++)
    {
        os << strinfigy_auto(*it);
        if (it != prev(obj.end()))
            os << ", ";
    }
    os << "]";
    return os.str();
}
template <typename... Args>
std::string strinfigy_auto(std::map<Args...> obj)
{
    std::ostringstream os;
    os << "{";
    for (auto it = obj.begin(); it != obj.end(); it++)
    {
        os << it->first << ": " << strinfigy_auto(it->second);
        if (it != prev(obj.end()))
            os << ", ";
    }
    os << "}";
    return os.str();
}
template <typename... Args>
std::string strinfigy_auto(std::queue<Args...> obj)
{
    std::ostringstream os;
    os << "[";
    while (!obj.empty())
    {
        os << strinfigy_auto(obj.front());
        obj.pop();
        if (!obj.empty())
            os << ", ";
    }
    os << "]";
    return os.str();
}
template <typename... Args>
std::string strinfigy_auto(std::stack<Args...> obj)
{
    std::ostringstream os;
    os << "[";
    while (!obj.empty())
    {
        os << strinfigy_auto(obj.top());
        obj.pop();
        if (!obj.empty())
            os << ", ";
    }
    os << "]";
    return os.str();
}
template <typename... Args>
std::string strinfigy_auto(std::set<Args...> obj)
{
    std::ostringstream os;
    os << "{";
    for (auto it = obj.begin(); it != obj.end(); it++)
    {
        os << strinfigy_auto(*it);
        if (it != prev(obj.end()))
            os << ", ";
    }
    os << "}";
    return os.str();
}

template <typename T>
T _conv_string(T value, int lineNum = 0, int col = 0)
{
    std::string s = strinfigy_auto(value);
    _special_print(s, lineNum, col);
    return value;
}
template <typename T>
T _conv_string(int value, int lineNum = 0, int col = 0)
{
    std::string s = strinfigy_auto(value);
    _special_print(s, lineNum, col);

    return value;
}
template <typename T>
T _conv_string(std::string value, int lineNum = 0, int col = 0)
{
    std::string s = strinfigy_auto(value);
    _special_print(s, lineNum, col);

    return value;
}
int _special_printf(int lineNum, int col, const char *format, ...)
{
    va_list args1, args2;
    va_start(args1, format);

    // Calculate size and format into dynamic buffer
    int size = vsnprintf(nullptr, 0, format, args1) + 1;
    std::unique_ptr<char[]> buffer(new char[size]);
    vsprintf(buffer.get(), format, args1);

    va_end(args1);

    std::string str1 = std::string(buffer.get());
    _special_print(str1, lineNum, col);

    va_start(args2, format);
    int printedChars = vprintf(format, args2); // Print to stdout
    va_end(args2);

    return printedChars;
};
