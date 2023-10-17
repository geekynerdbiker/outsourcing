public class Dino{
    int id;
    String species;

    Dino(int id, String species) {
        this.id = id;
        this.species = species;
    }

    public int getId() {
        return this.id;
    }

    public String getSpecies() {
        return this.species;
    }

    public String toString() {
        return Character.toString(this.species.charAt(0)) + Integer.toString(this.id);
    }
}
