#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// a very mighty ciorba cu afumatura si oua of libraries, it appears to be

using namespace std;

const long long inf = 1e18;

struct edge{
    int to;
    long long weight; // in the specifc contest of this problem, its supposed to be length
}; // but it does not really matter

int main()
{
    // we are tasked with finding the shortest / cheapest path from vertex 1 to n
    // not we, just me, i, actually
    int n, m, u , v;
    long long w, d;
    cin >> n >> m;
    vector<vector<edge>> adj(n + 1);
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        if(u != v) // because apparently we can have an edge from v to .... v. and its not free.
        {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }
    vector<long long> dist(n + 1, inf); // to store the minimum distance from a vertice to 1
    vector<int> parent(n + 1, -1); // because we have to reconstruct the path
    // note that if a vertice is not reached, its parent is marked as -1
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    // priority queue for jikstra. the element at the top has the smallest provisional cost from 1 to it
    dist[1] = 0;
    pq.push({0, 1}); // i suppose we all have to start somewhere
    while(!pq.empty())
    {
        d = pq.top().first;
        u = pq.top().second;
        pq.pop();
        if(d > dist[u])
            continue; // it means there is no point to continue with this path
        if(u == n)
            break; // it means we are done for the day;
        // since the element at the top of the heap is always the one with the least provisonal cost
        // it means there is no other waty to reach n and have a lower cost
        // so we can safely exit the loop knowing that we have not missed a better path
        for(const auto& edge: adj[u])
        {
            // we. i, just did some fancy stuff
            // we know what auto does. const makes it so that we dont accidentally change the weight or
            // something else by accident. & means it works straight on the list, without copying ti to memory
            v = edge.to;
            w = edge.weight;
            if(dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    if(dist[n] == inf)
    {
        cout << -1 << '\n';
        return 0; // this stops the execution of the rest of the program. curat murdar coane fanica
    }
    vector <int> path;
    for(int i = n; i != -1; i = parent[i])
        {
            path.push_back(i);
        }
    for(int i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i] << " ";
    }
    return 0;
}