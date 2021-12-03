#include "Vertex.h"

Vertex::Vertex(int key) {
    m_key = key;
    m_size = NULL;
    m_pEHead = NULL;
    m_pNext = NULL;
}

Vertex::~Vertex() {
    
}

void Vertex::SetNext(Vertex* pNext) {
    m_pNext = pNext;
}

void Vertex::AddEdge(int edgeKey, int weight) {
    m_pEHead = new Edge(edgeKey, weight);
}

void Vertex::Clear() {}
