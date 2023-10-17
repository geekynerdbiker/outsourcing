package tests;

import static org.junit.jupiter.api.Assertions.*;

import java.io.IOException;
import java.lang.reflect.Method;
import java.time.Duration;
import java.util.ArrayList;
import java.util.Random;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import serviceClasses.Graded;
import serviceClasses.PlayerNode;
import stage2.PlayerLinkedList;

class CustomLinkedListTest {

    @Test
    @Graded(description = "addToFront", marks = 10)
    public void testAddToFront() {
    	
    	// Adding null to an empty list
        PlayerLinkedList list = new PlayerLinkedList();
        list.addToFront(null);
        assertNull(list.start);

        // Adding null to a list with 1 player
        PlayerNode[] players = new PlayerNode[] { generatePlayer1() };
        list = new PlayerLinkedList();
        list.start = players[0];
        list.addToFront(null);
        assertNull(list.start.next);

        // Adding a player to an empty list
        PlayerNode p = generatePlayer1();
        list = new PlayerLinkedList();
        list.addToFront(p);
        assertTrue(list.start == p);
        assertNull(list.start.next);

        // Adding five Players to a list
        players = new PlayerNode[5];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            list.addToFront(players[i]);
    	}
        assertTrue(nodesNameAndScoresEqual(players[4], list.start));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[0], list.start.next.next.next.next));
        assertNull(list.start.next.next.next.next.next);
        
        // Adding eight Players to a list
        players = new PlayerNode[7];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            list.addToFront(players[i]);
    	}
        assertTrue(nodesNameAndScoresEqual(players[6], list.start));
        assertTrue(nodesNameAndScoresEqual(players[5], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[4], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[0], list.start.next.next.next.next.next.next));
        assertNull(list.start.next.next.next.next.next.next.next);
        
        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "addToEnd", marks = 10)
    public void testAddToEnd() {
    	
    	// Adding null to an empty list
        PlayerLinkedList list = new PlayerLinkedList();
        list.addToEnd(null);
        assertNull(list.start);

        // Adding null to a list with 1 player
        PlayerNode[] players = new PlayerNode[] { generatePlayer1() };
        list = new PlayerLinkedList();
        list.start = players[0];
        list.addToEnd(null);
        assertNull(list.start.next);

        // Adding a player to an empty list
        PlayerNode p = generatePlayer1();
        list = new PlayerLinkedList();
        list.addToEnd(p);
        assertTrue(list.start == p);
        assertNull(list.start.next);

        // Adding five Players to a list
        players = new PlayerNode[5];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            list.addToEnd(players[i]);
    	}
        assertTrue(nodesNameAndScoresEqual(players[0], list.start));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[4], list.start.next.next.next.next));
        assertNull(list.start.next.next.next.next.next);
        
        // Adding eight Players to a list
        players = new PlayerNode[7];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            list.addToEnd(players[i]);
    	}
        assertTrue(nodesNameAndScoresEqual(players[0], list.start));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[4], list.start.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[5], list.start.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[6], list.start.next.next.next.next.next.next));
        assertNull(list.start.next.next.next.next.next.next.next);
        
        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "add", marks = 10)
    public void testAdd() {
    	
    	// Adding null to an empty list
        PlayerLinkedList list = new PlayerLinkedList();
        list.add(0, null);
        assertNull(list.start);

        // Adding null to a list with 1 player
        PlayerNode[] players = new PlayerNode[] { generatePlayer1() };
        list = new PlayerLinkedList();
        list.start = players[0];
        list.add(1, null);
        assertNull(list.start.next);

        // Adding a player to an empty list
        PlayerNode p = generatePlayer1();
        list = new PlayerLinkedList();
        list.add(0, p);
        assertTrue(list.start == p);
        assertNull(list.start.next);
        
        p = generatePlayer1();
        list = new PlayerLinkedList();
        list.add(1, p); //out of bounds
        assertNull(list.start);

        // Adding five Players to start of a list
        players = new PlayerNode[5];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            list.add(0, players[i]);
    	}
        assertTrue(nodesNameAndScoresEqual(players[4], list.start));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[0], list.start.next.next.next.next));
        assertNull(list.start.next.next.next.next.next);
        
        // Adding eight Players to a list
        players = new PlayerNode[7];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            list.add(i, players[i]);
    	}
        assertTrue(nodesNameAndScoresEqual(players[0], list.start));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[4], list.start.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[5], list.start.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[6], list.start.next.next.next.next.next.next));
        assertNull(list.start.next.next.next.next.next.next.next);
    	
        // add somewhere in the middle
        p = generatePlayer1();
        list.add(3, p);
        p = generatePlayer2();
        list.add(5, p);
        assertTrue(nodesNameAndScoresEqual(players[0], list.start));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(generatePlayer1(), list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(generatePlayer2(), list.start.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[4], list.start.next.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[5], list.start.next.next.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[6], list.start.next.next.next.next.next.next.next.next));
        assertNull(list.start.next.next.next.next.next.next.next.next.next);
        
        // out of bounds
        p = generatePlayer2();
        list.add(12, p);
        // ensure remains unchanged
        assertTrue(nodesNameAndScoresEqual(players[0], list.start));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(generatePlayer1(), list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(generatePlayer2(), list.start.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[4], list.start.next.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[5], list.start.next.next.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[6], list.start.next.next.next.next.next.next.next.next));
        assertNull(list.start.next.next.next.next.next.next.next.next.next);
        
        list.add(-5, p);
        // ensure remains unchanged
        assertTrue(nodesNameAndScoresEqual(players[0], list.start));
        assertTrue(nodesNameAndScoresEqual(players[1], list.start.next));
        assertTrue(nodesNameAndScoresEqual(players[2], list.start.next.next));
        assertTrue(nodesNameAndScoresEqual(generatePlayer1(), list.start.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[3], list.start.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(generatePlayer2(), list.start.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[4], list.start.next.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[5], list.start.next.next.next.next.next.next.next));
        assertTrue(nodesNameAndScoresEqual(players[6], list.start.next.next.next.next.next.next.next.next));
        assertNull(list.start.next.next.next.next.next.next.next.next.next);
        
        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "findPlayer", marks = 10)
    public void testFindPlayer() {
    	
    	// Empty players list
    	PlayerLinkedList list = new PlayerLinkedList();
        assertNull(list.findPlayer("Alice"));
        assertNull(list.findPlayer("Ursula"));
        assertNull(list.findPlayer("Michael"));
        assertNull(list.findPlayer("Nataly"));
        assertNull(list.findPlayer("PlayerThatDoesn'tExist"));
    	
    	// Player does not exist
        PlayerNode[] players = new PlayerNode[5];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
        	list.addToEnd(players[i]);
        }
        assertNull(list.findPlayer("Michael"));
        assertNull(list.findPlayer("Nataly"));
        assertNull(list.findPlayer("PlayerThatDoesn'tExist"));
    	
    	// Player is the first
        players = new PlayerNode[5];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
        	list.addToEnd(players[i]);
        }
        
        list.start.name = "Rachel";
        assertTrue(list.findPlayer("Rachel") == list.start);
        
        list.start.name = "Anthony";
        assertTrue(list.findPlayer("Anthony") == list.start);
        
    	// Player is the last
        players = new PlayerNode[5];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
        	list.addToEnd(players[i]);
        }
        
        list.start.next.next.next.next.name = "Rachel";
        assertTrue(list.findPlayer("Rachel") == list.start.next.next.next.next);
        
        list.start.next.next.next.next.name = "Anthony";
        assertTrue(list.findPlayer("Anthony") == list.start.next.next.next.next);
    	
        players = new PlayerNode[5];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
        	list.addToEnd(players[i]);
        }
        
        list.start.next.next.name = "Rachel";
        assertTrue(list.findPlayer("Rachel") == list.start.next.next);
        
        list.start.next.next.next.name = "Anthony";
        assertTrue(list.findPlayer("Anthony") == list.start.next.next.next);
        
        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "removeAllOccurrences", marks = 5)
    public void testRemoveAllOccurrences() {
    	
    	// None of the Player names contain the String
    	PlayerNode[] players = new PlayerNode[10];
        PlayerLinkedList list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
        	list.addToEnd(players[i]);
        }
        PlayerLinkedList instanceCopy = new PlayerLinkedList(list); // instance copy to check against after function is called
        list.removeAllOccurrences("hello");
        assertTrue(list.equals(instanceCopy));
        list.removeAllOccurrences("testing123");
        assertTrue(list.equals(instanceCopy));
    	
        // PlayerList with 1 Player (player's name includes the String)
        players = new PlayerNode[1];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
        	list.addToEnd(players[i]);
        }
        
        list.start.name = "Samuel";
        list.removeAllOccurrences("Sam");
        assertNull(list.start);
        
        // Remove all Players except the last one
        players = new PlayerNode[5];
        list = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            if(i != 4) {
            	players[i].name = "Samuel";
            }
        	list.addToEnd(players[i]);
        }
        
        PlayerLinkedList expected = new PlayerLinkedList();
        expected.addToEnd(players[4]);
        
        list.removeAllOccurrences("Sam");
        assertNull(list.start.next);
        assertTrue(list.equals(expected));
        
        // One player name contains the String (first Player)
        players = new PlayerNode[5];
        list = new PlayerLinkedList();
        expected = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            if(i == 0) {
            	players[i].name = "Lauren";
            }
        	list.addToEnd(players[i]);
        	if(i != 0) {
        		expected.addToEnd(new PlayerNode(players[i], null));
        	}
        }
        
        list.removeAllOccurrences("ren");
        assertTrue(list.equals(expected));
        
        // One player name contains the String (last Player)
        players = new PlayerNode[7];
        list = new PlayerLinkedList();
        expected = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            if(i == 6) {
            	players[i].name = "Lauren";
            }
        	list.addToEnd(players[i]);
        	if(i != 6) {
        		expected.addToEnd(new PlayerNode(players[i], null));
        	}
        }
        
        list.removeAllOccurrences("ren");
        assertTrue(list.equals(expected));
        
        // One player name contains the String
        players = new PlayerNode[15];
        list = new PlayerLinkedList();
        expected = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            if(i == 8) {
            	players[i].name = "Lauren";
            }
        	list.addToEnd(players[i]);
        	if(i != 8) {
        		expected.addToEnd(new PlayerNode(players[i], null));
        	}
        }
        
        list.removeAllOccurrences("ren");
        assertTrue(list.equals(expected));
    	
    	// Multiple players have names that contain the String
        players = new PlayerNode[12];
        list = new PlayerLinkedList();
        expected = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            if(i == 3 || i == 6 || i == 7 || i == 8 || i == 11) {
            	players[i].name = "Michael";
            }
        	list.addToEnd(players[i]);
        	if(i != 3 && i != 6 && i != 7 && i != 8 && i != 11) {
        		expected.addToEnd(new PlayerNode(players[i], null));
        	}
        }
        
        list.removeAllOccurrences("Michael");
        assertTrue(list.equals(expected));
        
        players = new PlayerNode[8];
        list = new PlayerLinkedList();
        expected = new PlayerLinkedList();
        for (int i = 0; i < players.length; i++) {
            players[i] = generateRandomPlayer(0, 100);
            if(i == 2 || i == 5 || i == 6) {
            	players[i].name = "Nataly";
            }
        	list.addToEnd(players[i]);
        	if(i != 2 && i != 5 && i != 6) {
        		expected.addToEnd(new PlayerNode(players[i], null));
        	}
        }
        
        list.removeAllOccurrences("Nataly");
        assertTrue(list.equals(expected));
        
        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "mergeAscending", marks = 2.5)
    public void testMergeAscending() {
        // players is empty
        PlayerNode[] players = new PlayerNode[0];
        PlayerNode[] p = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), new PlayerNode("Bob", new int[] {90, 92, 57, 84}), new PlayerNode("Charlie", new int[] {98, 99, 94, 92, 91}), new PlayerNode("Alice", new int[] {95, 97})};
        PlayerNode[] expected1 = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), new PlayerNode("Bob", new int[] {90, 92, 57, 84}), new PlayerNode("Charlie", new int[] {98, 99, 94, 92, 91}), new PlayerNode("Alice", new int[] {95, 97})};
        
        PlayerLinkedList list = new PlayerLinkedList(players);
        PlayerNode pList = (new PlayerLinkedList(p)).start;
        PlayerLinkedList expected = new PlayerLinkedList(expected1);
        
        list.mergeAscending(pList);
        
        assertTrue(list.equals(expected));
        
        // p is empty
        players =  new PlayerNode[] {new PlayerNode("Bob", new int[] {90, 92, 57, 84}), new PlayerNode("Charlie", new int[] {98, 99, 94, 92, 91}), new PlayerNode("Alice", new int[] {95, 97}), new PlayerNode("Ursula", new int[] {45, 23})};
        p = new PlayerNode[0];
        expected1 = new PlayerNode[] {new PlayerNode("Bob", new int[] {90, 92, 57, 84}), new PlayerNode("Charlie", new int[] {98, 99, 94, 92, 91}), new PlayerNode("Alice", new int[] {95, 97}), new PlayerNode("Ursula", new int[] {45, 23})};
        
        list = new PlayerLinkedList(players);
        pList = (new PlayerLinkedList(p)).start;
        expected = new PlayerLinkedList(expected1);
        
        PlayerNode temp = expected.start;
        for(int i = 0; i < expected1.length; i++, temp = temp.next) { // error will be flagged if expected1 and expected are not the same length
            assertTrue(nodesNameAndScoresEqual(expected1[i], temp)); // check addToEnd is working
        }
        
        list.mergeAscending(pList);
        
        assertTrue(list.equals(expected));
        
        // players and p both have one Player each
        players = new PlayerNode[] {new PlayerNode("Dave", new int[] {80, 85})};
        p = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23})};
        expected1 = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), new PlayerNode("Dave", new int[] {80, 85})};
        
        list = new PlayerLinkedList(players);
        pList = (new PlayerLinkedList(p)).start;
        expected = new PlayerLinkedList(expected1);
        
        temp = expected.start;
        for(int i = 0; i < expected1.length; i++, temp = temp.next) { // error will be flagged if expected1 and expected are not the same length
            assertTrue(nodesNameAndScoresEqual(expected1[i], temp)); // check addToEnd is working
        }
        
        list.mergeAscending(pList);
        
        assertTrue(list.equals(expected));
        
        // players and p both have one Player each
        players = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23})}; // swap from above test
        p = new PlayerNode[] {new PlayerNode("Dave", new int[] {80, 85})};
        expected1 = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), new PlayerNode("Dave", new int[] {80, 85})};
        
        list = new PlayerLinkedList(players);
        pList = (new PlayerLinkedList(p)).start;
        expected = new PlayerLinkedList(expected1);
        
        temp = expected.start;
        for(int i = 0; i < expected1.length; i++, temp = temp.next) { // error will be flagged if expected1 and expected are not the same length
            assertTrue(nodesNameAndScoresEqual(expected1[i], temp)); // check addToEnd is working
        }
        
        list.mergeAscending(pList);
        
        assertTrue(list.equals(expected));
        
        // multiple Players in both players and p
        players = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), generatePlayer1(), generatePlayer2(), new PlayerNode("Dave", new int[] {80, 85})};
        p = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 28}), new PlayerNode("Bob", new int[] {90, 92, 57, 84}), new PlayerNode("Charlie", new int[] {98, 99, 94, 92, 91}), new PlayerNode("Alice", new int[] {95, 97})};
        expected1 = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), new PlayerNode("Ursula", new int[] {45, 28}), generatePlayer1(), new PlayerNode("Bob", new int[] {90, 92, 57, 84}), new PlayerNode("Charlie", new int[] {98, 99, 94, 92, 91}), new PlayerNode("Alice", new int[] {95, 97}), generatePlayer2(), new PlayerNode("Dave", new int[] {80, 85})};
        
        list = new PlayerLinkedList(players);
        pList = (new PlayerLinkedList(p)).start;
        expected = new PlayerLinkedList(expected1);
        
        temp = expected.start;
        for(int i = 0; i < expected1.length; i++, temp = temp.next) { // error will be flagged if expected1 and expected are not the same length
            assertTrue(nodesNameAndScoresEqual(expected1[i], temp)); // check addToEnd is working
        }
        
        list.mergeAscending(pList);
        
        assertTrue(list.equals(expected));
        
        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "mergeAscending (Timeout)", marks = 2.5)
    public void testMergeAscendingAdvanced() { 
    	/**
    	 * The test must finish within 2 seconds. It will take around 
    	 * 0.1 * seconds for a good implementation and about 20 seconds 
    	 * for a slow implementation
    	**/ 
    	assertTimeoutPreemptively(Duration.ofSeconds(2), () -> {
    		//Create a list containing 25000 nodes with values 1, 2, 3, ... 
    		int numberOfNodes = 25000; PlayerLinkedList list = new PlayerLinkedList();
    		for(int i = numberOfNodes; i >= 1; i--)
    			list.addToFront(new PlayerNode("Node " + i, new int[] { i }, null));
    		
    		//Create another list with the same number of nodes
    		PlayerLinkedList list2 = new PlayerLinkedList();
    		for(int i = numberOfNodes; i >= 1; i--)
    			list2.addToFront(new PlayerNode("Node " + i, new int[] { i }, null));
    		
    		//Merge list1 with the nodes in list2
    		list.mergeAscending(list2.start);
    		
    		// Check Nodes have correct values
    		PlayerNode current = list.start;
    		for(int i = 1; i <= numberOfNodes; i++) {
    			assertEquals(i, current.averageScore());
    			assertEquals(i, current.next.averageScore());
    			current = current.next.next;
    		}
    	});
    	
    	currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
	}
    
    @Test
    @Graded(description = "flatten", marks = 5)
    public void testFlatten() {
    	
    	// players is empty
    	PlayerNode[] players = new PlayerNode[0];
    	PlayerLinkedList list = new PlayerLinkedList(players);
    	int[] expected = new int[]{};
    	int[] actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	// players has one Player
    	players = new PlayerNode[] {new PlayerNode("Dave", new int[] {80, 85})};
    	list = new PlayerLinkedList(players);
    	expected = new int[]{80, 85};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	players = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), new PlayerNode("Dave", new int[] {80, 85})};
    	list = new PlayerLinkedList(players);
    	expected = new int[]{45, 23, 80, 85};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	// multiple Players
    	players = new PlayerNode[] {new PlayerNode("Dave", new int[] {80, 85}), new PlayerNode("Ursula", new int[] {45, 23})};
    	list = new PlayerLinkedList(players);
    	expected = new int[]{80, 85, 45, 23};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	players = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), new PlayerNode("Ursula", new int[] {45, 28}), generatePlayer1(), new PlayerNode("Bob", new int[] {90, 92, 57, 84}), new PlayerNode("Charlie", new int[] {98, 99, 94, 92, 91}), new PlayerNode("Alice", new int[] {95, 97}), generatePlayer2()};
    	list = new PlayerLinkedList(players);
    	expected = new int[]{45, 23, 45, 28, 18, 58, 93, 46, 17, 58, 140, 90, 92, 57, 84, 98, 99, 94, 92, 91, 95, 97, 184, 85, 49, 80, 57, 203, 408, 5, 0, 105};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
        
        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "recreate2D", marks = 5)
    public void testRecreate2D() {
    	
    	// players is empty
    	PlayerNode[] players = new PlayerNode[0];
    	PlayerLinkedList list = new PlayerLinkedList(players);
    	int[][] expected = new int[0][0];
    	int[][] actual = list.recreate2D();
    	assertEquals(expected.length, actual.length);
    	
    	// Players has two Players
    	players = new PlayerNode[] {new PlayerNode("Dave", new int[] {80, 85}), new PlayerNode("Ursula", new int[] {45, 23, 79, 54, 84})};
    	list = new PlayerLinkedList(players);
    	expected = new int[][] {new int[] {80, 85}, new int[] {45, 23, 79, 54, 84}};
    	actual = list.recreate2D();
    	for(int i = 0; i < actual.length; i++) {
    		for(int j = 0; j < actual[i].length; j++) {
    			expected[i][j] = actual[i][j];
    		}
    	}
    	for(int i = 0; i < players.length; i++) {
    		assertFalse(players[i].scores == actual[i]); // test result is a deep copy
    	}
    	
    	// players has one Player
    	players = new PlayerNode[] {new PlayerNode("Dave", new int[] {80, 85})};
    	list = new PlayerLinkedList(players);
    	expected = new int[][] {new int[] {80, 85}};
    	actual = list.recreate2D();
    	for(int i = 0; i < actual.length; i++) {
    		for(int j = 0; j < actual[i].length; j++) {
    			expected[i][j] = actual[i][j];
    		}
    	}
    	for(int i = 0; i < players.length; i++) {
    		assertFalse(players[i].scores == actual[i]); // test result is a deep copy
    	}
    	
    	players = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23})};
    	list = new PlayerLinkedList(players);
    	expected = new int[][] {new int[] {45, 23}};
    	actual = list.recreate2D();
    	for(int i = 0; i < actual.length; i++) {
    		for(int j = 0; j < actual[i].length; j++) {
    			expected[i][j] = actual[i][j];
    		}
    	}
    	for(int i = 0; i < players.length; i++) {
    		assertFalse(players[i].scores == actual[i]); // test result is a deep copy
    	}
    	
    	// multiple Players
    	players = new PlayerNode[] {new PlayerNode("Ursula", new int[] {45, 23}), new PlayerNode("Ursula", new int[] {45, 28}), generatePlayer1(), new PlayerNode("Bob", new int[] {90, 92, 57, 84}), new PlayerNode("Charlie", new int[] {98, 99, 94, 92, 91}), new PlayerNode("Alice", new int[] {95, 97}), generatePlayer2()};
    	list = new PlayerLinkedList(players);
    	expected = new int[][] {new int[] {45, 23}, new int[] {45, 28}, new int[] {18, 58, 93, 46, 17, 58, 140}, new int[] {90, 92, 57, 84}, new int[] {98, 99, 94, 92, 91}, new int[] {95, 97}, new int[] {184, 85, 49, 80, 57, 203, 408, 5, 0, 105}};
    	actual = list.recreate2D();
    	for(int i = 0; i < actual.length; i++) {
    		for(int j = 0; j < actual[i].length; j++) {
    			expected[i][j] = actual[i][j];
    		}
    	}
    	for(int i = 0; i < players.length; i++) {
    		assertFalse(players[i].scores == actual[i]); // test result is a deep copy
    	}
        
        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }

    private static final String[] FIRST_NAMES = { "Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Henry",
            "Isabelle", "Jack", "Kate", "Luke", "Molly", "Nathan", "Olivia", "Peter", "Quentin", "Rose", "Samuel",
            "Tina", "Ursula", "Victoria", "Walter", "Xavier", "Yvonne", "Zachary" };

    // Generate a random player with scores between min (inclusive) and max
    // (exclusive)
    public PlayerNode generateRandomPlayer(int min, int max) {
        Random r = new Random();
        String name = FIRST_NAMES[r.nextInt(FIRST_NAMES.length)];
        int[] scores = new int[r.nextInt(50)];
        for (int i = 0; i < scores.length; i++)
            scores[i] = min + r.nextInt(max - min);
        PlayerNode player = new PlayerNode(name, scores, null);
        return player;
    }

    public PlayerNode generatePlayer1() {
        int[] scores = { 18, 58, 93, 46, 17, 58, 140 };
        PlayerNode player = new PlayerNode("Michael", scores, null);
        return player;
    }

    public PlayerNode generatePlayer2() {
        int[] scores = { 184, 85, 49, 80, 57, 203, 408, 5, 0, 105 };
        PlayerNode player = new PlayerNode("Nataly", scores, null);
        return player;
    }
    
    // Check two Nodes have same name and scores
    public static boolean nodesNameAndScoresEqual(PlayerNode n1, PlayerNode n2) {
    	if (n1.scores.length != n2.scores.length) {
    		return false;
    	}
    	for(int i = 0; i < n1.scores.length; i++) {
    		if(n1.scores[i] != n2.scores[i]) {
    			return false;
    		}
    	}
    	return n1.name.equals(n2.name);
    }

    /*
     * DO NOT MODIFY BELOW
     */

    public static double score = 0;
    public static String result = "";
    public static String currentMethodName = null;
    ArrayList<String> methodsPassed = new ArrayList<String>();

    @BeforeEach
    public void run() {
        currentMethodName = null;
    }

    @AfterEach
    public void logSuccess() throws NoSuchMethodException, SecurityException {
        if (currentMethodName != null && !methodsPassed.contains(currentMethodName)) {
            methodsPassed.add(currentMethodName);
            Method method = getClass().getMethod(currentMethodName);
            Graded graded = method.getAnnotation(Graded.class);
            score += graded.marks();
            score = Math.min(score, 100);
            result += graded.description() + " passed. Marks awarded: " + graded.marks() + "\n";
            serviceClasses.CSV.write(this.getClass().toString(), currentMethodName, graded.marks());
        }
    }

    @AfterAll
    public static void wrapUp() throws IOException {
        if (result.length() != 0) {
            result = result.substring(0, result.length() - 1); // remove the last "\n"
        }
        System.out.println(result);
        System.out.println("\nMarks for this file: " + score);
    }

}
