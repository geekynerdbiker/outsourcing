package org.example;

import guru.nidi.graphviz.engine.Format;
import guru.nidi.graphviz.engine.Graphviz;
import org.jgrapht.graph.DefaultDirectedGraph;
import org.jgrapht.graph.DefaultEdge;

import java.io.*;
import java.util.*;

public class GraphFeatures {
    public DefaultDirectedGraph<String, DefaultEdge> graph;
    SearchAlgorithm algo;

    public GraphFeatures(SearchAlgorithm algo) {
        // Initialize an empty directed graph when creating a new MyGraph object.
        this.graph = new DefaultDirectedGraph<>(DefaultEdge.class);
        this.algo = algo;
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
        DFS,
        RW
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
        SearchAlgorithm bfs = new BFS();
        SearchAlgorithm dfs = new DFS();
        SearchAlgorithm rw = new RW();
        GraphFeatures g1 = new GraphFeatures(bfs);
        GraphFeatures g2 = new GraphFeatures(dfs);
        GraphFeatures g3 = new GraphFeatures(rw);
        g1.parseGraph("input.dot"); // Provide the path to your DOT input file
        g2.parseGraph("input.dot"); // Provide the path to your DOT input file
        g3.parseGraph("input.dot"); // Provide the path to your DOT input file

        // Add nodes (if needed)
        String[] newNodes = {"D", "E", "F"};
        g1.addNodes(newNodes);
        g2.addNodes(newNodes);
        g3.addNodes(newNodes);

        // Add edges
        g1.addEdge("A", "D");
        g1.addEdge("D", "E");
        g1.addEdge("E", "A");

        g2.addEdge("A", "D");
        g2.addEdge("D", "E");
        g2.addEdge("E", "A");

        g3.addEdge("A", "D");
        g3.addEdge("D", "E");
        g3.addEdge("E", "A");

        // Output the graph to a DOT file
        g1.outputDOTGraph("output1.dot");
        g2.outputDOTGraph("output2.dot");
        g3.outputDOTGraph("output3.dot");

        // Output the graph to a PNG image
        g1.outputGraphics("outputDOT1.png", "PNG");
        g2.outputGraphics("outputDOT2.png", "PNG");
        g3.outputGraphics("outputDOT3.png", "PNG");

//        // Remove nodes and edges (demonstrating the remove APIs)
//        g.removeNode("A");
//        g.removeEdge("D", "E");

        // Find a path from node "A" to node "E" using BFS
        Path pathBFS = g1.graphSearch("A", "E", Algorithm.BFS);
        Path pathDFS = g2.graphSearch("A", "E", Algorithm.DFS);
        Path pathRW = g3.graphSearch("A", "E", Algorithm.RW);

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
        if (pathRW != null) {
            System.out.println("RW Path from A to E: " + pathDFS);
        } else {
            System.out.println("No RW path from A to E.");
        }
    }
}

interface SearchAlgorithm {
    public Path graphSearch(String srcLabel, String dstLabel, GraphFeatures.Algorithm algo);
    public DefaultDirectedGraph<String, DefaultEdge> graph;
}

class BFS implements SearchAlgorithm {
    public Path graphSearch(String srcLabel, String dstLabel, GraphFeatures.Algorithm algo) {
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
    }
}

class DFS implements SearchAlgorithm {
    public Path graphSearch(String srcLabel, String dstLabel, GraphFeatures.Algorithm algo) {
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


class RW implements SearchAlgorithm {
    public Path graphSearch(String srcLabel, String dstLabel, GraphFeatures.Algorithm algo) {
        // Create a queue for RW
        Queue<String> queue = new ArrayDeque<>();
        // Create a map to keep track of visited nodes and their parent nodes
        Map<String, String> parentMap = new HashMap<>();

        // Initialize the starting node
        queue.add(srcLabel);
        parentMap.put(srcLabel, null);

        // Perform RW
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

            // Visit neighbors random
            Random random = new Random();
            DefaultEdge[] edges = graph.outgoingEdgesOf(currentNode);
            int next = random.nextInt(edges.length);
            String neighborNode = graph.getEdgeTarget(edges[next]);
            if (!parentMap.containsKey(neighborNode)) {
                queue.push(neighborNode);
                parentMap.put(neighborNode, currentNode);
            }
        }
    }
}