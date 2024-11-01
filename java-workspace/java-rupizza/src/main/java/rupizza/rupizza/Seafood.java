package rupizza.rupizza;

import java.util.ArrayList;

/**
 * Subclass of Pizza that represents Seafood Pizza option.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class Seafood extends Pizza {
    protected static final double BASE_PRICE = 17.99;

    public Seafood() {
        this.sauce = Sauce.ALFREDO;
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
        toppings.add(Topping.SHRIMP);
        toppings.add(Topping.SQUID);
        toppings.add(Topping.CRAB_MEAT);
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
        StringBuilder pizza = new StringBuilder("[Seafood]");
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
