// Author : aqibm22

#include <bits/stdc++.h>
#include "Graph.h"
using namespace std;

class DirectedGraph : public Graph
{
public:
    DirectedGraph(int nodes) : Graph(nodes)
    {}

    virtual bool isCyclic();

    virtual void addEdge(int u, int v, long long w = 1) {
        adjacencyList[u].push_back({v, w});
    }
    vector<vector<int>> getStronglyConnectedComponents();
    vector<int> topologicalSort();

private:

    vector<int> getEndTimes();
    void EndTimeHelper(int src, vector<int>& EndTimes, vector<bool>& visited);
    DirectedGraph getReversal();

};

vector<vector<int>> DirectedGraph :: topologicalSort() {
    vector<int> topo;
    int numberOfNodes = this -> getNumberOfNodes();

    vector<int> indegree(numberOfNodes + 1, 0); // to calculate the indegreeree of the nodes

    queue<int> nodesLeftToExplore;

    for (int i = 1; i <= numberOfNodes; i++)
        for (auto &it : adjacencyList[i])
            indegree[it.first]++;
    for (int i = 1; i <= numberOfNodes; i++) {
        if (!indegree[i])
            nodesLeftToExplore.push(i);
    }
    while (!nodesLeftToExplore.empty()) {
        int u = nodesLeftToExplore.top();
        nodesLeftToExplore.pop();
        topo.push_back(u);
        for (auto &v : adjacencyList[u])
        {
            indegree[v.first]--;
            if (!indegree[v.first])
                nodesLeftToExplore.push(v.first);
        }
    }
    if (topo.size() != numberOfNodes)
        return {};
    else
        return topo;
}

bool DirectedGraph::isCyclic() {
    vector<int> topo = topologicalSort();
    if (topo.size() == 0)
        return 1; // yes there is a cycle
    return 0; // no cycle
}

vector<vector<int>> DirectedGraph :: getStronglyConnectedComponents() {
    vector<vector<int>> stronglyConnectedComponents;
    int numberOfNodes = this -> getNumberOfNodes();
    vector<int> EndTimes = this -> getEndTimes();
    DirectedGraph reversedGraph = this -> getReversal();

    vector<bool> visited(numberOfNodes + 1, 0);

    for (int i = EndTimes.size() - 1; i >= 0; i--) {
        vector<int> SCC;
        if (!visited[EndTimes[i]])
        {
            reversedGraph.dfsHelper(EndTimes[i], SCC, visited);
            stronglyConnectedComponents.push_back(SCC);
        }
    }

    return stronglyConnectedComponents;
}

vector<int> DirectedGraph :: getEndTimes() {
    vector<int> EndTimes;
    vector<bool> visited(this -> getNumberOfNodes() + 1, 0);

    for (int src = 1; src <= this -> getNumberOfNodes(); src++) {
        if (!visited[src])
        {
            EndTimeHelper(src, EndTimes, visited);
        }
    }

    return EndTimes;
}


void DirectedGraph :: EndTimeHelper(int src, vector<int>& EndTimes, vector<bool>& visited) {
    visited[src] = 1;

    for (auto neighbour : this -> adjacencyList[src]) {
        if (!visited[neighbour.first])
            EndTimeHelper(neighbour.first, EndTimes, visited);
    }

    EndTimes.push_back(src);
}

DirectedGraph DirectedGraph :: getReversal() {
    DirectedGraph gT(this -> getNumberOfNodes());

    for (int node = 1; node <= this -> getNumberOfNodes(); node++) {
        for (auto edge : adjacencyList[node]) {
            gT.addEdge(edge.first, node);
        }
    }
    return gT;
}
