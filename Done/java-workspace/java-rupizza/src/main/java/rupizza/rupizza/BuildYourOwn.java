package rupizza.rupizza;

import java.util.ArrayList;

/**
 * Subclass of Pizza that represents Build Your Own Pizza option.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class BuildYourOwn extends Pizza {
    protected static final double BASE_PRICE = 8.99;
    protected static final double ADD_TOPPING = 1.49;
    private ArrayList<Topping> toppings = new ArrayList<>();

    /**
     * Default constructor.
     */
    public BuildYourOwn() {
        this.sauce = Sauce.TOMATO;
        this.size = Size.SMALL;
    }

    /**
     * Calculate the price.
     *
     * @return price.
     */
    @Override
    public double getPrice() {
        double price = BASE_PRICE;
        if (this.size == Size.MEDIUM)
            price += ADD_MEDIUM;
        else if (this.size == Size.LARGE)
            price += ADD_LARGE;
        if (this.extraCheese)
            price += EXTRA_CHEESE;
        if (this.extraSauce)
            price += EXTRA_SAUCE;
        if (toppings.size() > 3)
            price += (toppings.size() - 3) * ADD_TOPPING;
        return price;
    }

    /**
     * Sauce setter function.
     *
     * @param sauce sauce of pizza.
     */
    @Override
    public void setSauce(Sauce sauce) {
        this.sauce = sauce;
    }

    /**
     * Size setter function.
     *
     * @param size size of the pizza.
     */
    @Override
    public void setSize(Size size) {
        this.size = size;
    }

    /**
     * Extra sauce selection setter function.
     *
     * @param extraSauce whether there is extra sauce or not.
     */
    @Override
    public void setExtraSauce(boolean extraSauce) {
        this.extraSauce = extraSauce;
    }

    /**
     * Extra cheese selection setter function.
     *
     * @param extraCheese whether there is extra cheese or not.
     */
    @Override
    public void setExtraCheese(boolean extraCheese) {
        this.extraCheese = extraCheese;
    }

    /**
     * Topping setter function.
     *
     * @param toppings topping list of custom pizza.
     */
    public void setToppings(ArrayList<Topping> toppings) {
        this.toppings = toppings;
    }

    /**
     * Override toString() function.
     *
     * @return string containing data.
     */
    @Override
    public String toString() {
        StringBuilder pizza = new StringBuilder("[Custom]");
        for (Topping topping : this.toppings) {
            pizza.append(" ").append(topping.toString());
        }
        pizza.append(" ").append(this.sauce.getFlavor());
        pizza.append(" ").append(this.size.getPizzaSize());
        pizza.append(" ").append(String.format("%.2f", this.getPrice()));
        return pizza.toString();
    }
}
