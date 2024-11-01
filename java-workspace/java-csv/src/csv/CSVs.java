package csv;

import java.io.*;
import java.util.List;
import java.util.ArrayList;

public class CSVs {
    /**
     * @param isFirstLineHeader csv 파일의 첫 라인을 헤더(타이틀)로 처리할까요?
     */
    public static Table createTable(File csv, boolean isFirstLineHeader) {
        BufferedReader br;

        List<String> line;
        List<List<String>> table = new ArrayList<>();

        try {
            br = new BufferedReader(new FileReader(csv));
            String input, token;

            while ((input = br.readLine()) != null) {
                line = new ArrayList<>();
                int start = 0;
                boolean quote = false;

                for (int i = 0; i < input.length(); ++i) {
                    char curr = input.charAt(i);

                    if (curr == '"') quote = !quote;
                    if (!quote && curr == ',' || i == input.length() - 1) {
                        int end = i;
                        if (curr != ',' && i == input.length() - 1)
                            end += 1;

                        token = input.substring(start, end);
                        if (token.startsWith("\"")) {
                            token = token.substring(1, token.length() - 1);
                            token = token.replaceAll("\"\"", "\"");
                        }
                        line.add(token);
                        start = i + 1;
                    } if (curr == ',' && i == input.length() - 1)
                        line.add("");
                }
                table.add(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return new TableImpl(table, isFirstLineHeader);
    }

    /**
     * @return 새로운 Table 객체를 반환한다. 즉, 첫 번째 매개변수 Table은 변경되지 않는다.
     */
    public static Table sort(Table table, int byIndexOfColumn, boolean isAscending, boolean isNullFirst) {
        table = table.selectRows(0, table.getRowCount());
        table = table.sort(byIndexOfColumn, isAscending, isNullFirst);

        return table;
    }

    /**
     * @return 새로운 Table 객체를 반환한다. 즉, 첫 번째 매개변수 Table은 변경되지 않는다.
     */
    public static Table shuffle(Table table) {
        table = table.selectRows(0, table.getRowCount());
        table = table.shuffle();

        return table;
    }
}