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
    Product *allProducts[10] = {NULL};
    string name;

    void showProducts()
    {
        for (int i = 0; i < 10; ++i)
        {
            if (allProducts[i] == NULL)
                break;
            cout << i + 1 << ". " << allProducts[i]->name << endl;
        }
    }
    void showProductInfo(int index)
    {
        cout << "Name: " << allProducts[index]->name << endl;
        cout << "Brand: " << allProducts[index]->brand << endl;
        cout << "Price: " << allProducts[index]->price << endl;
    }
};

class Lenovo : public Brand
{
public:
    Lenovo()
    {
        name = "Lenovo";
        allProducts[0] = new Product("Lenovo V15", "Lenovo", 50000);
        allProducts[1] = new Product("Lenovo X13", "Lenovo", 40000);
    }
};
class Apple : public Brand
{
public:
    Apple()
    {
        name = "Apple";
        allProducts[0] = new Product("Apple Macbook", "Apple", 50000);
        allProducts[1] = new Product("Apple M1", "Apple", 40000);
    }
};
class HP : public Brand
{
public:
    HP()
    {
        name = "HP";

        allProducts[0] = new Product("HP G9", "HP", 50000);
        allProducts[1] = new Product("HP 15t", "HP", 40000);
    }
};
class Samsung : public Brand
{
public:
    Samsung()
    {
        name = "Samsung";
        allProducts[0] = new Product("HP G9", "HP", 50000);
        allProducts[1] = new Product("HP 15t", "HP", 40000);
    }
};
class Sony : public Brand
{
public:
    Sony()
    {
        name = "Sony";
        allProducts[0] = new Product("HP G9", "HP", 50000);
        allProducts[1] = new Product("HP 15t", "HP", 40000);
    }
};
Product *cart[100] = {NULL};
Brand *pcBrands[10] = {NULL};
Brand *phoneBrands[10] = {NULL};
Brand *headphoneBrands[10] = {NULL};
Brand **allCategories[10] = {NULL};

void displayCart()
{
    for (int i = 0; i < 100; i++)
    {
        if (cart[i] == NULL)
        {
            break;
        }
        cout << cart[i]->name;
    }
}
void addToCart(int brand_index, int input2)
{

    for (int i = 0; i < 100; i++)
    {
        if (cart[i] == NULL)
        {
            cart[i] = pcBrands[brand_index]->allProducts[input2];
            break;
        }
    }
    pcBrands[brand_index]->showProductInfo(input2);
    cout << "Added to Cart";
}
void removeFromCart(int input3)
{

    for (int i = 0; i < 100; i++)
    {
        if (i == input3)
        {
            cart[i] = NULL;
            while (cart[i + 1] != NULL)
            {
                cart[i] = cart[i + 1];
                i++;
            }
            break;
        }
    }
    cout << "Removed from Cart";
}

int main()
{

    pcBrands[0] = new Lenovo();
    pcBrands[1] = new Apple();
    pcBrands[2] = new HP();
    allCategories[0] = pcBrands;

    phoneBrands[0] = new Samsung();
    allCategories[1] = phoneBrands;

    headphoneBrands[0] = new Sony();
    allCategories[2] = headphoneBrands;

    // cout << "Choose option:\n"
    //         "1. Lenovo\n"
    //         "2. Apple\n"
    //         "3. HP\n";
    int input, input2, input3;
    cout << "Choose option:\n"
            "1. BUY\n"
            "2. Remove from Cart\n"
            "3. Exit\n";

    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout << "Choose option:\n"
                "1. Laptop\n"
                "2. Phone\n"
                "3. Headphone\n";
        int choices;
        cin >> choices;
        Brand **brands = allCategories[choices - 1];
        cout << "Choose brand:\n";
        for (int i = 0; i < 10; i++)
        {
            if (brands[i] == NULL)
                break;
            cout << brands[i]->name << endl;
        }

        int choice2;
        cin >> choice2;
        Product **products = pcBrands[choice2 - 1]->allProducts;
        for (int i = 0; i < 10; i++)
        {
            if (products[i] == NULL)
                break;
            cout << products[i]->name << endl;
        }

        int choice3;
        cin >> choice3;

        cout << products[choice3 - 1]->name << " has been added";

        break;
    }
    case 2:
        displayCart();
        cout << "Enter option you want to remove: ";

        cin >> input3;
        removeFromCart(input3);
        break;
    case 3:
        break;
        exit(0);
        break;
    default:
        break;
    }
}
