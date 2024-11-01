//package rupizza.rupizza;
//
//import org.testng.annotations.Test;
//
//import java.util.ArrayList;
//
//import static org.junit.jupiter.api.Assertions.*;
//
//class BuildYourOwnTest {Ï
//
//    @Test
//    void getPrice1() {
//        BuildYourOwn byo = new BuildYourOwn();
//
//        ArrayList<Topping> toppings = new ArrayList<>();
//        toppings.add(Topping.HAM);
//        toppings.add(Topping.PINEAPPLE);
//        toppings.add(Topping.BEEF);
//        byo.setToppings(toppings);
//
//        assertEquals(byo.getPrice(), 8.99);
//    }
//
//    @Test
//    void getPrice2() {
//        BuildYourOwn byo = new BuildYourOwn();
//        byo.setSize(Size.LARGE);
//
//        ArrayList<Topping> toppings = new ArrayList<>();
//        toppings.add(Topping.HAM);
//        toppings.add(Topping.PINEAPPLE);
//        toppings.add(Topping.BEEF);
//        byo.setToppings(toppings);
//
//        assertEquals(byo.getPrice(), 12.99);
//    }
//
//    @Test
//    void getPrice3() {
//        BuildYourOwn byo = new BuildYourOwn();
//        byo.setSize(Size.SMALL);
//        byo.setSauce(Sauce.ALFREDO);
//
//        ArrayList<Topping> toppings = new ArrayList<>();
//        toppings.add(Topping.HAM);
//        toppings.add(Topping.PINEAPPLE);
//        toppings.add(Topping.BEEF);
//        byo.setToppings(toppings);
//
//        assertEquals(byo.getPrice(), 8.99);
//    }
//
//    @Test
//    void getPrice4() {
//        BuildYourOwn byo = new BuildYourOwn();
//        byo.setSize(Size.LARGE);
//        byo.setSauce(Sauce.ALFREDO);
//
//        ArrayList<Topping> toppings = new ArrayList<>();
//        toppings.add(Topping.HAM);
//        toppings.add(Topping.PINEAPPLE);
//        toppings.add(Topping.BEEF);
//        toppings.add(Topping.SAUSAGE);
//        byo.setToppings(toppings);
//
//        assertEquals(byo.getPrice(), 14.48);
//    }
//
//    @Test
//    void getPrice5() {
//        BuildYourOwn byo = new BuildYourOwn();
//        byo.setSize(Size.LARGE);
//
//        ArrayList<Topping> toppings = new ArrayList<>();
//        toppings.add(Topping.HAM);
//        toppings.add(Topping.PINEAPPLE);
//        toppings.add(Topping.BEEF);
//        toppings.add(Topping.SAUSAGE);
//        toppings.add(Topping.ONION);
//        toppings.add(Topping.MUSHROOM);
//        byo.setToppings(toppings);
//
//        assertEquals(byo.getPrice(), 17.46);
//    }
//}