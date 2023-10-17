import java.io.*;
import java.nio.file.Files;

public class SheepdogBot {
    private static final int[] dirX = {-1, 0, 1, 0, -1, -1, 1, 1};
    private static final int[] dirY = {0, 1, 0, -1, -1, 1, 1, -1};
    private static final int GRID_SIZE = 31;
    private static final int PEN_SIZE = 5;
    private static final int INVALID_CELL = -1;

    private static int[][] grid;
    private static int[][] value;
    private static int[][] policy;

    private static NeuralNetwork model;

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        Bot1();
        Bot2();
    }

    public static void Bot1() {
        init();
        valueIteration();
        printGrid(value);
        printGrid(policy);
    }

    public static void Bot2() throws IOException, ClassNotFoundException {
        init();
        valueIteration();
        trainModel();
        simulate();
    }

    private static void init() {
        grid = new int[GRID_SIZE][GRID_SIZE];
        value = new int[GRID_SIZE][GRID_SIZE];
        policy = new int[GRID_SIZE][GRID_SIZE];
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = INVALID_CELL;
                value[i][j] = Integer.MAX_VALUE;
                policy[i][j] = -1;
            }
        }

        for (int i = 0; i < PEN_SIZE; i++) {
            for (int j = 0; j < PEN_SIZE; j++) {
                grid[i][j] = 1;
            }
        }

        int sheepX = 0;
        int sheepY = 0;
        int robotX = GRID_SIZE - 1;
        int robotY = GRID_SIZE - 1;
        grid[sheepX][sheepY] = 2;
        grid[robotX][robotY] = 3;
    }

    private static void valueIteration() {
        boolean changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    if (grid[i][j] != INVALID_CELL) {
                        int minValue = Integer.MAX_VALUE;
                        int bestAction = -1;
                        for (int k = 0; k < 8; k++) {
                            int newX = i + dirX[k];
                            int newY = j + dirY[k];
                            if (isValid(newX, newY)) {
                                int newStateValue = value[newX][newY] + 1;
                                if (newStateValue < minValue) {
                                    minValue = newStateValue;
                                    bestAction = k;
                                }
                            }
                        }
                        value[i][j] = minValue;
                        policy[i][j] = bestAction;
                        changed = true;
                    }
                }
            }
        }
    }

    private static void trainModel() throws IOException, ClassNotFoundException {
        File valueFile = new File("value.txt");
        model = new NeuralNetwork(GRID_SIZE * GRID_SIZE, 128, 1);
        ObjectInputStream in = new ObjectInputStream(Files.newInputStream(valueFile.toPath()));
        model.load(in);
        in.close();

        // Train the model
        int epochs = 1000;
        for (int i = 0; i < epochs; i++) {
            // Generate a random state
            int state = generateRandomState();

            // Get the predicted number of moves from the model
            int predictedMoves = model.predict(state);

            // Get the actual number of moves
            int actualMoves = value[state / GRID_SIZE][state % GRID_SIZE];

            // Calculate the loss
            int loss = (predictedMoves - actualMoves) * (predictedMoves - actualMoves);

            // Update the model
            model.update(state, actualMoves, loss);
        }
    }

    private static int generateRandomState() {
        int state = (int) (Math.random() * GRID_SIZE * GRID_SIZE);
        while (grid[state / GRID_SIZE][state % GRID_SIZE] == INVALID_CELL) {
            state = (int) (Math.random() * GRID_SIZE * GRID_SIZE);
        }
        return state;
    }

    private static void simulate() {
        // Set the sheep and robot positions
        int sheepX = 0;
        int sheepY = 0;
        int robotX = GRID_SIZE - 1;
        int robotY = GRID_SIZE - 1;

        while (true) {
            // Get the action from the model
            int action = model.predict(encodeState(sheepX, sheepY, robotX, robotY));

            // Move the robot
            int newRobotX = robotX + dirX[action];
            int newRobotY = robotY + dirY[action];
            if (isValid(newRobotX, newRobotY)) {
                robotX = newRobotX;
                robotY = newRobotY;
            }

            // Check if the sheep is caught
            if (grid[robotX][robotY] == 2) {
                System.out.println("The sheep is caught!");
                break;
            }
        }
    }

    private static int encodeState(int sheepX, int sheepY, int robotX, int robotY) {
        return sheepX * GRID_SIZE + sheepY + robotX * GRID_SIZE * GRID_SIZE + robotY;
    }

    private static boolean isValid(int x, int y) {
        return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] != INVALID_CELL;
    }

    private static void printGrid(int[][] grid) {
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                System.out.print(grid[i][j]);
            }
            System.out.println();
        }
    }
}
