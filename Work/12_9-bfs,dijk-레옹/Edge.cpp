#include "Edge.h"

Edge::Edge() {
    m_key = NULL;
    m_weight = NULL;
}

/// copy constructor
Edge::Edge(int key, int weight) {
    m_key = key;
    m_weight = weight;
}

/// set the next pointer of this edge
void Edge::SetNext(Edge* pNext) {
    m_pNext = pNext;
}
