package rupizza.rupizza;

import java.util.ArrayList;

/**
 * Order class for manage order.
 * Allow to make custom pizzas.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class Order {
    protected int orderNumber;
    protected ArrayList<Pizza> orderItems;

    /**
     * Default constructor.
     */
    public Order() {
        this.orderNumber = 1;
        this.orderItems = new ArrayList<>();
    }

    /**
     * Order items getter function.
     *
     * @return list of order items;
     */
    public ArrayList<Pizza> getOrderItems() {
        return this.orderItems;
    }

    /**
     * Add pizza into order item list.
     *
     * @param p pizza to added.
     */
    public void addToOrder(Pizza p) {
        int count = 0;
        for (Pizza item : orderItems) {
            count++;
        }
        orderItems.add(count, p);
    }

    /**
     * Increases order number.
     */
    public void incrementOrder() {
        this.orderNumber++;
    }

    /**
     * Getter list of pizza information.
     *
     * @return list of pizza as string.
     */
    public ArrayList<String> getList() {
        ArrayList<String> view = new ArrayList<String>();
        for (Pizza orderItem : orderItems) {
            view.add(orderItem.toString());
        }
        return view;
    }

    /**
     * Removes the given pizza at index from order.
     *
     * @param index index of pizza to remove.
     */
    public void removeItem(int index) {
        orderItems.remove(index);
    }

    /**
     * Size getter function.
     *
     * @return size of the orderItems arraylist.
     */
    public int getSize() {
        return orderItems.size();
    }


    /**
     * Order number getter function.
     *
     * @return order number.
     */
    public int getOrderNumber() {
        return orderNumber;
    }

    /**
     * Clear all items in order items list.
     */
    public void clearOrder() {
        this.orderItems = new ArrayList<Pizza>();
    }

    /**
     * Calculates total price.
     *
     * @return total order price.
     */
    public double orderPrice() {
        double price = 0;
        for (Pizza orderItem : orderItems) {
            price += orderItem.getPrice();
        }
        return price;
    }
}
