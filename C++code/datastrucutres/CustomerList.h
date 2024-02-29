#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H

#include <iostream>
#include <list>
#include <string>
#include "structures/User.h"

using namespace std;

struct Customer
{
    User userDetails;
    Customer *next = NULL;
};

class CustomerList
{
private:
    Customer *first = NULL;
    Customer *last = NULL;

    Customer *merge(Customer *left, Customer *right)
    {
        // Base cases
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;

        // Merge the two lists in ascending order of number of orders
        Customer *mergedList = nullptr;
        if (left->userDetails.userTotalorders <= right->userDetails.userTotalorders)
        {
            mergedList = left;
            mergedList->next = merge(left->next, right);
        }
        else
        {
            mergedList = right;
            mergedList->next = merge(left, right->next);
        }
        return mergedList;
    }

    void split(Customer *head, Customer **front, Customer **back)
    {
        if (head == nullptr || head->next == nullptr)
        {
            *front = head;
            *back = nullptr;
            return;
        }

        Customer *slow = head;
        Customer *fast = head->next;

        // Move fast pointer two steps ahead and slow pointer one step ahead
        while (fast != nullptr)
        {
            fast = fast->next;
            if (fast != nullptr)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        // Split the list into two halves
        *front = head;
        *back = slow->next;
        slow->next = nullptr;
    }

    void mergeSort(Customer **head)
    {
        if (*head == nullptr || (*head)->next == nullptr)
            return;

        Customer *front;
        Customer *back;
        split(*head, &front, &back);

        // Recursively sort the two halves
        mergeSort(&front);
        mergeSort(&back);

        // Merge the sorted halves
        *head = merge(front, back);
    }

public:
    void insertAtEnd(User user)
    {
        Customer *newCustomer = new Customer;
        newCustomer->userDetails = user;

        int userPrno = user.userPRcardno;
        bool customerExists = false;

        // Check if the customer already exists
        Customer *p = first;
        while (p != NULL)
        {
            if (p->userDetails.userPRcardno == userPrno)
            {
                customerExists = true;
                p->userDetails.userTotalorders++;
                break;
            }
            p = p->next;
        }

        if (customerExists)
        {
            cout << "Customer already exists." << endl;
        }
        else
        {
            if (first == NULL)
            {
                first = last = newCustomer;
            }
            else
            {
                last->next = newCustomer;
                last = newCustomer;
                newCustomer->next = NULL;
            }
        }
    }

    void sortCustomersByOrders()
    {
        Customer *p = first;
        if (p == NULL)
        {
            cout << "No Customers." << endl;
        }
        else
        {
            mergeSort(&first);
            display();
        }
    }

    void display()
    {
        Customer *p = first;
        if (p == NULL)
        {
            cout << "No Customers." << endl;
        }
        else
        {
            while (p != NULL)
            {
                cout << "Customer PRcard NO: " << p->userDetails.userPRcardno << ","
                     << "Customer Name: " << p->userDetails.name << ","
                     << "Customer Total orders: " << p->userDetails.userTotalorders << endl;
                p = p->next;
            }
        }
    }
};

#endif
