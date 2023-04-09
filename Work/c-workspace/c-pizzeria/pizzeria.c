//
// Assignment 2 DPST1091: CS Pizzeria
// pizzeria.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// TODO: INSERT-DESCRIPTION-HERE
//
// Version 1.0.0: Release

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: add any extra #includes your code needs here.

#include "pizzeria.h"
#include "save_string.h"

// TODO: add your own #defines here.
#define TRUE 1
#define FALSE 0

struct ingredient {
    // TODO: add your own fields in Stage 2.
    char name[MAX_STR_LENGTH];
    int amount;
    double price;
    struct ingredient *next;
};

struct order {
    // TODO: add your own fields in Stage 1.
    // Looking to store a price field? Try putting in "double price;" here!
    char customer[MAX_STR_LENGTH];
    char pizza[MAX_STR_LENGTH];
    double price;
    int time;
    struct order *next;
    struct ingredient * ingredients;
};

struct pizzeria {
    // TODO: add your own fields if required.
    struct ingredient *stock;
    struct order *selected;
    struct order *orders;
};

// TODO: add any other structs you define here.

//////////////////////////////////////////////////////////////////////

// TODO: add prototypes for any helper functions you create here.
void print_selected_single_order(char *customer, char *pizza_name, double price, int time_allowed);
// Prints a single order
void print_order(
                 int num,
                 char *customer,
                 char *pizza_name,
                 double price,
                 int time_allowed
                 );

// Prints an ingredient given the name, amount and price in the required format.
// This will be needed for stage 2.
void print_ingredient(char *name, int amount, double price);

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////


struct pizzeria *create_pizzeria() {
    // Allocates memory to store a `struct pizzeria` and returns a pointer to
    // it. The variable `new` holds this pointer!
    struct pizzeria *new = (struct pizzeria *)malloc(sizeof(struct pizzeria));
    
    new->stock = NULL;
    new->orders = NULL;
    new->selected = NULL;
    
    // TODO: this function has already been implemented for the current
    // struct pizzeria. When you decide to change struct pizzeria, change
    // this function as well.
    
    return new;
}

int add_order(
              struct pizzeria *pizzeria,
              char *customer,
              char *pizza_name,
              double price,
              int time_allowed
              ) {
    
    // TODO: fill in the rest of this function
    if (price < 0)
        return INVALID_PRICE;
    if (time_allowed <= 0)
        return INVALID_TIME;
    
    struct order *p = pizzeria->orders;
    struct order *q = NULL, *o;
    
    o = (struct order *)malloc(sizeof(struct order));
    
    for (int i = 0; i < MAX_STR_LENGTH; i++) {
        o->customer[i] = '\0';
        o->pizza[i] = '\0';
    }
    
    if (p == NULL) {
        strcpy(o->customer, customer);
        strcpy(o->pizza, pizza_name);
        o->price = price;
        o->time = time_allowed;
        o->next = NULL;
        o->ingredients = NULL;
        
        pizzeria->orders = o;
        
        return SUCCESS;
    }
    while (p) {
        q = p;
        p = p->next;
        
        if (p == NULL)
            break;
    }
       
    strcpy(o->customer, customer);
    strcpy(o->pizza, pizza_name);
    o->price = price;
    o->time = time_allowed;
    o->next = NULL;
    o->ingredients = NULL;
    q->next = o;
    
    
    return SUCCESS;
}

void print_all_orders(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    struct order *p = pizzeria->orders;
    
    int i = 1;
    while (p) {
        print_order(i++, p->customer, p->pizza, p->price, p->time);
        //        printf("%s ordered a %s pizza ($%.2lf) due in %d minutes.\n", p->customer, p->pizza, p->price, p->time);
        p = p->next;
        
        if (p == NULL)
            break;
    }
    // Do not change this part of the function
    print_selected_order(pizzeria);
    return;
}

int next_deadline(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    if (pizzeria->orders == NULL)
        return INVALID_CALL;
    
    struct order *p = pizzeria->orders;
    int deadline = -1;
    
    while (p) {
        if (deadline < 0) {
            deadline = p->time;
        } if (p->time < deadline) {
            deadline = p->time;
        }
        
        p = p->next;
        
        if (p == NULL)
            break;
    }
    
    return deadline;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

void select_next_order(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    struct order *p = pizzeria->selected;
    
    if (p == NULL) pizzeria->selected = pizzeria->orders;
    else pizzeria->selected = p->next;
    
    return;
}

void select_previous_order(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    struct order *p = pizzeria->selected;
    struct order *q = pizzeria->orders;
    
    if (p == NULL) {
        if (q == NULL) {
            pizzeria->selected = NULL;
            return;
        } while (q->next)
            q = q->next;
        pizzeria->selected = q;
        return;
    }
    
    if (p == q) {
        pizzeria->selected = NULL;
        return;
    }
    while (q->next != p)
        q = q->next;
    pizzeria->selected = q;
    
    return;
}

void print_selected_order(struct pizzeria *pizzeria) {
    
    // TODO: Change this once you have implemented the selected order
    // functionality.
    struct order *p = pizzeria->selected;
    
    if (p) {
        struct ingredient *q = pizzeria->selected->ingredients;
        
        print_selected_single_order(p->customer, p->pizza, p->price, p->time);
        while (q) {
            if (q == NULL)
                break;
            print_ingredient(q->name, q->amount, q->price);
            q = q->next;
        }
    } else
        printf("\nNo selected order.\n");
}

int add_ingredient(
                   struct pizzeria *pizzeria,
                   char *ingredient_name,
                   int amount,
                   double price
                   ) {
    
    // TODO: fill in the rest of this function
    if (pizzeria->selected == NULL)
        return INVALID_ORDER;
    if (price < 0)
        return INVALID_PRICE;
    if (amount <= 0)
        return INVALID_AMOUNT;
    
    struct ingredient *p = pizzeria->selected->ingredients;
    struct ingredient *q = NULL;
    struct ingredient *i = (struct ingredient*)malloc(sizeof(struct ingredient));
    
    for (int k = 0; k < MAX_STR_LENGTH; k++)
        i->name[k] = '\0';
    
    if (p == NULL) {
        strcpy(i->name, ingredient_name);
        i->amount = amount;
        i->price = price;
        i->next = NULL;
        
        pizzeria->selected->ingredients = i;
        
        return SUCCESS;
    } while (p) {
        if (p == NULL)
            break;
        if (strcmp(p->name, ingredient_name) < 0) {
            q = p;
            p = p->next;
            continue;
        } else if (strcmp(p->name, ingredient_name) > 0) {
            strcpy(i->name, ingredient_name);
            i->amount = amount;
            i->price = price;
            
            if (q == NULL) {
                i->next = p;
                pizzeria->selected->ingredients = i;
                return SUCCESS;
            } else {
                q->next = i;
                i->next = p;
                return SUCCESS;
            }
        } else {
            p->amount += amount;
            return SUCCESS;
        }
    }
    
    strcpy(i->name, ingredient_name);
    i->amount = amount;
    i->price = price;
    q->next = i;
    
    return SUCCESS;
}

double calculate_total_profit(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    if (pizzeria->selected == NULL)
        return INVALID_ORDER;
    
    struct ingredient *p = pizzeria->selected->ingredients;
    double profit = pizzeria->selected->price;
    
    while (p) {
        if (p == NULL)
            break;
        profit -= p->amount * p->price;
        p = p->next;
    }
    
    return profit;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////


int cancel_order(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    if (pizzeria->selected == NULL)
        return INVALID_ORDER;
    
    struct order *curr = pizzeria->selected;
    select_previous_order(pizzeria);
    struct order *prev = pizzeria->selected;
    
    if (prev)
        prev->next = curr->next;
    else
        pizzeria->orders = curr->next;
    pizzeria->selected = curr->next;
    
    struct ingredient *p = curr->ingredients;
    struct ingredient *q = p;
    
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(curr);
    
    return SUCCESS;
}

void free_pizzeria(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    struct order *p1 = pizzeria->orders;
    struct order *q1 = NULL;
    
    while (p1) {
        struct ingredient *p3 = p1->ingredients;
        struct ingredient *q3 = NULL;
        
        while (p3) {
            q3 = p3;
            p3 = p3->next;
            free(q3);
        }
        free(p3);
        
        q1 = p1;
        p1 = p1->next;
        free(q1);
    }
    free(p1);
    
    struct ingredient * p2 = pizzeria->stock;
    struct ingredient * q2 = p2;
    
    while (p2) {
        q2 = p2;
        p2 = p2->next;
        free(q2);
    }
    
    free(pizzeria);
    
    return;
}

int refill_stock(
                 struct pizzeria *pizzeria,
                 char *ingredient_name,
                 int amount,
                 double price
                 ) {
    
    // TODO: fill in the rest of this function
    if (price < 0)
        return INVALID_PRICE;
    if (amount <= 0)
        return INVALID_AMOUNT;
    
    struct ingredient *p = pizzeria->stock;
    struct ingredient *q = NULL;
    struct ingredient *i = (struct ingredient*)malloc(sizeof(struct ingredient));
    
    for (int k = 0; k < MAX_STR_LENGTH; k++)
        i->name[k] = '\0';
    
    if (p == NULL) {
        strcpy(i->name, ingredient_name);
        i->amount = amount;
        i->price = price;
        i->next = NULL;
        
        pizzeria->stock = i;
        
        return SUCCESS;
    } while (p) {
        if (strcmp(p->name, ingredient_name) < 0) {
            q = p;
            p = p->next;
            
            if (p == NULL)
                break;
            continue;
        } else if (strcmp(p->name, ingredient_name) > 0) {
            strcpy(i->name, ingredient_name);
            i->amount = amount;
            i->price = price;
            
            if (q == NULL) {
                i->next = p;
                pizzeria->stock = i;
                
                return SUCCESS;
            } else {
                q->next = i;
                i->next = p;
                return SUCCESS;
            }
        } else {
            p->amount += amount;
            return SUCCESS;
        }
    }
    
    strcpy(i->name, ingredient_name);
    i->amount = amount;
    i->price = price;
    q->next = i;
    
    return SUCCESS;
}

void print_stock(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    struct ingredient *p = pizzeria->stock;
    
    printf("The stock contains:\n");
    while (p) {
        if (p == NULL)
            break;
        print_ingredient(p->name, p->amount, p->price);
        p = p->next;
    }
    
    return;
}

int can_complete_order(struct pizzeria *pizzeria) {
    
    // TODO: fill in the rest of this function
    if (pizzeria->selected == NULL)
        return INVALID_ORDER;
    if (pizzeria->selected->ingredients == NULL)
        return INVALID_ORDER;
    
    struct ingredient *p = pizzeria->selected->ingredients;
    struct ingredient *s = pizzeria->stock;
    
    while (p && s) {
        if (strcmp(p->name, s->name) < 0) {
            p = p->next;
            
            if (p == NULL)
                break;
        } else if (strcmp(p->name, s->name) > 0) {
            s = s->next;
            
            if (s == NULL)
                break;
        } else {
            if (p->amount > s->amount)
                return INSUFFICIENT_STOCK;
    
            p = p->next;
            s = s->next;
            
            if (p == NULL || s == NULL)
                break;
        }
    }
    if (p != NULL)
        return INSUFFICIENT_STOCK;
    
    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

int complete_order(struct pizzeria *pizzeria) {
    if (can_complete_order(pizzeria) != SUCCESS)
        return INSUFFICIENT_STOCK;
    
    struct ingredient *p = pizzeria->selected->ingredients;
    struct ingredient *s = pizzeria->stock;
    struct ingredient *q = NULL;
    
    while (p && s) {
        if (strcmp(p->name, s->name) < 0) {
            p = p->next;
            
            if (p == NULL)
                break;
        } else if (strcmp(p->name, s->name) > 0) {
            q = s;
            s = s->next;
            
            if (s == NULL)
                break;
        } else {
            s->amount -= p->amount;
            
            if (s->amount == 0) {
                q->next = s->next;
                free(s);
                p = p->next;
                s = s->next;
            } else {
                q = s;
                p = p->next;
                s = s->next;
            } if (p == NULL || s == NULL)
                break;
        }
    }
    cancel_order(pizzeria);
    
    return SUCCESS;
}

int save_ingredients(struct pizzeria *pizzeria, char *file_name) {
    if (pizzeria->selected == NULL)
        return INVALID_ORDER;
    
    struct ingredient *p = pizzeria->selected->ingredients;
    char buffer[MAX_SAVE_LENGTH];
    
    for (int i = 0; i < MAX_SAVE_LENGTH; i++)
        buffer[i] = '\0';
    
    int l = 0;
    while (p) {
        if (p == NULL)
            break;
        l += sprintf(buffer + l, "%s\n", p->name);
        l += sprintf(buffer + l, "%d\n", p->amount);
        l += sprintf(buffer + l, "%.2lf\n\n", p->price);
        
        p = p->next;
    }
    save_string(file_name, buffer);
    
    return SUCCESS;
}

int load_ingredients(struct pizzeria *pizzeria, char *file_name) {
    if (pizzeria->selected == NULL)
        return INVALID_ORDER;
    
    char buffer[MAX_SAVE_LENGTH];
    
    for (int i = 0; i < MAX_SAVE_LENGTH; i++)
        buffer[i] = '\0';
    
    strcpy(buffer, load_string(file_name));
    
    char *ptr = strtok(buffer, "\n");
    
    while (ptr != NULL) {
        char name[MAX_STR_LENGTH];
        
        for (int i = 0; i < MAX_STR_LENGTH; i++)
            name[i] = '\0';
        
        strcpy(name, ptr);
        ptr = strtok(NULL, "\n");
        int amount = atoi(ptr);
        ptr = strtok(NULL, "\n");
        double price = atof(ptr);
        ptr = strtok(NULL, "\n\n");
        
        add_ingredient(pizzeria, name, amount, price);
    }
    
    
    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//               HELPER FUNCTIONS - Add your own here                 //
////////////////////////////////////////////////////////////////////////

// Prints a single order
//
// `print_order` will be given the parameters:
// - `num` -- the integer that represents which order it is sequentially.
// - `customer` -- the name of the customer for that order.
// - `pizza_name` -- the pizza the customer ordered.
// - `price` -- the price the customer is paying for the pizza.
// - `time_allowed` -- the time the customer will wait for the order.
//
// `print_order` assumes all parameters are valid.
//
// `print_order` returns nothing.
//
// This will be needed for Stage 1.
void print_order(
                 int num,
                 char *customer,
                 char *pizza_name,
                 double price,
                 int time_allowed
                 ) {
    
    printf("%02d: %s ordered a %s pizza ($%.2lf) due in %d minutes.\n",
           num, customer, pizza_name, price, time_allowed);
    
    return;
}

// Prints a single selected order
//
// `print_order` will be given the parameters:
// - `num` -- the integer that represents which order it is sequentially.
// - `customer` -- the name of the customer for that order.
// - `pizza_name` -- the pizza the customer ordered.
// - `price` -- the price the customer is paying for the pizza.
// - `time_allowed` -- the time the customer will wait for the order.
//
// `print_order` assumes all parameters are valid.
//
// `print_order` returns nothing.
//
// This will be needed for Stage 1.
void print_selected_single_order(
                                 char *customer,
                                 char *pizza_name,
                                 double price,
                                 int time_allowed
                                 ) {
    
    printf("\nThe selected order is %s's %s pizza ($%.2lf) due in %d minutes.\n",
           customer, pizza_name, price, time_allowed);
    
    return;
}

// Prints a single ingredient
//
// `print_ingredient` will be given the parameters:
// - `name` -- the string which contains the ingredient's name.
// - `amount` -- how many of the ingredient we either need or have.
// - `price` -- the price the ingredient costs.
//
// `print_ingredient` assumes all parameters are valid.
//
// `print_ingredient` returns nothing.
//
// This will be needed for Stage 2.
void print_ingredient(char *name, int amount, double price) {
    printf("    %s: %d @ $%.2lf\n", name, amount, price);
}


//    o Harry Margarita 15 20
//    o Hermione Grilled-Vegetable 14.49 60
//    o Molly Pepperoni 12.5 30
//    o Percy Anchovies 19.99 50
//    o Dumbledore Beef-n-Onion 10 30
//    o Remus Nutella 18.99 50
