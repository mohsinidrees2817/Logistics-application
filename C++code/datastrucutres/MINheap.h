#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <queue>
#include "structures/Package.h"

using namespace std;
#define Size 50

class MINheap
{
public:
    Package H[Size];
    int n = 0;

    void heapUp(int i)
    {
        int p;
        if (i == 0)
            return;
        if (i % 2 == 1)
            p = (i - 1) / 2;
        else
            p = (i - 2) / 2;
        if (H[i].deliverytime < H[p].deliverytime)
        {
            Package temp = H[i];
            H[i] = H[p];
            H[p] = temp;
            heapUp(p);
        }
    }

    void heapDown(int p)
    {
        int l, r, g;
        l = 2 * p + 1;
        r = 2 * p + 2;

        if (p >= n)
            return;

        if (l < n)
            if (r < n)
                if (H[l].deliverytime < H[r].deliverytime)
                    g = l;
                else
                    g = r;
            else
                g = l;
        else
            return;
        if (H[g].deliverytime < H[p].deliverytime)
        {
            Package t = H[g];
            H[g] = H[p];
            H[p] = t;
        }
        heapDown(g);
    }

    void insert(const Package &v)
    {
        if (n >= Size)
            return;
        H[n++] = v;
        heapUp(n - 1);
    }

    void remove()
    {
        if (n == 0)
            return;
        int p;
        H[0] = H[n - 1]; // replace 0 index with last
        n--;             // decrement total size
        heapDown(0);
    }

    void display()
    {
        for (int i = 0; i < n; i++){
            cout <<i+1<<":"<< H[i].trackingNumber << endl;
        }
    }

    bool isEmpty()
    {
        return (n == 0);
    }

    Package getFirst()
    {
        if (!isEmpty())
            return H[0];
    }
};

#endif
