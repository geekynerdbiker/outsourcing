package rupizza.rupizza;

import javafx.fxml.FXML;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;

import java.util.ArrayList;

/**
 * Controller class for Build Your Own Pizza Menu Window.
 * Allow to make custom pizzas.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class BuildYourOwnController {
    @FXML
    private CheckBox sausage;
    @FXML
    private CheckBox pepperoni;
    @FXML
    private CheckBox beef;
    @FXML
    private CheckBox ham;
    @FXML
    private CheckBox shrimp;
    @FXML
    private CheckBox squid;
    @FXML
    private CheckBox crab_meat;
    @FXML
    private CheckBox green_pepper;
    @FXML
    private CheckBox onion;
    @FXML
    private CheckBox mushroom;
    @FXML
    private CheckBox black_olive;
    @FXML
    private CheckBox pineapple;
    @FXML
    private CheckBox jalapeno;

    private int sauceNumber = -1;
    @FXML
    private RadioButton tomato;
    @FXML
    private RadioButton alfredo;

    private int sizeNumber = -1;
    @FXML
    private RadioButton small;
    @FXML
    private RadioButton medium;
    @FXML
    private RadioButton large;

    private final BuildYourOwn buildYourOwn = new BuildYourOwn();
    @FXML
    private Label buttonError;
    @FXML
    private Label priceBox;
    private ArrayList<Topping> toppings = new ArrayList<>();

    /**
     * Topping setter function.
     */
    @FXML
    protected void selectToppings() {
        if (toppings.size() < 7) {
            sausage.setDisable(false);
            pepperoni.setDisable(false);
            beef.setDisable(false);
            ham.setDisable(false);
            shrimp.setDisable(false);
            squid.setDisable(false);
            crab_meat.setDisable(false);
            green_pepper.setDisable(false);
            onion.setDisable(false);
            mushroom.setDisable(false);
            black_olive.setDisable(false);
            pineapple.setDisable(false);
            jalapeno.setDisable(false);

            if (!alreadySelected(Topping.SAUSAGE) && sausage.isSelected()) {
                toppings.add(Topping.SAUSAGE);
            } else if (alreadySelected(Topping.SAUSAGE) && !sausage.isSelected()) {
                toppings.remove(Topping.SAUSAGE);
            }
            if (!alreadySelected(Topping.PEPPERONI) && pepperoni.isSelected()) {
                toppings.add(Topping.PEPPERONI);
            } else if (alreadySelected(Topping.PEPPERONI) && !pepperoni.isSelected()) {
                toppings.remove(Topping.PEPPERONI);
            }
            if (!alreadySelected(Topping.BEEF) && beef.isSelected()) {
                toppings.add(Topping.BEEF);
            } else if (alreadySelected(Topping.BEEF) && !beef.isSelected()) {
                toppings.remove(Topping.BEEF);
            }
            if (!alreadySelected(Topping.HAM) && ham.isSelected()) {
                toppings.add(Topping.HAM);
            } else if (alreadySelected(Topping.HAM) && !ham.isSelected()) {
                toppings.remove(Topping.HAM);
            }
            if (!alreadySelected(Topping.SHRIMP) && shrimp.isSelected()) {
                toppings.add(Topping.SHRIMP);
            } else if (alreadySelected(Topping.SHRIMP) && !shrimp.isSelected()) {
                toppings.remove(Topping.SHRIMP);
            }
            if (!alreadySelected(Topping.SQUID) && squid.isSelected()) {
                toppings.add(Topping.SQUID);
            } else if (alreadySelected(Topping.SQUID) && !squid.isSelected()) {
                toppings.remove(Topping.SQUID);
            }
            if (!alreadySelected(Topping.CRAB_MEAT) && crab_meat.isSelected()) {
                toppings.add(Topping.CRAB_MEAT);
            } else if (alreadySelected(Topping.CRAB_MEAT) && !crab_meat.isSelected()) {
                toppings.remove(Topping.CRAB_MEAT);
            }
            if (!alreadySelected(Topping.GREEN_PEPPER) && green_pepper.isSelected()) {
                toppings.add(Topping.GREEN_PEPPER);
            } else if (alreadySelected(Topping.GREEN_PEPPER) && !green_pepper.isSelected()) {
                toppings.remove(Topping.GREEN_PEPPER);
            }
            if (!alreadySelected(Topping.ONION) && onion.isSelected()) {
                toppings.add(Topping.ONION);
            } else if (alreadySelected(Topping.ONION) && !onion.isSelected()) {
                toppings.remove(Topping.ONION);
            }
            if (!alreadySelected(Topping.MUSHROOM) && mushroom.isSelected()) {
                toppings.add(Topping.MUSHROOM);
            } else if (alreadySelected(Topping.MUSHROOM) && !mushroom.isSelected()) {
                toppings.remove(Topping.MUSHROOM);
            }
            if (!alreadySelected(Topping.BLACK_OLIVE) && black_olive.isSelected()) {
                toppings.add(Topping.BLACK_OLIVE);
            } else if (alreadySelected(Topping.BLACK_OLIVE) && !black_olive.isSelected()) {
                toppings.remove(Topping.BLACK_OLIVE);
            }
            if (!alreadySelected(Topping.PINEAPPLE) && pineapple.isSelected()) {
                toppings.add(Topping.PINEAPPLE);
            } else if (alreadySelected(Topping.PINEAPPLE) && !pineapple.isSelected()) {
                toppings.remove(Topping.PINEAPPLE);
            }
            if (!alreadySelected(Topping.JALAPENO) && jalapeno.isSelected()) {
                toppings.add(Topping.JALAPENO);
            } else if (alreadySelected(Topping.JALAPENO) && !jalapeno.isSelected()) {
                toppings.remove(Topping.JALAPENO);
            }
        }
        if (toppings.size() >= 7) {
            sausage.setDisable(true);
            pepperoni.setDisable(true);
            beef.setDisable(true);
            ham.setDisable(true);
            shrimp.setDisable(true);
            squid.setDisable(true);
            crab_meat.setDisable(true);
            green_pepper.setDisable(true);
            onion.setDisable(true);
            mushroom.setDisable(true);
            black_olive.setDisable(true);
            pineapple.setDisable(true);
            jalapeno.setDisable(true);
        }
        buildYourOwn.setToppings(toppings);
        priceBox.setText("Price: " + buildYourOwn.getPrice());
    }

    /**
     * Check the parameter topping is already selected.
     * this function for prevent duplication.
     *
     * @param topping
     * @return
     */
    boolean alreadySelected(Topping topping) {
        for (Topping t : toppings)
            if (t == topping)
                return true;
        return false;
    }

    /**
     * Sauce setter function.
     */
    @FXML
    void selectSauce() {
        if (tomato.isSelected()) {
            sauceNumber = 0;
        } else if (alfredo.isSelected()) {
            sauceNumber = 1;
        }
        priceBox.setText("Price: " + buildYourOwn.getPrice());
    }

    /**
     * Size setter function.
     */
    @FXML
    void selectSize() {
        if (small.isSelected()) {
            sizeNumber = 0;
            buildYourOwn.setSize(Size.SMALL);
        } else if (medium.isSelected()) {
            sizeNumber = 1;
            buildYourOwn.setSize(Size.MEDIUM);
        } else if (large.isSelected()) {
            sizeNumber = 2;
            buildYourOwn.setSize(Size.LARGE);
        }
        priceBox.setText("Price: " + buildYourOwn.getPrice());
    }

    /**
     * Clear all topping selections.
     */
    protected void clearAll() {
        toppings = new ArrayList<>();
        sausage.setSelected(false);
        sausage.setSelected(false);
        pepperoni.setSelected(false);
        beef.setSelected(false);
        ham.setSelected(false);
        shrimp.setSelected(false);
        squid.setSelected(false);
        crab_meat.setSelected(false);
        green_pepper.setSelected(false);
        onion.setSelected(false);
        mushroom.setSelected(false);
        black_olive.setSelected(false);
        pineapple.setSelected(false);
        jalapeno.setSelected(false);
        tomato.setSelected(false);
        alfredo.setSelected(false);
        small.setSelected(false);
        medium.setSelected(false);
        large.setSelected(false);

        priceBox.setText("Price:");
    }

    /**
     * Generate new pizza.
     */
    @FXML
    protected void makePizza() {
        if (toppings.size() == 0) {
            buttonError.setText("Topping not selected!");
        } else if (sauceNumber == -1) {
            buttonError.setText("Sauce not selected!");
        } else if (sizeNumber == -1) {
            buttonError.setText("Size not selected!");
        } else {
            buildYourOwn.setToppings(toppings);

            switch (sauceNumber) {
                case 0:
                    buildYourOwn.setSauce(Sauce.TOMATO);
                case 1:
                    buildYourOwn.setSauce(Sauce.ALFREDO);
            }
            switch (sizeNumber) {
                case 0:
                    buildYourOwn.setSize(Size.SMALL);
                case 1:
                    buildYourOwn.setSize(Size.MEDIUM);
                case 2:
                    buildYourOwn.setSize(Size.LARGE);
            }
            buttonError.setText("Pizza was created!");
            Order currentOrder = Store.getInstance().getCurrentOrder();
            currentOrder.addToOrder(buildYourOwn);
        }
        clearAll();
    }
}
