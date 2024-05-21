package com.example.myapplication;

/**
 * The Crust enumerated type defines values for different crusts, and associates them with a string representation.
 *
 * @author Trent Demers, Awad Shawl
 */
public enum Crust {
    BROOKLYN("Brooklyn"),
    DEEP_DISH("Deep Dish"),
    HAND_TOSSED("Hand Tossed"),
    PAN("Pan"),
    STUFFED("Stuffed"),
    THIN("Thin");

    private final String stringRepresentation;

    /**
     * Crust() is the implicit constructor for an instance of Crust, which necessitates a string representation.
     * @param stringRepresentation the string representation of the instance of Crust.
     */
    Crust(String stringRepresentation){
        this.stringRepresentation = stringRepresentation;
    }

    /**
     * getStringRepresentation() returns the string representation of this instance of Crust
     * @return the string representation of this instance of Crust
     */
    public String getStringRepresentation(){
        return this.stringRepresentation;
    }

}
