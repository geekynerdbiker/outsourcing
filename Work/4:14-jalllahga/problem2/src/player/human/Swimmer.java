package relay.player.human;

import relay.player.Swimmable;
import relay.map.Map;
import relay.simulator.Message;

public class Swimmer extends Human implements Swimmable {
    private double swimSpeed;

    public Swimmer(Map map){this(0, map);}
    public Swimmer(double position, Map map) {
        super(position,1.5,map);
        this.swimSpeed= 2;
    }

    @Override
    public void hear(Message message) {
        //TODO: Problem 2.2
    }

    @Override
    public void move() {
        //TODO: Problem 2.2
		//Use swim method.
		swim();
    }
    public void swim(){
        //TODO: Problem 2.2
    }

    @Override
    public String toCustomString() {
        //TODO: Problem 2.2
    }

    @Override
    public boolean getThrowUp(){return false;}

}
