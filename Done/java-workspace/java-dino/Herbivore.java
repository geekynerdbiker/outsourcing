public class Herbivore extends Dino implements MapObject{
    MapObjectType type = MapObjectType.HERBIVORE;

    Herbivore(int id, String species) {
        super(id, species);
    }

    public MapObjectType getType() { return this.type; }


    public String print() {
        return "H:" + this.species.charAt(0) + Integer.toString(this.id);
    }

    public boolean isEdible() {
        return true;
    }

    public boolean canMove() {
        return true;
    }
}
