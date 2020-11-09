#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "ugraph.h"
#include "wgraph.h"

template <class Vertex>
void dfs2(Vertex v, const UnweightedGraph<Vertex>* graph,
    std::set<Vertex> &reached, std::stack<Vertex> &TS) {
  typename std::set<Vertex>::iterator itr;
  std::set<Vertex> connected;

  reached.insert(v);
  connected = graph->getConnectionFrom(v);
  for (itr = connected.begin(); itr != connected.end(); itr++) {
    if (reached.find(*itr) == reached.end()) {
      dfs2(*itr, graph, reached, TS);
    }
  }
  TS.push(v);
}

template <class Vertex>
std::string topologicalSort(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  std::set<Vertex> reached;
  std::vector<Vertex> vertexes;
  std::stack<Vertex> TS;

  vertexes = graph->getVertexes();
  for (itr = vertexes.begin(); itr != vertexes.end(); itr++) {
    if (reached.find(*itr) == reached.end()) {
      dfs2(*itr, graph, reached, TS);
    }
  }

  std::stringstream aux;
  aux << "[";
  while (!TS.empty()) {
    aux << TS.top(); TS.pop();
    if (!TS.empty()) {
      aux << " ";
    }
  }
  aux << "]";
  return aux.str();
}

template <class Vertex>
bool isBipartite(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  typename std::set<Vertex>::iterator j;
  std::vector<Vertex> vertexes;
  std::set<Vertex> connections;
  std::map<Vertex, int> color;
  std::queue<Vertex> q;
  Vertex vertex;
  bool result;

  vertexes = graph->getVertexes();
  for (itr = vertexes.begin(); itr != vertexes.end(); itr++) {
    color.insert(std::pair<Vertex, int>((*itr), -1));
    vertex = (*itr);
  }

  result = true;
  color[vertex] = 1;
  q.push(vertex);
  while (!q.empty()) {
    vertex = q.front(); q.pop();
    connections = graph->getConnectionFrom(vertex);
    for (j = connections.begin(); j != connections.end(); j++) {
      if (color[(*j)] == -1) {
        color[(*j)] = 1 - color[vertex];
        q.push((*j));
      } else if (color[vertex] == color[(*j)]) {
        result = false;
      }
    }
  }

  return result;
}

template <class Vertex>
bool isCyclic(Vertex v, const UnweightedGraph<Vertex>* graph,
  std::set<Vertex> &reached, Vertex parent) {
  typename std::set<Vertex>::iterator itr;

  reached.insert(v);

  std::set<Vertex> connections = graph->getConnectionFrom(v);
  for (itr = connections.begin(); itr != connections.end(); itr++) {
    if (reached.find((*itr)) == reached.end()) {
      if (isCyclic((*itr), graph, reached, v)) {
        return true;
      }
    } else if ((*itr) != parent) {
      return true;
    }
  }
  return false;
}

template <class Vertex>
bool isTree(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  std::set<Vertex> reached;
  std::vector<Vertex> vertexes;
  Vertex start;

  vertexes = graph->getVertexes();
  start = vertexes[0];

  if (isCyclic(start, graph, reached, -1)) {
    return false;
  }

  for (itr = vertexes.begin(); itr != vertexes.end(); itr++) {
    if (reached.find((*itr)) == reached.end()) {
      return false;
    }
  }

  return true;
}

#endif /* ACTIVITY_H */
