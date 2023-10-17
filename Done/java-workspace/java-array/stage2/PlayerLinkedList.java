package stage2;

//DO NOT IMPORT ANY ADDITIONAL FILES
//The only import here should be: serviceClasses.PlayerNode

import serviceClasses.PlayerNode;
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
 * If a single loop is used anywhere in this file, you will receive half the
 * marks specified for ALL questions
 * <p>
 * No loops used - 60 marks in total. A single loop used - 30 marks in total
 *
 * @author mic
 */

public class PlayerLinkedList {
    public PlayerNode start;

    /**
     * (10 marks) If null is passed, no changes should be made.
     *
     * @param value - the PlayerNode object to add.
     */
    public void addToFront(PlayerNode value) {
        // TODO To be completed
        if (value == null)
            return;

        if (start == null)
            start = value;
        else {
            value.next = start;
            start = value;
        }
    }

    /**
     * (10 marks) Add the given PlayerNode to the end of the list. If null is
     * passed, no changes should be made.
     *
     * @param value - the PlayerNode object to add
     */
    public void addToEnd(PlayerNode value) {
        // TODO To be completed
        if (value == null)
            return;

        if (start == null)
            start = value;
        else {
            PlayerNode p = start;
            while (p.next != null)
                p = p.next;
            p.next = value;
        }
    }

    /**
     * (10 marks) Add the given PlayerNode at the specified 'idx'. If a null value
     * is passed, no change should be made and false should be returned.
     *
     * @param idx   - the location to place 'value'
     * @param value
     * @return true if 'idx' is a valid location, false otherwise
     */
    public boolean add(int idx, PlayerNode value) {
        // TODO To be completed
        int index = 0;

        if (value == null)
            return false;

        if (idx < 0)
            return false;
        else if (idx == 0) {
            addToFront(value);
        } else if (start == null) {
            if (idx != 0)
                return false;
            else
                addToFront(value);
        } else {
            PlayerNode p = start;
            PlayerNode q = null;

            while (p != null && index < idx) {
                q = p;
                p = p.next;
                index++;
            }
            if (p == null) {
                if (index == idx)
                    addToEnd(value);
                else
                    return false;
            } else {
                value.next = p;
                q.next = value;
            }
        }

        return false;
    }

    /**
     * (10 marks)
     *
     * @param name - the player to search for
     * @return the PlayerNode object with the passed name. Return null if no
     * PlayerNode object has the same name.
     */
    public PlayerNode findPlayer(String name) {
        // TODO To be completed
        if (start == null)
            return null;

        PlayerNode p = start;

        while (p != null) {
            if (p.name.equals(name))
                return p;
            p = p.next;
        }
        return null;
    }

    /**
     * (5 marks) This function should remove any PlayerNode objects from the list
     * that have a name that contains 'n'. The number of PlayerNode objects removed
     * should be returned.
     *
     * @param n - the player name to search for
     * @return the number of PlayerNode objects removed.
     */
    public int removeAllOccurrences(String n) {
        // TODO To be completed
        PlayerNode p = start;
        PlayerNode q = null;

        while (p != null) {
            if (p.name.contains(n)) {
                if (p == start) {
                    start = p.next;
                } else
                    q.next = p.next;
            }
            if (!p.name.contains(n))
                q = p;
            p = p.next;
        }

        return -1;
    }

    /**
     * (2.5 + 2.5 marks) Assume that the PlayerNode instance variable contains nodes that
     * are in ascending order by average score. Given a PlayerNode 'p' which you can
     * also assume is connected to other PlayerNodes in ascending order by average
     * score, add all PlayerNode objects from 'p' into the list while keeping the
     * list in ascending order.
     *
     * @param p - the PlayerNode objects to merge
     */
    public void mergeAscending(PlayerNode p) {
        // TODO To be completed
        PlayerNode pn = start;
        PlayerNode qn = null;

        if (p == null)
            return;
        if (start == null) {
            start = p;
            return;
        } else {
            while (pn.next != null)
                pn = pn.next;
            pn.next = p;
            pn = start;
        }

        boolean swapped;

        do {
            PlayerNode curr = start;
            PlayerNode prev = null;
            PlayerNode next = start.next;
            swapped = false;

            while ( next != null ) {
                if (curr.averageScore() > next.averageScore()) {
                    swapped = true;

                    if ( prev != null ) {
                        PlayerNode tmp = next.next;

                        prev.next = next;
                        next.next = curr;
                        curr.next = tmp;
                    } else {
                        PlayerNode tmp = next.next;

                        start = next;
                        next.next = curr;
                        curr.next = tmp;
                    }

                    prev = next;
                    next = curr.next;
                } else {
                    prev = curr;
                    curr = next;
                    next = next.next;
                }
            }
        } while( swapped );
    }

    /**
     * (5 marks)
     *
     * @return all players scores in the list flattened into a one dimensional
     * array. The scores should be in the order of player objects in the
     * list.
     */
    public int[] flatten() {
        // TODO To be completed
        if (start == null)
            return new int[]{};

        int numScores = 0;

        PlayerNode p = start;
        while (p != null) {
            numScores += p.scores.length;
            p = p.next;
        }

        int[] scores = new int[numScores];
        int idx = 0;

        p = start;
        while (p != null) {
            for (int j = 0; j < p.scores.length; j++)
                scores[idx++] = p.scores[j];
            p = p.next;
        }
        return scores;
    }

    /**
     * (5 marks)
     *
     * @return all players scores in a two dimensional array. The first subarray
     * should contain the scores of the first player object in 'players',
     * the second subarray should contain the scores of the second player
     * object in 'players' and so forth. A deep copy of each array should be
     * made.
     */
    public int[][] recreate2D() {
        // TODO To be completed
        if (start == null)
            return new int[][]{};

        PlayerNode p = start;

        int numPlayers = 0;
        while (p != null) {
            p = p.next;
            numPlayers++;
        }
        int[][] scores = new int[numPlayers][];
        int idx = 0;

        p = start;
        while (p != null) {
            scores[idx] = new int[p.scores.length];

            for (int j = 0; j < p.scores.length; j++)
                scores[idx][j] = p.scores[j];

            p = p.next;
            idx++;
        }
        return scores;
    }

    /**
     * DO NOT MODIFY
     */
    public PlayerLinkedList() {
        start = null;
    }

    /**
     * DO NOT MODIFY
     */
    public PlayerLinkedList(PlayerLinkedList l) {
        if (l.start != null) {
            start = new PlayerNode(l.start, null);
            PlayerNode temp = l.start.next;
            PlayerNode current = start;
            PlayerLinkedListHelper2(temp, current);
        }
    }

    /**
     * DO NOT MODIFY
     */
    public void PlayerLinkedListHelper2(PlayerNode temp, PlayerNode current) {
        if (temp == null)
            return;
        current.next = new PlayerNode(temp, null);
        temp = temp.next;
        current = current.next;
        PlayerLinkedListHelper2(temp, current);
    }

    /**
     * DO NOT MODIFY
     */
    public PlayerLinkedList(PlayerNode[] pN) {
        if (pN != null)
            PlayerLinkedListHelper(pN, 0);
    }

    /**
     * DO NOT MODIFY
     */
    public void PlayerLinkedListHelper(PlayerNode[] pN, int idx) {
        if (idx >= pN.length)
            return;
        addToEnd(pN[idx]);
        PlayerLinkedListHelper(pN, idx + 1);
    }

    /**
     * DO NOT MODIFY
     */
    public boolean equals(PlayerLinkedList pL) {
        PlayerNode temp1 = start;
        PlayerNode temp2 = pL.start;
        return equals(temp1, temp2);
    }

    /**
     * DO NOT MODIFY
     */
    public boolean equals(PlayerNode start1, PlayerNode start2) {
        if (start1 == null || start2 == null)
            return start1 == start2; // True only if both are null

        // Check data in current node
        if (!start1.name.equals(start2.name))
            return false;

        if (start1.scores.length != start2.scores.length)
            return false;

        if (!equals(start1.scores, start2.scores))
            return false;

        return equals(start1.next, start2.next);

    }

    /**
     * DO NOT MODIFY
     */
    public boolean equals(int[] arr1, int[] arr2) {
        if (arr1 == null || arr2 == null)
            return arr1 == arr2;

        if (arr1.length != arr2.length)
            return false;

        return equals(arr1, arr2, 0);
    }

    /**
     * DO NOT MODIFY
     */
    public boolean equals(int[] arr1, int[] arr2, int idx) {
        if (idx >= arr1.length)
            return true;
        if (arr1[idx] != arr2[idx])
            return false;
        else
            return equals(arr1, arr2, idx + 1);
    }

}
