package rupizza.rupizza;

/**
 * Singleton class  to share data between controllers.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class Store {
    private static final Store instance = new Store();
    private Order currentOrder;
    private final StoreOrders orderHistory;

    /**
     * Default Constructor
     */
    private Store() {
        currentOrder = new Order();
        orderHistory = new StoreOrders();
    }

    /**
     * Instance getter function.
     *
     * @return instance of Store;
     */
    public static Store getInstance() {
        return instance;
    }

    /**
     * Current order getter function.
     *
     * @return current order.
     */
    public Order getCurrentOrder() {
        return currentOrder;
    }

    /**
     * Set next order to be added to the order history.
     */
    public void setNextOrder() {
        Order placeholder = new Order();
        placeholder.incrementOrder();
        this.orderHistory.addOrder(placeholder);
        this.currentOrder = placeholder;
    }

    /**
     * Return full history of orders.
     *
     * @return store orders of current store.
     */
    public StoreOrders getOrderHistory() {
        return orderHistory;
    }
}