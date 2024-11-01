package database;

import java.util.ArrayList;
import java.util.List;

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

    int getWidth() {
        int width = header.length();

        if (isNumericColumn()) {
            for (String cell : cells) {
                if (cell == null) {
                    width = Math.max(width, 4);
                    continue;
                }

                if (cell.contains(".")) {
                    int lenInt = cell.substring(0, cell.indexOf('.')).length();
                    int lenFloat = cell.substring(cell.indexOf('.')).length();
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

    @Override
    public String getHeader() {
        return header;
    }

    @Override
    public String getValue(int index) {
        if (index >= cells.size())
            return cells.get(cells.size()-1);
        return cells.get(index);
    }

    @Override
    public <T extends Number> T getValue(int index, Class<T> t) {
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
    public void setValue(int index, int value) {
        cells.set(index, String.valueOf(value));
    }

    @Override
    public int count() {
        return cells.size();
    }

    @Override
    public void show() {
        int width = getWidth();
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
        long count = 0;
        for (String cell : cells) {
            if (cell == null) ++count;
        }
        return count;
    }
}