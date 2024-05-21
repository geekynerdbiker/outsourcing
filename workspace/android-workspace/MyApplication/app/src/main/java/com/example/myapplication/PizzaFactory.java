package com.example.myapplication;

/**
 * The PizzaFactory interface declares the methods to be used to create instances of Pizza.
 *
 * @author Trent Demers, Awad Shawl
 */
public interface PizzaFactory {

    /**
     * createDeluxe() is the method to be used to create an instance of Deluxe.
     * @return an instance of Deluxe.
     */
    Pizza createDeluxe();

    /**
     * createMeatzza() is the method to be used to create an instance of Meatzza.
     * @return an instance of Meatzza.
     */
    Pizza createMeatzza();

    /**
     * createBBQChicken() is the method to be used to create an instance of BBQChicken.
     * @return an instance of BBQChicken.
     */
    Pizza createBBQChicken();

    /**
     * createBuildYourOwn() is the method to be used to create an instance of BuildYourOwn.
     * @return an instance of BuildYourOwn.
     */
    Pizza createBuildYourOwn();
}

