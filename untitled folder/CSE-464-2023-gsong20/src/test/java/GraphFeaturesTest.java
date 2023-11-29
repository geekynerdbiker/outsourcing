import org.example.GraphFeatures;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.*;

public class GraphFeaturesTest {
    @Test
    public void testParseGraph() {
        System.out.println("Running testParseGraph");
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("testInput.dot"); // Provide a test input file

        // Check if the number of nodes, edges match the expected values
        assertEquals(3, g.graph.vertexSet().size());
        assertEquals(3, g.graph.edgeSet().size());
    }

    @Test
    public void testAddNode() {
        System.out.println("Running testAddNode");
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("testInput.dot"); // Provide a test input file

        // Add a node and check if it exists in the graph
        g.addNode("D");
        assertTrue(g.graph.containsVertex("D"));

        // Add a list of nodes and check if they exist in the graph
        String[] newNodes = {"E", "F"};
        g.addNodes(newNodes);
        assertTrue(g.graph.containsVertex("E"));
        assertTrue(g.graph.containsVertex("F"));
    }

    @Test
    public void testAddEdge() {
        System.out.println("Running testAddEdge");
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("testInput.dot"); // Provide a test input file

        // Add an edge and check if it exists in the graph
        g.addEdge("A", "C");
        assertTrue(g.graph.containsEdge("A", "C"));
    }

    @Test
    public void testOutputDOTGraph() throws IOException {
        System.out.println("Running testOutputDOTGraph");
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("testInput.dot"); // Provide a test input file
        g.outputDOTGraph("testOutput.dot"); // Output to a test file

        // Read the expected output from a file
        String expected = new String(Files.readAllBytes(Paths.get("testExpectedOutput.dot")), StandardCharsets.UTF_8);

        // Read the actual output from the generated file
        String actual = new String(Files.readAllBytes(Paths.get("testOutput.dot")), StandardCharsets.UTF_8);

        // Compare the expected and actual output
        assertEquals(expected, actual);
    }

    @Test
    public void testOutputGraphics() {
        System.out.println("Running testOutputGraphics");
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("testInput.dot"); // Provide a test input file
        g.outputGraphics("testOutput.png", "PNG"); // Output to a test PNG file

        // Check if the PNG file exists
        File pngFile = new File("testOutput.png");
        assertTrue(pngFile.exists());
    }

    // Tests for removing node and edge
    @Test
    public void testRemoveNode() {
        System.out.println("Running testRemoveNode");
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("testInput.dot"); // Provide a test input file

        // Scenario 1: Remove an existing node and verify it is removed
        g.removeNode("A");
        assertFalse(g.graph.containsVertex("A"));
        assertEquals(2, g.graph.vertexSet().size()); // Verify total node count

        // Scenario 2: Attempt to remove a non-existent node, should not cause exceptions
        g.removeNode("X"); // X does not exist
        assertFalse(g.graph.containsVertex("X")); // X should still not exist

        // Scenario 3: Remove an existing node and verify it is removed
        g.removeNode("C");
        assertFalse(g.graph.containsVertex("C"));
        assertEquals(1, g.graph.vertexSet().size()); // Verify total node count
    }

    @Test
    public void testRemoveNodes() {
        System.out.println("Running testRemoveNodes");
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("testInput.dot"); // Provide a test input file

        // Scenario 1: Remove existing nodes and verify they are removed
        String[] nodesToRemove = {"A", "B", "C"};
        g.removeNodes(nodesToRemove);
        assertFalse(g.graph.containsVertex("A"));
        assertFalse(g.graph.containsVertex("B"));
        assertFalse(g.graph.containsVertex("C"));
        assertEquals(0, g.graph.vertexSet().size()); // Verify no nodes left

        // Scenario 2: Attempt to remove non-existent nodes, should not cause exceptions
        String[] nonExistentNodes = {"X", "Y"};
        g.removeNodes(nonExistentNodes);
        assertFalse(g.graph.containsVertex("X"));
        assertFalse(g.graph.containsVertex("Y"));
        assertEquals(0, g.graph.vertexSet().size()); // No nodes should exist
    }

    @Test
    public void testRemoveEdge() {
        System.out.println("Running testRemoveEdge");
        GraphFeatures g = new GraphFeatures();
        g.parseGraph("testInput.dot"); // Provide a test input file

        // Scenario 1: Remove an existing edge and verify it is removed
        g.removeEdge("A", "B");
        assertFalse(g.graph.containsEdge("A", "B"));
        assertEquals(2, g.graph.edgeSet().size()); // Verify total edge count

        // Scenario 2: Attempt to remove a non-existent edge, should not cause exceptions
        g.removeEdge("X", "Y"); // X -> Y does not exist
        assertFalse(g.graph.containsEdge("X", "Y")); // Edge should still not exist

        // Scenario 3: Remove an existing edge and verify it is removed
        g.removeEdge("B", "C");
        assertFalse(g.graph.containsEdge("B", "C"));
        assertEquals(1, g.graph.edgeSet().size()); // Verify total edge count
    }
}
