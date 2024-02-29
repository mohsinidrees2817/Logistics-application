
#ifndef PACKAGE_H
#define PACKAGE_H
#include <iostream>

using namespace std;

struct Package
{
    int trackingNumber;
    string sender;
    string recipient;
    string destinationcity;
    string streetaddress;
    int deliverytime;
    int distance;
    string orderstatus;
    int userPRcardno;
};

#endif