package rupizza.rupizza;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;

import static rupizza.rupizza.PizzaMaker.createPizza;

/**
 * Controller class for Specialty Pizza Menu Window.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class SpecialtyController {
    @FXML
    private ListView<Topping> specialtyToppings;
    @FXML
    private ComboBox<String> specialtySelection;
    @FXML
    private ComboBox<String> sizeSelection;
    @FXML
    private Label priceBox;
    @FXML
    private Label errorMessage;
    @FXML
    private Label buttonError;
    @FXML
    private CheckBox sauceSetter;
    @FXML
    private CheckBox cheeseSetter;

    /**
     * Initializer function.
     */
    @FXML
    public void initialize() {
        specialtySelection.setItems(FXCollections.observableArrayList(
                "Deluxe", "Supreme", "Meatzza", "Pepperoni", "Seafood"
        ));
        sizeSelection.setItems(FXCollections.observableArrayList(
                "Small", "Medium", "Large"
        ));
        specialtyToppings.setItems(FXCollections.observableArrayList());
        pickerFunction();
        sizeFunction();

    }

    @FXML
    protected void pickerFunction() {
        specialtySelection.valueProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                ObservableList<Topping> toppingList = switch (newValue) {
                    case "Deluxe" -> createToppingList("Deluxe");
                    case "Supreme" -> createToppingList("Supreme");
                    case "Meatzza" -> createToppingList("Meatzza");
                    case "Pepperoni" -> createToppingList("Pepperoni");
                    case "Seafood" -> createToppingList("Seafood");
                    default -> throw new IllegalStateException();
                };
                specialtyToppings.setItems(toppingList);
                Pizza pizza = createPizza(newValue.toLowerCase());
                sizeSelection.getSelectionModel().clearSelection();
                priceBox.setText("Price: " + pizza.getPrice());
                errorMessage.setText("");
            }
        });
    }

    @FXML
    protected void sizeFunction() {
        sizeSelection.valueProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                String pizzaType = specialtySelection.getSelectionModel().getSelectedItem();
                if (pizzaType != null) {
                    Pizza pizza = createPizza(pizzaType);
                    assert pizza != null;
                    pizza.setSize(Size.valueOf(newValue.toUpperCase()));
                    Double price = pizza.getPrice();
                    priceBox.setText("Price: " + String.format("%.2f", price));
                } else {
                    errorMessage.setText("Select type first.");
                }
            }
        });
    }

    @FXML
    protected void extra() {
        String pizzaType = specialtySelection.getSelectionModel().getSelectedItem();
        if (pizzaType != null) {
            Pizza pizza = createPizza(pizzaType);
            assert pizza != null;
            pizza.setSize(Size.valueOf(sizeSelection.getSelectionModel().getSelectedItem().toUpperCase()));
            if (sauceSetter.isSelected())
                pizza.setExtraSauce(true);
            if (cheeseSetter.isSelected())
                pizza.setExtraCheese(true);
            Double price = pizza.getPrice();
            priceBox.setText("Price: " + String.format("%.2f", price));
        } else {
            errorMessage.setText("Select type first.");
        }
    }

    @FXML
    protected void makePizza() {
        if (specialtySelection.getSelectionModel().getSelectedItem() != null) {
            Pizza pizza = createPizza(specialtySelection.getSelectionModel().getSelectedItem());

            if (sizeSelection.getSelectionModel().getSelectedItem() != null) {
                String size = sizeSelection.getSelectionModel().getSelectedItem();
                if (pizza == null) {
                    buttonError.setText("Select pizza type");
                    return;
                }
                pizza.setSize(Size.valueOf(size.toUpperCase()));
                if (sauceSetter.isSelected()) {
                    pizza.setExtraSauce(true);
                }
                if (cheeseSetter.isSelected()) {
                    pizza.setExtraCheese(true);
                }
                buttonError.setText("Pizza was created!");
                clearAll();
                Order currentOrder = Store.getInstance().getCurrentOrder();
                currentOrder.addToOrder(pizza);
            } else {
                buttonError.setText("Size not selected!");
            }
        } else {
            buttonError.setText("Please select a pizza type!");
        }
    }

    @FXML
    protected void clearAll() {
        specialtyToppings.setItems(FXCollections.observableArrayList());
        specialtySelection.getSelectionModel().clearSelection();
        sizeSelection.getSelectionModel().clearSelection();
        cheeseSetter.setSelected(false);
        sauceSetter.setSelected(false);
        priceBox.setText("Price:");
    }

    protected ObservableList<Topping> createToppingList(String type) {
        if (type.equals("Supreme")) {
            return FXCollections.observableArrayList(
                    Topping.SAUSAGE, Topping.PEPPERONI, Topping.GREEN_PEPPER, Topping.ONION, Topping.MUSHROOM);
        }
        if (type.equals("Deluxe")) {
            return FXCollections.observableArrayList(
                    Topping.SAUSAGE, Topping.PEPPERONI, Topping.HAM,
                    Topping.GREEN_PEPPER, Topping.ONION, Topping.BLACK_OLIVE, Topping.MUSHROOM);
        }
        if (type.equals("Meatzza")) {
            return FXCollections.observableArrayList(
                    Topping.SAUSAGE, Topping.PEPPERONI, Topping.BEEF, Topping.HAM);
        }
        if (type.equals("Pepperoni")) {
            return FXCollections.observableArrayList(Topping.PEPPERONI);
        } else {
            return FXCollections.observableArrayList(
                    Topping.SHRIMP, Topping.SQUID, Topping.CRAB_MEAT);
        }
    }
}
