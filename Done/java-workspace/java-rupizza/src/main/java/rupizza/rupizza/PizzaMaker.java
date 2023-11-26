package rupizza.rupizza;

/**
 * Pizza maker class.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class PizzaMaker {
    /**
     * Create appropriate pizza class and return object.
     *
     * @param pizzaType String of pizza type.
     * @return pizza class.
     */
    public static Pizza createPizza(String pizzaType) {
        return switch (pizzaType.toLowerCase()) {
            case "deluxe" -> new Deluxe();
            case "supreme" -> new Supreme();
            case "meatzza" -> new Meatzza();
            case "seafood" -> new Seafood();
            case "pepperoni" -> new Pepperoni();
            case "byo" -> new BuildYourOwn();
            default -> null;
        };
    }
}