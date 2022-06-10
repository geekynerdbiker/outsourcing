package csv;

import java.util.*;
import java.util.stream.Collectors;

class ColumnImpl implements Column {
    private String header;
    private List<String> cells;
    List<String> result;

    ColumnImpl() {
        this.cells = new ArrayList<>();
    }

    ColumnImpl(String header) {
        this();
        this.header = header;
    }

    void addCell(String cell) {
        if (cell != null && cell.length() == 0) cell = null;
        cells.add(cell);
    }

    boolean isIntegerColumn() {
        for (String cell : cells) {
            try {
                if (cell != null) Integer.parseInt(cell);
            } catch (NumberFormatException e) {
                return false;
            }
        }
        return true;
    }

    int getWidth() {
        int width = header.length();

        if (isNumericColumn()) {
            for (String cell : cells) {
                if (cell == null) {
                    width = Math.max(width, 4);
                    continue;
                }

                if (cell.contains(".")) {
                    var lenInt = cell.substring(0, cell.indexOf('.')).length();
                    var lenFloat = cell.substring(cell.indexOf('.')).length();
                    width = Math.max(width, lenInt + Math.min(lenFloat, 7));
                    continue;
                }

                width = Math.max(width, cell.length());
            }

            return width;
        }

        for (String cell : cells) {
            width = Math.max(width, cell == null ? 4 : cell.length());
        }

        return width;
    }

    private double getQuartile(int q) {
        List<Double> doubles = new ArrayList<>();
        for (int i = 0; i < count(); ++i) {
            try {
                var cell = getValue(i, Double.class);
                doubles.add(cell);
            } catch (IllegalArgumentException e) {
            }
        }
        Collections.sort(doubles);

        double index = q * (doubles.size() - 1) / 4.0;
        int lower = (int) Math.floor(index);

        if (lower < 0) return doubles.get(0);

        if (lower >= doubles.size() - 1) return doubles.get(doubles.size() - 1);

        double fraction = index - lower;
        return doubles.get(lower) + fraction * (doubles.get(lower + 1) - doubles.get(lower));
    }

    @Override
    public String getHeader() {
        return header;
    }

    @Override
    public String getValue(int index) {
        return cells.get(index);
    }

    @Override
    public <T extends Number> T getValue(int index, Class<T> t) throws IllegalArgumentException {
        if (cells.get(index) == null) {
            throw new IllegalArgumentException("Cannot cast 'null' to Number");
        }
        if (t.isAssignableFrom(Double.class)) {
            return t.cast(Double.parseDouble(cells.get(index)));
        }
        if (t.isAssignableFrom(Integer.class)) {
            return t.cast(Integer.parseInt(cells.get(index)));
        }

        throw new IllegalArgumentException("Bad type.");
    }

    @Override
    public void setValue(int index, String value) {
        cells.set(index, value);
    }

    @Override
    public <T extends Number> void setValue(int index, T value) {
        cells.set(index, String.valueOf(value));
    }

    @Override
    public int count() {
        return cells.size();
    }

    @Override
    public void print() {
        var width = getWidth();
        result = new ArrayList<>();

        if (isNumericColumn()) {
            for (String cell : cells) {
                if (cell != null && cell.contains(".")) {
                    cell = Math.round(Double.parseDouble(cell) * 1000000) / 1000000.0 + "";
                }
                result.add(String.format("%" + width + "s", cell));
            }
        } else {
            for (String cell : cells) {
                result.add(String.format("%" + width + "s", cell));
            }
        }
    }

    @Override
    public boolean isNumericColumn() {
        for (String cell : cells) {
            try {
                if (cell != null) Double.parseDouble(cell);
            } catch (NumberFormatException e) {
                return false;
            }
        }
        return true;
    }

    @Override
    public long getNullCount() {
        var count = 0;
        for (String cell : cells) {
            if (cell == null) ++count;
        }
        return count;
    }

    @Override
    public long getNumericCount() {
        var count = 0;
        for (String cell : cells) {
            try {
                if (cell != null) {
                    Double.parseDouble(cell);
                    ++count;
                }
            } catch (NumberFormatException e) {

            }
        }
        return count;
    }

    @Override
    public double getNumericMin() {
        var min = Double.MAX_VALUE;
        for (String cell : cells) {
            try {
                if (cell != null) {
                    min = Math.min(min, Double.parseDouble(cell));
                }
            } catch (NumberFormatException e) {

            }
        }
        return min;
    }

    @Override
    public double getNumericMax() {
        var max = -Double.MAX_VALUE;
        for (String cell : cells) {
            try {
                if (cell != null) {
                    max = Math.max(max, Double.parseDouble(cell));
                }
            } catch (NumberFormatException e) {

            }
        }
        return max;
    }

    @Override
    public double getMean() {
        var sum = 0.0;
        for (String cell : cells) {
            try {
                if (cell != null) {
                    sum += Double.parseDouble(cell);
                }
            } catch (NumberFormatException e) {

            }
        }
        return sum / getNumericCount();
    }

    @Override
    public double getStd() {
        var sum = 0.0;
        var mean = getMean();

        for (String cell : cells) {
            try {
                if (cell != null) {
                    sum += Math.pow(Double.parseDouble(cell) - mean, 2);
                }
            } catch (NumberFormatException e) {

            }
        }
        return Math.sqrt(sum / (getNumericCount() - 1));
    }

    @Override
    public double getQ1() {
        return getQuartile(1);
    }

    @Override
    public double getMedian() {
        return getQuartile(2);
    }

    @Override
    public double getQ3() {
        return getQuartile(3);
    }

    @Override
    public boolean fillNullWithMean() {
        if (!isNumericColumn() || getNullCount() == 0) return false;

        var mean = getMean();
        for (var row = 0; row < cells.size(); ++row) {
            if (getValue(row) == null) {
                setValue(row, mean);
            }
        }
        return true;
    }

    @Override
    public boolean fillNullWithZero() {
        if (!isNumericColumn() || getNullCount() == 0) return false;

        for (var row = 0; row < cells.size(); ++row) {
            if (getValue(row) == null) {
                setValue(row, 0);
            }
        }
        return true;
    }

    @Override
    public boolean standardize() {
        if (!isNumericColumn()) return false;

        var isModified = false;
        var std = getStd();
        var mean = getMean();

        for (var row = 0; row < count(); ++row) {
            try {
                var value = getValue(row, Double.class);
                value = (value - mean) / std;
                setValue(row, value);
                isModified = true;
            } catch (IllegalArgumentException e) {

            }
        }
        return isModified;
    }

    @Override
    public boolean normalize() {
        if (!isNumericColumn()) return false;

        var isModified = false;
        var min = getNumericMin();
        var range = getNumericMax() - min;

        for (var row = 0; row < count(); ++row) {
            try {
                var value = getValue(row, Double.class);
                value = (value - min) / range;
                setValue(row, value);
                isModified = true;
            } catch (IllegalArgumentException e) {

            }
        }
        return isModified;
    }

    @Override
    public boolean factorize() {
        TreeSet<String> set = new TreeSet<>(cells.stream().filter(c -> c != null).collect(Collectors.toSet()));
        if (set.size() != 2) return false;

        var isModified = false;
        var first = set.first();
        var last = set.last();

        for (var row = 0; row < count(); ++row) {
            if (getValue(row).equals(first)) {
                setValue(row, 0);
                isModified = true;
            } else if (getValue(row).equals(last)) {
                setValue(row, 1);
                isModified = true;
            }
        }
        return isModified;
    }
}