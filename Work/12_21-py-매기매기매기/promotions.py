def fidelity_priority_promo(order):   # 3번 문제
    """20% discount for customers with 2000 or more fidelity points and with 20 or more same product"""
    for item in order.cart:
        if item.quantity >= 20:
            return order.total() * .2 if order.customer.fidelity >= 2000 else 0
    return 0


def fidelity_promo(order):
    """5% discount for customers with 1000 or more fidelity points"""
    return order.total() * .05 if order.customer.fidelity >= 1000 else 0


def bulk_item_promo(order):
    """10% discount for each LineItem with 20 or more units"""
    discount = 0
    for item in order.cart:
        if item.quantity >= 20:
            discount += item.total() * .1
    return discount


def large_order_promo(order):
    """7% discount for orders with 10 or more distinct items"""
    distinct_items = {item.product for item in order.cart}
    if len(distinct_items) >= 10:
        return order.total() * .07
    return 0
