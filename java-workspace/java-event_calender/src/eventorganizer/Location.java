package eventorganizer;

/**
 * Location class
 *
 * @author Dongjin Kim
 */
public enum Location {
    ARC103("Allison Road Classroom", "Busch"),
    HLL114("Hill Center", "Busch"),
    AB2225("Academic Building", "College Avenue"),
    MU302("Murray Hall", "College Avenue"),
    BE_AUD("Beck Hall", "Livingston"),
    TIL232("Tillett Hall", "Livingston");

    private final String building;
    private final String campus;

    /**
     * Creates predefined Location objects
     *
     * @param building the building of location
     * @param campus   the campus of location
     */
    Location(String building, String campus) {
        this.building = building;
        this.campus = campus;
    }

    /**
     * Returns a string representation
     *
     * @return string in format (building name, campus name)
     */
    @Override
    public String toString() {
        return this.name() + " (" + this.building + ", " + this.campus + ")";
    }

    /**
     * Compares this location
     *
     * @param l the location to be compared.
     * @return true if same,
     * false if not
     */
    public boolean isEqual(Location l) {
        return this.building.equals(l.building) && this.campus.equals(l.campus);
    }
}

