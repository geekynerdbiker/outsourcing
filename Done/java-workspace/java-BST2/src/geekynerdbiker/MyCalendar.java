

public class MyCalendar {
    MyTreeMap<Integer, Integer> calendar;
    
    public MyCalendar() {
        // TODO
        this.calendar = new MyTreeMap<>();
    }
    
    public boolean book(int start, int end) {
        // TODO
        if (start < 0 || start >= end) {
            throw new IllegalArgumentException();
        }
        Integer floorKey = calendar.floorKey(start);
        if (floorKey != null && calendar.get(floorKey) > start) {
            return false;
        }
        Integer ceilingKey = calendar.ceilingKey(start);
        if (ceilingKey != null && ceilingKey < end) {
             return false;
        }
        calendar.put(start, end);
        return true;
    }

    public MyTreeMap getCalendar(){
        return this.calendar;
    }
}