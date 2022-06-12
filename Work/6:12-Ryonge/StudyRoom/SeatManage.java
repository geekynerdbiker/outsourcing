package StudyRoom;

public class SeatManage{
	boolean setTable[][] = new boolean[2][5];
	int countEmpty;
	SeatManage() {
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 5; j++) 
				setTable[i][j] = false;
		}
		countEmpty = 10;
	}
	
	void clear() {
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 5; j++) 
				setTable[i][j] = false;
		}
	}
	
	void print() {
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 5; j++) {
				if(setTable[i][j])
					System.out.print("C");
				else
					System.out.print("V");
				System.out.print("["+ (i + 1) + (j + 1) + "]\t");
			}
			System.out.println();
		}
	}
	
	boolean setSeat(int x, int y) {
		if(setTable[x - 1][y - 1]) {
			System.out.println("이미 사용 중 입니다.");
			return false;
		}
		else {
			setTable[x - 1][y - 1] = true;
			return true;
		}
	}
	
	void releaseSeat(int x, int y) {
		if(setTable[x - 1][y - 1])
			setTable[x - 1][y - 1] = false;
	}
	
	int countEmptySeat() {
		countEmpty = 10;
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 5; j++)
				if(setTable[i][j]) countEmpty--;
		}
		return countEmpty;
	}
}
