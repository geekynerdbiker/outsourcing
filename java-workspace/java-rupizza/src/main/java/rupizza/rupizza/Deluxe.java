package rupizza.rupizza;

import java.util.ArrayList;

/**
 * Subclass of Pizza that represents Deluxe Pizza option.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class Deluxe extends Pizza {
    protected static final double BASE_PRICE = 14.99;

    /**
     * Default constructor.
     */
    public Deluxe() {
        this.sauce = Sauce.TOMATO;
        this.size = Size.SMALL;
        this.toppings = createToppings();
    }

    /**
     * Price getter function.
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
        return price;
    }

    /**
     * Topping creator(setter) function.
     *
     * @return list of toppings.
     */
    private ArrayList<Topping> createToppings() {
        ArrayList<Topping> toppings = new ArrayList<Topping>();
        toppings.add(Topping.SAUSAGE);
        toppings.add(Topping.PEPPERONI);
        toppings.add(Topping.GREEN_PEPPER);
        toppings.add(Topping.ONION);
        toppings.add(Topping.MUSHROOM);
        return toppings;
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
     * Override toString() function.
     *
     * @return string containing data.
     */
    @Override
    public String toString() {
        StringBuilder pizza = new StringBuilder("[Deluxe]");
        for (Topping topping : this.toppings) {
            pizza.append(" ").append(topping.toString());
        }
        pizza.append(" ").append(this.sauce.getFlavor());
        pizza.append(" ").append(this.size.getPizzaSize());
        if (this.extraCheese) {
            pizza.append(" extraCheese");
        }
        if (this.extraSauce) {
            pizza.append(" extraSauce");
        }
        pizza.append(" ").append(String.format("%.2f", this.getPrice()));
        return pizza.toString();
    }
}
