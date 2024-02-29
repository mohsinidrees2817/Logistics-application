#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <string>
#include "structures/Package.h"

using namespace std;

const int TABLE_SIZE = 100;

class HashTable
{

private:
    list<Package> *hashTable[TABLE_SIZE];

    int hashFunction(int userPRcardno)
    {
        int sum = 0;

        while (userPRcardno > 0)
        {
            sum += userPRcardno % 10;
            userPRcardno /= 10;
        }

        return sum % TABLE_SIZE;
    }

public:
    HashTable()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            hashTable[i] = nullptr;
        }
    }

    void insertOrder(const Package &order)
    {
        int index = hashFunction(order.userPRcardno);

        if (hashTable[index] == nullptr)
        {
            hashTable[index] = new list<Package>;
        }

        hashTable[index]->push_back(order);
    }



    void displayOrders()
    {
        cout << "{" << endl;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] != nullptr)
            {
                for (const Package &order : *hashTable[i])
                {
                    cout << "User PR Card No: " << order.userPRcardno << endl;
                    cout << "Package ID: " << order.trackingNumber << endl;
                    cout << "Sender: " << order.sender << endl;
                    cout << "Recipient: " << order.recipient << endl;
                    cout << "Destination City: " << order.destinationcity << endl;
                    cout << "Street Address: " << order.streetaddress << endl;
                    cout << "Delivery Time: " << order.deliverytime << endl;
                    cout << "Distance: " << order.distance << endl;
                    cout << endl;
                }
            }
        }
        cout << "}" << endl;
    }


    list<Package> *findcustomerorders(int userPRcardno)
    {
        int index = hashFunction(userPRcardno);
        return hashTable[index];
    }

    void findOrders()
    {
        int userPRcardno;
        cout << "Enter user PR card NO: ";
        cin >> userPRcardno;

        list<Package> *orders = findcustomerorders(userPRcardno);

        if (orders != nullptr)
        {
            cout << "Orders found for user PR Card No: " << userPRcardno << endl;

            bool foundOrders = false;

            for (const Package &order : *orders)
            {
                if (order.userPRcardno == userPRcardno)
                {
                    cout << "Customer Order ID: " << order.trackingNumber << "Order destination city: " << order.destinationcity << endl;
                    foundOrders = true;
                }
            }

            if (!foundOrders)
            {
                cout << "No orders found for user PR Card No: " << userPRcardno << endl;
            }
        }
        else
        {
            cout << "User Not found: " << userPRcardno << endl;
        }
    }
};

#endif
