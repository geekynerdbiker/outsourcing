package database;

import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.StringTokenizer;
import java.util.function.Predicate;

class TableImpl implements Table {
    private List<ColumnImpl> columns;
    private String name;

    TableImpl(List<List<String>> table) {
        this.columns = new ArrayList<>();

        ColumnImpl columnImpl;
        for (int col = 0; col < table.get(0).size(); ++col) {
            columnImpl = new ColumnImpl(table.get(0).get(col));

            columns.add(columnImpl);
        }

        for (int row = 1; row < table.size(); ++row) {
            for (int col = 0; col < table.get(row).size(); ++col) {
                columns.get(col).addCell(table.get(row).get(col));
            }
        }
    }

    public void setName(String name) {
        StringTokenizer st = new StringTokenizer(name, ".");
        name = st.nextToken();
        this.name = name;
    }

    @Override
    public Table crossJoin(Table rightTable) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;


        line = new ArrayList<>();
        for (int col = 0; col < getColumnCount(); ++col) {
            line.add(columns.get(col).getHeader());
        }
        for (int col = 0; col < rightTable.getColumnCount(); ++col) {
            line.add(rightTable.getColumn(col).getHeader());
        }
        table.add(line);


        for (int row = 0; row < getRowCount(); ++row) {
            for (int row2 = 0; row2 < rightTable.getRowCount(); ++row2) {
                line = new ArrayList<>();
                for (int col = 0; col < getColumnCount(); ++col) {
                    line.add(columns.get(col).getValue(row));
                }

                for (int col2 = 0; col2 < rightTable.getColumnCount(); ++col2) {
                    line.add(rightTable.getColumn(col2).getValue(row2));
                }
                table.add(line);
            }
        }
        return new TableImpl(table);
    }

    @Override
    public Table innerJoin(Table rightTable, List<JoinColumn> joinColumns) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;


        line = new ArrayList<>();
        for (int col = 0; col < getColumnCount(); ++col) {
            line.add(columns.get(col).getHeader());
        }
        for (int col = 0; col < rightTable.getColumnCount(); ++col) {
            line.add(rightTable.getColumn(col).getHeader());
        }
        table.add(line);


        for (int row = 0; row < getRowCount(); ++row) {
            line = new ArrayList<>();

            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getValue(row));

                if (Objects.equals(columns.get(col).getHeader(), joinColumns.get(0).getColumnOfThisTable()))
                    for (int col2 = 0; col2 < rightTable.getColumnCount(); ++col2) {
                        for (int row2 = 0; row2 < rightTable.getRowCount(); ++row2) {
                            if (Objects.equals(rightTable.getColumn(col2).getHeader(), joinColumns.get(0).getColumnOfAnotherTable()))
                                if (Objects.equals(columns.get(col).getValue(row), rightTable.getColumn(col2).getValue(row2)))
                                    for (int col3 = 0; col3 < rightTable.getColumnCount(); ++col3)
                                        line.add(rightTable.getColumn(col3).getValue(row2));
                        }
                    }
            }
            if (line.size() == getColumnCount() + rightTable.getColumnCount())
                table.add(line);
        }
        return new TableImpl(table);
    }

    @Override
    public Table outerJoin(Table rightTable, List<JoinColumn> joinColumns) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;


        line = new ArrayList<>();
        for (int col = 0; col < getColumnCount(); ++col) {
            line.add(columns.get(col).getHeader());
        }
        for (int col = 0; col < rightTable.getColumnCount(); ++col) {
            line.add(rightTable.getColumn(col).getHeader());
        }
        table.add(line);


        for (int row = 0; row < getRowCount(); ++row) {
            line = new ArrayList<>();

            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getValue(row));

                if (Objects.equals(columns.get(col).getHeader(), joinColumns.get(0).getColumnOfThisTable()))
                    for (int col2 = 0; col2 < rightTable.getColumnCount(); ++col2) {
                        for (int row2 = 0; row2 < rightTable.getRowCount(); ++row2) {
                            if (Objects.equals(rightTable.getColumn(col2).getHeader(), joinColumns.get(0).getColumnOfAnotherTable()))
                                if (Objects.equals(columns.get(col).getValue(row), rightTable.getColumn(col2).getValue(row2)))
                                    for (int col3 = 0; col3 < rightTable.getColumnCount(); ++col3)
                                        line.add(rightTable.getColumn(col3).getValue(row2));
                        }
                    }
            }
            table.add(line);
        }
        return new TableImpl(table);
    }

    @Override
    public Table fullOuterJoin(Table rightTable, List<JoinColumn> joinColumns) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;


        line = new ArrayList<>();
        for (int col = 0; col < getColumnCount(); ++col) {
            line.add(columns.get(col).getHeader());
        }
        for (int col = 0; col < rightTable.getColumnCount(); ++col) {
            line.add(rightTable.getColumn(col).getHeader());
        }
        table.add(line);

        for (int row = 0; row < getRowCount(); ++row) {
            line = new ArrayList<>();
            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getValue(row));
            }
            for (int col = 0; col < rightTable.getColumnCount(); ++col) {
                line.add("null");
            }
            table.add(line);
        }

        for (int row = 0; row < getRowCount(); ++row) {
            line = new ArrayList<>();

            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getValue(row));

                if (Objects.equals(columns.get(col).getHeader(), joinColumns.get(0).getColumnOfThisTable()))
                    for (int col2 = 0; col2 < rightTable.getColumnCount(); ++col2) {
                        for (int row2 = 0; row2 < rightTable.getRowCount(); ++row2) {
                            if (Objects.equals(rightTable.getColumn(col2).getHeader(), joinColumns.get(0).getColumnOfAnotherTable()))
                                if (Objects.equals(columns.get(col).getValue(row), rightTable.getColumn(col2).getValue(row2)))
                                    for (int col3 = 0; col3 < rightTable.getColumnCount(); ++col3)
                                        line.add(rightTable.getColumn(col3).getValue(row2));
                        }
                    }
            }
            if (line.size() == getColumnCount() + rightTable.getColumnCount())
                table.add(line);
        }

        for (int row = 0; row < rightTable.getRowCount(); ++row) {
            line = new ArrayList<>();
            for (int col = 0; col < getColumnCount(); ++col) {
                line.add("null");
            }

            for (int col = 0; col < rightTable.getColumnCount(); ++col) {
                line.add(rightTable.getColumn(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table);
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void show() {
        for (int col = 0; col < getColumnCount(); ++col) {
            int width = columns.get(col).getWidth();
            String header = columns.get(col).getHeader();

            System.out.format("%" + (width + 3) + "s", header + " | ");
        }
        System.out.println();

        columns.forEach(ColumnImpl::show);

        for (int row = 0; row < getRowCount(); ++row) {
            for (ColumnImpl column : columns)
                if (column.result.size() > row)
                    System.out.print(column.result.get(row) + " | ");
            System.out.println();
        }
    }

    @Override
    public void describe() {
        System.out.println("RangeIndex: " + String.valueOf(getRowCount()) + " entries, 0 to " + String.valueOf(getRowCount() - 1));
        System.out.println("Data columns (total " + String.valueOf(getColumnCount()) + " columns):");

        List<ColumnImpl> data = new ArrayList<>();
        List<List<String>> table = new ArrayList<>();
        List<String> line = new ArrayList<>();
        ColumnImpl columnImpl;

        line.add("#");
        line.add("Column");
        line.add("Non-Null Count");
        line.add("Dtype");
        table.add(line);

        for (int i = 0; i < getColumnCount(); i++) {
            line = new ArrayList<>();
            line.add(String.valueOf(i));
            line.add(getColumn(i).getHeader());
            line.add(String.valueOf(getColumn(i).getNullCount()) + " non-null");
            String dtype = "";

            try {
                Integer.parseInt(getColumn(i).getValue(0));
                dtype = "int";
            } catch (NumberFormatException ex) {
                dtype = "string";
            }

            line.add(dtype);
            table.add(line);
        }
        for (int col = 0; col < table.get(0).size(); ++col) {
            columnImpl = new ColumnImpl(table.get(0).get(col));

            data.add(columnImpl);
        }

        for (int row = 1; row < table.size(); ++row) {
            for (int col = 0; col < table.get(row).size(); ++col) {
                data.get(col).addCell(table.get(row).get(col));
            }
        }

        for (int col = 0; col < data.size(); ++col) {
            int width = data.get(col).getWidth();
            String header = data.get(col).getHeader();

            if (col < data.size() -1)
                System.out.format("%" + (width + 3) + "s", header + " | ");
            else
                System.out.format("%" + (width + 3) + "s", header + " | ");
        }
        System.out.println();

        data.forEach(ColumnImpl::show);

        for (int row = 0; row < getRowCount(); ++row) {
            for (ColumnImpl column : data)
                if (column.result.size() > row)
                    System.out.print(column.result.get(row) + " | ");
            System.out.println();
        }
    }

    @Override
    public Table head() {
        if (columns.size() < 5)
            return selectRows(0, columns.size() - 1);
        return selectRows(0, 5);
    }

    @Override
    public Table head(int lineCount) {
        if (columns.size() < lineCount)
            return selectRows(0, columns.size() - 1);
        return selectRows(0, lineCount);
    }

    @Override
    public Table tail() {
        if (columns.size() < 5)
            return selectRows(0, columns.size() - 1);
        return selectRows(getRowCount() - 5, getRowCount());
    }

    @Override
    public Table tail(int lineCount) {
        if (columns.size() < lineCount)
            if (columns.size() >= 5)
                return selectRows(columns.size() - 6, columns.size() - 1);
        return selectRows(getRowCount() - lineCount, getRowCount());
    }

    @Override
    public Table selectRows(int beginIndex, int endIndex) {
        if (beginIndex < 0)
            beginIndex = 0;
        if (endIndex > columns.size()) {
            beginIndex = endIndex - columns.size();
            endIndex = columns.size() - 1;
        }


        List<List<String>> table = new ArrayList<>();
        List<String> line;


        line = new ArrayList<>();
        for (int col = 0; col < getColumnCount(); ++col) {
            line.add(columns.get(col).getHeader());
        }
        table.add(line);


        for (int row = beginIndex; row < endIndex; ++row) {
            line = new ArrayList<>();
            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table);
    }

    @Override
    public Table selectRowsAt(int... indices) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;

        line = new ArrayList<>();
        for (int col = 0; col < getColumnCount(); ++col) {
            line.add(columns.get(col).getHeader());
        }
        table.add(line);


        for (int row : indices) {
            line = new ArrayList<>();
            for (int col = 0; col < getColumnCount(); ++col) {
                line.add(columns.get(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table);
    }

    @Override
    public Table selectColumns(int beginIndex, int endIndex) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;


        line = new ArrayList<>();
        for (int col = beginIndex; col < endIndex; ++col) {
            line.add(columns.get(col).getHeader());
        }
        table.add(line);


        for (int row = 0; row < getRowCount(); ++row) {
            line = new ArrayList<>();
            for (int col = beginIndex; col < endIndex; ++col) {
                line.add(columns.get(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table);
    }

    @Override
    public Table selectColumnsAt(int... indices) {
        List<List<String>> table = new ArrayList<>();
        List<String> line;


        line = new ArrayList<>();
        for (int col : indices) {
            line.add(columns.get(col).getHeader());
        }
        table.add(line);


        for (int row = 0; row < getRowCount(); ++row) {
            line = new ArrayList<>();
            for (int col : indices) {
                line.add(columns.get(col).getValue(row));
            }
            table.add(line);
        }

        return new TableImpl(table);
    }

    @Override
    public <T> Table selectRowsBy(String columnName, Predicate<T> predicate) {
        Column column = getColumn(columnName);
        List<Integer> rows = new ArrayList<Integer>();

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
            String value = attribute.getValue(i);
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
}
