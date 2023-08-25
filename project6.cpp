#include <iostream>
#include <string>
using namespace std;

class Product
{
public:
    string name;
    string brand;
    int price;
    Product(string n, string b, int p)
    {
        name = n;
        brand = b;
        price = p;
    }
};

class Brand
{
public:
    Product *allProducts[10];
    string name;

    void showProducts()
    {
        for (int i = 0; i < 10; ++i)
        {
            if (allProducts[i])
            {
                cout << i + 1 << ". " << allProducts[i]->name << endl;
            }
        }
    }
    void showProductInfo(int index)
    {
        cout << "Name: " << allProducts[index - 1]->name << endl;
        cout << "Brand: " << allProducts[index - 1]->brand << endl;
        cout << "Price: " << allProducts[index - 1]->price << endl;
    }
};

class Lenovo : public Brand
{
public:
    Lenovo()
    {
        allProducts[0] = new Product("Lenovo V15", "Lenovo", 50000);
        allProducts[1] = new Product("Lenovo X13", "Lenovo", 40000);
    }
};
class Apple : public Brand
{
public:
    Apple()
    {
        allProducts[0] = new Product("Apple Macbook", "Apple", 50000);
        allProducts[1] = new Product("Apple M1", "Apple", 40000);
    }
};
class HP : public Brand
{
public:
    HP()
    {
        allProducts[0] = new Product("HP G9", "HP", 50000);
        allProducts[1] = new Product("HP 15t", "HP", 40000);
    }
};

int main()
{
    Brand *allBrands[10] = {NULL};
    allBrands[0] = new Lenovo();
    allBrands[1] = new Apple();
    allBrands[2] = new HP();

    cout << "Choose option:\n"
            "1. Lenovo\n"
            "2. Apple\n"
            "3. HP\n";

    int input, input2;
    cin >> input;
    allBrands[input - 1]->showProducts();

    cin >> input2;
    allBrands[input - 1]->showProductInfo(input2);
}