package eventorganizer;

import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * Event organizer class
 *
 * @author Dongjin Kim
 */
public class EventOrganizer {
    private static final int MIN_DURATION = 30;
    private static final int MAX_DURATION = 120;

    /**
     * Runs the program
     */
    public void run() {
        System.out.println("Event Organizer running...");
        Scanner input = new Scanner(System.in);
        EventCalendar calendar = new EventCalendar();

        boolean isRunning = true;
        while (input.hasNextLine() && isRunning) {
            StringTokenizer st = new StringTokenizer(input.nextLine());
            String command;
            if (st.hasMoreTokens())
                command = st.nextToken();
            else continue;

            switch (command) {
                case "A":
                    addEvent(calendar, st);
                    break;
                case "R":
                    removeEvent(calendar, st);
                    break;
                case "P":
                    printEvents(calendar, "* Event calendar *");
                    break;
                case "PE":
                    printEvents(calendar, "* Event calendar by event date and start time *");
                    break;
                case "PC":
                    printEvents(calendar, "* Event calendar by campus and building *");
                    break;
                case "PD":
                    printEvents(calendar, "* Event calendar by department *");
                    break;
                case "Q":
                    isRunning = false;
                    System.out.println("Event Organizer terminated.");
                    break;
                default:
                    System.out.println(command + " is an invalid command!");
            }
        }
    }

    /**
     * Adds the event to calendar
     *
     * @param calendar the current calendar of events
     * @param st       list of parameters
     */
    private void addEvent(EventCalendar calendar, StringTokenizer st) {
        StringTokenizer dateTokens = new StringTokenizer(st.nextToken(), "/");
        int month = Integer.parseInt(dateTokens.nextToken()), day = Integer.parseInt(dateTokens.nextToken()),
                year = Integer.parseInt(dateTokens.nextToken());
        Date date = new Date(year, month, day);
        Timeslot startTime = getTimeSlot(st.nextToken().toUpperCase());
        Location location = getLocation(st.nextToken().toUpperCase());
        Department department = getDepartment(st.nextToken().toUpperCase());
        String email = st.nextToken();
        Contact contact = new Contact(department, email);
        int duration = Integer.parseInt(st.nextToken());

        if (!date.isValid()) {
            System.out.println(date + ": Invalid calendar date!");
            return;
        } else if (!date.isFutureDate()) {
            System.out.println(date + ": Event date must be a future date!");
            return;
        } else if (!date.isWithin6Months()) {
            System.out.println(date + ": Event date must be within 6 months!");
            return;
        }

        if (startTime == null) {
            System.out.println("Invalid time slot!");
            return;
        }
        if (location == null) {
            System.out.println("Invalid location!");
            return;
        }
        if (department == null || !contact.isValid()) {
            System.out.println("Invalid contact information!");
            return;
        }
        if (duration < MIN_DURATION || duration > MAX_DURATION) {
            System.out.println("Event duration must be at least " + MIN_DURATION + " minutes and at most " +
                    MAX_DURATION + " minutes");
            return;
        }

        Event event = new Event(date, startTime, location, contact, duration);

        if (!calendar.contains(event)) {
            calendar.add(event);
            System.out.println("Event added to the calendar.");
        } else {
            System.out.println("The event is already on the calendar.");
        }
    }


    /**
     * Removes the event from calendar
     *
     * @param calendar the current calendar of events
     * @param st       list of parameters
     */
    private void removeEvent(EventCalendar calendar, StringTokenizer st) {
        StringTokenizer dateTokens = new StringTokenizer(st.nextToken(), "/");
        int month = Integer.parseInt(dateTokens.nextToken()), day = Integer.parseInt(dateTokens.nextToken()),
                year = Integer.parseInt(dateTokens.nextToken());
        Date date = new Date(year, month, day);
        Timeslot startTime = getTimeSlot(st.nextToken().toUpperCase());
        Location location = getLocation(st.nextToken().toUpperCase());

        if (!date.isValid()) {
            System.out.println(date + ": Invalid calendar date!");
            return;
        } else if (!date.isFutureDate()) {
            System.out.println(date + ": Event date must be a future date!");
            return;
        } else if (!date.isWithin6Months()) {
            System.out.println(date + ": Event date must be within 6 months!");
            return;
        }

        if (startTime == null) {
            System.out.println("Invalid time slot!");
            return;
        }
        if (location == null) {
            System.out.println("Invalid location!");
            return;
        }

        Event event = new Event(date, startTime, location, null, 0);

        if (calendar.findToRemove(event) >= 0) {
            calendar.remove(event);
            System.out.println("Event has been removed from the calendar!");
        } else {
            System.out.println("Cannot remove; event is not in the calendar!");
        }
    }

    /**
     * Get timeslot from string
     *
     * @param timeslot the current timeslot of events
     * @return timeslot class from enum if exist
     */
    private Timeslot getTimeSlot(String timeslot) {
        for (Timeslot ts : Timeslot.values()) {
            if (ts.name().equals(timeslot)) {
                return ts;
            }
        }
        return null;
    }

    /**
     * Get location from string
     *
     * @param location the current location of events
     * @return location class from enum if exist
     */
    private Location getLocation(String location) {
        for (Location loc : Location.values()) {
            if (loc.name().equals(location)) {
                return loc;
            }
        }
        return null;
    }

    /**
     * Get department from string
     *
     * @param department the current department of events
     * @return department class from enum if exist
     */
    private Department getDepartment(String department) {
        for (Department dep : Department.values()) {
            if (dep.name().equals(department)) {
                return dep;
            }
        }
        return null;
    }

    /**
     * Print all event from calendar
     *
     * @param ec event calendar instance
     * @param s header string to print
     */
    private void printEvents(EventCalendar ec, String s) {
        Event[] e = ec.print();
        if (e == null)
            System.out.println("Event calendar is empty!");
        else {
            System.out.println(s);
            for (int i = 0; i < ec.getNumEvents(); i++)
                System.out.println(e[i]);
            System.out.println("* end of event calendar *");
        }
    }
}
