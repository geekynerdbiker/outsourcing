package comp2402w22a4;

import java.util.Set;
import java.util.HashSet;

public class HCPractice {
    public static class Person {
        String fname;     // first name
        String lname;     // last name
        int birthYear;    // year of birth, 4 digits.
        int luckyNumber;  // someone's lucky number, if they have one. If not, it's 0.

        public Person(String fname, String lname, int birthYear) {
            this.fname = fname;
            this.lname = lname;
            this.birthYear = birthYear;
        }

        public Person(String fname, String lname, int birthYear, int luckyNumber) {
            this(fname, lname, birthYear);
            this.luckyNumber = luckyNumber;
        }

        public String toString() {
            return "(" + fname + " " + lname + ": " + birthYear + ", lucky number: " + luckyNumber + ")";
        }

        // TODO(Student): Implement this method.
        public boolean equals(Object o) {
            if (o instanceof Person) {
                Person p = (Person) o;
                return this.fname.compareTo(p.fname) == 0 && this.lname.compareTo(p.lname) == 0 && this.birthYear == p.birthYear && this.luckyNumber == p.luckyNumber;
            }
            return false;
        }

        // TODO(Student): Implement this method
        public int hashCode() {
            return luckyNumber;
        }

    }

    public static void main(String[] args) {
        // If you want to run the program with assertions on,
        // use the -ea runtime parameter, e.g.
        // java -ea comp2402w22a4.HCPractice
        System.out.println("HashSet on Persons...");
        Set<Person> hs1 = new HashSet<>();

        hs1.add(new Person("Fname" + 1, "Lname" + 3, 2000));
        hs1.add(new Person("Fname" + 1, "Lname" + 3, 2000));

        Person p = new Person("Fname" + 2, "Lname" + 4, 2000);
        Person q = new Person("Fname" + 2, "Lname" + 4, 2000, 7);
        hs1.add(p);
        hs1.add(p);
        hs1.add(q);
        System.out.println(hs1);
        assert (hs1.size() == 2);
        assert (hs1.contains(p));
        assert (hs1.contains(q));

        for (int i = 0; i < 10000; i++) {
            hs1.add(new Person("Lname" + 1, "Fname" + 1, 2000, 3));
        }
        assert (hs1.size() == 3);
        System.out.println("Done adding");
    }

}
