package com.dcu.monitoring.domain.test;

import lombok.Data;



@Data
public class JSONData {
    private String robotId;
    private int state;
    private Pair startPoint;
    private Pair currentPoint;
    private Pair nextPoint;
    private Pair targetPoint;

    public JSONData(String robotId, int state, Pair startPoint, Pair currentPoint, Pair nextPoint, Pair targetPoint) {
        this.robotId = robotId;
        this.state = state;
        this.startPoint = startPoint;
        this.currentPoint = currentPoint;
        this.nextPoint = nextPoint;
        this.targetPoint = targetPoint;
    }

    public String getRobotId() {
        return robotId;
    }

    public int getState() {
        return state;
    }

    public Pair getCurrentPoint() {
        return currentPoint;
    }

    public Pair getNextPoint() {
        return nextPoint;
    }

    public Pair getStartPoint() {
        return startPoint;
    }

    public Pair getTargetPoint() {
        return targetPoint;
    }

}
