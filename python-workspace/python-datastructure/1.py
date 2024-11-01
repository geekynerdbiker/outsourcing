import random


class Node(object):
    def __init__(self, data):
        self.data = data
        self.prev = None
        self.next = None


class DList(object):
    def __init__(self):
        self.head = None
        self.result = 0

    def is_empty(self):
        return self.head is None

    def insert(self, value):
        if self.is_empty():
            self.head = Node(value)
            self.head.next = self.head
            self.head.prev = self.head
        else:
            node = Node(value)
            q = None
            p = self.head

            while p.next != self.head:
                q = p
                p = p.next

            node.next = p.next
            node.prev = p
            p.next.prev = node
            p.next = node

    def print(self):
        s = '[ '
        p = self.head
        while p.next != self.head:
            s += str(p.data) + ' '
            p = p.next

        s += ']'
        print(s)

    def shift(self):
        p = self.head

        while p.next != self.head:
            if p.data == 1:
                p.data = 2
            elif p.data == 2:
                p.data = 1
            p = p.next

    def swap_front(self, node):
        node.next = node.next.next

    def move(self, player, direction, distance):
        p = self.head
        playerNode = self.head

        while playerNode.data != player:
            p = p.next
            playerNode = playerNode.next

        p.next.prev = p.prev
        p.prev.next = p.next
        self.head = p.next
        if direction > 0:
            for i in range(distance):
                p = p.next
        else:
            for i in range(distance):
                p = p.prev

        if playerNode.data == 1 and p.data == 2:
            self.result = 1
        elif playerNode.data == 2 and p.data == 1:
            self.result = 2

        playerNode.prev = p.prev
        playerNode.next = p
        p.prev.next = playerNode
        p.prev = playerNode


def init():
    dl = DList()
    for i in range(16):
        if i == 0:
            dl.insert(1)
        elif i == 8:
            dl.insert(2)
        else:
            dl.insert(0)
    return dl


def roll():
    dice1 = random.randint(1, 6)
    dice2 = random.randint(1, 6)
    return (dice1, dice2)


def turn(player):
    if player == 1:
        return 2
    else:
        return 1


game = init()
player = 1
direction = 1
distance = 0

print('Game start!\n player 초기 위치')
game.print()

while game.result == 0:
    dice = roll()
    distance = dice[0] + dice[1]

    if dice[0] == 6 and dice[1] == 6:
        direction *= -1
        print(player, ' ', dice, ' 이동방향 전환')
        player = turn(player)
    elif dice[0] == 5 and dice[1] == 5:
        game.shift()
        print(player, ' ', dice, ' 위치 전환')
        player = turn(player)
    elif dice[0] == 1 and dice[1] == 1:
        game.move(player, direction * -1, 1)
        print(player, ' ', dice, ' 뒤로 한칸')
        game.print()
        player = turn(player)
    else:
        game.move(player, direction, distance)
        print(player, ' ', dice, ' ', distance, '칸 전진')
        if game.result == 0:
            game.print()
            player = turn(player)
        else:
            print(game.result, ' player won!')
