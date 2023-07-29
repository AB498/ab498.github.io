#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
std::string ConvToString(const T &value)
{
    std::cout << "_res_";
    std::ostringstream os;
    os << value;
    return os.str();
}

template <typename T>
std::string ConvToString(const std::vector<T> &vec)
{
    std::ostringstream os;
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i > 0)
            os << ", ";
        os << ConvToString(vec[i]);
    }
    os << "]";
    return os.str();
}

template <typename K, typename V>
std::string ConvToString(const std::map<K, V> &map)
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
    return os.str();
}

template <typename T>
std::string ConvToString(const T *arr, size_t N)
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
    return os.str();
}

template <typename T, size_t N>
std::string ConvToString(const T (&arr)[N])
{
    std::ostringstream os;
    os << "[";
    for (size_t i = 0; i < N; i++)
    {
        os << ConvToString(arr[i]);
        if (i != N - 1)
            os << ", ";
    }
    os << "]";
    return os.str();
}
std::string ConvToString(const char *value)
{
    return std::string(value);
}

#include <iostream>
using namespace std;
int hello()
{
    return 1;
}
int main()
{
    there
    hello();
    int a = 4 - ConvToString(hello());
    cout << "Hello World!";
    return 0;
}