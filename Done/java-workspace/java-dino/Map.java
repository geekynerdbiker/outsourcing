import java.util.Random;

public class Map {

    MapObject[][] map;
    int herbivore;
    int carnivore;

    String[] herbivoreName = {
            "Triceratops",
            "Stegosaurus",
            "Brachiosaurus",
            "Ankylosaurus",
            "Sauropoda"
    };

    String[] carnivoreName = {
            "Tyrannosaurus",
            "Theropods",
            "Tyrannosaurus rex",
            "Spinosaurus",
            "Giganotosaurus"};

    int[] herbivoreId = {10, 11, 12, 13, 14};

    int[] carnivoreId = {20, 21, 22, 23, 24};


    public Map(int width, int height, int herbivore, int carnivore) {
        this.herbivore = herbivore;
        this.carnivore = carnivore;
        this.map = new MapObject[width][height];
    }

    public void generate() {
        int count = 0;
        do {
            Random r = new Random();
            int x = r.nextInt(map.length);
            r = new Random();
            int y = r.nextInt(map[0].length);

            if (map[x][y] == null) {
                map[x][y] = new Fence();
                count++;
            }
        } while (count < (map.length) * (map[0].length) * 0.1);
    }

    public void randomHerbivore() {
        int count = 0;
        do {
            Random r = new Random();
            int x = r.nextInt(map.length);
            r = new Random();
            int y = r.nextInt(map[0].length);

            if (map[x][y] == null) {
                r = new Random();
                int s = r.nextInt(5);
                map[x][y] = new Herbivore(herbivoreId[s], herbivoreName[s]);
                count++;
            }
        } while (count < herbivore);
    }

    public void randomCarnivore() {
        int count = 0;
        do {
            Random r = new Random();
            int x = r.nextInt(map.length);
            r = new Random();
            int y = r.nextInt(map[0].length);

            if (map[x][y] == null) {
                r = new Random();
                int s = r.nextInt(5);
                map[x][y] = new Carnivore(carnivoreId[s], carnivoreName[s]);
                count++;
            }
        } while (count < carnivore);
    }

    public void empty() {
        for (int a = 0; a < map.length; a++) {
            for (int b = 0; b < map[0].length; b++) {
                if (map[a][b] == null) {
                    map[a][b] = new Empty();
                }
            }
        }
    }

    public boolean checkCoordinate(int x, int y) {
        return map[x][y].getType() != MapObjectType.EMPTY && map[x][y].getType() != (MapObjectType.FENCE);
    }

    public MapObject getCoordinate(int x, int y) {
        if (x < 0 || x > map.length - 1 || y < 0 || y > map[0].length - 1) {
            return null;
        }
        return map[x][y];
    }

    public String toString() {
        String output = "------------------------------------------------------------------------------------" +
                "--------------------------------------------------------" + "\n";
        for (int a = 0; a < map.length; a++) {
            for (int b = 0; b < map[0].length; b++) {
                output += map[a][b].print();
            }
            output += "\n";
        }
        output += "------------------------------------------------------------------------------------" +
                "--------------------------------------------------------";
        return output;
    }
}