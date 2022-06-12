import os, time

admin_password = 'admin'


class Kiosk:
    def __init__(self):
        self.items = {}

    def add_menu(self, item, price):
        self.items[item] = price

    def print_menu(self):
        os.system('clear')

        if not self.items:
            print("판매중인 제품이 존재하지 않습니다.")
        else:
            item_no = 1
            for item, price in self.items.items():
                print(str(item_no) + "번 제품: \t" + item + "\t" * (2 - len(item) // 8) + str(price) + "원")
                item_no += 1

            if not user.permission:
                name = input('\n주문하실 제품명을 입력하세요: ')
                if name in self.items:
                    amount = int(input('주문하실 제품의 수량을 입력하세요: '))
                    if amount <= 0:
                        print('올바르지 않은 수량입니다.')
                        return
                    print(name + ' 제품 ' + str(amount) + '개의 가격은 ' + str(self.items[name] * amount) + '원입니다.')

                    while True:
                        ans = input('장바구니에 추가하시겠습니까? ')
                        if ans.upper() == 'YES':
                            user.add_to_cart(name, amount)
                            print("제품이 정상적으로 추가되었습니다.")
                            break
                        elif ans.upper() == 'NO':
                            print("제품 추가가 취소되었습니다.")
                            break
                        else:
                            print('입력은 YES 또는 NO 입니다.')
                else:
                    print('존재하지 않는 상품입니다.')
        time.sleep(1)


class User:
    def __init__(self, password):
        os.system('clear')
        if password == admin_password:
            print("관리자 모드로 진입합니다.")
            time.sleep(2)
            self.permission = True
        else:
            if password != '':
                print("잘못된 관리자 비밀번호입니다. 고객 모드로 진입합니다.")
                time.sleep(2)
            self.permission = False

        self.cart = {}
        self.cost = 0
        self.budget = 100000

    def print_cart(self):
        os.system('clear')
        print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
        if not self.cart:
            print("장바구니가 비어있습니다.")
        else:
            print("[ 장바구니 ]")
            for item in self.cart:
                print("제품명: " + item + "\t수량: " + str(self.cart[item]))
            print("합계 금액: " + str(self.cost) + "원")
        time.sleep(2)

    def add_to_cart(self, name, amount):
        if name not in self.cart:
            self.cart[name] = amount
        else:
            self.cart[name] += amount
        self.cost += kiosk.items[name] * amount

    def delete_from_cart(self):
        os.system('clear')
        print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
        if not self.cart:
            print("장바구니가 비어있습니다.")
        else:
            print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
            print("[ 장바구니 ]")
            for item in self.cart:
                print("제품명: " + item + "\t수량: " + str(self.cart[item]))
            print("합계 금액: " + str(self.cost) + "원")

        name = input("삭제하실 제품명을 입력하세요: ")

        if name in kiosk.items:
            amount = int(input('삭제하실 제품의 수량을 입력하세요: '))

            if amount <= 0 or self.cart[name] > amount:
                print('올바르지 않은 수량입니다.')
                return
            while True:
                ans = input("정말로 삭제하시겠습니까?: ")
                if ans.upper() == 'YES':
                    if self.cart[name] == amount:
                        del self.cart[name]
                        self.cost -= kiosk.items[name] * amount
                        print("제품이 정상적으로 삭제되었습니다.")
                        break
                    elif self.cart[name] > amount:
                        self.cart[name] -= amount
                        self.cost -= kiosk.items[name] * amount
                        print("제품이 정상적으로 삭제되었습니다.")
                        break

                elif ans.upper() == 'NO':
                    print("삭제가 취소되었습니다.")
                    break
                else:
                    print('입력은 YES 또는 NO 입니다.')
            time.sleep(1)
        else:
            print("존재하지 않는 제품입니다.")
            time.sleep(1)

    def check_out(self):
        os.system('clear')
        if not self.cart:
            print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
            print("장바구니가 비어있습니다.")
        else:
            print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
            print("[ 장바구니 ]")
            for item in self.cart:
                print("제품명: " + item + "\t수량: " + str(self.cart[item]))
            print("합계 금액: " + str(self.cost) + "원")

            while True:
                ans = input("결제하시겠습니까?: ")
                if ans.upper() == 'YES':
                    if self.budget >= self.cost:
                        print("제품이 정상적으로 결제되었습니다.")
                        self.budget -= self.cost
                        self.cart = {}
                        self.cost = 0
                        break
                    else:
                        print('잔액이 부족합니다.')
                elif ans.upper() == 'NO':
                    print("결제가 취소되었습니다.")
                    break
                else:
                    print('입력은 YES 또는 NO 입니다.')


def print_admin_command():
    os.system('clear')
    print('1: 판매 제품')
    print('2: 제품 추가')
    print('3: 제품 수정')
    print('4: 제품 삭제')
    print('0: 메인 메뉴')
    return int(input("\n메뉴를 선택해주세요: "))


def add_menu():
    os.system('clear')
    name = input("제품명을 입력하세요: ")
    price = int(input("가격을 입력하세요: "))

    if price <= 0:
        print('올바르지 않은 가격입니다.')
        return
    if name in kiosk.items:
        print("이미 존재하는 제품명입니다. 가격만 수정됩니다.")
        kiosk.items[name] = price
        time.sleep(1)
    else:
        kiosk.add_menu(name, price)
        print("제품이 정상적으로 추가되었습니다.")
        time.sleep(1)


def edit_menu():
    os.system('clear')
    name = input("수정하실 제품명을 입력하세요: ")

    if name in kiosk.items:
        print("현재 " + name + "의 가격은 " + str(kiosk.items[name]) + "원입니다.")
        price = int(input("변경하실 제품의 가격을 입력하세요: "))
        if price <= 0:
            print('올바르지 않은 가격입니다.')
            return

        kiosk.items[name] = price
        print("제품의 가격이 정상적으로 변경되었습니다.")
        time.sleep(1)
    else:
        print("존재하지 않는 제품입니다.")
        time.sleep(1)


def delete_menu():
    os.system('clear')
    name = input("삭제하실 제품명을 입력하세요: ")

    if name in kiosk.items:
        while True:
            ans = input("정말로 삭제하시겠습니까?: ")
            if ans.upper() == 'YES':
                del kiosk.items[name]
                print("제품이 정상적으로 삭제되었습니다.")
                break
            elif ans.upper() == 'NO':
                print("삭제가 취소되었습니다.")
                break
            else:
                print('입력은 YES 또는 NO 입니다.')
        time.sleep(1)
    else:
        print("존재하지 않는 제품입니다.")
        time.sleep(1)


def admin_mode():
    while True:
        cmd = print_admin_command()
        if cmd == 0:
            os.system('clear')
            return
        elif cmd == 1:
            kiosk.print_menu()
        elif cmd == 2:
            add_menu()
        elif cmd == 3:
            edit_menu()
        elif cmd == 4:
            delete_menu()


def print_command():
    os.system('clear')
    print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
    print('1: 메뉴 보기')
    print('2: 장바구니 확인')
    print('3: 장바구니 수정')
    print('4: 결제')
    print('0: 종료')
    return int(input("\n메뉴를 선택해주세요: "))


def user_mode():
    while True:
        cmd = print_command()
        if cmd == 0:
            exit(0)
        elif cmd == 1:
            kiosk.print_menu()
        elif cmd == 2:
            user.print_cart()
        elif cmd == 3:
            user.delete_from_cart()
        elif cmd == 4:
            user.check_out()


if __name__ == "__main__":

    global kiosk, user
    kiosk = Kiosk()

    while True:
        inp = input("주문하시려면 Enter키를 눌러주세요: ")
        user = User(inp)

        if user.permission:
            admin_mode()
        else:
            user_mode()
