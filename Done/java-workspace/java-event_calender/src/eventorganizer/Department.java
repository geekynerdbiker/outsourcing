package eventorganizer;

/**
 * Department class
 *
 * @author Dongjin Kim
 */
public enum Department {
    BAIT("Business Analytics and Information Technology"),
    CS("Computer Science"),
    EE("Electrical Engineering"),
    ITI("Information Technology and Informatics"),
    MATH("Mathematics");

    private final String name;

    /**
     * Creates predefined Department objects
     *
     * @param name the full name of the department
     */
    Department(String name) {
        this.name = name;
    }

    /**
     * Returns a string representation
     *
     * @return full name of department
     */
    @Override
    public String toString() {
        return this.name;
    }
}
