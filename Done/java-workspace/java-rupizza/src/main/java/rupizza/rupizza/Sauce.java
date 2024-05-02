package rupizza.rupizza;

/**
 * Enum class for sauces.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public enum Sauce {
    ALFREDO("ALFREDO"),
    TOMATO("TOMATO");

    private final String flavor;

    /**
     * Constructor for the pizza's sauce.
     *
     * @param flavor flavor of the sauce.
     */
    Sauce(String flavor) {
        this.flavor = flavor;
    }

    /**
     * Getter method for the flavor of the sauce.
     *
     * @return flavor of the sauce.
     */
    public String getFlavor() {
        return this.flavor;
    }

}
