package ajou_service;

public class member {
	private String name;
	private String id;
	private String pw;
	
	public member(String name, String id, String pw)
	{
		this.name = name;
		this.id = id;
		this.pw = pw;
	}
	
	public String get_id()
	{
		return this.id;
	}
	
	public String get_pw()
	{
		return this.pw;
	}
	
	public void change_pw(String pw) {
		this.pw = pw;
	}
	public String get_name()
	{
		return this.name;
	}

}
