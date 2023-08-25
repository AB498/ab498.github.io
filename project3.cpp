#include <iostream>
#include <vector>
#include <string>

using namespace std;

void homeScreen();

class Vehicle
{
    string model;
    string color;
    float price;

    string vehicleType = "None";

public:
    string getModel()
    {
        return model;
    }
    string getColor()
    {
        return color;
    }
    float getPrice()
    {
        return price;
    }
    float getPrice(int BDT)
    {
        if (BDT)
            return price * 100;
        else
            return price;
    }
    string getType()
    {
        return vehicleType;
    }
    void setModel(string m)
    {
        model = m;
    }
    void setColor(string c)
    {
        color = c;
    }
    void setPrice(float p)
    {
        price = p;
    }

    friend void setType(Vehicle &v, string s);
    Vehicle()
    {
    }
    ~Vehicle()
    {
        cout << "Vehicle destroyed" << endl;
    }
};

class Bus : public Vehicle
{
public:
    Bus()
    {
        setModel("Tata");
        setColor("Red");
        setPrice(100);
        setType(*this, "Bus");
    }
};
class Ambulance : public Vehicle
{
public:
    Ambulance()
    {
        setModel("Tesla");
        setColor("White");
        setPrice(100);
        setType(*this, "Ambulance");
    }
};

class Bicycle : public Vehicle
{
public:
    Bicycle()
    {
        setModel("Atlas");
        setColor("Black");
        setPrice(100);
        setType(*this, "Bicycle");
    }
};

void setType(Vehicle &v, string s)
{
    v.vehicleType = s;
}

void displayLocations()
{
    cout << "Locations: \n"
            "1. Cantonment, Dhaka \n"
            "2. Mirpur, Dhaka \n";
}

int main()
{

main:
    cout << "\nSelect an option \n"
            "1. Rent Vehicle \n"
            "2. Pickup and drop-off locations \n";
    int input;

    cin >> input;
    switch (input)
    {
    case 1:
        cout << "Vehicle type? \n"
                "1. Bus \n"
                "2. Bicycle  \n"
                "3. Ambulance  \n";
        int input2;
        cin >> input2;
        Vehicle *vehicle;
        switch (input2)
        {
        case 1:
            vehicle = new Bus();
            break;
        case 2:
            vehicle = new Bicycle();
            break;
        case 3:
            vehicle = new Ambulance();
            break;
        default:
            break;
        }
        cout << "\nYou have rented: " << endl;
        cout << "Vehicle type: " << vehicle->getType() << endl;
        cout << "Model: " << vehicle->getModel() << endl;
        cout << "Color: " << vehicle->getColor() << endl;
        cout << "Price: " << vehicle->getPrice() << endl;
        cout << endl;
        goto main;
    case 2:
        displayLocations();
        goto main;

        break;
    default:
        cout << endl
             << "Invalid input" << endl;
        goto main;
        break;
    }

    return 0;
}