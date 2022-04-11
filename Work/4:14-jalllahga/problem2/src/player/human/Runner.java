package relay.player.human;

import relay.player.Throwable;
import relay.map.Map;
import relay.simulator.Message;

public class Runner extends Human implements Throwable{

    public Runner(Map map){this(0, map);}
    public Runner(double position, Map map) {
        super(position, 2, map);
    }

    @Override
    public void hear(Message message) {
        //TODO: Problem 2.2
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

