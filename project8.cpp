#include <iostream>
#include <string>
using namespace std;
class friend_class;

class Cart;

class store
{
protected:
    string name;
    double price;

public:
    store(const string &n, double p) : name(n), price(p) {}
    string getName() const
    {
        return name;
    }
    double getPrice() const
    {
        return price;
    }
    virtual void displayDetails(){};
    friend class friend_class;
};
class Product
{
private:
    string name;
    double price;

public:
    Product(const string &n, double p) : name(n), price(p) {}
    string getName()
    {
        return name;
    }
    double getPrice()
    {
        return price;
    }
};
class User
{
private:
    string username;
    string password;

public:
    User(const string &u, const string &p) : username(u), password(p) {}
    string getUsername() const
    {
        return username;
    }
    bool authenticate(const string &inputPassword) const
    {
        return inputPassword == password;
    }
};
class Cart
{
public:
    Product **products;
    int itemCount;
    int capacity;
    Product **phoneProducts;
    int phoneCount;
    int phoneCapacity;
    Product **laptopProducts;
    int laptopCount;
    int laptopCapacity;
    Product **headphoneProducts;
    int headphoneCount;
    int headphoneCapacity;

public:
    Cart() : products(NULL), itemCount(0), capacity(0),
             phoneProducts(NULL), phoneCount(0), phoneCapacity(0),
             laptopProducts(NULL), laptopCount(0), laptopCapacity(0),
             headphoneProducts(NULL), headphoneCount(0), headphoneCapacity(0) {}
    void addToPhoneCart(Product *product)
    {
        if (phoneCount >= phoneCapacity)
        {
            PhoneCapacity();
        }
        phoneProducts[phoneCount++] = product;
    }
    void addToLaptopCart(Product *product)
    {
        if (laptopCount >= laptopCapacity)
        {
            LaptopCapacity();
        }
        laptopProducts[laptopCount++] = product;
    }
    void addToHeadphoneCart(Product *product)
    {
        if (headphoneCount >= headphoneCapacity)
        {
            HeadphoneCapacity();
        }
        headphoneProducts[headphoneCount++] = product;
    }
    void PhoneCapacity()
    {
        int newCapacity;
        if (phoneCapacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = phoneCapacity * 2;
        }
        Product **temp = new Product *[newCapacity];
        for (int i = 0; i < phoneCount; ++i)
        {
            temp[i] = phoneProducts[i];
        }
        delete[] phoneProducts;
        phoneProducts = temp;
        phoneCapacity = newCapacity;
    }
    void LaptopCapacity()
    {
        int newCapacity;
        if (laptopCapacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = laptopCapacity * 2;
        }
        Product **temp = new Product *[newCapacity];
        for (int i = 0; i < laptopCount; ++i)
        {
            temp[i] = laptopProducts[i];
        }
        delete[] laptopProducts;
        laptopProducts = temp;
        laptopCapacity = newCapacity;
    }
    void HeadphoneCapacity()
    {
        int newCapacity;
        if (headphoneCapacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = headphoneCapacity * 2;
        }
        Product **temp = new Product *[newCapacity];
        for (int i = 0; i < headphoneCount; ++i)
        {
            temp[i] = headphoneProducts[i];
        }
        delete[] headphoneProducts;
        headphoneProducts = temp;
        headphoneCapacity = newCapacity;
    }
    void removePhoneCart(int index)
    {
        if (index >= 0 && index < phoneCount)
        {
            delete phoneProducts[index];
            for (int i = index; i < phoneCount - 1; ++i)
            {
                phoneProducts[i] = phoneProducts[i + 1];
            }
            phoneCount--;
            cout << "Phone count " << phoneCount;
        }
    }
    void removeLaptopCart(int index)
    {
        if (index >= 0 && index < laptopCount)
        {
            delete laptopProducts[index];
            for (int i = index; i < laptopCount - 1; ++i)
            {
                laptopProducts[i] = laptopProducts[i + 1];
            }
            laptopCount--;
        }
    }
    void removeHeadphoneCart(int index)
    {
        if (index >= 0 && index < headphoneCount)
        {
            delete headphoneProducts[index];
            for (int i = index; i < headphoneCount - 1; ++i)
            {
                headphoneProducts[i] = headphoneProducts[i + 1];
            }
            headphoneCount--;
        }
    }
    void displayCart()
    {
        cout << "My shopping cart";
        cout << endl;
        cout << "Phones:\n";
        for (int i = 0; i < phoneCount; ++i)
        {
            cout << i + 1 << ". " << phoneProducts[i]->getName() << " - $" << phoneProducts[i]->getPrice() << endl;
        }
        cout << "Laptops:\n";
        for (int i = 0; i < laptopCount; ++i)
        {
            cout << i + 1 << ". " << laptopProducts[i]->getName() << " - $" << laptopProducts[i]->getPrice() << endl;
        }
        cout << "Headphones:\n";
        for (int i = 0; i < headphoneCount; ++i)
        {
            cout << i + 1 << ". " << headphoneProducts[i]->getName() << " - $" << headphoneProducts[i]->getPrice() << endl;
        }
        int totalItems = phoneCount + laptopCount + headphoneCount;
        cout << "Total items in cart: " << totalItems << endl;
    }
};
Cart cart;

class Laptop : public store
{
private:
    int ram;
    int storage;
    int battery;

public:
    Laptop(const string &n, double p, int r, int s, int b)
        : store(n, p), ram(r), storage(s), battery(b) {}
    int getRAM() const
    {
        return ram;
    }
    int getStorage() const
    {
        return storage;
    }
    int getBattery() const
    {
        return battery;
    }
    void displayDetails()
    {
        cout << "Welcome to Laptop Store!" << endl;
        cout << "BRANDS:" << endl;
        cout << "1. lenovo" << endl
             << "2. hp " << endl
             << "3. DELL" << endl;
        cout << endl;
        // laptop er 3 ta company ( lenovo, hp, dell) ; lenovo(A,B,C) ; hp(D,E,F) ; dell(G,H,I) ;
        cout << "Select a Laptop Company:";
        int company;
        cin >> company;
        cout << endl;
        // lenovo laptop (A,B,C)
        if (company == 1) // LAPTOP COMPANY 1
        {
            Laptop laptopA(" Laptop lenovo model ", 1499.99, 16, 512, 6);
            Laptop laptopB(" Laptop lenovo model ", 1499.99, 16, 512, 6);
            Laptop laptopC(" Laptop lenovo model ", 1499.99, 16, 512, 6);
            cout << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << laptopA.getName() << endl;
            cout << "Price: $" << laptopA.getPrice() << endl;
            cout << "RAM: " << laptopA.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopA.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopA.getBattery() << "mAh" << endl;
            cout << "Option 2: " << endl;
            cout << endl;
            cout << "Name: " << laptopB.getName() << endl;
            cout << "Price: $" << laptopB.getPrice() << endl;
            cout << "RAM: " << laptopB.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopB.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopB.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << laptopC.getName() << endl;
            cout << "Price: $" << laptopC.getPrice() << endl;
            cout << "RAM: " << laptopC.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopC.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopC.getBattery() << "mAh" << endl;
            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;
            Product *p1 = new Product(laptopA.getName(), laptopA.getPrice());
            Product *p2 = new Product(laptopA.getName(), laptopA.getPrice());
            Product *p3 = new Product(laptopA.getName(), laptopA.getPrice());
            if (choice == 1)
            {
                cart.addToLaptopCart(p1);
            }
            else if (choice == 2)
            {
                cart.addToLaptopCart(p2);
            }
            else if (choice == 3)
            {
                cart.addToLaptopCart(p3);
            }
        }
        // HP (D,E,F)
        else if (company == 2) // LAPTOP COMPANY2
        {
            Laptop laptopD(" Laptop hp model ", 1499.99, 16, 512, 6);
            Laptop laptopE(" Laptop hp model ", 1499.99, 16, 512, 6);
            Laptop laptopF(" Laptop hp model ", 1499.99, 16, 512, 6);
            cout << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << laptopD.getName() << endl;
            cout << "Price: $" << laptopD.getPrice() << endl;
            cout << "RAM: " << laptopD.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopD.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopD.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 2: " << endl;
            cout << "Name: " << laptopE.getName() << endl;
            cout << "Price: $" << laptopE.getPrice() << endl;
            cout << "RAM: " << laptopE.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopE.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopE.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << laptopF.getName() << endl;
            cout << "Price: $" << laptopF.getPrice() << endl;
            cout << "RAM: " << laptopF.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopF.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopF.getBattery() << "mAh" << endl;
            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;
            Product *p1 = new Product(laptopD.getName(), laptopD.getPrice());
            Product *p2 = new Product(laptopD.getName(), laptopD.getPrice());
            Product *p3 = new Product(laptopD.getName(), laptopD.getPrice());
            if (choice == 1)
            {
                cart.addToLaptopCart(p1);
            }
            else if (choice == 2)
            {
                cart.addToLaptopCart(p2);
            }
            else if (choice == 3)
            {
                cart.addToLaptopCart(p3);
            }
        }
        // DELL ( G,H,I )
        else // LAPTOP COMPANY 3
        {
            Laptop laptopG(" Laptop DELL model ", 1499.99, 16, 512, 6);
            Laptop laptopH(" Laptop DELL model ", 1499.99, 16, 512, 6);
            Laptop laptopI(" Laptop DELL model ", 1499.99, 16, 512, 6);
            cout << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << laptopG.getName() << endl;
            cout << "Price: $" << laptopG.getPrice() << endl;
            cout << "RAM: " << laptopG.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopG.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopG.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 2: " << endl;
            cout << "Name: " << laptopH.getName() << endl;
            cout << "Price: $" << laptopH.getPrice() << endl;
            cout << "RAM: " << laptopH.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopH.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopH.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << laptopI.getName() << endl;
            cout << "Price: $" << laptopI.getPrice() << endl;
            cout << "RAM: " << laptopI.getRAM() << "GB" << endl;
            cout << "Storage: " << laptopI.getStorage() << "GB SSD" << endl;
            cout << "Battery: " << laptopI.getBattery() << "mAh" << endl;

            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;
            Product *p1 = new Product(laptopH.getName(), laptopH.getPrice());
            Product *p2 = new Product(laptopH.getName(), laptopH.getPrice());
            Product *p3 = new Product(laptopH.getName(), laptopH.getPrice());
            if (choice == 1)
            {
                cart.addToLaptopCart(p1);
            }
            else if (choice == 2)
            {
                cart.addToLaptopCart(p2);
            }
            else if (choice == 3)
            {
                cart.addToLaptopCart(p3);
            }
        }
    }
    friend class friend_class;
};
class Phone : public store
{
private:
    int ram;
    int storage;
    int battery;

public:
    Phone(const string &n, double p, int r, int s, int b)
        : store(n, p), ram(r), storage(s), battery(b) {}
    int getRAM() const
    {
        return ram;
    }
    int getStorage() const
    {
        return storage;
    }
    int getBattery() const
    {
        return battery;
    }
    void displayDetails()
    {
        cout << "Welcome to phone Store!" << endl;
        cout << "BRANDS:" << endl;
        cout << "1.SAMSUNG " << endl
             << "2.Xiaomi " << endl
             << "3.OnePlus" << endl;
        cout << endl;
        cout << "Select a phone Company:";
        int company;
        cin >> company;
        cout << endl;
        // samsung(a,b,c)
        if (company == 1) // PHONE COMPANY 1
        {
            Phone phoneA("Smartphone samsung a ", 599.99, 8, 128, 4000);
            Phone phoneB("Smartphone samsung b ", 599.99, 8, 128, 4000);
            Phone phoneC("Smartphone samsung c ", 599.99, 8, 128, 4000);
            cout << "Samsung products:" << endl;
            cout << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << phoneA.getName() << endl;
            cout << "Price: $" << phoneA.getPrice() << endl;
            cout << "RAM: " << phoneA.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneA.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneA.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 2: " << endl;
            cout << "Name: " << phoneB.getName() << endl;
            cout << "Price: $" << phoneB.getPrice() << endl;
            cout << "RAM: " << phoneB.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneB.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneB.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << phoneC.getName() << endl;
            cout << "Price: $" << phoneC.getPrice() << endl;
            cout << "RAM: " << phoneC.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneC.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneC.getBattery() << "mAh" << endl;

            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;

            Product *phone1 = new Product("Phone Model A", 122499.99);
            Product *phone2 = new Product("Phone Model B", 122599.99);
            Product *phone3 = new Product("Phone Model C", 122699.99);
            if (choice == 1)
            {
                cart.addToPhoneCart(phone1);
            }
            else if (choice == 2)
            {
                cart.addToPhoneCart(phone2);
            }
            else if (choice == 3)
            {
                cart.addToPhoneCart(phone3);
            }
        }
        // xiaomi
        else if (company == 2) // PHONE COMPANY 2
        {
            Phone phoneX1("Smartphone Xiaomi a ", 599.99, 8, 128, 4000);
            Phone phoneX2("Smartphone X b ", 599.99, 8, 128, 4000);
            Phone phoneX3("Smartphone X c ", 599.99, 8, 128, 4000);
            cout << "Xiaomi products:" << endl;
            cout << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << phoneX1.getName() << endl;
            cout << "Price: $" << phoneX1.getPrice() << endl;
            cout << "RAM: " << phoneX1.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneX1.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneX1.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 2: " << endl;
            cout << "Name: " << phoneX2.getName() << endl;
            cout << "Price: $" << phoneX2.getPrice() << endl;
            cout << "RAM: " << phoneX2.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneX2.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneX2.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << phoneX3.getName() << endl;
            cout << "Price: $" << phoneX3.getPrice() << endl;
            cout << "RAM: " << phoneX3.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneX3.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneX3.getBattery() << "mAh" << endl;

            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;

            Product *phone1 = new Product("Phone Model A", 122499.99);
            Product *phone2 = new Product("Phone Model B", 122599.99);
            Product *phone3 = new Product("Phone Model C", 122699.99);
            if (choice == 1)
            {
                cart.addToPhoneCart(phone1);
            }
            else if (choice == 2)
            {
                cart.addToPhoneCart(phone2);
            }
            else if (choice == 3)
            {
                cart.addToPhoneCart(phone3);
            }
        }
        // oneplus
        else // PHONE COMPANY 3
        {
            Phone phoneO1("Smartphone Xiaomi a ", 599.99, 8, 128, 4000);
            Phone phoneO2("Smartphone X b ", 599.99, 8, 128, 4000);
            Phone phoneO3("Smartphone X c ", 599.99, 8, 128, 4000);
            cout << "OnePlus products:" << endl;
            cout << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << phoneO1.getName() << endl;
            cout << "Price: $" << phoneO1.getPrice() << endl;
            cout << "RAM: " << phoneO1.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneO1.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneO1.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 2: " << endl;
            cout << "Name: " << phoneO2.getName() << endl;
            cout << "Price: $" << phoneO2.getPrice() << endl;
            cout << "RAM: " << phoneO2.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneO2.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneO2.getBattery() << "mAh" << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << phoneO3.getName() << endl;
            cout << "Price: $" << phoneO3.getPrice() << endl;
            cout << "RAM: " << phoneO3.getRAM() << "GB" << endl;
            cout << "Storage: " << phoneO3.getStorage() << "GB" << endl;
            cout << "Battery: " << phoneO3.getBattery() << "mAh" << endl;
            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;

            Product *phone1 = new Product("Phone Model A", 122499.99);
            Product *phone2 = new Product("Phone Model B", 122599.99);
            Product *phone3 = new Product("Phone Model C", 122699.99);
            if (choice == 1)
            {
                cart.addToPhoneCart(phone1);
            }
            else if (choice == 2)
            {
                cart.addToPhoneCart(phone2);
            }
            else if (choice == 3)
            {
                cart.addToPhoneCart(phone3);
            }
        }
    }
    friend class friend_class;
};
class Headphones : public store
{
private:
    string type;

public:
    Headphones(const string &n, double p, const string &t)
        : store(n, p), type(t) {}
    string getType() const
    {
        return type;
    }
    void displayDetails()
    {
        cout << endl;
        cout << " Welcome to Headphone Store!" << endl;
        cout << "BRANDS:" << endl;
        cout << "1.Sony " << endl
             << "2.Bose " << endl
             << "3.Marshall" << endl;
        cout << endl;
        cout << "Select a Headphone Company:";
        int company;
        cin >> company;
        cout << endl;
        if (company == 1)
        {
            Headphones headphonesA("Wireless Headphones model a ", 149.99, "Over-ear");
            Headphones headphonesB("Wireless Headphones model b ", 149.99, "Over-ear");
            Headphones headphonesC("Wireless Headphones model c ", 149.99, "Over-ear");
            cout << "Headphones model 1 :" << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << headphonesA.getName() << endl;
            cout << "Price: $" << headphonesA.getPrice() << endl;
            cout << "Type: " << headphonesA.getType() << endl;
            cout << endl;
            cout << "Option 2: " << endl;
            cout << "Name: " << headphonesB.getName() << endl;
            cout << "Price: $" << headphonesB.getPrice() << endl;
            cout << "Type: " << headphonesB.getType() << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << headphonesC.getName() << endl;
            cout << "Price: $" << headphonesC.getPrice() << endl;
            cout << "Type: " << headphonesC.getType() << endl;
            cout << endl;
            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;

            Product *p1 = new Product(headphonesA.getName(), headphonesB.getPrice());
            Product *p2 = new Product(headphonesB.getName(), headphonesB.getPrice());
            Product *p3 = new Product(headphonesC.getName(), headphonesB.getPrice());
            if (choice == 1)
            {
                cart.addToHeadphoneCart(p1);
            }
            else if (choice == 2)
            {
                cart.addToHeadphoneCart(p2);
            }
            else if (choice == 3)
            {
                cart.addToHeadphoneCart(p3);
            }
        }
        else if (company == 2)
        {
            Headphones headphonesD("Wireless Headphones model a ", 149.99, "Over-ear");
            Headphones headphonesE("Wireless Headphones model b ", 149.99, "Over-ear");
            Headphones headphonesF("Wireless Headphones model c ", 149.99, "Over-ear");
            cout << "Headphones model 2 :" << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << headphonesD.getName() << endl;
            cout << "Price: $" << headphonesD.getPrice() << endl;
            cout << "Type: " << headphonesD.getType() << endl;
            cout << endl;
            cout << "Option 2: " << endl;
            cout << "Name: " << headphonesE.getName() << endl;
            cout << "Price: $" << headphonesE.getPrice() << endl;
            cout << "Type: " << headphonesE.getType() << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << headphonesF.getName() << endl;
            cout << "Price: $" << headphonesF.getPrice() << endl;
            cout << "Type: " << headphonesF.getType() << endl;
            cout << endl;

            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;
            Product *p1 = new Product(headphonesD.getName(), headphonesD.getPrice());
            Product *p2 = new Product(headphonesE.getName(), headphonesD.getPrice());
            Product *p3 = new Product(headphonesF.getName(), headphonesD.getPrice());
            if (choice == 1)
            {
                cart.addToHeadphoneCart(p1);
            }
            else if (choice == 2)
            {
                cart.addToHeadphoneCart(p2);
            }
            else if (choice == 3)
            {
                cart.addToHeadphoneCart(p3);
            }
        }
        else
        {
            Headphones headphonesG("Wireless Headphones model a ", 149.99, "Over-ear");
            Headphones headphonesH("Wireless Headphones model b ", 149.99, "Over-ear");
            Headphones headphonesI("Wireless Headphones model c ", 149.99, "Over-ear");
            cout << "Headphones model 3 :" << endl;
            cout << "Option 1: " << endl;
            cout << "Name: " << headphonesG.getName() << endl;
            cout << "Price: $" << headphonesG.getPrice() << endl;
            cout << "Type: " << headphonesG.getType() << endl;
            cout << endl;
            cout << "Option 2: " << endl;
            cout << "Name: " << headphonesH.getName() << endl;
            cout << "Price: $" << headphonesH.getPrice() << endl;
            cout << "Type: " << headphonesH.getType() << endl;
            cout << endl;
            cout << "Option 3: " << endl;
            cout << "Name: " << headphonesI.getName() << endl;
            cout << "Price: $" << headphonesI.getPrice() << endl;
            cout << "Type: " << headphonesI.getType() << endl;
            cout << endl;

            cout << "Enter option you want to buy: ";
            int choice;
            cin >> choice;
            Product *p1 = new Product(headphonesG.getName(), headphonesG.getPrice());
            Product *p2 = new Product(headphonesG.getName(), headphonesG.getPrice());
            Product *p3 = new Product(headphonesG.getName(), headphonesG.getPrice());
            if (choice == 1)
            {
                cart.addToHeadphoneCart(p1);
            }
            else if (choice == 2)
            {
                cart.addToHeadphoneCart(p2);
            }
            else if (choice == 3)
            {
                cart.addToHeadphoneCart(p3);
            }
        }
    }
    friend class friend_class;
};

class friend_class
{
public:
    void display()
    {
        int press;
        while (true)
        {
            cout << endl
                 << "Search in ShopTech" << endl
                 << "1. Laptop" << endl
                 << "2. Phone" << endl
                 << "3. Headphone " << endl;
            cout
                << "Enter 0 to exit." << endl
                << "Press: ";
            cin >> press;
            if (press == 0)
                break;
            switch (press)
            {
            case 1:
            {
                Laptop *laptop = new Laptop("Laptop lenovo model ", 1499.99, 16, 512, 6);
                laptop->displayDetails();
                delete laptop; // Delete the allocated memory
                break;
            }
            case 2:
            {
                Phone *phone = new Phone("Smartphone samsung a ", 599.99, 8, 128, 4000);
                phone->displayDetails();
                delete phone; // Delete the allocated memory
                break;
            }
            case 3:
            {
                Headphones *headphones = new Headphones("Wireless Headphones model a ", 149.99, "Over-ear");
                headphones->displayDetails();
                delete headphones; // Delete the allocated memory
                break;
            }
            default:
                cout << "Invalid choice." << endl;
                break;
            }
        }
    }
};
int main()
{
    User user("AHMED", "password");
    cout << " Welcome to ShopTech ! "
         << endl;
    cout << "Please log in.\n"
         << endl;
    string inputUsername, inputPassword;
    cout << "Username: ";
    cin >> inputUsername;
    cout << "Password: ";
    cin >> inputPassword;
    if (user.authenticate(inputPassword))
    {
        cout << endl;
        cout << " Login successful. Hey Welcome Back, Ahmed. " << user.getUsername()
             << " !" << endl;
        //************************** store er vetore *********************************
        //************************** store er vetore *********************************
        while (true)
        {
            friend_class ob;
            ob.display();
            cout << endl;
            cout << "1. Want to add products on MY CART ? ";
            cout << endl;
            cout << "2.Back to homepage. ";
            cout << endl;
            cout << "3.Show My Cart." << endl;
            cout << "press:";
            int press2;
            cin >> press2;
            cout << endl;
            /*
            if(press2==1)
            {
            }
            if(press2==3)
            {
            cart.display();
            }
            */
            if (press2 == 2)
            {
                friend_class ob;
                ob.display();
            }
            //*******************************************************
            // Product *laptop1 = new Product("Laptop Model X", 122999.99);
            // Product *laptop2 = new Product("Laptop Model Y", 1221199.99);
            // Product *laptop3 = new Product("Laptop Model Z", 122399.99);
            // Product *headphone1 = new Product("Headphones Model H1", 189.99);
            // Product *headphone2 = new Product("Headphones Model H2", 2599.99);
            // Product *headphone3 = new Product("Headphones Model H3", 15109.99);
            // cart.addToLaptopCart(laptop1);
            // cart.addToLaptopCart(laptop2);
            // cart.addToLaptopCart(laptop3);
            // cart.addToHeadphoneCart(headphone1);
            // cart.addToHeadphoneCart(headphone2);
            // cart.addToHeadphoneCart(headphone3);
            cout << endl;
            cart.displayCart();
            cout << endl;
            char choice;
            cout << "Do you want to remove any items from the cart?" << endl
                 << "Enter your choice(y/n): ";
            cin >> choice;
            cout << endl;
            if (choice == 'y' || choice == 'Y')
            {
                cout << "From Which item you want to remove ? " << endl
                     << "1. phone" << endl
                     << "2. laptop" << endl
                     << "3.                headphone " << endl
                     << endl
                     << " Enter the number of your choice : ";
                char choice_again;
                cin >> choice_again;
                if (choice_again == '1')
                {

                    cout << endl
                         << "List of Phones : ";
                    for (int i = 0; i < cart.phoneCount; ++i)
                    {
                        cout << i + 1 << ". " << cart.phoneProducts[i]->getName();
                    }

                    cout << endl
                         << "Enter the number of the phone model according to the list to remove : ";
                    int n;
                    cin >>
                        n;
                    cart.removePhoneCart(n - 1);
                }
                else if (choice_again == '2')
                {

                    cout << endl
                         << "List of Laptops : ";
                    for (int i = 0; i < cart.phoneCount; ++i)
                    {
                        cout << i + 1 << ". " << cart.phoneProducts[i]->getName();
                    }

                    cout << endl
                         << "Enter the number of the phone model according to the list to remove : ";
                    int n;
                    cin >>
                        n;
                    cart.removeLaptopCart(n - 1);
                }
                else if (choice_again == '3')
                {
                    cout << endl
                         << "List of Headphones : ";
                    for (int i = 0; i < cart.phoneCount; ++i)
                    {
                        cout << i + 1 << ". " << cart.phoneProducts[i]->getName();
                    }

                    cout << endl
                         << "Enter the number of the phone model according to the list to remove : ";
                    int n;
                    cin >>
                        n;
                    cart.removeHeadphoneCart(n - 1);
                }
                else
                {
                    cout << "Invalid choice." << endl;
                }
            }
            cout << endl;
            cart.displayCart();
        }
    }
    else
    {
        cout << "Authentication failed. Goodbye." << endl;
    }
    return 0;
}