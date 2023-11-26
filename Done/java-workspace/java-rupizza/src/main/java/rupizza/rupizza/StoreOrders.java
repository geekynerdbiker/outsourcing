package rupizza.rupizza;

import java.util.ArrayList;

/**
 * StoreOrders class for the entire order history.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class StoreOrders {
    private final ArrayList<Order> orderList;
    private int nextOrder;

    /**
     * Default Constructor
     */
    public StoreOrders() {
        this.orderList = new ArrayList<Order>();
        this.nextOrder = 1;
    }

    /**
     * Add an order to order list.
     *
     * @param o order to add.
     */
    public void addOrder(Order o) {
        orderList.add(o);
    }

    /**
     * Next order getter function.
     *
     * @return the number of the next order.
     */
    public int getNextOrder() {
        this.nextOrder = this.orderList.size();
        return this.nextOrder;
    }

    /**
     * Total number of orders getter function.
     *
     * @return size of the order list.
     */
    public int getNumOrders() {
        return this.orderList.size();
    }

    /**
     * Order of specific index getter function.
     *
     * @param index index of the order.
     * @return order.
     */
    public Order getOrder(int index) {
        return this.orderList.get(index);
    }

    /**
     * Total order list getter function.
     * @return order list.
     */

    public ArrayList<Order> getOrderList() {
        return this.orderList;
    }
}