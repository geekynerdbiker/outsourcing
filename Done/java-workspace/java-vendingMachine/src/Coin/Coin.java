package Coin;

public class Coin {
	private String coinName;
	private int coinNum;

	public Coin(String coinName, int coinNum) {
		super();
		this.coinName = coinName;
		this.coinNum = coinNum;
	}
	public String getCoinName() {
		return coinName;
	}

	public void setCoinName(String coinName) {
		this.coinName = coinName;
	}
	public int getCoinNum() {
		return coinNum;
	}
	public void setCoinNum(int coinNum) {
		this.coinNum = coinNum;
	}
}
