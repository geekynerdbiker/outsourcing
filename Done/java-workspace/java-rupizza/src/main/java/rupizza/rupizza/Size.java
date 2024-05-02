package rupizza.rupizza;

/**
 * Enum class for sizes.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public enum Size {
    SMALL("Small"), MEDIUM("Medium"), LARGE("Large");

    private final String pizzaSize;

    /**
     * Constructor for the enum class.
     *
     * @param pizzaSize size of the pizza.
     */
    Size(String pizzaSize) {
        this.pizzaSize = pizzaSize;
    }

    /**
     * Getter method for pizza size.
     *
     * @return size of pizza.
     */
    public String getPizzaSize() {
        return this.pizzaSize;
    }
}
