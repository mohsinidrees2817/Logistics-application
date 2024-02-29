#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include "structures/Paths.h"

using namespace std;

#define MAX_NODES 500

struct Edge
{
    int weight;
    int distance;
    int deliveryTime;
    string serviceLevel;
};

class Graph
{
private:
    int n;
    string V[MAX_NODES];
    unordered_map<string, unordered_map<string, Edge> > edges;

public:
    Graph()
    {
        n = 0;
    }
    // Paths paths;
    void addVertex(string vertex)
    {
        if (search(vertex) < 0)
        {
            V[n] = vertex;
            n++;
        }
    }

    void addEdge(string from, string to, int weight, int distance, int deliveryTime, string serviceLevel)
    {
        int f = search(from);
        int t = search(to);
        if (f < 0 || t < 0)
        {
            cout << from << " vertex " << to << " not found" << endl;
            return;
        }

        Edge edge;
        edge.weight = weight;
        edge.distance = distance;
        edge.deliveryTime = deliveryTime;
        edge.serviceLevel = serviceLevel;

        edges[from][to] = edge;
        // edges[to][from] = edge; // for undirected graph
    }

    bool hasVertex(string vertex)
    {
        return (search(vertex) >= 0);
    }

    void displayVertices()
    {
        for (int i = 0; i < n; i++)
        {
            cout << V[i] << endl;
        }
    }

    int search(string vertex)
    {
        for (int i = 0; i < n; i++)
            if (V[i] == vertex)
                return i;
        return -1;
    }

    vector<string> getLinkedCities(string city)
    {
        vector<string> linkedCities;
        if (edges.count(city) > 0)
        {
            for (auto it = edges[city].begin(); it != edges[city].end(); ++it)
            {
                linkedCities.push_back(it->first);
            }
        }
        return linkedCities;
    }

    int getEdgeWeight(string from, string to)
    {
        if (edges[from].count(to) > 0)
            return edges[from][to].weight;
        return 0;
    }

    Paths canReachDestination(string from, string to)
    {
        unordered_map<string, int> distance;
        unordered_map<string, int> deliveryTime;
        unordered_map<string, string> previous;
        priority_queue<pair<int, string>, vector<pair<int, string> >, greater<pair<int, string> > > pq;

        // Initialize distances to infinity and previous vertices to null
        for (int i = 0; i < n; i++)
        {
            distance[V[i]] = INT_MAX;
            deliveryTime[V[i]] = INT_MAX;
            previous[V[i]] = "";
        }

        // Distance and delivery time to the source city are 0
        distance[from] = 0;
        deliveryTime[from] = 0;
        pq.push(make_pair(0, from));

        while (!pq.empty())
        {
            string current = pq.top().second;
            pq.pop();

            // Stop if the destination city is reached
            if (current == to)
            {
                // Build the route
                vector<string> route;
                string city = to;
                while (city != "")
                {
                    route.push_back(city);
                    city = previous[city];
                }
                reverse(route.begin(), route.end());

                // Return the shortest distance, delivery time, and route
                Paths info;
                info.distance = distance[to];
                info.deliveryTime = deliveryTime[to];
                info.route = route;
                return info;
            }

            for (const auto &neighbor : edges[current])
            // for (int i = 0; i < edges[current].size(); ++i)
            {
                string next = neighbor.first;
                int weight = neighbor.second.weight;
                int time = neighbor.second.deliveryTime;

                int totalDistance = distance[current] + weight;
                int totalTime = deliveryTime[current] + time;
                
                if (totalDistance < distance[next])
                {
                    distance[next] = totalDistance;
                    deliveryTime[next] = totalTime;
                    previous[next] = current;
                    pq.push(make_pair(totalDistance, next));
                }
            }
        }

        // If the destination city is not reachable
        vector<string> route;
        Paths info;
        info.distance = 0;
        info.deliveryTime = 0;
        info.route = route;
        return info;
    }

   

};
