package ssu.btetris.model;


import java.io.Serializable;

public class JTetris implements Serializable {
    public enum TetrisState {
        Running(), NewBlock(), Finished();

        TetrisState() {
        }

    }

    public boolean any_block_crash = false;
    public int change_rotate = 0;
    public static int iScreenDw;
    public static int nBlockTypes;
    public static int nBlockDegrees;
    public static Matrix[][] setOfBlockObjects;

    private static Matrix[][] createSetOfBlocks(int[][][][] setOfArrays) throws Exception {
        int ntypes = setOfArrays.length;
        int ndegrees = setOfArrays[0].length;
        Matrix[][] setOfObjects = new Matrix[nBlockTypes][nBlockDegrees];
        for (int t = 0; t < ntypes; t++)
            for (int d = 0; d < ndegrees; d++)
                setOfObjects[t][d] = new Matrix(setOfArrays[t][d]);
        return setOfObjects;
    }

    private static int max(int a, int b) {
        return (Math.max(a, b));
    }

    private static int findLargestBlockSize(int[][][][] setOfArrays) {
        int size, max_size = 0;
        for (int t = 0; t < nBlockTypes; t++) {
            for (int d = 0; d < nBlockDegrees; d++) {
                size = setOfArrays[t][d].length;
                max_size = max(max_size, size);
            }
        }

        return max_size;
    }

    public static void init(int[][][][] setOfBlockArrays) throws Exception {
        nBlockTypes = setOfBlockArrays.length;
        nBlockDegrees = setOfBlockArrays[0].length;
        setOfBlockObjects = createSetOfBlocks(setOfBlockArrays);
        iScreenDw = findLargestBlockSize(setOfBlockArrays);
    }

    private final int iScreenDx;
    private TetrisState state;
    private int top;
    private int left;
    private final Matrix iScreen;
    private Matrix oScreen;
    public Matrix get_oScreen() {
        return oScreen;
    }
    private Matrix currBlk;
    private int idxBlockType;
    private int idxBlockDegree;

    private int[][] createArrayScreen(int dy, int dx, int dw) {
        int y, x;
        int[][] array = new int[dy + dw][dx + 2 * dw];
        for (y = 0; y < array.length; y++)
            for (x = 0; x < dw; x++)
                array[y][x] = 1;
        for (y = 0; y < array.length; y++)
            for (x = dw + dx; x < array[0].length; x++)
                array[y][x] = 1;
        for (y = dy; y < array.length; y++)
            for (x = 0; x < array[0].length; x++)
                array[y][x] = 1;
        return array;
    }

    boolean vert_delete(Matrix screen) {
        boolean vert_deleted = false;
        int point_1 = 0;
        int point_1_x = 0, point_1_y = 0;
        int point_2 = 0;
        int point_2_x = 0, point_2_y = 0;
        int count = 0;
        for (int i = 0; i <= 24; i++) {
            for (int j = 3; j <= 17; j++) {
                if (screen.get_array()[i][j] == 0) {
                    point_1 = 0;
                    point_2 = 0;
                    point_1_x = 0;
                    point_1_y = 0;
                    point_2_x = 0;
                    point_2_y = 0;
                    count = 0;
                } else {
                    if (count == 0) {
                        point_1 = screen.get_array()[i][j];
                        count++;
                        point_1_x = i;
                        point_1_y = j;
                        continue;
                    }
                    if (count == 1) {
                        if (point_1 == screen.get_array()[i][j]) {
                            count++;
                            point_2 = point_1;
                            point_2_x = i;
                            point_2_y = j;
                        } else {
                            point_1 = screen.get_array()[i][j];
                            point_1_x = i;
                            point_1_y = j;
                        }
                        continue;
                    }
                    if (count == 2) {
                        if (point_2 == screen.get_array()[i][j]) {
                            if (point_2 == screen.get_array()[i][j + 1]) {
                                screen.get_array()[i][j + 1] = 0;
                            }
                            if (point_2 == screen.get_array()[i][j + 2]) {
                                screen.get_array()[i][j + 2] = 0;
                            }
                            count = 0;
                            point_1 = 0;
                            point_2 = 0;
                            screen.get_array()[point_1_x][point_1_y] = 0;
                            screen.get_array()[point_2_x][point_2_y] = 0;
                            screen.get_array()[i][j] = 0;
                            point_1_x = 0;
                            point_1_y = 0;
                            point_2_x = 0;
                            point_2_y = 0;
                            vert_deleted = true;
                        } else {
                            count = 1;
                            point_1 = screen.get_array()[i][j];
                            point_2 = 0;
                            point_1_x = i;
                            point_1_y = j;
                            point_2_x = 0;
                            point_2_y = 0;
                        }
                    }
                }
            }
        }
        return vert_deleted;
    }

    boolean hori_delete(Matrix screen) {
        boolean hori_deleted = false;
        int point_3 = 0;
        int point_3_x = 0, point_3_y = 0;
        int point_4 = 0;
        int point_4_x = 0, point_4_y = 0;
        int count_hori = 0;
        for (int j = 3; j <= 17; j++) {
            for (int i = 0; i <= 24; i++) {
                if (screen.get_array()[i][j] == 0) {
                    point_3 = 0;
                    point_4 = 0;
                    point_3_x = 0;
                    point_3_y = 0;
                    point_4_x = 0;
                    point_4_y = 0;
                    count_hori = 0;
                } else {
                    if (count_hori == 0) {
                        point_3 = screen.get_array()[i][j];
                        count_hori++;
                        point_3_x = i;
                        point_3_y = j;
                        continue;
                    }
                    if (count_hori == 1) {
                        if (point_3 == screen.get_array()[i][j]) {
                            count_hori++;
                            point_4 = point_3;
                            point_4_x = i;
                            point_4_y = j;
                        } else {
                            point_3 = screen.get_array()[i][j];
                            point_3_x = i;
                            point_3_y = j;
                        }
                        continue;
                    }
                    if (count_hori == 2) {
                        if (point_4 == screen.get_array()[i][j]) {
                            if (point_4 == screen.get_array()[i + 1][j]) {
                                screen.get_array()[i + 1][j] = 0;
                            }
                            if (point_4 == screen.get_array()[i + 2][j]) {
                                screen.get_array()[i + 2][j] = 0;
                            }
                            count_hori = 0;
                            point_3 = 0;
                            point_4 = 0;
                            screen.get_array()[point_3_x][point_3_y] = 0;
                            screen.get_array()[point_4_x][point_4_y] = 0;
                            screen.get_array()[i][j] = 0;
                            point_3_x = 0;
                            point_3_y = 0;
                            point_4_x = 0;
                            point_4_y = 0;
                            hori_deleted = true;
                        } else {
                            count_hori = 1;
                            point_3 = screen.get_array()[i][j];
                            point_4 = 0;
                            point_3_x = i;
                            point_3_y = j;
                            point_4_x = 0;
                            point_4_y = 0;
                        }
                    }
                }
            }
        }
        return hori_deleted;
    }

    private Matrix deleteFullLines(Matrix screen, Matrix blk) {
        if (blk == null) return screen;
        while (true) {
            boolean vert_delete_bool;
            boolean hori_delete_bool;
            
            vert_delete_bool = vert_delete(screen);
            setting_wall(screen);
            hori_delete_bool = hori_delete(screen);
            setting_wall(screen);
            if (!vert_delete_bool && !hori_delete_bool) break;
        }
        return screen;

    }

    public JTetris(int cy, int cx) throws Exception {
        if (cy < iScreenDw || cx < iScreenDw) throw new TetrisException("too small screen");
        iScreenDx = cx;
        int[][] arrayScreen = createArrayScreen(cy, iScreenDx, iScreenDw);
        state = TetrisState.NewBlock;
        iScreen = new Matrix(arrayScreen);
        oScreen = new Matrix(iScreen);
    }

    public boolean check_vert_hori(Matrix A) {
        return A.get_array()[0][1] == '0';
    }

    public boolean check_p(boolean vert_hori, int num_rotate) {
        if (num_rotate % 2 != 0) {
            vert_hori = !vert_hori;
        }
        return vert_hori;
    }

    public boolean check_pp(Matrix A, Matrix B, boolean vert_hori, int num_rotate) {
        if (num_rotate % 2 != 0) {
            vert_hori = !vert_hori;
        }
        if (vert_hori) {
            for (int i = 0; i < 3; i++) {
                if (A.get_array()[1][i] != B.get_array()[1][i]) {
                    return false;
                }
            }
        } else {
            for (int i = 0; i < 3; i++) {
                if (A.get_array()[i][1] != B.get_array()[i][1]) {
                    return false;
                }
            }
        }
        return true;
    }

    public int check_wall(Matrix A) {
        if (A.get_array()[0][0] != 0 && A.get_array()[1][0] != 0 && A.get_array()[2][0] != 0) {
            return 1;
        } else if (A.get_array()[0][2] != 0 && A.get_array()[1][2] != 0 && A.get_array()[2][2] != 0) {
            return 2;
        } else {
            return 3;
        }
    }

    void setting_wall(Matrix A) {
        for (int i = 17; i >= 3; i--) {
            for (int j = 24; j >= 0; j--) {
                if (A.get_array()[j][i] == 0) continue;
                int cur = A.get_array()[j][i], cur_height = j + 1;
                while (cur_height <= 24) {
                    if (A.get_array()[cur_height][i] != 0) break;
                    cur_height++;
                }
                A.get_array()[j][i] = 0;
                A.get_array()[cur_height - 1][i] = cur;
            }
        }
    }

    public TetrisState accept(char key) throws Exception {
        Matrix tempBlk;
        if (state == TetrisState.NewBlock) {
            change_rotate = 0;
            oScreen = deleteFullLines(oScreen, currBlk);
            iScreen.paste(oScreen, 0, 0);
            state = TetrisState.Running;
            idxBlockType = key - '0';
            idxBlockDegree = 0;
            currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
            top = 0;
            left = iScreenDw + iScreenDx / 2 - (currBlk.get_dx() + 1) / 2;
            tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
            tempBlk = tempBlk.add(currBlk);
            oScreen.paste(iScreen, 0, 0);
            oScreen.paste(tempBlk, top, left);
            System.out.println();
            boolean temp_in_accept = check_vert_hori(currBlk);
            boolean temp_in_accept_crash = check_pp(tempBlk, currBlk, temp_in_accept, change_rotate);
            if (!temp_in_accept_crash) {
                state = TetrisState.Finished;
                return state;
            }
            return state;
        }
        switch (key) {
            case 'a':
                left--;
                boolean check_in_a = check_vert_hori(currBlk);
                boolean temp_in_key_a_check_rotate = check_p(check_in_a, change_rotate);
                tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
                tempBlk = tempBlk.add(currBlk);
                if (temp_in_key_a_check_rotate) {
                    if (tempBlk.get_array()[1][0] != currBlk.get_array()[1][0]) {
                        any_block_crash = true;
                        break;
                    }
                } else {
                    boolean temp_in_a_else = check_pp(tempBlk, currBlk, check_in_a, change_rotate);
                    if (!temp_in_a_else) {
                        any_block_crash = true;
                    }
                }
                break;
            case 'd':
                left++;
                boolean check_in_d = check_vert_hori(currBlk);
                boolean temp_in_key_d_check_rotate = check_p(check_in_d, change_rotate);
                tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
                tempBlk = tempBlk.add(currBlk);
                if (temp_in_key_d_check_rotate) {
                    if (tempBlk.get_array()[1][2] != currBlk.get_array()[1][2]) {
                        any_block_crash = true;
                        break;
                    }
                } else {
                    boolean temp_in_d_else = check_pp(tempBlk, currBlk, check_in_d, change_rotate);
                    if (!temp_in_d_else) {
                        any_block_crash = true;
                    }
                }
                break;

            case 's':
                top++;
                boolean check_in_s = check_vert_hori(currBlk);
                boolean temp_in_key_s_check_rotate = check_p(check_in_s, change_rotate);
                tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
                tempBlk = tempBlk.add(currBlk);
                if (temp_in_key_s_check_rotate) {
                    boolean temp_in_s_if = check_pp(tempBlk, currBlk, check_in_s, change_rotate);
                    if (!temp_in_s_if) {
                        any_block_crash = true;
                    }
                } else {
                    if (tempBlk.get_array()[2][1] != currBlk.get_array()[2][1]) {
                        any_block_crash = true;
                        break;
                    }
                }
                break;
            case 'w':
                tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
                tempBlk = tempBlk.add(currBlk);
                int temp_in_w_wall = check_wall(tempBlk);
                change_rotate++;
                idxBlockDegree = (idxBlockDegree + 1) % nBlockDegrees;
                currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
                if (temp_in_w_wall == 1) {
                    any_block_crash = true;
                } else any_block_crash = temp_in_w_wall == 2;
                break;
            case ' ':
                boolean vert_true_hori_false;
                boolean temp_bool;
                vert_true_hori_false = currBlk.get_array()[0][1] == '0';
                do {
                    top++;
                    tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
                    tempBlk = tempBlk.add(currBlk);
                    temp_bool = check_pp(tempBlk, currBlk, vert_true_hori_false, change_rotate);
                } while (temp_bool);
                any_block_crash = true;
                break;
            default:
                System.out.println("unknown key!");
        }
        tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
        tempBlk = tempBlk.add(currBlk);
        if (any_block_crash) {
            any_block_crash = false;
            switch (key) {
                case 'a':
                    left++;
                    break;
                case 'd':
                    left--;
                    break;
                case 's':
                case ' ':
                    top--;
                    state = TetrisState.NewBlock;
                    break;
                case 'w':
                    change_rotate--;
                    idxBlockDegree = (idxBlockDegree + nBlockDegrees - 1) % nBlockDegrees;
                    currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
                    break;
            }
            tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
            tempBlk = tempBlk.add(currBlk);
        }
        oScreen.paste(iScreen, 0, 0);
        oScreen.paste(tempBlk, top, left);
        return state;
    }

    static class TetrisException extends Exception {
        public TetrisException(String msg) {
            super(msg);
        }
    }
}


