package eventorganizer;

/**
 * Contact class
 *
 * @author Dongjin Kim
 */
public class Contact {
    private Department department;
    private String email;

    /**
     * Creates a Contact object
     *
     * @param department the department of the contact
     * @param email      the email of the contact
     */
    public Contact(Department department, String email) {
        this.department = department;
        this.email = email;
    }

    /**
     * Returns the department
     *
     * @return department
     */
    public Department getDepartment() {
        return this.department;
    }

    /**
     * Checks if the department name and email address are valid
     *
     * @return true if valid, false if not
     */
    public boolean isValid() {
        if (!this.email.endsWith("@rutgers.edu"))
            return false;

        for (Department department : Department.values()) {
            if (this.department.name().equals(department.name()))
                return true;
        }
        return false;
    }

    /**
     * Returns a string representation
     *
     * @return string version of contact of format department, email
     */
    @Override
    public String toString() {
        return this.department + ", " + this.email;
    }
}
