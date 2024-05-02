# strategy_best3.py
# Strategy pattern -- function-based implementation
# selecting best promotion from imported module

"""
    >>> from promotions import *
    >>> joe = Customer('John Doe', 0)
    >>> ann = Customer('Ann Smith', 1100)
    >>> cart = [LineItem('banana', 4, .5),
    ...         LineItem('apple', 10, 1.5),
    ...         LineItem('watermellon', 5, 5.0)]
    >>> Order(joe, cart)
    <Order total: 42.00 due: 42.00>
    >>> Order(ann, cart)
    <Order total: 42.00 due: 39.90>
    >>> banana_cart = [LineItem('banana', 30, .5),
    ...                LineItem('apple', 10, 1.5)]
    >>> Order(joe, banana_cart)
    <Order total: 30.00 due: 28.50>
    >>> long_order = [LineItem(str(item_code), 1, 1.0)
    ...               for item_code in range(10)]
    >>> Order(joe, long_order)
    <Order total: 10.00 due: 9.30>
    >>> Order(joe, cart)
    <Order total: 42.00 due: 42.00>

# BEGIN STRATEGY_BEST_TESTS

    >>> Order(joe, long_order)
    <Order total: 10.00 due: 9.30>
    >>> Order(joe, banana_cart)
    <Order total: 30.00 due: 28.50>
    >>> Order(ann, cart)
    <Order total: 42.00 due: 39.90>

# END STRATEGY_BEST_TESTS
"""

from collections import namedtuple
import inspect

import promotions

Customer = namedtuple('Customer', 'name fidelity')


class LineItem:

    def __init__(self, product, quantity, price):
        self.product = product
        self.quantity = quantity
        self.price = price

    def total(self):
        return self.price * self.quantity


class Order:  # the Context

    def __init__(self, customer, cart):
        promos = [func for name, func in  # 4번 문제
                  inspect.getmembers(promotions, inspect.isfunction)]

        self.customer = customer
        self.cart = list(cart)
        self.promotion = max(promo(self) for promo in promos)  # 4번 문제

    def total(self):
        if not hasattr(self, '__total'):
            self.__total = sum(item.total() for item in self.cart)
        return self.__total

    def due(self):
        if self.promotion is None:
            discount = 0
        else:
            discount = self.promotion
        return self.total() - discount

    def __repr__(self):
        fmt = '<Order total: {:.2f} due: {:.2f}>'
        return fmt.format(self.total(), self.due())

    # BEGIN STRATEGY_BEST3

# END STRATEGY_BEST3
