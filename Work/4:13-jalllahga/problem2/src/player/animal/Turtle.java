package relay.player.animal;

import relay.player.Swimmable;
import relay.map.Map;

public class Turtle extends Animal implements Swimmable {
    private double swimSpeed;

    public Turtle(Map map){this(0, map);}
    public Turtle(double position, Map map) {
        super(position,1,map);
        this.swimSpeed= 2.5;
    }

    @Override
    public void move() {
        //TODO: Problem 2.2 
		//Use swim method
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
