public class Whale
{
    private String species;
    private char direction;
    private boolean injured;
    private char calf;
    private boolean hascalf;
    private boolean rare;
    private char migaloo;

    public Whale()
    {
        species = "unknown";
        direction = 'X';
        injured = false;
        calf = 'X';
        hascalf = false;
        rare = false;
        migaloo = 'X';
    }
    public Whale(String species, char direction, boolean injured, char calf, boolean hascalf, boolean rare, char migaloo)
    {
        this.species = species;
        this.direction = direction;
        this.injured = injured;
        this.calf = calf;
        this.hascalf = hascalf;
        this.rare = rare;
        this.migaloo = migaloo;
    }
    public void display()
    {
        System.out.println("species : " + species);
        System.out.println("direction : " + direction);
        System.out.println("injured : " + injured);
        System.out.println("calf : " + calf);
        System.out.println("hascalf : " + hascalf);
        System.out.println("rare : " + rare);
        System.out.println("Migaloo : " + migaloo);
    }
    public String getSpecies()
    {
        return species;
    }
    public char getDirection()
    {
        return direction;
    }
    public boolean getInjured()
    {
        return injured;
    }
    public char getCalf()
    {
        return calf;
    }
    public boolean getHasCalf()
    {
        return hascalf;
    }
    public boolean getRare()
    {
        return rare;
    }
    public char getMigaloo()
    {
        return migaloo;
    }

    public static void main(String[] args)
    {
        Whale wh = new Whale();
        wh.test();
    }
    public void setSpecies(String species)
    {
        this.species = species;
    }
    public void setDirection(char direction)
    {
        this.direction = direction;
    }
    public void setInjured(boolean injured)
    {
        this.injured = injured;
    }
    public void setCalf(char calf)
    {
        this.calf = calf;
    }
    public void setHasCalf(boolean hascalf)
    {
        this.hascalf = hascalf;
    }
    public void setRare(boolean rare)
    {
        this.rare = rare;
    }
    public void setMigaloo(char migaloo)
    {
        this.migaloo = migaloo;
    }
    public void test()
    {
        System.out.println("Test Whale class");
        Whale wh1 = new Whale();
        wh1.display();


    }
}