package com.example.myapplication;

/**
 * The Size enumerated type defines values for different sizes, and associates them with a string representation.
 *
 * @author Trent Demers, Awad Shawl
 */
public enum Size {
    SMALL("Small"),
    MEDIUM("Medium"),
    LARGE("Large");

    private final String stringRepresentation;

    /**
     * Size() is the implicit constructor for an instance of Size, which necessitates a string representation.
     * @param stringRepresentation the string representation of the instance of Size.
     */
    Size(String stringRepresentation){
        this.stringRepresentation = stringRepresentation;
    }

    /**
     * getStringRepresentation() returns the string representation of this instance of Size.
     * @return the string representation of this instance of Size.
     */
    public String getStringRepresentation(){
        return this.stringRepresentation;
    }
}
