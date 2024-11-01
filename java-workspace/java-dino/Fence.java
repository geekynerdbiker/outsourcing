public class Fence implements MapObject {

    MapObjectType type = MapObjectType.FENCE;

    public MapObjectType getType() {
        return this.type;
    }

    public String print() {
        return "#####";
    }

    public boolean isEdible() {
        return false;
    }

    public boolean canMove() {
        return false;
    }
}
