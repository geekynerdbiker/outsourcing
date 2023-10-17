import java.io.Console;
import java.io.IOException;
import java.util.Random;

class GameMaster {

    Map game = new Map(20, 20, 20, 5);

    public void Eat() {
        int[] score = new int[2];
        for (int a = 0; a < game.map.length; a++) {
            for (int b = 0; b < game.map[0].length; b++) {
                if (game.getCoordinate(a, b).getType() == MapObjectType.CARNIVORE && Move(a, b, MapObjectType.HERBIVORE)) {
                    score = neighbor(a, b, MapObjectType.HERBIVORE);
                    if (((Carnivore) game.map[a][b]).tryEat()) {
                        game.map[score[0]][score[1]] = new Empty();
                    }
                }
            }
        }
    }

    public void move() {
        int count = 0;
        MapObject[] temp = new MapObject[25];
        int[] pos = new int[2];

        for (int a = 0; a < game.map.length; a++) {
            for (int b = 0; b < game.map[0].length; b++) {
                if (game.checkCoordinate(a, b)) {
                    if (isNotMoved(game.map[a][b], temp) && Move(a, b, MapObjectType.EMPTY)) {
                        pos = neighbor(a, b, MapObjectType.EMPTY);
                        temp[count] = game.map[a][b];
                        game.map[a][b] = game.map[pos[0]][pos[1]];
                        game.map[pos[0]][pos[1]] = temp[count];
                        count++;
                    }
                }
            }
        }
    }

    public boolean isNotMoved(MapObject testobjekt, MapObject[] testtemp) {
        boolean x = true;
        for (MapObject i : testtemp) {
            if (testobjekt.equals(i)) {
                x = false;
                break;
            }
        }
        return x;
    }

    public boolean Move(int a, int b, MapObjectType type) {
        boolean x = (game.getCoordinate(a, b + 1) != null) && (game.getCoordinate(a, b + 1).getType() == type);

        if ((game.getCoordinate(a + 1, b) != null) && (game.getCoordinate(a + 1, b).getType() == type)) {
            x = true;
        }
        if ((game.getCoordinate(a + 1, b + 1) != null) && (game.getCoordinate(a + 1, b + 1).getType() == type)) {
            x = true;
        }
        if ((game.getCoordinate(a, b - 1) != null) && (game.getCoordinate(a, b - 1).getType() == type)) {
            x = true;
        }
        if ((game.getCoordinate(a + 1, b - 1) != null) && (game.getCoordinate(a + 1, b - 1).getType() == type)) {
            x = true;
        }
        if ((game.getCoordinate(a - 1, b) != null) && (game.getCoordinate(a - 1, b).getType() == type)) {
            x = true;
        }
        if ((game.getCoordinate(a - 1, b + 1) != null) && (game.getCoordinate(a - 1, b + 1).getType() == type)) {
            x = true;
        }
        if ((game.getCoordinate(a - 1, b - 1) != null) && (game.getCoordinate(a - 1, b - 1).getType() == type)) {
            x = true;
        }
        return x;
    }


    public int[] neighbor(int a, int b, MapObjectType type) {
        int[] arr = new int[2];
        Random random = new Random();
        int num = 0;

        do {
            num = random.nextInt(8) + 1;
            switch (num) {
                case 1:
                    if ((game.getCoordinate(a, b + 1) != null) && (game.getCoordinate(a, b + 1).getType() == type)) {
                        arr[0] = a;
                        arr[1] = b + 1;
                    }
                    break;
                case 2:
                    if ((game.getCoordinate(a + 1, b) != null) && (game.getCoordinate(a + 1, b).getType() == type)) {
                        arr[0] = a + 1;
                        arr[1] = b;
                    }
                    break;
                case 3:
                    if ((game.getCoordinate(a + 1, b + 1) != null) && (game.getCoordinate(a + 1, b + 1).getType() == type)) {
                        arr[0] = a + 1;
                        arr[1] = b + 1;
                    }
                    break;
                case 4:
                    if ((game.getCoordinate(a, b - 1) != null) && (game.getCoordinate(a, b - 1).getType() == type)) {
                        arr[0] = a;
                        arr[1] = b - 1;
                    }
                    break;
                case 5:
                    if ((game.getCoordinate(a + 1, b - 1) != null) && (game.getCoordinate(a + 1, b - 1).getType() == type)) {
                        arr[0] = a + 1;
                        arr[1] = b - 1;
                    }
                    break;
                case 6:
                    if ((game.getCoordinate(a - 1, b) != null) && (game.getCoordinate(a - 1, b).getType() == type)) {
                        arr[0] = a - 1;
                        arr[1] = b;
                    }
                    break;
                case 7:
                    if ((game.getCoordinate(a - 1, b + 1) != null) && (game.getCoordinate(a - 1, b + 1).getType() == type)) {
                        arr[0] = a - 1;
                        arr[1] = b + 1;
                    }
                    break;
                case 8:
                    if ((game.getCoordinate(a - 1, b - 1) != null) && (game.getCoordinate(a - 1, b - 1).getType() == type)) {
                        arr[0] = a - 1;
                        arr[1] = b - 1;
                    }
                    break;
                default:
                    break;
            }
        } while (arr[0] == 0 && arr[1] == 0);
        return arr;
    }

    public boolean existHerbivore() {
        boolean x = false;
        for (int a = 0; a < game.map.length; a++) {
            for (int b = 0; b < game.map[0].length; b++) {
                if (game.map[a][b].getType() == MapObjectType.HERBIVORE) {
                    x = true;
                }
            }
        }
        return x;
    }

    public int[] numberOfDino() {
        int numberOfHerbivore = 0;
        int numberOfCarnivore = 0;
        int[] x = new int[2];
        for (int a = 0; a < game.map.length; a++) {
            for (int b = 0; b < game.map[0].length; b++) {
                if (game.map[a][b].getType() == MapObjectType.HERBIVORE) {
                    numberOfHerbivore++;
                }
                if (game.map[a][b].getType() == MapObjectType.CARNIVORE) {
                    numberOfCarnivore++;
                }
            }
        }
        x[0] = numberOfHerbivore;
        x[1] = numberOfCarnivore;
        return x;
    }

    public void listHerbivore() {
        System.out.print("Living Herbivores: " + "\n");
        for (int a = 0; a < game.map.length; a++) {
            for (int b = 0; b < game.map[0].length; b++) {
                if (game.map[a][b].getType() == MapObjectType.HERBIVORE) {
                    System.out.println(game.map[a][b].print());
                }
            }
        }
    }

    public void listCarnivore() {
        System.out.print("Living Carnivores: " + "\n");
        for (int a = 0; a < game.map.length; a++) {
            for (int b = 0; b < game.map[0].length; b++) {
                if (game.map[a][b].getType() == MapObjectType.CARNIVORE) {
                    System.out.println(game.map[a][b].print());
                }
            }
        }
    }

    public void gameLoop() throws InterruptedException, IOException {
        int[] dinos = new int[2];
        int round = 0;
        game.generate();
        game.randomCarnivore();
        game.randomHerbivore();
        game.empty();
        do {
            System.out.print(game.toString() + "\n");
            dinos = numberOfDino();
            listHerbivore();
            System.out.println("\n" + "The Number of Herbivores: " + dinos[0]);
            listCarnivore();
            System.out.println("\n" + "The Number of Carnivores: " + dinos[1] + "\n");
            Eat();
            move();
            round++;

            Thread.sleep(1000);
        } while (existHerbivore());
        System.out.print(game.toString() + "\n");
        listCarnivore();
        System.out.println("\n" + "The Number of Carnivores: " + numberOfDino()[1] +
                "\n" + "The Number of Herbivores: " + numberOfDino()[0]);
        System.out.println("Total Round: " + round);
    }

    public static void main(String[] args) throws InterruptedException, IOException {
        GameMaster gameEngine = new GameMaster();
        gameEngine.gameLoop();
    }
}