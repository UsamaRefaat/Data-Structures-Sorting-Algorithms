#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
using namespace std ;

class item
{
public:
    string itemName;
    string category;
    int price;

    item(string name, string cat, int p) : itemName(name), category(cat), price(p) {}

    struct LessThanName
    {
        bool operator()(const item &a, const item &b) const
        {
            return a.itemName < b.itemName;
        }
    };

    struct LessThanPrice
    {
        bool operator()(const item &a, const item &b) const
        {
            return a.price < b.price;
        }
    };

    void print() const
    {
        cout << "Name: " << itemName << ", Category: " << category << ", Price: " << price << '\n';
    }
};

#endif // ITEM_H
