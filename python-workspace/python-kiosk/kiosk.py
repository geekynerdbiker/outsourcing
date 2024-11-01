import os, time

# 관리자 비밀번호 설정
admin_password = 'admin'


# 키오스크 클래스
class Kiosk:
    # 초기화 함수
    def __init__(self):
        self.items = {}

    # 메뉴 추가 함수
    def add_menu(self, item, price):
        self.items[item] = price

    # 메뉴 출력 함수
    def print_menu(self):
        os.system('clear')

        # 제품이 등록되지 않았을 때
        if not self.items:
            print("판매중인 제품이 존재하지 않습니다.")
            # 제품이 1개 이상 등록되어 있을 때
        else:
            item_no = 1
            # 1번 제품부터 출력
            for item, price in self.items.items():
                print(str(item_no) + "번 제품: \t" + item + "\t" * (2 - len(item) // 8) + str(price) + "원")
                item_no += 1

            # 관리자가 아니라면 주문 시작
            if not user.permission:
                name = input('\n주문하실 제품명을 입력하세요: ')
                if name in self.items:
                    amount = int(input('주문하실 제품의 수량을 입력하세요: '))
                    # 수량이 음수일 때 예외 처리: 함수 종료
                    if amount <= 0:
                        print('올바르지 않은 수량입니다.')
                        return
                    # 주문할 제품의 이름, 갯수, 총합 가격 출력
                    print(name + ' 제품 ' + str(amount) + '개의 가격은 ' + str(self.items[name] * amount) + '원입니다.')

                    # 장바구니에 추가. 올바른 입력을 받을 때까지 반복
                    while True:
                        ans = input('장바구니에 추가하시겠습니까? ')
                        # 대소문자 구분을 하지 않기 위해 입력받은 문자열을 모두 대문자로 변경 upper()
                        if ans.upper() == 'YES':
                            user.add_to_cart(name, amount)
                            print("제품이 정상적으로 추가되었습니다.")
                            break
                        elif ans.upper() == 'NO':
                            print("제품 추가가 취소되었습니다.")
                            break
                            # 입력이 올바르지 않을 경우
                        else:
                            print('입력은 YES 또는 NO 입니다.')
                else:
                    print('존재하지 않는 상품입니다.')
        time.sleep(1)


# 유저 클래스
class User:
    # 초기화 시 입력받은 비밀번호로 초기화
    def __init__(self, password):
        os.system('clear')
        # 관리자 비밀번호와 일치하면 관리자 모드로 진입
        if password == admin_password:
            print("관리자 모드로 진입합니다.")
            time.sleep(2)
            # 관리자 권한 부여
            self.permission = True
            # 입력을 하였으나 비밀번호가 틀릴 때
        else:
            # 무언가를 입력했을 때
            if password != '':
                print("잘못된 관리자 비밀번호입니다. 고객 모드로 진입합니다.")
                time.sleep(2)
            # 관리자 권한 미부여
            self.permission = False

        # 장바구니, 총합 금액, 예산 초기화
        self.cart = {}
        self.cost = 0
        self.budget = 100000

    # 장바구니 출력
    def print_cart(self):
        os.system('clear')
        print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
        # 장바구니가 비어있을 경우
        if not self.cart:
            print("장바구니가 비어있습니다.")
            # 그렇지 않은 경우
        else:
            print("[ 장바구니 ]")
            for item in self.cart:
                print("제품명: " + item + "\t수량: " + str(self.cart[item]))
            print("합계 금액: " + str(self.cost) + "원")
        time.sleep(2)

    # 장바구니에 제품 추가
    def add_to_cart(self, name, amount):
        # 새로운 상품을 추가할 때
        if name not in self.cart:
            self.cart[name] = amount
            # 이미 존재하는 상품을 추가할 때는 수량만 증가
        else:
            self.cart[name] += amount
        # 추가된 수량만큼 장바구니 총합 금액 증액
        self.cost += kiosk.items[name] * amount

    # 장바구니에서 제품 삭제
    def delete_from_cart(self):
        os.system('clear')
        print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
        # 장바구니가 비어있는 경우
        if not self.cart:
            print("장바구니가 비어있습니다.")
            # 비어있지 않은 경우
        else:
            print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
            print("[ 장바구니 ]")
            # 각각의 제품과 갯수 출력
            for item in self.cart:
                print("제품명: " + item + "\t수량: " + str(self.cart[item]))
            # 합계 금액 출력
            print("합계 금액: " + str(self.cost) + "원")

        name = input("삭제하실 제품명을 입력하세요: ")

        # 입력받은 제품이 장바구니에 담겨져 있다면
        if name in kiosk.items:
            amount = int(input('삭제하실 제품의 수량을 입력하세요: '))

            # 삭제할 수량이 장바구니에 담겨진 수량보다 많거나, 음수인 경우 예외 처리: 함수 종료
            if amount <= 0 or self.cart[name] > amount:
                print('올바르지 않은 수량입니다.')
                return
            # 정말로 삭제할 것인지 올바른 입력을 받을때까지 반복
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
        # 입력받은 제품명이 장바구니에 존재하지 않을 경우
        else:
            print("존재하지 않는 제품입니다.")
            time.sleep(1)

    # 결제
    def check_out(self):
        os.system('clear')
        # 장바구니가 비어있는 경우
        if not self.cart:
            print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
            print("장바구니가 비어있습니다.")
            # 그렇지 않은 경우
        else:
            print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
            print("[ 장바구니 ]")
            for item in self.cart:
                print("제품명: " + item + "\t수량: " + str(self.cart[item]))
            print("합계 금액: " + str(self.cost) + "원")

            # 정말로 결제할 것인지 올바른 입력을 받을 때까지 반복
            while True:
                ans = input("결제하시겠습니까?: ")
                if ans.upper() == 'YES':
                    # 가지고 있는 예산이 합계 금액보다 크거나 같은 경우
                    if self.budget >= self.cost:
                        print("제품이 정상적으로 결제되었습니다.")
                        self.budget -= self.cost
                        self.cart = {}
                        self.cost = 0
                        break
                    # 그렇지 않은 경우 결제를 진행하지 않음
                    else:
                        print('잔액이 부족합니다.')
                elif ans.upper() == 'NO':
                    print("결제가 취소되었습니다.")
                    break
                else:
                    print('입력은 YES 또는 NO 입니다.')


# 관리자 기능 출력
def print_admin_command():
    os.system('clear')
    print('1: 판매 제품')
    print('2: 제품 추가')
    print('3: 제품 수정')
    print('4: 제품 삭제')
    print('0: 메인 메뉴')
    return int(input("\n메뉴를 선택해주세요: "))


# 판매중인 상품 추가
def add_menu():
    os.system('clear')
    name = input("제품명을 입력하세요: ")
    price = int(input("가격을 입력하세요: "))

    # 가격이 음수인 경우 예외 처리: 함수 종료
    if price <= 0:
        print('올바르지 않은 가격입니다.')
        return
    # 목록에 이미 존재하는 제품일 경우 가격만 수정
    if name in kiosk.items:
        print("이미 존재하는 제품명입니다. 가격만 수정됩니다.")
        kiosk.items[name] = price
        time.sleep(1)
    else:
        kiosk.add_menu(name, price)
        print("제품이 정상적으로 추가되었습니다.")
        time.sleep(1)


# 제품 수정
def edit_menu():
    os.system('clear')
    name = input("수정하실 제품명을 입력하세요: ")

    # 입력받은 제품이 판매중인 목록에 존재하는 경우
    if name in kiosk.items:
        print("현재 " + name + "의 가격은 " + str(kiosk.items[name]) + "원입니다.")
        price = int(input("변경하실 제품의 가격을 입력하세요: "))
        # 입력받은 가격이 음수인 경우
        if price <= 0:
            print('올바르지 않은 가격입니다.')
            return

        kiosk.items[name] = price
        print("제품의 가격이 정상적으로 변경되었습니다.")
        time.sleep(1)
    # 입력받은 제품이 판매중인 목록에 존재하지 않는 경우
    else:
        print("존재하지 않는 제품입니다.")
        time.sleep(1)


# 제품 삭제
def delete_menu():
    os.system('clear')
    name = input("삭제하실 제품명을 입력하세요: ")

    # 입력받은 제품이 판매중인 목록에 존재하는 경우
    if name in kiosk.items:
        # 정말로 삭제할 것인지 올바른 입력을 받을 때까지 반복
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
    # 입력받은 제품이 판매중인 목록에 존재하지 않는 경우
    else:
        print("존재하지 않는 제품입니다.")
        time.sleep(1)


# 관리자 모드 기능 입력받는 함수
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


# 고객 기능 출력
def print_command():
    os.system('clear')
    print('현재 잔액은 ' + str(user.budget) + '원 입니다.\n')
    print('1: 메뉴 보기')
    print('2: 장바구니 확인')
    print('3: 장바구니 수정')
    print('4: 결제')
    print('0: 종료')
    return int(input("\n메뉴를 선택해주세요: "))


# 고객 모드 기능 입력받는 함수
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


# 메인 함수
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
