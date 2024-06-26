#include "Graph.h"

#include <iostream>
#include <sstream>
#include <functional>

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<Node*> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<Edge*> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(Node* n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(Edge* e) {
  // DONE FOR YOU
  edges.push_back(e);
}

void Graph::removeNode(Node* n) {
  // DONE FOR YOU
  for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}

void Graph::removeEdge(Edge* e) {
  // DONE FOR YOU
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node* n) {
  // DONE FOR YOU
  set<Edge*> ret;
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    Edge* edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
  for (Node* node : nodes) {
    node->clear();
  }
  //  node->setColor(WHITE);
  //  node->setDiscoveryTime(-1);
  //  node->setFinishTime(-1);
  //  node->setRank(-1);
  //}
  for (Edge* edge : edges) {
    edge->setType(UNDISCOVERED_EDGE);
  }
  clock = 0;
  // TODO
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

void Graph::dfs(Node* start) {
  //clear();

  //function<void(Node*)> dfs_visit = [&](Node* u) {
  //  u->setColor(GRAY, clock++);
  //  set<Edge*> adjEdges = getAdjacentEdges(u);
  //  for (Edge* edge : adjEdges) {
  //    Node* v = edge->getEnd();
  //    if (v->getColor() == WHITE) {
  //      edge->setType(TREE_EDGE);
  //      dfs_visit(v);
  //    }
  //  }
  //  u->setColor(BLACK, clock++);


  //  clock++;
  //  u->setDiscoveryTime(clock);

  //  set<Edge*> adjEdges = getAdjacentEdges(u);
  //  for (Edge* edge : adjEdges) {
  //    Node* v = edge->getEnd();
  //    if (v->getColor() == WHITE) {
  //      edge->setType(TREE_EDGE);
  //      dfs_visit(v);
  //    }
  //  }
  //  u->setColor(BLACK);
  //  clock++;
  //  u->setFinishTime(clock);


  //};
  //dfs_visit(start);
  // TODO
}

void Graph::bfs(Node* start) {
  clear();

  queue<Node*> q;
  q.push(start);
  start->setRank(0);

  while (!q.empty()) {
    Node* u = q.front();
    q.pop();

    set<Edge*> adjEdges = getAdjacentEdges(u);
    for (Edge* edge : adjEdges) {
      Node* v = edge->getEnd();
      //if (v->getColor() == WHITE) {
      //  v->setColor(GRAY, clock++);
      //  v->setRank(u->getRank() + 1);
      //  q.push(v);
      //}
    }
    //u->setColor(BLACK, clock++);
  }
  // TODO
}

void Graph::bfs(Node* start, Node* finish) {
  clear();

  queue<Node*> q;
  q.push(start);
  start->setRank(0);

  while (!q.empty()) {
    Node* u = q.front();
    q.pop();

    if (u == finish) {
      finish->setColor(BLACK, clock++);
      return;
    }

    set<Edge*> adjEdges = getAdjacentEdges(u);
    for (Edge* edge : adjEdges) {
      Node* v = edge->getEnd();
    //  if (v->getColor() == WHITE) {
    //    v->setColor(GRAY, clock++);
    //    v->setRank(u->getRank() + 1);
    //    q.push(v);
      //}
    }
    u->setColor(BLACK, clock++);
  }
  finish->setRank(-1);
  // TODO
}

// overloading operator << lets you put a Graph object into an output
// stream.
ostream& operator<<(ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<Node*>::iterator it = graph.nodes.begin();
       it != graph.nodes.end(); it++) {
    Node* n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<Edge*>::iterator it = graph.edges.begin();
       it != graph.edges.end(); it++) {
    Edge* e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness.
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<Node*> nodes = g->getNodes();
  vector<Edge*> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    Node* n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\""
       << textColor << "\" fillcolor=\"" << what(c) << "\""
       << " ]" << endl;
  }

  string edgeColor = "black";
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    Edge* e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData()
       << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}