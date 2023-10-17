import java.util.ArrayList;

class Edge {
    Vertex target;
    long weight;
    Boolean isTransfer;

    public Edge(Vertex target, long weight, Boolean isTransfer) {
        this.target = target;
        this.weight = weight;
        this.isTransfer = isTransfer;
    }
}

class Vertex implements Comparable<Vertex> {
    String id;
    String name;
    String line;
    ArrayList<Edge> adj;
    long dist;
    Vertex prev;

    public Vertex(String id, String name, String line) {
        super();
        this.id = id;
        this.line = line;
        this.name = name;
        this.adj = new ArrayList<>();
        this.dist = Long.MAX_VALUE;
    }

    public void addEdge(Edge e) {
        this.adj.add(e);
    }

    public int compareTo(Vertex v) {
        return Long.compare(this.dist, v.dist);
    }
}

