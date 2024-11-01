package stage1;

//DO NOT IMPORT ANY ADDITIONAL FILES
//The only import here should be: serviceClasses.Player

import serviceClasses.Player;
//DO NOT IMPORT ANY ADDITIONAL FILES

/**
 * Group Member 1
 * Student id:
 * First name:
 * Last name:
 * <p>
 * Group Member 2
 * Student id:
 * First name:
 * Last name:
 * <p>
 * Primary author:
 * addToFront:
 * addToEnd:
 * add:
 * findPlayer:
 * removeAllOccurences:
 * mergeAscending:
 * flatten:
 * recreate2D:
 */

/**
 * Total of 40 marks for this file
 *
 * @author mic
 */

public class PlayerArrayList {
    public Player[] players;
    public int numPlayers;
    private int capacity;

    /**
     * (7 marks) Add the given player to the end of the list. If no space is
     * available, increase the list by 5 additional spaces before adding. If null is
     * passed, no change should be made.
     *
     * @param value - the player object to add
     */
    public void addToEnd(Player value) {
        if (value == null) {
            return;
        }
        if (numPlayers == players.length) {
            Player[] newPlayers = new Player[players.length + 5];
            for (int i = 0; i < numPlayers; i++) {
                newPlayers[i] = players[i];
            }
            newPlayers[numPlayers++] = value;
            players = newPlayers;
        } else {

            players[numPlayers++] = value;
        }
    }

    /**
     * (7 marks) Add the given player to the front of the list. If no space is
     * available, increase the list by 5 additional spaces before adding. If null is
     * passed, no changes should be made.
     *
     * @param value - the player object to add
     */
    public void addToFront(Player value) {
        // TODO To be completed
        if (value == null) {
            return;
        }
        if (numPlayers == players.length) {
            Player[] newPlayers = new Player[players.length + 5];

            for (int i = 0; i < numPlayers; i++) {
                newPlayers[i + 1] = players[i];
            }
            newPlayers[0] = value;
            numPlayers++;

            players = newPlayers;
        } else {
            Player[] newPlayers = new Player[players.length];

            for (int i = 0; i < numPlayers; i++) {
                newPlayers[i + 1] = players[i];
            }
            newPlayers[0] = value;
            numPlayers++;

            players = newPlayers;
        }
    }

    /**
     * (7 marks) Add the given player at the specified 'idx'. This method should
     * check that idx is a valid location. If no space is available, increase the
     * list by 5 additional spaces before adding. If a null value is passed, no
     * change should be made and false should be returned.
     *
     * @param idx   - the location to place 'value'
     * @param value
     * @return true if 'idx' is a valid location, false otherwise
     */
    public boolean add(int idx, Player value) {
        // TODO To be completed
        if (value == null) {
            return false;
        }
        if (idx > players.length || idx < 0) {
            return false;
        }
        if (numPlayers == players.length) {
            Player[] newPlayers = new Player[players.length + 5];

            for (int i = 0; i < numPlayers; i++) {
                if (i < idx)
                    newPlayers[i] = players[i];
                else
                    newPlayers[i + 1] = players[i];
            }

            newPlayers[idx] = value;
            numPlayers++;

            players = newPlayers;
        } else {
            Player[] newPlayers = new Player[players.length];

            for (int i = 0; i < numPlayers; i++) {
                if (i < idx)
                    newPlayers[i] = players[i];
                else
                    newPlayers[i + 1] = players[i];
            }

            newPlayers[idx] = value;
            numPlayers++;

            players = newPlayers;
        }
        return true;
    }

    /**
     * (7 marks)
     *
     * @param name - the player to search for
     * @return the Player object with the passed name. Return null if no Player
     * object has the same name.
     */
    public Player findPlayer(String name) {
        // TODO To be completed

        for (int i = 0; i < numPlayers; i++)
            if (players[i].name.equals(name))
                return players[i];
        return null;
    }

    /**
     * (3 marks) This function should remove any Player objects from 'players' that
     * have a name that contains 'n'. The number of Player objects removed should be
     * returned. This function should not change the size of the 'players' array but
     * numPlayers should be adjusted accordingly.
     *
     * @param n - the player name to search for
     * @return the number of Player objects removed.
     */
    public int removeAllOccurrences(String n) {
        // TODO To be completed

        int removed = 0;
        for (int i = 0; i < numPlayers; i++)
            if (players[i].name.contains(n)) {
                for (int j = i; j < players.length - 1; j++) {
                    players[j] = players[j + 1];
                }
                i--;
                numPlayers--;
                removed++;
            }
        if (removed != 0)
            return removed;
        return -1;
    }

    /**
     * (3 marks) Assume that the 'players' instance variable contains objects that
     * are in ascending order by average score. Given a list 'p' which you can also
     * assume is in ascending order by average score, add all Player objects from
     * 'p' into 'players' while keeping 'players' in ascending order.
     *
     * @param p - the Player objects to merge
     */
    public void mergeAscending(Player[] p) {
        // TODO To be completed
        Player[] newPlayers = new Player[numPlayers + p.length];

        for (int i = 0; i < numPlayers; i++)
            newPlayers[i] = players[i];
        for (int i = numPlayers; i < numPlayers + p.length; i++)
            newPlayers[i] = p[i - numPlayers];

        for (int i = 0; i < numPlayers + p.length; i++) {
            for (int j = i; j < numPlayers + p.length - 1; j++)
                if (newPlayers[j].averageScore() > newPlayers[j + 1].averageScore()) {
                    Player tmp = newPlayers[j + 1];
                    newPlayers[j + 1] = newPlayers[j];
                    newPlayers[j] = tmp;
                }
        }
        players = newPlayers;
        numPlayers += p.length;
    }

    /**
     * (3 marks)
     *
     * @return all players scores flattened into a one dimensional array. The scores
     * should be in the order of player objects in 'players'
     */
    public int[] flatten() {
        // TODO To be completed
        int numScores = 0;

        for (int i = 0; i < numPlayers; i++)
            numScores += players[i].scores.length;

        int[] scores = new int[numScores];
        int idx = 0;

        for (int i = 0; i < numPlayers; i++)
            for (int j = 0; j < players[i].scores.length; j++)
                scores[idx++] = players[i].scores[j];
        return scores;
    }

    /**
     * (3 marks)
     *
     * @return all players scores in a two dimensional array. The first subarray
     * should contain the scores of the first player object in 'players',
     * the second subarray should contain the scores of the second player
     * object in 'players' and so forth. A deep copy of each array should be
     * made.
     */
    public int[][] recreate2D() {
        // TODO To be completed
        int[][] scores = new int[numPlayers][];
        int idx = 0;

        for (int i = 0; i < numPlayers; i++) {
            scores[idx] = new int[players[i].scores.length];

            for (int j = 0; j < players[i].scores.length; j++)
                scores[idx][j] = players[i].scores[j];

            idx++;
        }
        return scores;
    }

    /**
     * DO NOT MODIFY
     */
    public PlayerArrayList() {
        players = new Player[0];
    }

    /**
     * DO NOT MODIFY
     */
    public PlayerArrayList(int n) {
        players = new Player[n];
    }

    /**
     * DO NOT MODIFY
     */
    public PlayerArrayList(PlayerArrayList pL) {
        numPlayers = pL.numPlayers;
        players = new Player[pL.numPlayers];
        for (int i = 0; i < players.length; i++) {
            players[i] = new Player(pL.players[i]);
        }
    }

    /**
     * DO NOT MODIFY
     */
    public PlayerArrayList(Player[] p, int nP) {
        players = p;
        numPlayers = nP;
    }

    /**
     * DO NOT MODIFY
     *
     * @return the current used space in the list
     */
    public int size() {
        return numPlayers;
    }

    /**
     * DO NOT MODIFY Increase the available space in 'data' by the given value
     *
     * @param n - the amount of space to add
     */
    public void grow(int n) {
        Player[] copy = new Player[players.length + n];
        for (int i = 0; i < numPlayers; i++)
            copy[i] = players[i];
        players = copy;
    }

    /**
     * DO NOT MODIFY
     *
     * @return whether the parameter object is an instance copy of the calling object
     */
    public boolean equals(PlayerArrayList other) {
        if (this.numPlayers != other.numPlayers) {
            return false;
        }
        for (int i = 0; i < this.numPlayers; i++) {
            if (!this.players[i].equals(other.players[i])) {
                return false;
            }
        }
        return true;
    }

}
