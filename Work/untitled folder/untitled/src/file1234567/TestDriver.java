package file1234567;

public class TestDriver {
	public static void main(String[] args) {
		File courseworkpdf = new File("courseworkpdf", 1);
		File courseworkzip = new File("coursework zip file", 2);

		Directory coursework = new Directory("coursework");
		coursework.add(courseworkpdf);
		coursework.add(courseworkzip);

		Directory unittests = new Directory("unit tests");
		File test1 = new File("unit test 1", 56);
		unittests.add(test1);

		coursework.add(unittests);
		coursework.remove(courseworkzip);
		System.out.println(coursework.display("\t"));

		System.out.println(coursework.search("unit test 1").getName());
	}
}