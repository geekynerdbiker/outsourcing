package eventorganizer;

/**
 * Event calendar class
 *
 * @author Dongjin Kim
 */
public class EventCalendar {
    private Event[] events; // the array holding the list of events
    private int numEvents; // current number of events in the array

    private static final int NOT_FOUND = -1;
    private static final int CAPACITY = 4;
    private static final int EMPTY = 0;


    /**
     * Creates an empty list
     */
    public EventCalendar() {
        events = new Event[CAPACITY];
        numEvents = EMPTY;
    }

    /**
     * Searches for an event
     *
     * @param e the event to be searched
     * @return the index of event if found, -1 if not found
     */
    private int find(Event e) {
        for (int i = 0; i < events.length; ++i) {
            if (events[i].equals(e))
                return i;
        }
        return NOT_FOUND;
    }

    /**
     * Increases the capacity of event list by 4
     */
    private void grow() {
        Event[] increasedEvents = new Event[numEvents + CAPACITY];
        for (int i = 0; i < numEvents; ++i) {
            increasedEvents[i] = events[i];
        }
        events = increasedEvents;
    }

    /**
     * Searches for an event to remove
     *
     * @param e the event to be searched
     * @return the index of event if found, -1 if not found
     */
    public int findToRemove(Event e) {
        for (int i = 0; i < numEvents; ++i) {
            if (events[i].getDate().compareTo(e.getDate()) == 0)
                if (events[i].getStartTime().isEqual(e.getStartTime()))
                    if (events[i].getLocation().isEqual(e.getLocation()))
                        return i;
        }
        return NOT_FOUND;
    }

    /**
     * Adds an event to the end of the list
     *
     * @param e the event to be added
     */
    public void add(Event e) {
        if (numEvents >= events.length) {
            grow();
        }
        events[numEvents] = e;
        ++numEvents;
    }

    /**
     * Deletes the specified event
     *
     * @param e the event to be deleted
     */
    public void remove(Event e) {
        int indexOfEvent = findToRemove(e);
        for (int i = indexOfEvent; i < numEvents - 1; ++i)
            events[i] = events[i + 1];

        --numEvents;
        events[numEvents] = null;
    }

    /**
     * Checks whether an event exists in the list
     *
     * @param e the event to be searched
     * @return true if list contains specified event, false if not
     */
    public boolean contains(Event e) {
        if (numEvents == EMPTY)
            return false;
        for (int i = 0; i < numEvents; i++) {
            if (events[i].equals(e))
                return true;
        }
        return false;
    }

    /**
     * Prints the array of events
     *
     * @return event list
     */
    public Event[] print() {
        if (numEvents == EMPTY)
            return null;
        else
            return events;
    }

    /**
     * Print the array of events ordered by date and timeslot
     *
     * @return event list
     */
    public Event[] printByTimeslot() {
        for (int i = 1; i < numEvents; ++i) {
            Event key = events[i];
            int j = i - 1;
            while (j >= 0 && events[j].compareTo(key) > 0) {
                events[j + 1] = events[j];
                --j;
            }
            events[j + 1] = key;
        }
        return print();
    }

    /**
     * Print the array of events ordered by location
     *
     * @return event list
     */
    public Event[] printByLocation() {
        for (int i = 1; i < numEvents; ++i) {
            Event key = events[i];
            int j = i - 1;
            while (j >= 0 && events[j].getLocation().compareTo(key.getLocation()) > 0) {
                events[j + 1] = events[j];
                --j;
            }
            events[j + 1] = key;
        }
        return print();
    }

    /**
     * Print the array of events ordered by department
     *
     * @return event list
     */
    public Event[] printByDepartment() {
        for (int i = 1; i < numEvents; ++i) {
            Event key = events[i];
            int j = i - 1;
            while (j >= 0 && events[j].getDepartment().compareTo(key.getDepartment()) > 0) {
                events[j + 1] = events[j];
                --j;
            }
            events[j + 1] = key;
        }
        return print();
    }

    /**
     * Return event list
     *
     * @return event list
     */
    public Event[] getEvents() {
        return events;
    }

    /**
     * Return number of events added
     *
     * @return number of events
     */
    public int getNumEvents() {
        return numEvents;
    }
}
