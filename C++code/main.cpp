#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "datastrucutres/Graph.h"
#include "datastrucutres/Warehouse.h"
#include <list>
#include "datastrucutres/CustomerList.h"

using namespace std;

int currentNumber = 10000;
// read file
void readFile(Graph &g)
{
    ifstream fin("DHL_DATASET_CANADA.csv");
    if (!fin)
    {
        cerr << "Failed to open the file." << endl;
        return;
    }
    string line, word;
    vector<string> lineData;
    int lines = 0;
    while (getline(fin, line))
    {
        if (lines == 0)
        {
            lines++;
            continue; // Skip the header line
        }
        stringstream s(line);
        while (getline(s, word, ','))
        {
            lineData.push_back(word);
        }
        string city = lineData[0];
        string connectedCity = lineData[1];
        int cost = stoi(lineData[2]);
        int distance = stoi(lineData[3]);
        int deliveryTime = stoi(lineData[4]);
        string serviceLevel = lineData[5];

        g.addVertex(city);
        g.addVertex(connectedCity);
        g.addEdge(city, connectedCity, cost, distance, deliveryTime, serviceLevel);

        // Clearing vector
        lineData.clear();
        lines++;
    }

    fin.close();
}

// HANDLE ORDER
void handleOrder(Graph &g, Warehouse &warehouse, string employeeCity, CustomerList &userList)
{
    User user;
    Package package;

    // Display all available cities
    cout << "Available cities:" << endl;
    g.displayVertices();

    // Get the user's destination city
    cout << "Enter the destination city: ";
    getline(cin, package.destinationcity);
    // Check if the destination city is valid and exists in the graph
    if (g.search(package.destinationcity) < 0)
    {
        cout << "Invalid destination city. Please enter a valid city." << endl;
        return;
    }
    Paths path = g.canReachDestination(employeeCity, package.destinationcity);
    if (path.distance == 0 && path.deliveryTime == 0)
    {
        cout << "Sorry, we cannot offer services to the specified destination from this city." << endl;
        return;
    }
    user.address = employeeCity;

    cout << "Enter the sender's name: ";
    getline(cin, package.sender);
    user.name = package.sender;
    string PRNO;
    cout << "Enter sender's PR Card number: ";
    getline(cin, PRNO);
    try
    {
        user.userPRcardno = stoi(PRNO);
        package.userPRcardno = stoi(PRNO);
    }
    catch (const invalid_argument &e)
    {
        cout << "Invalid PRNO. Please enter an integer." << std::endl;
        return;
    }
    cout << "Enter the recipient's name: ";
    getline(cin, package.recipient);
    cout << "Enter the recipient's street address: ";
    getline(cin, package.streetaddress);
    package.deliverytime = path.deliveryTime;
    package.distance = path.distance;
    string status = "Inwarehouse";
    package.orderstatus = status;
    currentNumber++;
    package.trackingNumber = currentNumber;
    warehouse.addOrder(package);
    user.userTotalorders = 1;
    userList.insertAtEnd(user);

    // Print the entered details
    cout << endl
         << "Order details:" << endl;
    cout << "Sender Name: " << package.sender << endl;
    cout << "Sender City: " << user.address << endl;
    cout << "Package ID: " << package.trackingNumber << endl;
    cout << "Recipient Name: " << package.recipient << endl;
    cout << "Recipient city: " << package.destinationcity << endl;
    cout << "Recipient street address: " << package.streetaddress << endl;
    cout << "Distance: " << package.distance << " km" << endl;
    cout << "Delivery Time: " << package.deliverytime << " hours" << endl;
    cout << "Delivery route: ";
    for (int i = 0; i < path.route.size(); ++i)
    {
        cout << path.route[i] << " -> ";
    }
    cout << package.streetaddress << endl;
}

int main()
{
    Graph g;
    Warehouse warehouse;
    CustomerList customerlist;

    readFile(g);
    cout << "***********************************************************\n";
    cout << "-----------------------------------------------------------\n";
    cout << "                  DHL EXPRESS LOGISTICS                     \n";
    cout << "-----------------------------------------------------------\n";
    cout << "***********************************************************\n";
    cout << "\nWelcome to the Order Management Application for Employees!\n";
    cout << "\nAvailable Cities:\n";
    g.displayVertices();
    string employeeCity;
    cout << "Enter your city of operation: ";
    getline(cin, employeeCity);
    // Check if the employee's city exists in the graph
    if (g.search(employeeCity) < 0)
    {
        cout << "Invalid city of operation. Please enter a valid city." << endl;
        return 0;
    }

    int choice;
    do
    {
        cout << "Please select an option:" << endl;
        cout << "1. Place Order" << endl;
        cout << "2. All orders in ware house" << endl;
        cout << "3. Dispatch order from warehouse" << endl;
        cout << "4. Check Orders on way" << endl;
        cout << "5. Mark order as completed" << endl;
        cout << "6. Check completed orders" << endl;
        cout << "7. Latest completed order" << endl;
        cout << "8. Check specific Order status" << endl;
        cout << "9. Display all orders and there Status" << endl;
        cout << "10. Display all Customers" << endl;
        cout << "11. Find Specific Customer orders" << endl;
        cout << "12. Show Customer in such way that customer with more orders will come first" << endl;
        cout << "13. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining characters in the input buffer
        switch (choice)
        {
        case 1:
            handleOrder(g, warehouse, employeeCity, customerlist); // take order info from customer find shortest route,distance and time and push order to Queue.
            break;
        case 2:
            warehouse.displayOrders(); // display all orders in ware house(display of queue)
            break;
        case 3:
            warehouse.dispatchOrder(); // disptach order from ware house (removed from queue and push to min heap as order with less time has high priority to complete early)
            break;
        case 4:
            warehouse.displayOrdersonway(); // display all orders on way (display of min heap)
            break;
        case 5:
            warehouse.completeorder(); // adds order to stack and remove from heap( we used stack as from stack we can easily get latest completed order)
            break;
        case 6:
            warehouse.displaycompletedorders(); // displays completed order
            break;
        case 7:
            warehouse.latestcompletedorder(); // display latest completed order
            break;
        case 8:
            warehouse.trackOrder(); // When order is placed we also store them in AVL. Than with further processes we continiously update order in avl with order status. (we use avl because we easily search  a specifc order in less time)
            break;
        case 9:
            warehouse.displayAllorders(); // displays all orders which branch  have processed with there respective statuses of warehouse, on way and completed
            break;
        case 10:
            customerlist.display(); // display all cutomer list
            break;
        case 11:
            warehouse.findusersorder(); // display specific user orders it will find using seperate chaining.
            break;
        case 12:
            customerlist.sortCustomersByOrders(); // it will sort customer by their number of orders using using merge sort
            break;
        case 13:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        cout << endl;
    } while (choice != 13);

    return 0;
}
