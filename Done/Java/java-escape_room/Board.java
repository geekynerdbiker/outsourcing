package pa1;

import java.util.Scanner;

public class Board implements Game {
    Scanner sc = new Scanner(System.in);
    Player player;
    Ghost ghost;
    Key key;
    Door door;
    char[][] board;

    public Board() {
        /* add your code, you can add parameter, too */
        board = new char[][]{
                {' ', '■', ' ', ' ', ' ', ' ', '■', ' ', '■', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', '■', ' ', '■', '■', '■', '■', ' ', '■', ' ', '■', ' ', '■', '■', ' '},
                {' ', '■', ' ', ' ', ' ', '■', ' ', ' ', '■', ' ', '■', ' ', ' ', '■', ' '},
                {' ', '■', ' ', '■', ' ', '■', ' ', '■', '■', ' ', '■', '■', ' ', '■', ' '},
                {' ', ' ', ' ', '■', ' ', '■', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', '■', '■', '■', ' ', ' ', ' ', '■', '■', '■', '■', '■', '■', '■', ' '},
                {' ', ' ', ' ', ' ', ' ', '■', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '■', ' '},
                {'■', '■', ' ', '■', '■', '■', ' ', '■', '■', '■', '■', '■', ' ', '■', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' ', '■', ' ', ' ', ' ', ' ', ' ', '■', ' '},
                {' ', '■', '■', ' ', '■', '■', ' ', '■', ' ', '■', '■', '■', ' ', '■', ' '},
                {' ', '■', ' ', ' ', ' ', ' ', ' ', '■', ' ', ' ', ' ', '■', ' ', '■', ' '},
                {' ', '■', ' ', '■', '■', '■', '■', '■', '■', '■', '■', '■', ' ', '■', ' '},
                {' ', '■', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '■', ' '},
                {' ', '■', '■', '■', ' ', '■', '■', '■', '■', '■', '■', '■', ' ', '■', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
        };
    }

    public void printBoard() {
        /* add your code, you can add parameter, too */
        if (key.getX() != -1)
            this.board[key.getY()][key.getX()] = 'K';
        this.board[door.getY()][door.getX()] = 'D';

        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board.length; j++) {
                if ((i == ghost.getY() || i == ghost.getY() * -1) && (j == ghost.getX() || j == ghost.getX() * -1)) {
                    System.out.print("G ");
                    continue;
                }
                if (i == player.getY() && j == player.getX()) {
                    System.out.print("P ");
                    continue;
                }
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
    }

    public void initObjects() {
        /* add your code, you can add parameter, too */
        int x, y;
        while (true) {
            System.out.println("input player x, y (0 ~ 14) :");
            x = sc.nextInt();
            y = sc.nextInt();

            if (x >= 0 && x < 15 && y >= 0 && y < 15 && board[y][x] == ' ') {
                player = new Player(x, y);
                break;
            }
        }
        while (true) {
            System.out.println("input ghost x, y (0 ~ 14) :");
            x = sc.nextInt();
            y = sc.nextInt();

            if (x >= 0 && x < 15 && y >= 0 && y < 15 && (x != player.getX() || y != player.getY())) {
                ghost = new Ghost(x, y);
                break;
            }
        }
        while (true) {
            System.out.println("input key x, y (0 ~ 14) :");
            x = sc.nextInt();
            y = sc.nextInt();

            if (x >= 0 && x < 15 && y >= 0 && y < 15 && board[y][x] == ' ') {
                if (x != player.getX() || y != player.getY()) {
                    key = new Key(x, y);
                    break;
                }
            }
        }
        while (true) {
            System.out.println("Input door x, y (0 ~ 14) :");
            x = sc.nextInt();
            y = sc.nextInt();

            if (x >= 0 && x < 15 && y >= 0 && y < 15 && board[y][x] == ' ') {
                if (x != player.getX() || y != player.getY()) {
                    if (x != key.getX() || y != key.getY()) {
                        door = new Door(x, y);
                        break;
                    }
                }
            }
        }
        sc.nextLine();
    }

    public void movePlayer() {
        /* add your code, you can add parameter, too */
        String input = sc.nextLine();
        int x, y;

        if (input.compareTo("u") == 0) {
            x = 0;
            y = -1;
        } else if (input.compareTo("d") == 0) {
            x = 0;
            y = 1;
        } else if (input.compareTo("l") == 0) {
            x = -1;
            y = 0;
        } else if (input.compareTo("r") == 0) {
            x = 1;
            y = 0;
        } else {
            return;
        }

        if (player.getX() + x >= 0 && player.getX() + x < 15 && player.getY() + y >= 0 && player.getY() + y < 15 && board[player.getY() + y][player.getX() + x] != '■') {
            board[player.getY()][player.getX()] = ' ';
            player.move(x, y);
        }
        if (player.getX() == key.getX() && player.getY() == key.getY()) {
            key.setX(-1);
        }
    }

    public void moveGhost() {
        /* add your code, you can add parameter, too */
        if (ghost.getX() >= 0 && ghost.getY() >= 0)
            ghost.move(player.getX(), player.getY());
        ghost.setX(ghost.getX() * -1);
        ghost.setY(ghost.getY() * -1);

    }

    public boolean isFinish() {
        /* add your code, you can add parameter, too */
        if (key.getX() == -1 && door.getX() == player.getX() && door.getY() == player.getY()) {
            if ((player.getX() == ghost.getX() || player.getX() == ghost.getX() * -1) && (player.getY() == ghost.getY() || player.getY() == ghost.getY() * -1)) {
                System.out.println("YOU LOSE");
                sc.close();
                return true;
            }
            System.out.println("YOU WIN");
            sc.close();
            return true;
        }
        if ((player.getX() == ghost.getX() || player.getX() == ghost.getX() * -1) && (player.getY() == ghost.getY() || player.getY() == ghost.getY() * -1)) {
            System.out.println("YOU LOSE");
            sc.close();
            return true;
        }

        return false;
    }

}
