import java.util.Arrays;

public class SeatManage {
    boolean[][] setTable;

    SeatManage() {
        this.setTable = new boolean[2][5];
    }

    void clear() {
        for (boolean[] booleans : setTable) Arrays.fill(booleans, false);
    }

    void print() {
        for (int i = 0; i < setTable.length; i++) {
            for (int j = 0; j < setTable[i].length; j++) {
                if (setTable[i][j])
                    System.out.print("C[" + (i + 1) + (j + 1) + "]\t");
                else
                    System.out.print("V[" + (i + 1) + (j + 1) + "]\t");
            }
            System.out.println();
        }
    }

    boolean setSeat(int x, int y) {
        if (!setTable[x][y]) {
            setTable[x][y] = true;
            System.out.println("선택되었습니다.");
            return true;
        } else {
            System.out.println("이미 사용 중 입니다.");
            return false;
        }
    }

    void releaseSeat(int x, int y) {
        if (setTable[x][y])
            setTable[x][y] = false;
    }
}