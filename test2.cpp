#include <iostream>
#include <vector>
using namespace std;
class BaseClass
{
public:
    virtual string getInfo()
    {
        return "Original";
    }
};
class DerivedClass : public BaseClass
{
public:
    string getInfo() override
    {
        return "Overridden";
    }
};
vector<BaseClass *> list;
int main()
{
    DerivedClass *derived = new DerivedClass();
    list.push_back(derived);
    cout << derived->getInfo() << endl; // output: Overridden
    cout << list[0]->getInfo() << endl; // output: Original
}