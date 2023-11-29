import guru.nidi.graphviz.engine.Format;
import guru.nidi.graphviz.engine.Graphviz;
import org.jgrapht.graph.DefaultDirectedGraph;
import org.jgrapht.graph.DefaultEdge;

import java.io.*;
import java.util.*;

public class GraphFeatures {
    public DefaultDirectedGraph<String, DefaultEdge> graph;

    public GraphFeatures() {
        // Initialize an empty directed graph when creating a new MyGraph object.
        this.graph = new DefaultDirectedGraph<>(DefaultEdge.class);
    }

    public void parseGraph(String filepath) {
        try (BufferedReader br = new BufferedReader(new FileReader(filepath))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.contains("->")) {
                    // Parse edges (e.g., "a -> b")
                    String[] parts = line.split("->");
                    String srcNode = parts[0].trim();
                    String dstNode = parts[1].trim();
                    this.graph.addVertex(srcNode);
                    this.graph.addVertex(dstNode);
                    this.graph.addEdge(srcNode, dstNode);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String toString() {
        // Print information about the graph, including nodes and edges.
        StringBuilder result = new StringBuilder();
        result.append("Number of nodes: ").append(graph.vertexSet().size()).append("\n");
        result.append("Nodes: ").append(graph.vertexSet()).append("\n");
        result.append("Number of edges: ").append(graph.edgeSet().size()).append("\n");
        result.append("Edges: ").append(graph.edgeSet()).append("\n");
        return result.toString();
    }

    public void outputGraph(String filepath) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filepath))) {
            for (DefaultEdge edge : graph.edgeSet()) {
                String srcNode = graph.getEdgeSource(edge);
                String dstNode = graph.getEdgeTarget(edge);
                writer.println(srcNode + " -> " + dstNode);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void addNode(String label) {
        if (!graph.containsVertex(label)) {
            graph.addVertex(label);
        } else {
            System.out.println("Node with label '" + label + "' already exists.");
        }
    }

    public void addNodes(String[] labels) {
        for (String label : labels) {
            addNode(label);
        }
    }

    public void addEdge(String srcLabel, String dstLabel) {
        if (graph.containsVertex(srcLabel) && graph.containsVertex(dstLabel)) {
            DefaultEdge newEdge = new DefaultEdge();
            if (!graph.containsEdge(srcLabel, dstLabel)) {
                graph.addEdge(srcLabel, dstLabel, newEdge);
            } else {
                System.out.println("Edge between '" + srcLabel + "' and '" + dstLabel + "' already exists.");
            }
        } else {
            System.out.println("One or both of the specified nodes do not exist.");
        }
    }

    public void outputDOTGraph(String path) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(path))) {
            writer.println("digraph G {");

            // Write nodes with attributes
            for (String node : graph.vertexSet()) {
                writer.println("    " + node + " [label=\"" + node + "\"];");
            }

            // Write edges with attributes
            for (DefaultEdge edge : graph.edgeSet()) {
                String srcNode = graph.getEdgeSource(edge);
                String dstNode = graph.getEdgeTarget(edge);
                writer.println("    " + srcNode + " -> " + dstNode + " [label=\"" + graph.getEdgeWeight(edge) + "\"];");
            }

            writer.println("}");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void outputGraphics(String path, String format) {
        try {
            Graphviz.fromFile(new File("output.dot"))
                    .render(Format.valueOf(format))
                    .toFile(new File(path));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // Remove functions
    public void removeNode(String label) {
        if (graph.containsVertex(label)) {
            graph.removeVertex(label);
            System.out.println("Removed Node " + label);
        } else {
            System.out.println("Node with label '" + label + "' does not exist.");
        }
    }

    public void removeNodes(String[] labels) {
        for (String label : labels) {
            removeNode(label);
        }
    }

    public void removeEdge(String srcLabel, String dstLabel) {
        if (graph.containsEdge(srcLabel, dstLabel)) {
            graph.removeEdge(srcLabel, dstLabel);
            System.out.println("Removed Edge " + srcLabel + " -> " + dstLabel);
        } else {
            System.out.println("Edge between '" + srcLabel + "' and '" + dstLabel + "' does not exist.");
        }
    }

    public enum Algorithm {
        BFS,
        DFS
    }

    public Path graphSearch(String srcLabel, String dstLabel, Algorithm algo) {
        if (algo == Algorithm.BFS) {
            // Create a queue for BFS
            Queue<String> queue = new LinkedList<>();
            // Create a map to keep track of visited nodes and their parent nodes
            Map<String, String> parentMap = new HashMap<>();

            // Initialize the starting node
            queue.add(srcLabel);
            parentMap.put(srcLabel, null);

            // Perform BFS
            while (!queue.isEmpty()) {
                String currentNode = queue.poll();

                // Check if the destination node is found
                if (currentNode.equals(dstLabel)) {
                    // Reconstruct the path from destination to source
                    List<String> pathNodes = new ArrayList<>();
                    String node = dstLabel;
                    while (node != null) {
                        pathNodes.add(node);
                        node = parentMap.get(node);
                    }
                    Collections.reverse(pathNodes);
                    return new Path(pathNodes);
                }

                // Visit neighbors
                for (DefaultEdge edge : graph.outgoingEdgesOf(currentNode)) {
                    String neighborNode = graph.getEdgeTarget(edge);
                    if (!parentMap.containsKey(neighborNode)) {
                        queue.add(neighborNode);
                        parentMap.put(neighborNode, currentNode);
                    }
                }
            }

            // If the destination node is not reachable, return null
            return null;
        } else if (algo == Algorithm.DFS) {
            // Create a stack for DFS
            Deque<String> stack = new ArrayDeque<>();
            // Create a map to keep track of visited nodes and their parent nodes
            Map<String, String> parentMap = new HashMap<>();

            // Initialize the starting node
            stack.push(srcLabel);
            parentMap.put(srcLabel, null);

            // Perform DFS
            while (!stack.isEmpty()) {
                String currentNode = stack.pop();

                // Check if the destination node is found
                if (currentNode.equals(dstLabel)) {
                    // Reconstruct the path from destination to source
                    List<String> pathNodes = new ArrayList<>();
                    String node = dstLabel;
                    while (node != null) {
                        pathNodes.add(node);
                        node = parentMap.get(node);
                    }
                    Collections.reverse(pathNodes);
                    return new Path(pathNodes);
                }

                // Visit neighbors
                for (DefaultEdge edge : graph.outgoingEdgesOf(currentNode)) {
                    String neighborNode = graph.getEdgeTarget(edge);
                    if (!parentMap.containsKey(neighborNode)) {
                        stack.push(neighborNode);
                        parentMap.put(neighborNode, currentNode);
                    }
                }
            }

            // If the destination node is not reachable, return null
            return null;
        } else {
            // Handle the case when an unsupported algorithm is chosen
            throw new IllegalArgumentException("Unsupported algorithm: " + algo);

        }
    }

    public static void main(String[] args) {
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("input.dot"); // Provide the path to your DOT input file

        // Add nodes (if needed)
        String[] newNodes = {"D", "E", "F"};
        g.addNodes(newNodes);

        // Add edges
        g.addEdge("A", "D");
        g.addEdge("D", "E");
        g.addEdge("E", "A");

        // Output the graph to a DOT file
        g.outputDOTGraph("output.dot");

        // Output the graph to a PNG image
        g.outputGraphics("outputDOT.png", "PNG");

//        // Remove nodes and edges (demonstrating the remove APIs)
//        g.removeNode("A");
//        g.removeEdge("D", "E");

        // Find a path from node "A" to node "E" using BFS
        Path pathBFS = g.graphSearch("A", "E", Algorithm.BFS);
        Path pathDFS = g.graphSearch("A", "E", Algorithm.DFS);

        if (pathBFS != null) {
            System.out.println("BFS Path from A to E: " + pathBFS);
        } else {
            System.out.println("No BFS path from A to E.");
        }
        if (pathDFS != null) {
            System.out.println("DFS Path from A to E: " + pathDFS);
        } else {
            System.out.println("No DFS path from A to E.");
        }
    }
}

class BFS extends GraphFeatures {
    @Override
    public Path graphSearch(String srcLabel, String dstLabel, Algorithm algo) {
        // Create a stack for DFS
        Queue<String> queue = new LinkedList<>();
        // Create a map to keep track of visited nodes and their parent nodes
        Map<String, String> parentMap = new HashMap<>();

        // Initialize the starting node
        queue.add(srcLabel);
        parentMap.put(srcLabel, null);

        // Perform BFS
        while (!queue.isEmpty()) {
            String currentNode = queue.poll();

            // Check if the destination node is found
            if (currentNode.equals(dstLabel)) {
                // Reconstruct the path from destination to source
                List<String> pathNodes = new ArrayList<>();
                String node = dstLabel;
                while (node != null) {
                    pathNodes.add(node);
                    node = parentMap.get(node);
                }
                Collections.reverse(pathNodes);
                return new Path(pathNodes);
            }

            // Visit neighbors
            for (DefaultEdge edge : graph.outgoingEdgesOf(currentNode)) {
                String neighborNode = graph.getEdgeTarget(edge);
                if (!parentMap.containsKey(neighborNode)) {
                    queue.add(neighborNode);
                    parentMap.put(neighborNode, currentNode);
                }
            }
        }

        // If the destination node is not reachable, return null
        return null;
    }
}

class DFS extends GraphFeatures {
    @Override
    public Path graphSearch(String srcLabel, String dstLabel, Algorithm algo) {
        // Create a stack for DFS
        Deque<String> stack = new ArrayDeque<>();
        // Create a map to keep track of visited nodes and their parent nodes
        Map<String, String> parentMap = new HashMap<>();

        // Initialize the starting node
        stack.push(srcLabel);
        parentMap.put(srcLabel, null);

        // Perform DFS
        while (!stack.isEmpty()) {
            String currentNode = stack.pop();

            // Check if the destination node is found
            if (currentNode.equals(dstLabel)) {
                // Reconstruct the path from destination to source
                List<String> pathNodes = new ArrayList<>();
                String node = dstLabel;
                while (node != null) {
                    pathNodes.add(node);
                    node = parentMap.get(node);
                }
                Collections.reverse(pathNodes);
                return new Path(pathNodes);
            }

            // Visit neighbors
            for (DefaultEdge edge : graph.outgoingEdgesOf(currentNode)) {
                String neighborNode = graph.getEdgeTarget(edge);
                if (!parentMap.containsKey(neighborNode)) {
                    stack.push(neighborNode);
                    parentMap.put(neighborNode, currentNode);
                }
            }
        }

        // If the destination node is not reachable, return null
        return null;
    }
}
