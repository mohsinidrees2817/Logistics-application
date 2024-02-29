#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include "structures/Package.h"

using namespace std;

struct Order
{
    Package orderdetails;
    Order *left = NULL;
    Order *right = NULL;

    int height;
};

class AVLTree
{
private:
    Order *root;

public:
    AVLTree()
    {
        root = NULL;
    }

    Order *newNode(Package orderinfo)
    {
        Order *node = new Order;
        node->orderdetails = orderinfo;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return node;
    }

    int max(int a, int b)
    {
        return a > b ? a : b;
    }

    int getHeight(Order *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        int leftheight = getHeight(node->left);
        int rightheight = getHeight(node->right);
        return max(leftheight, rightheight) + 1;
    }

    int height(struct Order *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int getBalance(struct Order *N)
    {
        if (N == NULL)
            return 0;
        else
            return height(N->left) - height(N->right);
    }

    Order *leftRotate(struct Order *x)
    {
        struct Order *y = x->right;
        struct Order *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Order *rightRotate(struct Order *y)
    {
        struct Order *x = y->left;
        struct Order *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Order *insertNode(Order *node, Package orderinfo)
    {
        // Find the correct position to insertNode the node and insert it
        if (node == NULL)
            return (newNode(orderinfo));
        if (orderinfo.trackingNumber < node->orderdetails.trackingNumber)
            node->left = insertNode(node->left, orderinfo);
        else if (orderinfo.trackingNumber > node->orderdetails.trackingNumber)
            node->right = insertNode(node->right, orderinfo);
        else
            return node;

        // assigining height to new node
        node->height = 1 + max(height(node->left), height(node->right));

        // checking balance of whole tree.
        int balance = getBalance(node);

        // if tree is left skewed do right rotation means root has balance factor +2
        if (balance > 1 && orderinfo.trackingNumber < node->left->orderdetails.trackingNumber)
            return rightRotate(node);

        // if tree is right skewed do left rotation means root has balance factor -2
        if (balance < -1 && orderinfo.trackingNumber > node->right->orderdetails.trackingNumber)
            return leftRotate(node);

        // here we do two rotations one left and other right
        if (balance > 1 && orderinfo.trackingNumber > node->left->orderdetails.trackingNumber)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // here we do two rotations one right and other left
        if (balance < -1 && orderinfo.trackingNumber < node->right->orderdetails.trackingNumber)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node; // returns node if tree is balanced.
    }

    Order *searchOrder(Order *node, int trackingNumber)
    {
        if (node == NULL || node->orderdetails.trackingNumber == trackingNumber)
            return node;

        if (node->orderdetails.trackingNumber < trackingNumber)
            return searchOrder(node->right, trackingNumber);

        return searchOrder(node->left, trackingNumber);
    }

    void updateOrder(Order *node, int trackingNumber, const string &orderStatus)
    {
        if (node == NULL)
            return;

        if (node->orderdetails.trackingNumber == trackingNumber)
        {
            node->orderdetails.orderstatus = orderStatus;
            return;
        }
        if (node->orderdetails.trackingNumber < trackingNumber)
            updateOrder(node->right, trackingNumber, orderStatus);
        else
            updateOrder(node->left, trackingNumber, orderStatus);
    }

    void insert(Package orderdetails)
    {
        root = insertNode(root, orderdetails);
    }

    void updateOrderStatus(int trackingNumber, string orderStatus)
    {
        updateOrder(root, trackingNumber, orderStatus);
    }

    void searchSpecificOrder()
    {
        if (root == NULL)
        {
            cout << "There are no orders" << endl;
            return;
        }
        int trackingnumber;
        cout << "Enter tracking number: ";
        cin >> trackingnumber;
        Order *order = searchOrder(root, trackingnumber);
        if (order == NULL)
        {
            cout << "Wrong tracking number" << endl;
        }
        else
        {
            cout << "Order Status: " << order->orderdetails.orderstatus << endl;
        }
    }

    void inorderTraversal(Order *node)
    {
        if (node != NULL)
        {
            inorderTraversal(node->left);
            cout << "Order ID: " << node->orderdetails.trackingNumber << ", Order Status: " << node->orderdetails.orderstatus << endl;
            inorderTraversal(node->right);
        }
    }

    void displayAllOrders()
    {
        if (root == NULL)
        {
            cout << "There are no orders" << endl;
            return;
        }
        cout << "All Orders:" << endl;
        inorderTraversal(root);
    }
};
#endif
