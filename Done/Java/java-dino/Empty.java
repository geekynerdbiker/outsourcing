public class Empty implements MapObject {

    MapObjectType type = MapObjectType.EMPTY;

    public MapObjectType getType() {
        return this.type;
    }

    public String print() {
        return "     ";
    }

    public boolean isEdible() {
        return false;
    }

    public boolean canMove() {
        return false;
    }

}