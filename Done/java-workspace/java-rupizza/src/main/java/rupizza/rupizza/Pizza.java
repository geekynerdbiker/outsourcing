package rupizza.rupizza;

import java.util.ArrayList;

/**
 * Abstract class based class for pizza types.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public abstract class Pizza {
    protected static final double ADD_MEDIUM = 2.00;
    protected static final double ADD_LARGE = 4.00;
    protected static final double EXTRA_SAUCE = 1.0;
    protected static final double EXTRA_CHEESE = 1.0;

    protected ArrayList<Topping> toppings;
    protected Size size;
    protected Sauce sauce;
    protected boolean extraSauce;
    protected boolean extraCheese;

    public abstract double getPrice();

    public abstract void setSauce(Sauce sauce);

    public abstract void setSize(Size size);

    public abstract void setExtraSauce(boolean extraSauce);

    public abstract void setExtraCheese(boolean extraCheese);

    public abstract String toString();

}
