import java.util.Random;

public class Carnivore extends Dino implements MapObject{
    MapObjectType type = MapObjectType.CARNIVORE;

    Carnivore(int id, String species) {
        super(id, species);
    }

    public MapObjectType getType() { return this.type; }

    public String print() {
        return "C:" + this.species.charAt(0) + Integer.toString(this.id);
    }

    public boolean isEdible() {
        return false;
    }

    public boolean canMove() {
        return true;
    }


    public boolean tryEat() {
        Random r = new Random();

        return r.nextInt(3) == 2;
    }
}
