// Author : aqibm22


#include <vector>
#include <queue>
using namespace std;

// This is the parent class
class Graph {

public:

  Graph(int nodes) {
    numberOfNodes = nodes;
    adjacencyList = vector<vector<pair<int, long long>>>(nodes + 1);
  }

  virtual void addEdge(int u, int v, long long weight) = 0;
  virtual bool isCyclic() = 0;
  vector<int> bfs(int source);
  vector<int> dfs(int source);
  int getNumberOfNodes()
  {
    return numberOfNodes;
  }

protected:
  int numberOfNodes;
  // denotes the number of nodes

  vector<vector<pair<int, long long>>> adjacencyList;
  /*adjacencyList[i] represents direct neighbours of node i
  adjacencyList[i].first represents an edge from node i to node adjList[i].first.
  adjacencyList[i].second represents weight of this edge.*/

  void dfsHelper(int source, vector<int>& nodesDiscovered, vector<bool>& visited);

};

vector<int> Graph::bfs(int source) {
  vector<int> nodesDiscovered;
  queue<int> nodesToExplore;
  vector<bool> visited(numberOfNodes + 1, 0);

  nodesToExplore.push(source);
  visited[source] = true;

  while (!nodesToExplore.empty())
  {
    int explore = nodesToExplore.front();
    nodesToExplore.pop();
    nodesDiscovered.push_back(explore);

    for (pair<int, long long> neighbours : adjacencyList[explore])
    {
      int neighbour = neighbours.first;
      if (!visited[neighbour])
      {
        visited[neighbour] = 1;
        nodesToExplore.push(neighbour);
      }
    }
  }
  return nodesDiscovered;
}

void Graph::dfsHelper(int source, vector<int> &nodesDiscovered, vector<bool> &visited) {
  visited[source] = 1;
  nodesDiscovered.push_back(source);

  for (pair<int, long long> neighbours : adjacencyList[source])
  {
    int neighbour = neighbours.first;
    if (visited[neighbour] == false)
      dfsHelper(neighbour, nodesDiscovered, visited);

  }
}

vector<int> Graph::dfs(int source) {
  vector<int> nodesDiscovered;
  vector<bool> visited(numberOfNodes + 1, false);
  dfsHelper(source, nodesDiscovered, visited);
  return nodesDiscovered;
}
