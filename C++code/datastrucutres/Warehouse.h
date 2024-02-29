#include <iostream>
#include <queue>
#include <stack>
#include "MINheap.h"
#include "AVLtree.h"
#include "HashTable.h"

using namespace std;

class Warehouse
{
private:
    queue<Package> orders;
    MINheap dispatchedorders;
    stack<Package> completedorders;
    AVLTree allOrders;
    HashTable Usersorders;

public:
    void addOrder(Package order)
    {
        orders.push(order);
        cout << "Order added to the warehouse: " << order.trackingNumber << endl;
        allOrders.insert(order);
        Usersorders.insertOrder(order);
    }

    void displayOrders()
    {
        if (orders.empty())
        {
            cout << "No orders in the warehouse." << endl;
            return;
        }

        cout << "Orders in the warehouse:" << endl;
        int orderCount = 1;
        queue<Package> tempOrders = orders;
        while (!tempOrders.empty())
        {
            cout << "Order " << orderCount++ << ": " << tempOrders.front().trackingNumber << endl;
            tempOrders.pop();
        }
    }

    void dispatchOrder()
    {
        if (orders.empty())
        {
            cout << "No orders in the warehouse to dispatch." << endl;
        }
        else
        {
            Package order = orders.front();
            orders.pop();
            order.orderstatus = "On way";
            dispatchedorders.insert(order);
            allOrders.updateOrderStatus(order.trackingNumber, order.orderstatus);
            cout << "Order dispatched: " << order.trackingNumber << endl;
            cout << "Order status: " << order.orderstatus << endl;
        }
    }

    void displayOrdersonway()
    {
        if (dispatchedorders.isEmpty())
        {
            cout << "No orders on way";
        }
        else
        {
            cout << "Orders on way" << endl;
            dispatchedorders.display();
        }
    }

    void completeorder()
    {
        if (dispatchedorders.isEmpty())
        {
            cout << "No orders are on way";
        }
        else
        {

            Package completedorder = dispatchedorders.getFirst();
            completedorder.orderstatus = "completed";
            completedorders.push(completedorder);
            allOrders.updateOrderStatus(completedorder.trackingNumber, completedorder.orderstatus);

            dispatchedorders.remove();
            cout << "order completed: " << completedorder.trackingNumber << endl;
        }
    }

    void displaycompletedorders()
    {
        if (completedorders.empty())
        {
            cout << "No orders completed yet";
        }
        else
        {
            stack<Package> temporders = completedorders; // Create a temporary stack to preserve the order
            cout << "Delivered Orders: " << endl;
            while (!temporders.empty())
            {
                cout << temporders.top().trackingNumber << endl;
                temporders.pop();
            }
            cout << endl;
        }
    }

    void latestcompletedorder()
    {
        if (!completedorders.empty())
        {
            cout << "Latest completed order: " << completedorders.top().trackingNumber << endl;
        }
        else
        {
            cout << "no order completed yet" << endl;
        }
    }
    void trackOrder()
    {
        allOrders.searchSpecificOrder();
    }

    void displayAllorders()
    {
        allOrders.displayAllOrders();
    }

    void findusersorder()
    {
        Usersorders.findOrders();
        
    }
};