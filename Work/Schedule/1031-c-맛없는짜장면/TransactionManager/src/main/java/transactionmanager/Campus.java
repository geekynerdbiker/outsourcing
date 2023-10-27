package transactionmanager;

/**
 * Campus class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public enum Campus {
    NEW_BRUNSWICK(0),
    NEWARK(1),
    CAMDEN(2);

    private final int collegeCode;

    /**
     * Creates predefined Campus objects
     *
     * @param collegeCode the code of the college
     */

    Campus(int collegeCode) {
        this.collegeCode = collegeCode;
    }

    /**
     * Returns an int representation
     *
     * @return code of college
     */
    public int getCollegeCode() {
        return this.collegeCode;
    }

    /**
     * Returns a string representation
     *
     * @return full name of department
     */
}