//  Complete this file by adding your code when "// FILL IN WITH YOUR CODE" is written

#ifndef ASSIGNMENT4_GRAPH
#define ASSIGNMENT4_GRAPH

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

using namespace std;

class Graph {         // Directed graph class for assignment 4

public:

  // Define public data types of Vertex and Edge and the associated iterators.

  class Vertex;
  class Edge;

  typedef list<Vertex> VertexList;
  typedef list<Edge> EdgeList;
  typedef VertexList::iterator VertexItor;
  typedef EdgeList::iterator EdgeItor;

private:

  VertexList vertexCollection;  // list of all the vertices in the graph
  int n;                        // Number of vertices in the graph
  
  struct VertexObject {         // vertex object class
    VertexObject(string _id) : id(_id){}   // constructor
    string id;                  // id of the vertex
    int aux;                    // auxiliary data field that you may use in your
                                // implementation of Dijkstra's algorithm
    EdgeList outgoingEdgeList;  // list of outgoing edges from this vertex
  };
  
public:

  class Vertex{     //  vertex class; it is essentially a pointer to a vertex object
  public:
    Vertex(VertexObject * v = NULL) : vobj(v){}  // constructor
    string& operator*() const{                   // returns the vertex id
      return vobj->id;
    }
    void setAux(int x){                    // sets the auxiliary data
      vobj->aux = x;
    }
    const int & getAux() const{                  // returns the auxiliary data
      return vobj->aux;
    }
    EdgeList outgoingEdgeList() const{           // returns the outgoing edge list
      return vobj->outgoingEdgeList;
    }
    bool operator==(const Vertex &v){       // checks whether two vertices point to the same vertex object
      return this->vobj == v.vobj;
    }
    bool isAdjacentTo(const Vertex &v){     // checks whether the current vertex has an outgoing edge to v
      for(EdgeItor itr = vobj->outgoingEdgeList.begin(); itr != vobj->outgoingEdgeList.end(); itr++){
        if(itr->dest() == v)
          return true;
      }

      return false;
    }
  private:
    VertexObject * vobj; // pointer to the associated vertex object
  friend class Graph;
  };
  
  class Edge{   // edge class
  public:
    Edge(Vertex origin, Vertex dest, double weight=0) : _weight(weight),
      _origin(origin), _dest(dest) {}   // constructor
    double& operator*(){               // returns the weight
      return _weight;
    }
    Vertex origin() const{            // returns the origin
      return _origin;
    }
    Vertex dest() const{              // returns the destination
      return _dest;
    }
  private:           // private data members
    double _weight;
    Vertex _origin;
    Vertex _dest;
  friend class  Graph;
  };
  
public:

  Graph() : n(0) {}   // constructor
  int size() const{   // returns the size of the graph
    return n;
  }
  Vertex insertVertex(const string& id){     // inserts a new vertex
      Vertex newVertex(new VertexObject(id));
    vertexCollection.push_back(newVertex);
    n += 1;

    return newVertex;
  }
  
  Edge insertEdge(double weight, Vertex origin, Vertex dest){  // inserts a new edge
   Edge newEdge(origin, dest, weight);

    for(VertexItor itr = vertexCollection.begin(); itr != vertexCollection.end(); itr++){
      if(*itr == origin){
        itr->vobj->outgoingEdgeList.push_back(newEdge);
        break;
      }
    }

    return newEdge;
  }
  
  VertexList getVertexCollection() const{  // returns a list of all the vertices
    return vertexCollection;
  }
  
  // Read a graph from an input file.
  // The graph should initially be empty. Otherwise, throw a runtime_error
  void ReadFile(string filename, Vertex & s, Vertex & t){
    ifstream is(filename);

    int N, M, S, T;
    is >> N >> M >> S >> T;

    vector<Vertex> v(N);

    for(int i = 0; i < N; i++){
      int idx;
      string id;
      is >> idx >> id;
      v[idx] = insertVertex(id);
    }

    s = v[S];
    t = v[T];

    for(int i = 0; i < M; i++){
      int oIdx, dIdx;
      double w;
      is >> oIdx >> dIdx >> w;
      insertEdge(w, v[oIdx], v[dIdx]);
    }
  }
};

vector<string> Dijkstra(Graph &G, Graph::Vertex s, Graph::Vertex t);
  // computes a shortest path from vertex s to vertex t in graph G
  // definition is to be written in the graph.cpp file
#endif

