package tests;

import static org.junit.jupiter.api.Assertions.*;

import java.io.IOException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Random;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import serviceClasses.Graded;
import serviceClasses.Player;
import stage1.PlayerArrayList;

class CustomArrayListTest {

    @Test
    @Graded(description = "addToEnd", marks = 7)
    public void testAddToEnd() {

        // Adding null to an empty list
        PlayerArrayList list = new PlayerArrayList();
        list.addToEnd(null);
        assertEquals(0, list.numPlayers);
        assertEquals(0, list.players.length);

        // Adding null to a list with 1 player
        Player[] players = { generatePlayer1() };
        list = new PlayerArrayList(players, 1);
        list.addToEnd(null);
        assertEquals(1, list.numPlayers);
        assertEquals(1, list.players.length);

        // Adding a player to an empty list
        Player player1 = generatePlayer1();
        list = new PlayerArrayList();
        list.addToEnd(player1);
        assertEquals(1, list.numPlayers);
        assertEquals(5, list.players.length);
        assertTrue(player1.equals(list.players[0]));

        // Adding a player to a list with one Player and 0 free space
        player1 = generatePlayer1();
        players = new Player[] { generatePlayer1() };
        list = new PlayerArrayList(players, 1);
        list.addToEnd(player1);
        assertEquals(2, list.numPlayers);
        assertEquals(6, list.players.length);
        assertTrue(player1.equals(list.players[1]));

        // Adding a player to a list with four Players and 1 free space
        Player player2 = generatePlayer2();
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 4); // list has 5 Player objects but numPlayers is 4
        list.addToEnd(player2); // player2 should replace the last Player object
        assertEquals(5, list.numPlayers);
        assertEquals(5, list.players.length);
        assertTrue(player2.equals(list.players[4]));

        // Adding a player to a list with five Players and 0 free space
        player2 = generatePlayer2();
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5); // list has 5 Player objects and numPlayers is 5
        list.addToEnd(player2);
        assertEquals(6, list.numPlayers);
        assertEquals(10, list.players.length);
        assertTrue(player2.equals(list.players[5]));

        currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "addToFront", marks = 7)
    public void testAddToFront() {
    	
    	// Adding null to an empty list
        PlayerArrayList list = new PlayerArrayList();
        list.addToFront(null);
        assertEquals(0, list.numPlayers);
        assertEquals(0, list.players.length);

        // Adding null to a list with 1 player
        Player[] players = { generatePlayer1() };
        list = new PlayerArrayList(players, 1);
        list.addToFront(null);
        assertEquals(1, list.numPlayers);
        assertEquals(1, list.players.length);

        // Adding a player to an empty list
        Player player1 = generatePlayer1();
        list = new PlayerArrayList();
        list.addToFront(player1);
        assertEquals(1, list.numPlayers);
        assertEquals(5, list.players.length);
        assertTrue(player1.equals(list.players[0]));

        // Adding a player to a list with one Player and 0 free space
        player1 = generatePlayer1();
        players = new Player[] { generatePlayer1() };
        list = new PlayerArrayList(players, 1);
        list.addToFront(player1);
        assertEquals(2, list.numPlayers);
        assertEquals(6, list.players.length);
        assertTrue(player1.equals(list.players[0]));

        // Adding a player to a list with four Players and 1 free space
        Player player2 = generatePlayer2();
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 4); // list has 5 Player objects but numPlayers is 4
        PlayerArrayList instanceCopy = new PlayerArrayList(list); // instance copy to check against after Player is added
        list.addToFront(player2); // player2 should replace the first Player object, and all other Players should shift down
        assertEquals(5, list.numPlayers);
        assertEquals(5, list.players.length);
        assertTrue(player2.equals(list.players[0]));
        // check all the other Players are in the same original order
        for(int i = 1; i < list.numPlayers; i++) {
        	assertTrue(list.players[i].equals(instanceCopy.players[i-1]));
        }

        // Adding a player to a list with five Players and 0 free space
        player2 = generatePlayer2();
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5); // list has 5 Player objects and numPlayers is 5
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after Player is added
        list.addToFront(player2);
        assertEquals(6, list.numPlayers);
        assertEquals(10, list.players.length);
        assertTrue(player2.equals(list.players[0]));
        // check all the other Players are in the same original order
        for(int i = 1; i < list.numPlayers; i++) {
        	assertTrue(list.players[i].equals(instanceCopy.players[i-1]));
        }
        
    	currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "add", marks = 7)
    public void testAdd() {
    	
    	// Adding null to start of an empty list
        PlayerArrayList list = new PlayerArrayList();
        list.add(0, null);
        assertEquals(0, list.numPlayers);
        assertEquals(0, list.players.length);

        // Adding null to start of a list with 1 player
        Player[] players = { generatePlayer1() };
        list = new PlayerArrayList(players, 1);
        list.add(0, null);
        assertEquals(1, list.numPlayers);
        assertEquals(1, list.players.length);

        // Adding a player to an empty list
        Player player1 = generatePlayer1();
        list = new PlayerArrayList();
        list.add(0, player1); // add to start AND end
        assertEquals(1, list.numPlayers);
        assertEquals(5, list.players.length);
        assertTrue(player1.equals(list.players[0]));
        list = new PlayerArrayList();
        list.add(1, player1); // out of bounds
        assertEquals(0, list.numPlayers);
        assertEquals(0, list.players.length);
        list.add(10, player1); // out of bounds
        assertEquals(0, list.numPlayers);
        assertEquals(0, list.players.length);
        list.add(-5, player1); // out of bounds
        assertEquals(0, list.numPlayers);
        assertEquals(0, list.players.length);

        // Adding a player to a list with one Player and 0 free space
        player1 = generatePlayer1();
        players = new Player[] { generatePlayer1() };
        list = new PlayerArrayList(players, 1);
        list.add(0, player1); // add to start
        assertEquals(2, list.numPlayers);
        assertEquals(6, list.players.length);
        assertTrue(player1.equals(list.players[0]));
        
        players = new Player[] { generatePlayer1() };
        list = new PlayerArrayList(players, 1);
        list.add(1, player1); // add to end
        assertEquals(2, list.numPlayers);
        assertEquals(6, list.players.length);
        assertTrue(player1.equals(list.players[1]));
        
        players = new Player[] { generatePlayer1() };
        list = new PlayerArrayList(players, 1);
        list.add(2, player1); // out of bounds
        assertEquals(1, list.numPlayers);
        assertEquals(1, list.players.length);
        assertFalse(player1 == list.players[0]); // should NOT be added - should not be the same reference copy

        // Adding a player to a list with four Players and 1 free space
        Player player2 = generatePlayer2();
        // add to start
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 4); // list has 5 Player objects but numPlayers is 4
        PlayerArrayList instanceCopy = new PlayerArrayList(list); // instance copy to check against after Player is added
        list.add(0, player2); // player2 should replace the first Player object, and all other Players should shift down
        assertEquals(5, list.numPlayers);
        assertEquals(5, list.players.length);
        assertTrue(player2.equals(list.players[0]));
        // check all the other Players are in the same original order
        for(int i = 1; i < list.numPlayers; i++) {
        	assertTrue(list.players[i].equals(instanceCopy.players[i-1]));
        }
        
        // add to end
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 4); // list has 5 Player objects but numPlayers is 4
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after Player is added
        list.add(4, player2); // player2 should replace the last Player object
        assertEquals(5, list.numPlayers);
        assertEquals(5, list.players.length);
        assertTrue(player2.equals(list.players[4]));
        // check all the other Players are in the same original order
        for(int i = 0; i < list.numPlayers - 1; i++) {
        	assertTrue(list.players[i].equals(instanceCopy.players[i]));
        }
        
        // add somewhere in the middle
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 4); // list has 5 Player objects but numPlayers is 4
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after Player is added
        list.add(2, player2); // player2 should be the object at index 2, and all other Player objects previously at index 2 and onwards, should shift down
        assertEquals(5, list.numPlayers);
        assertEquals(5, list.players.length);
        assertTrue(player2.equals(list.players[2]));
        // check all the other Players are in the same original order
        for(int i = 0; i < list.numPlayers; i++) {
        	if(i < 2) {
        		assertTrue(list.players[i].equals(instanceCopy.players[i]));
        	}
        	if(i > 2) {
        		assertTrue(list.players[i].equals(instanceCopy.players[i - 1]));
        	}
        }
        
        // out of bounds
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 4); // list has 5 Player objects but numPlayers is 4
        list.add(-10, player2); // index out of bounds (shouldn't be added to the list)
        assertEquals(4, list.numPlayers);
        assertEquals(5, list.players.length);

        // Adding a player to a list with five Players and 0 free space
        player2 = generatePlayer2();
        // add to start
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5); // list has 5 Player objects and numPlayers is 5
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after Player is added
        list.add(0, player2);
        assertEquals(6, list.numPlayers);
        assertEquals(10, list.players.length);
        assertTrue(player2.equals(list.players[0]));
        // check all the other Players are in the same original order
        for(int i = 1; i < list.numPlayers; i++) {
        	assertTrue(list.players[i].equals(instanceCopy.players[i-1]));
        }
        
        // add to end
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5); // list has 5 Player objects and numPlayers is 5
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after Player is added
        list.add(5, player2);
        assertEquals(6, list.numPlayers);
        assertEquals(10, list.players.length);
        assertTrue(player2.equals(list.players[5]));
        // check all the other Players are in the same original order
        for(int i = 1; i < list.numPlayers - 1; i++) {
        	assertTrue(list.players[i].equals(instanceCopy.players[i]));
        }
        
        // add somewhere in the middle
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5); // list has 5 Player objects and numPlayers is 5
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after Player is added
        list.add(3, player2);
        assertEquals(6, list.numPlayers);
        assertEquals(10, list.players.length);
        assertTrue(player2.equals(list.players[3]));
        // check all the other Players are in the same original order
        for(int i = 0; i < list.numPlayers; i++) {
        	if(i < 3) {
        		assertTrue(list.players[i].equals(instanceCopy.players[i]));
        	}
        	if(i > 3) {
        		assertTrue(list.players[i].equals(instanceCopy.players[i - 1]));
        	}
        }
        
    	currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "findPlayer", marks = 7)
    public void testFindPlayer() {
    	
    	// Empty players list
    	PlayerArrayList list = new PlayerArrayList();
        assertNull(list.findPlayer("Alice"));
        assertNull(list.findPlayer("Ursula"));
        assertNull(list.findPlayer("Michael"));
        assertNull(list.findPlayer("Nataly"));
        assertNull(list.findPlayer("PlayerThatDoesn'tExist"));
    	
    	// Player does not exist
        Player[] players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5);
        assertNull(list.findPlayer("Michael"));
        assertNull(list.findPlayer("Nataly"));
        assertNull(list.findPlayer("PlayerThatDoesn'tExist"));
    	
    	// Player is the first
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5);
        
        list.players[0].name = "Rachel";
        assertTrue(list.findPlayer("Rachel") == list.players[0]);
        
        list.players[0].name = "Anthony";
        assertTrue(list.findPlayer("Anthony") == list.players[0]);
        
    	// Player is the last
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5);
        
        list.players[4].name = "Rachel";
        assertTrue(list.findPlayer("Rachel") == list.players[4]);
        
        list.players[4].name = "Anthony";
        assertTrue(list.findPlayer("Anthony") == list.players[4]);
    	
    	// Player is somewhere in the middle
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5);
        
        list.players[2].name = "Rachel";
        assertTrue(list.findPlayer("Rachel") == list.players[2]);
        
        list.players[3].name = "Anthony";
        assertTrue(list.findPlayer("Anthony") == list.players[3]);
    	
    	// Player exists, but not within the numPlayers range
        players = new Player[10];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 5); // only the first 5 players are in the range
        
        list.players[7].name = "Rachel";
        assertNull(list.findPlayer("Rachel"));
        
        list.players[5].name = "Anthony";
        assertNull(list.findPlayer("Anthony"));
        
    	currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "removeAllOccurrences", marks = 3)
    public void testRemoveAllOccurrences() {
    	
    	// None of the Player names contain the String
    	Player[] players = new Player[10];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        PlayerArrayList list = new PlayerArrayList(players, 7);
        PlayerArrayList instanceCopy = new PlayerArrayList(list); // instance copy to check against after function is called
        list.removeAllOccurrences("hello");
        assertTrue(list.equals(instanceCopy));
        list.removeAllOccurrences("testing123");
        assertTrue(list.equals(instanceCopy));
    	
        // PlayerList with 1 Player (player's name includes the String)
        players = new Player[5];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 1);
        list.players[0].name = "Samuel";
        list.removeAllOccurrences("Sam");
        assertEquals(0, list.numPlayers);
        assertEquals(5, list.players.length);
        
        // One player name contains the String (first Player)
        players = new Player[10];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 7);
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after function is called
        list.players[0].name = "Lauren";
        list.removeAllOccurrences("ren");
        assertEquals(6, list.numPlayers);
        assertEquals(10, list.players.length);
        for(int i = 0; i < list.numPlayers; i++) {
        	list.players[i].equals(instanceCopy.players[i+1]);
        }
        
        // One player name contains the String (last Player)
        players = new Player[10];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 7);
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after function is called
        list.players[6].name = "Bernard";
        list.removeAllOccurrences("Bernard");
        assertEquals(6, list.numPlayers);
        assertEquals(10, list.players.length);
        for(int i = 0; i < list.numPlayers; i++) {
        	list.players[i].equals(instanceCopy.players[i]);
        }
        
        // One player name contains the String
        players = new Player[10];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 7);
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after function is called
        list.players[5].name = "Michael";
        list.removeAllOccurrences("Michael");
        assertEquals(6, list.numPlayers);
        assertEquals(10, list.players.length);
        for(int i = 0; i < list.numPlayers; i++) {
        	if(i < 5) {
        		list.players[i].equals(instanceCopy.players[i]);
        	}
        	if(i >= 5) {
        		list.players[i].equals(instanceCopy.players[i+1]);
        	}
        }
    	
    	// Multiple players have names that contain the String
        players = new Player[15];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 8);
        list.players[5].name = "Michael";
        list.players[2].name = "Michael";
        list.players[4].name = "Michael";
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after function is called
        list.removeAllOccurrences("Michael");
        assertEquals(5, list.numPlayers);
        assertEquals(15, list.players.length);
        assertTrue(list.players[0].equals(instanceCopy.players[0]));
        assertTrue(list.players[1].equals(instanceCopy.players[1]));
        assertTrue(list.players[2].equals(instanceCopy.players[3]));
        assertTrue(list.players[3].equals(instanceCopy.players[6]));
        assertTrue(list.players[4].equals(instanceCopy.players[7]));
    	
    	// Players outside of the numPlayers range contain the String
        players = new Player[15];
        for (int i = 0; i < players.length; i++)
            players[i] = generateRandomPlayer(0, 100);
        list = new PlayerArrayList(players, 8);
        list.players[5].name = "Nataly";
        list.players[2].name = "Nataly";
        list.players[4].name = "Nataly";
        players[8].name = "Nataly";
        players[12].name = "Nataly";
        players[14].name = "Nataly";
        instanceCopy = new PlayerArrayList(list); // instance copy to check against after function is called
        list.removeAllOccurrences("Nataly");
        assertEquals(5, list.numPlayers);
        assertEquals(15, list.players.length);
        assertTrue(list.players[0].equals(instanceCopy.players[0]));
        assertTrue(list.players[1].equals(instanceCopy.players[1]));
        assertTrue(list.players[2].equals(instanceCopy.players[3]));
        assertTrue(list.players[3].equals(instanceCopy.players[6]));
        assertTrue(list.players[4].equals(instanceCopy.players[7]));
        
    	currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "mergeAscending", marks = 3)
    public void testMergeAscending() {
    	
        // players is empty
    	Player[] players = new Player[0];
    	Player[] p = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97})};
    	Player[] expected1 = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97})};
    	PlayerArrayList list = new PlayerArrayList(players, 0);
    	PlayerArrayList expected = new PlayerArrayList(expected1, 4);
    	list.mergeAscending(p);
    	assertEquals(4, list.numPlayers);
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertTrue(list.players[i].equals(expected.players[i]));
    	}
    	
    	// numPlayers is originally zero (but there are players in the players array)
    	players = new Player[] {new Player("Dave", new int[] {80, 85}), new Player("Ursula", new int[] {45, 23})};
    	p = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97})};
    	expected1 = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97})};
    	list = new PlayerArrayList(players, 0);
    	expected = new PlayerArrayList(expected1, 4);
    	list.mergeAscending(p);
    	assertEquals(4, list.numPlayers);
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertTrue(list.players[i].equals(expected.players[i]));
    	}
    	
    	// p is empty
    	players =  new Player[] {new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97}), new Player("Ursula", new int[] {45, 23})};
    	p = new Player[0];
    	expected1 = new Player[] {new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97})};
    	list = new PlayerArrayList(players, 3);
    	expected = new PlayerArrayList(expected1, 3);
    	list.mergeAscending(p);
    	assertEquals(3, list.numPlayers);
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertTrue(list.players[i].equals(expected.players[i]));
    	}
    	
    	// players and p both have one Player each
    	players = new Player[] {new Player("Dave", new int[] {80, 85})};
    	p = new Player[] {new Player("Ursula", new int[] {45, 23})};
    	expected1 = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Dave", new int[] {80, 85})};
    	list = new PlayerArrayList(players, 1);
    	expected = new PlayerArrayList(expected1, 2);
    	list.mergeAscending(p);
    	assertEquals(2, list.numPlayers);
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertTrue(list.players[i].equals(expected.players[i]));
    	}
    	
    	// players and p both have one Player each
    	players = new Player[] {new Player("Ursula", new int[] {45, 23})}; // swap from above test
    	p = new Player[] {new Player("Dave", new int[] {80, 85})};
    	expected1 = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Dave", new int[] {80, 85})};
    	list = new PlayerArrayList(players, 1);
    	expected = new PlayerArrayList(expected1, 2);
    	list.mergeAscending(p);
    	assertEquals(2, list.numPlayers);
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertTrue(list.players[i].equals(expected.players[i]));
    	}
    	
    	// multiple Players in both players and p
    	players = new Player[] {new Player("Ursula", new int[] {45, 23}), generatePlayer1(), generatePlayer2(), new Player("Dave", new int[] {80, 85})};
    	p = new Player[] {new Player("Ursula", new int[] {45, 28}), new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97})};
    	expected1 = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Ursula", new int[] {45, 28}), generatePlayer1(), new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97}), generatePlayer2()};
    	list = new PlayerArrayList(players, 3);
    	expected = new PlayerArrayList(expected1, 7);
    	list.mergeAscending(p);
    	assertEquals(7, list.numPlayers);
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertTrue(list.players[i].equals(expected.players[i]));
    	}
        
    	currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "flatten", marks = 3)
    public void testFlatten() {
    	
    	// players is empty
    	Player[] players = new Player[0];
    	PlayerArrayList list = new PlayerArrayList(players, 0);
    	int[] expected = new int[]{};
    	int[] actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	// numPlayers is originally zero (but there are players in the players array)
    	players = new Player[] {new Player("Dave", new int[] {80, 85}), new Player("Ursula", new int[] {45, 23})};
    	list = new PlayerArrayList(players, 0);
    	expected = new int[]{};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	// players has one Player
    	players = new Player[] {new Player("Dave", new int[] {80, 85})};
    	list = new PlayerArrayList(players, 1);
    	expected = new int[]{80, 85};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	players = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Dave", new int[] {80, 85})};
    	list = new PlayerArrayList(players, 1);
    	expected = new int[]{45, 23};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	// multiple Players
    	players = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Ursula", new int[] {45, 28}), generatePlayer1(), new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97}), generatePlayer2()};
    	list = new PlayerArrayList(players, 7);
    	expected = new int[]{45, 23, 45, 28, 18, 58, 93, 46, 17, 58, 140, 90, 92, 57, 84, 98, 99, 94, 92, 91, 95, 97, 184, 85, 49, 80, 57, 203, 408, 5, 0, 105};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
    	
    	list = new PlayerArrayList(players, 6);
    	expected = new int[]{45, 23, 45, 28, 18, 58, 93, 46, 17, 58, 140, 90, 92, 57, 84, 98, 99, 94, 92, 91, 95, 97};
    	actual = list.flatten();
    	assertArrayEquals(expected, actual);
        
    	currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }
    
    @Test
    @Graded(description = "recreate2D", marks = 3)
    public void testRecreate2D() {
    	
    	// players is empty
    	Player[] players = new Player[0];
    	PlayerArrayList list = new PlayerArrayList(players, 0);
    	int[][] expected = new int[0][0];
    	int[][] actual = list.recreate2D();
    	assertEquals(expected.length, actual.length);
    	
    	// numPlayers is originally zero (but there are players in the players array)
    	players = new Player[] {new Player("Dave", new int[] {80, 85}), new Player("Ursula", new int[] {45, 23})};
    	list = new PlayerArrayList(players, 0);
    	expected = new int[0][0];
    	actual = list.recreate2D();
    	assertEquals(expected.length, actual.length);
    	
    	// players has one Player
    	players = new Player[] {new Player("Dave", new int[] {80, 85})};
    	list = new PlayerArrayList(players, 1);
    	expected = new int[][] {new int[] {80, 85}};
    	actual = list.recreate2D();
    	for(int i = 0; i < actual.length; i++) {
    		for(int j = 0; j < actual[i].length; j++) {
    			expected[i][j] = actual[i][j];
    		}
    	}
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertFalse(list.players[i].scores == actual[i]); // test result is a deep copy
    	}
    	
    	players = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Dave", new int[] {80, 85})};
    	list = new PlayerArrayList(players, 1);
    	expected = new int[][] {new int[] {45, 23}};
    	actual = list.recreate2D();
    	for(int i = 0; i < actual.length; i++) {
    		for(int j = 0; j < actual[i].length; j++) {
    			expected[i][j] = actual[i][j];
    		}
    	}
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertFalse(list.players[i].scores == actual[i]); // test result is a deep copy
    	}
    	
    	// multiple Players
    	players = new Player[] {new Player("Ursula", new int[] {45, 23}), new Player("Ursula", new int[] {45, 28}), generatePlayer1(), new Player("Bob", new int[] {90, 92, 57, 84}), new Player("Charlie", new int[] {98, 99, 94, 92, 91}), new Player("Alice", new int[] {95, 97}), generatePlayer2()};
    	list = new PlayerArrayList(players, 7);
    	expected = new int[][] {new int[] {45, 23}, new int[] {45, 28}, new int[] {18, 58, 93, 46, 17, 58, 140}, new int[] {90, 92, 57, 84}, new int[] {98, 99, 94, 92, 91}, new int[] {95, 97}, new int[] {184, 85, 49, 80, 57, 203, 408, 5, 0, 105}};
    	actual = list.recreate2D();
    	for(int i = 0; i < actual.length; i++) {
    		for(int j = 0; j < actual[i].length; j++) {
    			expected[i][j] = actual[i][j];
    		}
    	}
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertFalse(list.players[i].scores == actual[i]); // test result is a deep copy
    	}
    	
    	list = new PlayerArrayList(players, 6);
    	expected = new int[][] {new int[] {45, 23}, new int[] {45, 28}, new int[] {18, 58, 93, 46, 17, 58, 140}, new int[] {90, 92, 57, 84}, new int[] {98, 99, 94, 92, 91}, new int[] {95, 97}};
    	actual = list.recreate2D();
    	for(int i = 0; i < actual.length; i++) {
    		for(int j = 0; j < actual[i].length; j++) {
    			expected[i][j] = actual[i][j];
    		}
    	}
    	for(int i = 0; i < list.numPlayers; i++) {
    		assertFalse(list.players[i].scores == actual[i]); // test result is a deep copy
    	}
        
    	currentMethodName = new Throwable().getStackTrace()[0].getMethodName();
    }

    private static final String[] FIRST_NAMES = { "Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Henry",
            "Isabelle", "Jack", "Kate", "Luke", "Molly", "Nathan", "Olivia", "Peter", "Quentin", "Rose", "Samuel",
            "Tina", "Ursula", "Victoria", "Walter", "Xavier", "Yvonne", "Zachary" };

    // Generate a random player with scores between min (inclusive) and max
    // (exclusive)
    public Player generateRandomPlayer(int min, int max) {
        Random r = new Random();
        String name = FIRST_NAMES[r.nextInt(FIRST_NAMES.length)];
        int[] scores = new int[r.nextInt(50)];
        for (int i = 0; i < scores.length; i++)
            scores[i] = min + r.nextInt(max - min);
        Player player = new Player(name, scores);
        return player;
    }

    public Player generatePlayer1() {
        int[] scores = { 18, 58, 93, 46, 17, 58, 140 };
        Player player = new Player("Michael", scores);
        return player;
    }

    public Player generatePlayer2() {
        int[] scores = { 184, 85, 49, 80, 57, 203, 408, 5, 0, 105 };
        Player player = new Player("Nataly", scores);
        return player;
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
