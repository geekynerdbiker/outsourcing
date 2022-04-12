package relay.player.animal;

import relay.player.Throwable;
import relay.map.Map;

public class Rabbit extends Animal implements Throwable {

    public Rabbit(Map map){this(0, map);}
    public Rabbit(double position, Map map) {
        super(position,3,map);
    }

    @Override
    public void move() {
        //TODO: Problem 2.2
    }

    @Override
    public String toCustomString() {
        //TODO: Problem 2.2
    }

    public boolean throwUp(double position, Map map){
        //TODO: Problem 2.2
    }
    @Override
    public boolean getThrowUp(){
        //TODO: Problem 2.2
    }

}
