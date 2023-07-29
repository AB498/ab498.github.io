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
template <typename... Args>
std::string _fne_formatted_(const std::string &format, Args... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for ''
    if (size_s <= 0)
    {
        std::cout<<("Error during formatting.");
        return 1;
    }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '' inside
}

#include <iostream>
using namespace std;
int hello()
{
    return 1;
}
int main()
{
    cout << ConvToString(hello());
    int a = 4 - ConvToString(hello());
    cout << "Hello World!";
    return 0;
}