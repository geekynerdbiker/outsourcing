#include <iostream>
#include <cstring>
#include "main.h"

// only one manager
Manager m = Manager();
// unexpectable customer
Customer* c;

int main(int argc, const char * argv[]) {
    MainProcess mp;
    
    int m_menu = 0, c_menu = 0;
    while (true) {
        mp.print_menu();
        int role = mp.get_role();
        
        // manager
        if (role == 1) {
            m.print_menu();
            m_menu = m.get_menu();
            
            // add product
            if (m_menu == 1) {
                int cmd = 1;
                
                while (cmd) {
                    Product p;
                    
                    int pid;
                    string name;
                    int amount;
                    double price;
                    
                    cout << "Product id: ";
                    cin >> pid;
                    cout << "Product name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Product amount: ";
                    cin >> amount;
                    cout << "Product price: ";
                    cin >> price;
                    
                    p.set_pid(pid);
                    p.set_name(name);
                    p.set_amount(amount);
                    p.set_price(price);
                    
                    mp.add_product(p);
                    cout << "Add another product (0: no, 1: yes)? ";
                    cin >> cmd;
                }
            } else if (m_menu == 2) { // query product
                string pid;
                
                cout << "Input a product ID (input \"*\" to list all products): ";
                cin >> pid;
                
                if (pid == "*")
                    mp.query_product_all();
                else {
                    int i_pid = stoi(pid);
                    mp.query_product(i_pid);
                }
            } else if (m_menu == 3) { // add customer
                int cmd = 1;
                
                while (cmd) {
                    Customer customer;
                    
                    int cid;
                    string name;
                    int gender;
                    string number;
                    string address;
                    
                    cout << "Customer id: ";
                    cin >> cid;
                    cout << "Customer name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Customer gender(1: male, 2: female): ";
                    cin >> gender;
                    cout << "Mobile number: ";
                    cin.ignore();
                    getline(cin, number);
                    cout << "Address: ";
                    cin.ignore();
                    getline(cin, address);
                    
                    
                    customer.set_cid(cid);
                    customer.set_name(name);
                    customer.set_gender(gender);
                    customer.set_number(number);
                    customer.set_address(address);
                    
                    mp.add_customer(customer);
                    cout << "Add another product (0: no, 1: yes)? ";
                    cin >> cmd;
                }
            } else if (m_menu == 4) { // query customer
                string cid;
                
                cout << "Input a customer ID (input \"*\" to list all customers): ";
                cin >> cid;
                
                if (cid == "*")
                    mp.query_customer_all();
                else {
                    int i_cid = stoi(cid);
                    mp.query_customer(i_cid);
                }
            } else { // wrong input
                cout << "Wrong Input" << endl;
                role = mp.get_role();
            }
        } else if (role == 2) { // customer
            int cid;
            bool quit = false;
            cout << "Please input your customer ID: ";
            cin >> cid;
            
            c = mp.find_customer(cid);
            while (c != nullptr) {
                string cmd;
                cout << "Failed to find your customer ID. Please input a new customer ID or input \"quit\" to move to parent menu: ";
                getline(cin, cmd);
                
                if (cmd == "quit") {
                    quit = true;
                    continue;
                }
                int i_cid = stoi(cmd);
                c = mp.find_customer(i_cid);
            }
            
            if (quit) continue;
            c->print_menu();
            c_menu = c->get_menu();
            
            if (c_menu == 1) { // add product into cart
                int cmd = 1;
                
                while (cmd) {
                    Product p;
                    
                    int pid;
                    int amount;
                    
                    cout << "Please input product id: ";
                    cin >> pid;
                    
                    Product *product = mp.find_product(pid);
                    if (product == nullptr) {
                        cout << "Failed to find product. Please check pid and try again." << endl;
                        break;
                    }
                    
                    cout << "Input the amount of product you want to buy: ";
                    cin >> amount;
                    
                    if (product->get_amount() < amount) {
                        cout << "Not enough amount of product." << endl;
                        break;
                    }
                    if (product->get_price() * amount > c->get_capital()) {
                        cout << "You don't have enough capital." << endl;
                        break;
                    }
                    
                    p.set_pid(product->get_pid());
                    p.set_name(product->get_name());
                    p.set_amount(amount);
                    p.set_price(product->get_price());
                    
                    c->add_into_cart(p);
                    cout << "Add productinto cart sucessfully." << endl;
                    
                }
            } else if (c_menu == 2) { // query product in cart
                string pid;
                
                cout << "Input a product ID for query (input \"*\" to list all products): ";
                cin >> pid;
                
                if (pid == "*")
                    c->query_product_all();
                else {
                    int i_pid = stoi(pid);
                    c->query_product(i_pid);
                }
            } else if (c_menu == 3) { // check up
                double total = c->check_up();
                
                int cmd;
                cout << "Please confirm to check up(0: no, 1: yes)? ";
                cin >> cmd;
                
                if (cmd == 1)
                    c->deduct_capital(total);
                    cout << "Check up successfully!" << endl;
            } else { // wrong input
                cout << "Wrong Input" << endl;
                role = mp.get_role();
            }
        } else if (role == 3) { // quit the program
            return 0;
        } else { // wrong input
            cout << "Wrong Input" << endl;
            role = mp.get_role();
        }
    }
    return 0;
}
