import requests
import json
import time


NAVER_API_KEY = '네이버 API 키'
KAKAO_API_KEY = '카카오 API 키'

ORDER_FILE_PATH = 'orders.json'


class Order:
    def __init__(self, order_id, customer_name, phone_number, order_date):
        self.order_id = order_id
        self.customer_name = customer_name
        self.phone_number = phone_number
        self.order_date = order_date

    def to_json(self):
        return json.dumps(self.__dict__, ensure_ascii=False)

    @staticmethod
    def from_json(json_data):
        data = json.loads(json_data)
        return Order(data['order_id'], data['customer_name'], data['phone_number'], data['order_date'])


def fetch_orders():
    url = 'https://api.naver.com/store/orders'
    headers = {
        'Authorization': f'Bearer {NAVER_API_KEY}'
    }
    response = requests.get(url, headers=headers)
    response.raise_for_status()
    orders = response.json()
    return orders


def load_existing_orders():
    try:
        with open(ORDER_FILE_PATH, 'r', encoding='utf-8') as file:
            return [Order.from_json(order) for order in json.load(file)]
    except FileNotFoundError:
        return []


def save_orders(orders):
    with open(ORDER_FILE_PATH, 'w', encoding='utf-8') as file:
        json.dump([order.to_json() for order in orders], file, ensure_ascii=False)


def get_new_orders(fetched_orders, existing_orders):
    existing_order_ids = {order.order_id for order in existing_orders}
    return [order for order in fetched_orders if order['order_id'] not in existing_order_ids]


def send_kakao_message(phone_number, message):
    url = 'https://api.kakao.com/v1/bizmessage/send'
    headers = {
        'Authorization': f'Bearer {KAKAO_API_KEY}',
    }
    data = {
        'phone_number': phone_number,
        'message': message
    }
    response = requests.post(url, headers=headers, data=data)
    response.raise_for_status()

    return response.json()

def main():
    while True:
        print("주문 조회 중...")
        fetched_orders = fetch_orders()
        existing_orders = load_existing_orders()

        new_orders = get_new_orders(fetched_orders, existing_orders)
        if new_orders:
            print(f"신규 주문 {len(new_orders)}건 발견!")
            for order_data in new_orders:
                order = Order(order_data['order_id'], order_data['customer_name'], order_data['phone_number'],
                              order_data['order_date'])
                message = f"{order.customer_name}님, 주문이 완료되었습니다! 감사합니다."
                send_kakao_message(order.phone_number, message)
                existing_orders.append(order)

        save_orders(existing_orders)

        print("10분 후에 다시 조회합니다...")
        time.sleep(600)


if __name__ == "__main__":
    main()
