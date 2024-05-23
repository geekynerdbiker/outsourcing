package studentstats;

import itertools.DoubleEndedIterator;

import studentapi.*;
import test.studentstats.MockStudentList;

/**
 * A (double ended) iterator over student records pulled from the student API.
 *
 * <p>This does not load the whole student list immediately, but rather queries the API ({@link
 * StudentList#getPage}) only as needed.
 */
public class StudentListIterator implements DoubleEndedIterator<Student> {
    // TASK(8): Implement StudentListIterator: Add any fields you require
    MockStudentList list;
    Student[] s, reverseS;
    int tries, retries;
    int page, reversePage;
    int index, reverseIndex;
    int curr, reverseCurr;

    /**
     * Construct an iterator over the given {@link StudentList} with the specified retry quota.
     *
     * @param list    The API interface.
     * @param retries The number of times to retry a query after getting {@link
     *                QueryTimedOutException} before declaring the API unreachable and throwing an {@link
     *                ApiUnreachableException}.
     */
    public StudentListIterator(StudentList list, int retries) {
        // TASK(8): Implement StudentListIterator
        this.list = (MockStudentList) list;
        this.retries = retries;

        s = null;
        reverseS = null;
        page = 0;
        reversePage = 0;
        index = 0;
        reverseIndex = 0;
        curr = 0;
        reverseCurr = 0;
    }

    /**
     * Construct an iterator over the given {@link StudentList} with a default retry quota of 3.
     *
     * @param list The API interface.
     */
    public StudentListIterator(StudentList list) {
        // TASK(8): Implement StudentListIterator
        this(list, 3);
    }

    @Override
    public boolean hasNext() {
        // TASK(8): Implement StudentListIterator
        return curr + reverseCurr < list.getNumStudents();
    }

    @Override
    public Student next() {
        // TASK(8): Implement StudentListIterator

        for (int i = 0; i < retries; i++) {
            try {
                if ((page == 0 && index == 0) || index == list.getPageSize()) {
                    s = list.getPage(page++);
                    index = 0;
                }
                curr++;
                return s[index++];
            } catch (QueryTimedOutException ignored) {
                page--;
            }
        }
        throw new ApiUnreachableException();
    }

    @Override
    public Student reverseNext() {
        // TASK(8): Implement StudentListIterator
        for (int i = 0; i < retries; i++) {
            try {
                if ((reversePage == 0 && reverseIndex == 0) || reverseIndex < 0 || reverseIndex == list.getPageSize()) {
                    reverseS = list.getPage(list.getNumPages() - reversePage - 1);
                    reversePage++;
                    reverseIndex = reverseS.length - 1;
                }
                reverseCurr++;

                return reverseS[reverseIndex--];
            } catch (QueryTimedOutException e) {
                reversePage--;
            }
        }
        throw new ApiUnreachableException();
    }
}
