
package models;

import java.io.Serializable;


public class Item implements Serializable {
    private int item_id;
    private Category category;
    private String item_name;
    private double price;
    private User user;

    public Item(int item_id, Category category, String item_name, double price, User user) {
        this.item_id = item_id;
        this.category = category;
        this.item_name = item_name;
        this.price = price;
        this.user = user;
    }

    public void setItem_id(int item_id) {
        this.item_id = item_id;
    }

    public int getItem_id() {
        return item_id;
    }

    public void setCategory(Category category) {
        this.category = category;
    }

    public Category getCategory() {
        return category;
    }

    public void setItem_name(String item_name) {
        this.item_name = item_name;
    }

    public String getItem_name() {
        return item_name;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public double getPrice() {
        return price;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public User getUser() {
        return user;
    }
}
