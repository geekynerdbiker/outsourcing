package serviceClasses;

import java.util.Arrays;

public class Player {
    public String name;
    public int[] scores; // Collection of player scores from past games (imagine a game of your choice)

    public Player(String n, int[] s) {
        name = n;
        scores = s;
    }
    
    public Player(Player p) {
        name = p.name;
        scores = new int[p.scores.length];
        for(int i = 0; i < scores.length; i++) {
        	scores[i] = p.scores[i];
        }
    }

    public int totalScore() {
        int total = 0;
        for (int i = 0; i < scores.length; i++)
            total += scores[i];
        return total;
    }
    
    public double averageScore() {
        return (double)totalScore() / scores.length;
    }

    /**
     * @param other
     * @return true if the calling object and parameter object contain the same
     *         values
     */
    public boolean equals(Player other) {
        if (scores.length != other.scores.length)
            return false;

        for (int i = 0; i < scores.length; i++) // Check values in scores
            if (scores[i] != other.scores[i])
                return false;

        // Guaranteed: scores must be the same

        return this.name.equals(other.name);
    }

}
