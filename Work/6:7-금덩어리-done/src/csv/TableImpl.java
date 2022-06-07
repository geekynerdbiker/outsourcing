package csv;

import java.util.*;
import java.util.function.Predicate;
import java.util.AbstractMap.SimpleEntry;


class TableImpl implements Table {
    private final boolean header;
    private List<ColumnImpl> columns;

    TableImpl(List<List<String>> table, boolean isFirstLineHeader) {
        this.header = isFirstLineHeader;
        this.columns = new ArrayList<>();

        ColumnImpl columnImpl;
        for (int col = 0; col < table.get(0).size(); ++col) {
            if (isFirstLineHeader)
                columnImpl = new ColumnImpl(table.get(0).get(col));
            else
                columnImpl = new ColumnImpl();

            columns.add(columnImpl);
        }

        for (int row = isFirstLineHeader ? 1 : 0; row < table.size(); ++row) {
            for (int col = 0; col < getColumnCount(); ++col) {
                columns.get(col).addCell(table.get(row).get(col));
            }
        }
    }

    @Override
    public String toString() {
        int[] dtypes = {0, 0, 0};
        String result = "";
        result += "<csv.Table@" + Integer.toHexString(hashCode()) + ">\n";
        result += "RangeIndex: " + columns.get(0).count() + " entries, 0 to " + (columns.get(0).count() - 1) + "\n";
        result += "Data columns (total " + columns.size() + " columns): \n";

        List<List<String>> info = new ArrayList<>();
        List<Integer> width = Arrays.asList(1, 6, 14, 5);

        info.add(Arrays.asList("#", "Column", "Non-null Count", "Dtype"));

        List<String> line;
        for (int i = 0; i < getColumnCount(); ++i) {
            line = new ArrayList<>();
            Column currentColumn = getColumn(i);

            line.add(i + "");
            line.add(currentColumn.getHeader());
            line.add(currentColumn.count() - currentColumn.getNullCount() + " non-null");

            if (((ColumnImpl) currentColumn).isIntegerColumn()) {
                ++dtypes[1];
                line.add("int");
            } else if (currentColumn.isNumericColumn()) {
                ++dtypes[0];
                line.add("double");
            } else {
                ++dtypes[2];
                line.add("String");
            }

            width.set(0, Math.max(width.get(0), line.get(0).length()));
            width.set(1, Math.max(width.get(1), line.get(1).length()));
            width.set(2, Math.max(width.get(2), line.get(2).length()));
            width.set(3, Math.max(width.get(3), line.get(3).length()));

            info.add(line);
        }

        for (List<String> row : info) {
            result += String.format("%" + width.get(0) + "s", row.get(0)) + " |"
                    + String.format("%" + width.get(1) + "s", row.get(1)) + " |"
                    + String.format("%" + width.get(2) + "s", row.get(2)) + " |"
                    + String.format("%-" + width.get(3) + "s", row.get(3)) + "\n";
        }
        result += "dtypes: double(" + dtypes[0] + "), int(" + dtypes[1] + "), String(" + dtypes[2] + ")";

        return result;
    }

    @Override
    public void print() {
        if (header) {
            for (int col = 0; col < getColumnCount(); ++col) {
                var width = columns.get(col).getWidth();
                var header = columns.get(col).getHeader();

                System.out.format("%" + (width + 3) + "s", header + " | ");
            }
            System.out.println();
        }

        columns.forEach(ColumnImpl::print);

        for (int row = 0; row < getRowCount(); ++row) {
            for (var column : columns)
                System.out.print(column.result.get(row) + " | ");
            System.out.println();
        }
    }

    @Override
    public Table getStats() {
        List<List<String>> statsTable = new ArrayList<>();

        List<String> line;

        line = new ArrayList<>(Arrays.asList(""));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getHeader());
        }
        statsTable.add(line);

        line = new ArrayList<>(Arrays.asList("count"));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getNumericCount() + "");
        }
        statsTable.add(line);

        line = new ArrayList<>(Arrays.asList("mean"));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getMean() + "");
        }
        statsTable.add(line);

        line = new ArrayList<>(Arrays.asList("std"));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getStd() + "");
        }
        statsTable.add(line);

        line = new ArrayList<>(Arrays.asList("min"));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getNumericMin() + "");
        }
        statsTable.add(line);

        line = new ArrayList<>(Collections.singletonList("25%"));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getQ1() + "");
        }
        statsTable.add(line);

        line = new ArrayList<>(Collections.singletonList("50%"));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getMedian() + "");
        }
        statsTable.add(line);

        line = new ArrayList<>(Collections.singletonList("75%"));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getQ3() + "");
        }
        statsTable.add(line);

        line = new ArrayList<>(Arrays.asList("max"));
        for (Column column : columns) {
            if (column.getNumericCount() > 0)
                line.add(column.getNumericMax() + "");
        }
        statsTable.add(line);


        return new TableImpl(statsTable, true);
    }

    @Override
    public Table head() {
        return selectRows(0, 5);
    }

    @Override
    public Table head(int lineCount) {
        return selectRows(0, lineCount);
    }

    @Override
    public Table tail() {
        return selectRows(getRowCount() - 5, getRowCount());
    }

    @Override
    public Table tail(int lineCount) {
        return selectRows(getRowCount() - lineCount, getRowCount());
    }

    @Override
    public Table selectRows(int beginIndex, int endIndex) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;

        if (header) {
            line = new ArrayList<>();
            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getHeader());
            }
            table.add(line);
        }

        for (int row = beginIndex; row < endIndex; ++row) {
            line = new ArrayList<>();
            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table, header);
    }

    @Override
    public Table selectRowsAt(int... indices) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;

        if (header) {
            line = new ArrayList<>();
            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getHeader());
            }
            table.add(line);
        }

        for (int row : indices) {
            line = new ArrayList<>();
            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table, header);
    }

    @Override
    public Table selectColumns(int beginIndex, int endIndex) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;

        if (header) {
            line = new ArrayList<>();
            for (int col = beginIndex; col < endIndex; ++col) {
                line.add(columns.get(col).getHeader());
            }
            table.add(line);
        }

        for (int row = 0; row < getRowCount(); ++row) {
            line = new ArrayList<>();
            for (int col = beginIndex; col < endIndex; ++col) {
                line.add(columns.get(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table, header);
    }

    @Override
    public Table selectColumnsAt(int... indices) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;

        if (header) {
            line = new ArrayList<>();
            for (int col : indices) {
                line.add(columns.get(col).getHeader());
            }
            table.add(line);
        }

        for (int row = 0; row < getRowCount(); ++row) {
            line = new ArrayList<>();
            for (int col : indices) {
                line.add(columns.get(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table, header);
    }

    @Override
    public <T> Table selectRowsBy(String columnName, Predicate<T> predicate) {
        var column = getColumn(columnName);
        var rows = new ArrayList<Integer>();

        for (int row = 0; row < getRowCount(); ++row) {
            String stringValue = column.getValue(row);
            try {
                if (predicate.test((T) stringValue)) rows.add(row);
            } catch (Exception e) {
                if (stringValue != null) {
                    try {
                        Double doubleValue = Double.parseDouble(stringValue);
                        if (predicate.test((T) doubleValue)) rows.add(row);
                    } catch (Exception e2) {
                        try {
                            Integer integerValue = Integer.parseInt(stringValue);
                            if (predicate.test((T) integerValue)) rows.add(row);
                        } catch (NumberFormatException e3) {

                        }
                    }
                }
            }
        }

        return selectRowsAt(rows.stream().mapToInt(i -> i).toArray());
    }


    @Override
    public Table sort(int byIndexOfColumn, boolean isAscending, boolean isNullFirst) {
        Table prevTable = selectRows(0, getRowCount());
        Column attribute = getColumn(byIndexOfColumn);

        List<SimpleEntry<Integer, String>> list = new ArrayList<>();
        for (int i = 0; i < attribute.count(); ++i) {
            var value = attribute.getValue(i);
            if (value == null) {
                if (attribute.isNumericColumn()) {
                    value = Double.MAX_VALUE * (isNullFirst ^ isAscending ? 1 : -1) + "";
                } else {
                    value = isNullFirst ^ isAscending ? "\uffff" : "\u0000";
                }
            }
            list.add(new SimpleEntry<>(i, value));
        }

        if (attribute.isNumericColumn()) {
            list.sort((o1, o2) -> isAscending ? Double.valueOf(o1.getValue()).compareTo(Double.valueOf(o2.getValue())) : Double.valueOf(o2.getValue()).compareTo(Double.valueOf(o1.getValue())));
        } else {
            list.sort((o1, o2) -> isAscending ? o1.getValue().compareTo(o2.getValue()) : o2.getValue().compareTo(o1.getValue()));
        }

        for (int row = 0; row < getRowCount(); ++row)
            for (int col = 0; col < getColumnCount(); ++col)
                getColumn(col).setValue(row, prevTable.getColumn(col).getValue(list.get(row).getKey()));

        return this;
    }

    @Override
    public Table shuffle() {
        var prevTable = selectRows(0, getRowCount());

        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < getRowCount(); ++i) list.add(i);

        Collections.shuffle(list);

        for (int row = 0; row < getRowCount(); ++row)
            for (int col = 0; col < getColumnCount(); ++col)
                getColumn(col).setValue(row, prevTable.getColumn(col).getValue(list.get(row)));

        return this;
    }

    @Override
    public int getRowCount() {
        return columns.get(0).count();
    }

    @Override
    public int getColumnCount() {
        return columns.size();
    }

    @Override
    public Column getColumn(int index) {
        return columns.get(index);
    }

    @Override
    public Column getColumn(String name) {
        for (Column column : columns) {
            if (column.getHeader().equals(name)) {
                return column;
            }
        }
        return null;
    }

    @Override
    public boolean fillNullWithMean() {
        boolean isModified = false;

        for (int i = 0; i < getColumnCount(); ++i) {
            if (getColumn(i).fillNullWithMean()) {
                isModified = true;
            }
        }
        return isModified;
    }

    @Override
    public boolean fillNullWithZero() {
        boolean isModified = false;

        for (int i = 0; i < getColumnCount(); ++i) {
            if (getColumn(i).fillNullWithZero()) {
                isModified = true;
            }
        }
        return isModified;
    }

    @Override
    public boolean standardize() {
        boolean isModified = false;

        for (var i = 0; i < getColumnCount(); ++i) {
            if (getColumn(i).standardize()) {
                isModified = true;
            }
        }
        return isModified;
    }

    @Override
    public boolean normalize() {
        boolean isModified = false;

        for (var i = 0; i < getColumnCount(); ++i) {
            if (getColumn(i).normalize()) {
                isModified = true;
            }
        }
        return isModified;
    }

    @Override
    public boolean factorize() {
        boolean isModified = false;

        for (var i = 0; i < getColumnCount(); ++i) {
            if (getColumn(i).factorize()) {
                isModified = true;
            }
        }
        return isModified;
    }
}