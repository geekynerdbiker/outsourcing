package relay.simulator;

import relay.player.Player;
import relay.map.Map;

public class Message {
    private Player currentHuman;
    private Player currentAnimal;
    private Map map;
    private int time;


    public Message(Player human, Player animal, Map map, int time){
        this.currentHuman = human;
        this.currentAnimal = animal;
        this.map = map;
        this.time = time;
    }

    public double getDistance(){
    //TODO: Problem 2.1
    }

    @Override
    public String toString(){
    //TODO: Problem 2.1
}
