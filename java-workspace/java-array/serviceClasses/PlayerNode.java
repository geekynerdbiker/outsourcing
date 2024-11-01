package serviceClasses;

public class PlayerNode {
    public String name;
    public int[] scores; //Collection of player scores from past games (imagine a game of your choice)
    public PlayerNode next;
    
    public PlayerNode(String n, int[] s, PlayerNode nxt) {
        name = n;
        scores = s;
        next = nxt;
    }
    
    public PlayerNode(String n, int[] s) {
        name = n;
        scores = s;
        next = null;
    }
    
    public PlayerNode(PlayerNode pN, PlayerNode nxt) {
        name = pN.name;
        scores = new int[pN.scores.length];
        for(int i = 0; i < scores.length; i++) {
        	scores[i] = pN.scores[i];
        }
        next = nxt;
    }
    
    public int totalScore() {
        int total = 0;
        for(int i = 0; i < scores.length; i++)
            total += scores[i];
        return total;
    }
    
    public double averageScore() {
        return totalScore()/scores.length;
    }
}
