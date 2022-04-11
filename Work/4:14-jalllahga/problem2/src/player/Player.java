package relay.player;

import relay.map.Map;
import relay.simulator.Message;

public abstract class Player implements Comparable<Player>{
    private double position;
    private double velocity;
    private boolean currentPlayer;
    private double nextPlayerPosition;
    private Eyesight eyesight;
    private Map map;
    private int playerNum;
	private final String playerType;

    public Player(double velocity, Map map, String playerType){
        this(0, velocity, map, playerType);
    }
    public Player(double position, double velocity, Map map, String playerType) {
        this.position = position;
        this.velocity = velocity;
        this.map = map;
        currentPlayer = position == 0;
        this.eyesight = new Eyesight(map);
		this.playerType = playerType;
    }

    public void setNextPlayerPosition(double position) {
        nextPlayerPosition = position;
		eyesight.setNextPlayerPosition(position);
        }

    public int getPlayerNum() {
        return playerNum;
    }

    public void setPlayerNum(int num) {
        playerNum = num;
    }

    abstract public void move();
    abstract public boolean getThrowUp();
    abstract public void hear(Message message);

    public void passBaton(Player nextPlayer){
        //TODO: Problem 2.2
    }

    protected double getMovableDistance(double velocity){
        //TODO: Problem 2.2
    }

    @Override
    public String toString() {
        return toCustomString();
    }
    public abstract String toCustomString();

}
