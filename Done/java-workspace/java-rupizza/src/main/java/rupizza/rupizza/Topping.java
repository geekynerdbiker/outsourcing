package rupizza.rupizza;

/**
 * Enum class for pizza toppings.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public enum Topping {
    SAUSAGE("Sausage"),
    PEPPERONI("Pepperoni"),
    BEEF("Beef"),
    HAM("Ham"),
    SHRIMP("Shrimp"),
    SQUID("Squid"),
    CRAB_MEAT("Crab Meat"),
    GREEN_PEPPER("Green Pepper"),
    ONION("Onion"),
    MUSHROOM("Mushroom"),
    BLACK_OLIVE("Black Olive"),
    PINEAPPLE("Pineapple"),
    JALAPENO("Jalapeno");

    private final String toppingName;

    /**
     * Constructor for the enum class.
     *
     * @param toppingName name of the topping.
     */
    Topping(String toppingName) {
        this.toppingName = toppingName;
    }

    /**
     * Topping name getter function.
     *
     * @return name of the topping.
     */
    public String getToppingName() {
        return this.toppingName;
    }

    /**
     * Override toString() function.
     *
     * @return string containing data.
     */
    @Override
    public String toString() {
        return this.getToppingName();
    }
}
