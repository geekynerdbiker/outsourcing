package relay.simulator;

import relay.player.Player;
import relay.map.Map;
import java.util.ArrayList;

public class Simulator {
    final static int maxTeamPlayerNum=4;
    private final ArrayList<Player> humanPlayers;
    private final ArrayList<Player> animalPlayers;
    private final Map map;
    private boolean raceFinish = false; // For testbench
    public String[] raceLogForEval = new String[200]; // For evaluation, don't remove

    private Player currentHuman;
    private Player currentAnimal;

    public Simulator(ArrayList<Player> humanPlayers, ArrayList<Player> animalPlayers, Map map){
        //TODO: Problem 2.3
	    //for ascending order of position
        java.util.Collections.sort(humanPlayers);
        java.util.Collections.sort(animalPlayers);	
    }


    public void snapshot() {
        //TODO: Problem 2.3
    }


    public Message talk(int time) {
        Message msg = new Message(currentHuman, currentAnimal, map, time);
        raceLogForEval[time]=msg.toString();
        return msg;
    }

    public boolean getRaceFinish(){return raceFinish;}


     public void simulate() {
        //TODO: Problem 2.3
    }
}
