#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>


#ifndef main_h
#define main_h

using namespace std;

enum Gender {
    Male = 0,
    Female = 1
};

class Product{
private:
    int pid;
    string name;
    int amount;
    double price;
    
public:
    Product() {}
    
    // setter
    void set_pid(int pid) { this->pid = pid; }
    void set_name(string name) { this->name = name; }
    void set_amount(int amount) { this->amount = amount; }
    void set_price(double price) { this->price = price; }
    
    // getter
    int get_pid() { return pid; }
    string get_name() { return name; }
    int get_amount() { return amount; }
    double get_price() { return price; }
};

class Person{
private:
    string name;
    int gender;
    string number;
    string address;
    
public:
    // setter
    void set_name(string name) { this->name = name; }
    void set_gender(int gender) { this->gender = gender; }
    void set_number(string number) { this->number = number; }
    void set_address(string address) { this->address = address; }
    
    // getter
    string get_name() { return name; }
    int get_gender() { return gender; }
    string get_number() { return number; }
    string get_address() { return address; }
};

class Customer : public Person {
private:
    int cid;
    double capital = 10000;
    vector< Product > cart;
    
    
public:
    Customer() {}
    
    // print menu for customer
    void print_menu() {
        cout << "******************************" << endl;
        cout << "* 1: add products into cart  *" << endl;
        cout << "* 2: query products in cart  *" << endl;
        cout << "* 3: check up                *" << endl;
        cout << "* 4: move to parent menu     *" << endl;
        cout << "******************************" << endl;
    }
    
    // get input for menu of customer, return input
    int get_menu() {
        int menu;
        cout << "Please input a number to run the program: ";
        cin >> menu;
        
        return menu;
    }
    
    // setter
    void set_cid(int cid) { this->cid = cid; }
    
    // getter
    int get_cid() { return cid; }
    double get_capital() { return capital; }
    
    // push product into cart vector
    void add_into_cart(Product p) {
        cart.push_back(p);
    }
    
    // print specific product information in cart
    void query_product(int pid) {
        bool found = false;
        cout.precision(2);
        cout << right << setw(20) << fixed << "Procudt ID " << right << setw(20) << fixed << "Name" << right << setw(20) << fixed << "Amount" << right << setw(20) << fixed << "Price" << endl;
        for (int i = 0; i < cart.size(); i++) {
            if (pid == cart[i].get_pid()) {
                found = true;
                cout << right << setw(20) << fixed << cart[i].get_pid() << right << setw(20) << fixed << cart[i].get_name()  << right << setw(20) << fixed << cart[i].get_amount()
                << right << setw(20) << fixed << cart[i].get_price() << endl;
            }
        }
        
        if (!found)
            cout << right << setw(20) << fixed << "No product found!" << endl;
    }
    
    // print all products' information in cart
    void query_product_all() {
        bool found = false;
        cout.precision(2);
        cout << right << setw(20) << fixed << "Procudt ID " << right << setw(20) << fixed << "Name" << right << setw(20) << fixed << "Amount" << right << setw(20) << fixed << "Price" << endl;
        for (int i = 0; i < cart.size(); i++) {
            found = true;
            cout << right << setw(20) << fixed << cart[i].get_pid() << right << setw(20) << fixed << cart[i].get_name()  << right << setw(20) << fixed << cart[i].get_amount()
            << right << setw(20) << fixed << cart[i].get_price() << endl;
            
        }
        
        if (!found)
            cout << right << setw(20) << fixed << "No product found!" << endl;
    }
    
    // print bill and return total that sum of subtotal
    double check_up() {
        double total = 0;
        bool found = false;
        cout.precision(2);
        cout << right << setw(20) << fixed << "Procudt ID " << right << setw(20) << fixed << "Name" << right << setw(20) << fixed << "Amount" << right << setw(20) << fixed << "Price" << right << setw(20) << fixed << "Subtotal" << endl;
        for (int i = 0; i < cart.size(); i++) {
            found = true;
            cout << right << setw(20) << fixed << cart[i].get_pid() << right << setw(20) << fixed << cart[i].get_name()  << right << setw(20) << fixed << cart[i].get_amount()
            << right << setw(20) << fixed << cart[i].get_price() << right << setw(20) << fixed << cart[i].get_price() * cart[i].get_amount() << endl;
            total += cart[i].get_price() * cart[i].get_amount();
        }
        
        if (!found)
            cout << right << setw(20) << fixed << "No product found!" << endl;
        else {
            cout << "Total price: " << total << endl;
            cout << "Customer ID " << this->cid << "\t\tCustomer Name" << this->get_name() << "\t\tCapital :" << this->capital << endl;
        }
        return total;
    }
    
    // deduct customer's capital
    void deduct_capital(double capital) {
        this->capital -= capital;
    }
};

class Manager : public Person {
private:
    int age;
    string title;
    
public:
    Manager() {}
    
    // print menu for manager
    void print_menu() {
        cout << "******************************" << endl;
        cout << "* 1: add products            *" << endl;
        cout << "* 2: query products          *" << endl;
        cout << "* 3: add customers           *" << endl;
        cout << "* 4: query customers         *" << endl;
        cout << "* 5: move to parent menu     *" << endl;
        cout << "******************************" << endl;
    }
    
    // get input for menu of manager, return input
    int get_menu() {
        int menu;
        cout << "Please input a number to run the program: ";
        cin >> menu;
        
        return menu;
    }
};

class MainProcess : Person {
private:
    vector< Product > products;
    vector< Customer > customers;
    
public:
    Customer c;
    Manager m;
    
    MainProcess() {}
    
    // print menu
    void print_menu() {
        cout << "*************************" << endl;
        cout << "* 1: manager            *" << endl;
        cout << "* 2: customer           *" << endl;
        cout << "* 3: quit the program   *" << endl;
        cout << "*************************" << endl;
    }
    
    // get input for menu of role, return input
    int get_role() {
        int role;
        cout << "Please input a member to set your role: ";
        cin >> role;
        
        return role;
    }
    
    // add product into products vector (manager)
    void add_product(Product p) {
        products.push_back(p);
    }
    
    // print specific product information (manager)
    void query_product(int pid) {
        bool found = false;
        cout.precision(2);
        cout << right << setw(20) << fixed << "Procudt ID " << right << setw(20) << fixed << "Name" << right << setw(20) << fixed << "Amount" << right << setw(20) << fixed << "Price" << endl;
        for (int i = 0; i < products.size(); i++) {
            if (pid == products[i].get_pid()) {
                found = true;
                cout << right << setw(20) << fixed << products[i].get_pid() << right << setw(20) << fixed << products[i].get_name()  << right << setw(20) << fixed << products[i].get_amount()
                << right << setw(20) << fixed << products[i].get_price() << endl;
            }
        }
        
        if (!found)
            cout << right << setw(20) << fixed << "No product found!" << endl;
    }
    
    // print all products' information (manager)
    void query_product_all() {
        bool found = false;
        cout.precision(2);
        cout << right << setw(20) << fixed << "Procudt ID " << right << setw(20) << fixed << "Name" << right << setw(20) << fixed << "Amount" << right << setw(20) << fixed << "Price" << endl;
        for (int i = 0; i < products.size(); i++) {
            found = true;
            cout << right << setw(20) << fixed << products[i].get_pid() << right << setw(20) << fixed << products[i].get_name()  << right << setw(20) << fixed << products[i].get_amount()
            << right << setw(20) << fixed << products[i].get_price() << endl;
            
        }
        
        if (!found)
            cout << right << setw(20) << fixed << "No product found!" << endl;
    }
    
    // add customer into customers vector (manager)
    void add_customer(Customer c) {
        customers.push_back(c);
    }
    
    // print specific customer information (manager)
    void query_customer(int pid) {
        bool found = false;
        cout.precision(2);
        cout << right << setw(20) << fixed << "Customer ID " << right << setw(20) << fixed << "Name" << right << setw(20) << fixed << "Gender" << right << setw(20) << fixed << "Mobile Number" << right << setw(20) << fixed << "Capital" << right << setw(20) << fixed << "address" << endl;
        for (int i = 0; i < customers.size(); i++) {
            if (pid == customers[i].get_cid()) {
                found = true;
                cout << right << setw(20) << fixed << customers[i].get_cid() << right << setw(20) << fixed << customers[i].get_name() << right << setw(20) << fixed << customers[i].get_gender() << right << setw(20) << fixed << customers[i].get_number() << right << setw(20) << fixed << customers[i].get_capital() << right << setw(20) << fixed << customers[i].get_address() << endl;
            }
        }
        
        if (!found)
            cout << right << setw(20) << fixed << "No product found!" << endl;
    }
    
    // print all customers' information (manager)
    void query_customer_all() {
        bool found = false;
        cout.precision(2);
        cout << right << setw(20) << fixed << "Customer ID " << right << setw(20) << fixed << "Name" << right << setw(20) << fixed << "Gender" << right << setw(20) << fixed << "Mobile Number" << right << setw(20) << fixed << "Capital" << right << setw(20) << fixed << "address" << endl;
        for (int i = 0; i < customers.size(); i++) {
            found = true;
            cout << right << setw(20) << fixed << customers[i].get_cid() << right << setw(20) << fixed << customers[i].get_name() << right << setw(20) << fixed << customers[i].get_gender() << right << setw(20) << fixed << customers[i].get_number() << right << setw(20) << fixed << customers[i].get_capital() << right << setw(20) << fixed << customers[i].get_address() << endl;
            
        }
        
        if (!found)
            cout << right << setw(20) << fixed << "No product found!" << endl;
    }
    
    // find specific customer by cid and return its pointer
    Customer* find_customer(int cid) {
        for (int i = 0; i < customers.size(); i++)
            if (customers[i].get_cid() == cid)
                return &customers[i];
        return nullptr;
    }
    
    // find specific product by cid and return its pointer
    Product* find_product(int pid) {
        for (int i = 0; i < products.size(); i++)
            if (products[i].get_pid() == pid)
                return &products[i];
        return nullptr;
    }
};

#endif /* main_h */
