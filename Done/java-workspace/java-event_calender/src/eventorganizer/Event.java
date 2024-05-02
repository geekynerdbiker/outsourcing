package eventorganizer;

/**
 * Event class
 *
 * @author Dongjin Kim
 */
public class Event implements Comparable<Event> {
    private Date date; //the event date
    private Timeslot startTime; //the starting time
    private Location location;
    private Contact contact; //include the department name and email
    private int duration; //in minutes

    private static final int MAX_HOUR = 12;
    private static final int MAX_MINUTES = 60;
    private static final int MIN_DOUBLE_NUM = 10;

    /**
     * Creates an Event object with the specified date, startTime, location, contact, and duration
     *
     * @param date      the date of the event
     * @param startTime the start time of the event
     * @param location  the location of the event
     * @param contact   the contact for the event
     * @param duration  the duration of the event
     */
    public Event(Date date, Timeslot startTime, Location location, Contact contact, int duration) {
        this.date = date;
        this.startTime = startTime;
        this.location = location;
        this.contact = contact;
        this.duration = duration;
    }

    /**
     * Returns the date
     *
     * @return date
     */
    public Date getDate() {
        return this.date;
    }

    /**
     * Returns the startTime
     *
     * @return startTime
     */
    public Timeslot getStartTime() {
        return this.startTime;
    }

    /**
     * Returns the location
     *
     * @return location
     */
    public Location getLocation() {
        return this.location;
    }

    /**
     * Returns the department
     *
     * @return department
     */
    public Department getDepartment() {
        return this.contact.getDepartment();
    }

    /**
     * Checks if this event is equal to the specified object
     *
     * @param o the specified object
     * @return true if equal, false if not
     */
    @Override
    public boolean equals(Object o) {
        if (o instanceof Event) {
            Event event = (Event) o;
            return this.date.compareTo(event.date) == 0
                    && this.startTime.equals(event.startTime)
                    && this.duration == event.duration
                    && this.location.equals(event.location);
        }
        return false;
    }

    /**
     * Returns a string representation of the event
     *
     * @return string version of event in format
     * [Event Date: date] [Start: start time] [End: end time] @location [Contact: contact]
     */
    @Override
    public String toString() {
        int endHour = this.startTime.getHour(), endMinute = this.startTime.getMinute() + duration;
        boolean isAM = this.startTime.isAM();

        while (endMinute >= MAX_MINUTES) {
            ++endHour;
            endMinute -= MAX_MINUTES;
            if (endHour >= MAX_HOUR) {
                isAM = false;
            }
        }

        String endTime = endHour + ":";
        if (endMinute < MIN_DOUBLE_NUM)
            endTime += "0";
        endTime += endMinute;
        endTime += isAM ? "am" : "pm";

        String output = "[Event Date: " + this.date + "] ";
        output += "[Start: " + this.startTime + "] ";
        output += "[End: " + endTime + "] ";
        output += "@" + this.location;
        output += " [Contact: " + this.contact + "]";
        return output;
    }

    /**
     * Compares this event with the specified event
     *
     * @param e the object to be compared.
     * @return 1 if this event occurs after the specified event,
     * -1 if this event occurs before the specified event,
     * 0 if the events occur at the same time
     */
    @Override
    public int compareTo(Event e) {
        if (this.date.compareTo(e.date) > 0) {
            return 1;
        } else if (this.date.compareTo(e.date) < 0) {
            return -1;
        } else {
            if (this.startTime.compareTo(e.startTime) > 0) {
                return 1;
            } else if (this.startTime.compareTo(e.startTime) < 0) {
                return -1;
            } else {
                return 0;
            }
        }
    }
}