package transactionmanager;

/**
 * Profile class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class Profile implements Comparable<Profile> {
    private final String fname;
    private final String lname;
    private final Date dob;

    /**
     * Creates a Profile object
     *
     * @param fname first name
     * @param lname last name
     * @param dob   day of birth
     */
    public Profile(String fname, String lname, Date dob) {
        this.fname = fname;
        this.lname = lname;
        this.dob = dob;
    }

    /**
     * Compares this date
     *
     * @param o the object to be compared.
     * @return 0 if have same fname, lname, dob
     * 1, -1 if not
     */
    @Override
    public int compareTo(Profile o) {
        if (this.lname.toUpperCase().compareTo(o.lname.toUpperCase()) > 0) {
            return 1;
        } else if (this.lname.toUpperCase().compareTo(o.lname.toUpperCase()) < 0) {
            return -1;
        } else {
            if (this.fname.toUpperCase().compareTo(o.fname.toUpperCase()) > 0) {
                return 1;
            } else if (this.fname.toUpperCase().compareTo(o.fname.toUpperCase()) < 0) {
                return -1;
            } else {
                if (this.dob.compareTo(o.dob) > 0) {
                    return 1;
                } else if (this.dob.compareTo(o.dob) < 0) {
                    return -1;
                } else {
                    return 0;
                }
            }
        }
    }

    @Override
    public String toString() {
        return fname + " " + lname + " " + dob.toString();
    }
}