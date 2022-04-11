package relay.player;

import relay.map.Map;

public class Eyesight {
    private static final double range = 3;
    private double nextPlayerPosition;	
    private Map map;

    public Eyesight(Map map){
            this.map = map;
        }
	public void setNextPlayerPosition(double position){
        nextPlayerPosition=position;
    }
    public double getRange(){return range;}

    public double getDistanceToBoundary(double playerPosition){
        //TODO: Problem 2.1
    }
    public double getDistanceToNextPlayer(double playerPosition){
        //TODO: Problem 2.1
    }

}
