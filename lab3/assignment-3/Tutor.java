import java.util.Scanner;
import java.util.NoSuchElementException;

public class Tutor {
	public static void main(String[] args) {
		Lab lab = new Lab();

		Scanner in = new Scanner(System.in);
		int s = getPosInt(in, "How many students are there? ");
		int ts = getPosInt(in, "How many tesis students are there? ");
		int p = getPosInt(in, "How many prof. are there? ");
		in.close();

		Thread[] threads = new Thread[s+ts+p];
		for (int i = 0; i < s; i++) {
			threads[i] = new Thread(new Student(i, lab));
		}
		for (int i = s; i < s+ts; i++) {
			threads[i] = new Thread(new TesisStudent(i, lab));
		}
		for (int i = s+ts; i < s+ts+p; i++) {
			threads[i] = new Thread(new Professor(i, lab));
		}
		for (int i = 0; i < s+ts+p; i++) {
			threads[i].start();
		}
		for (int i = 0; i < s+ts+p; i++) {
			try {
				threads[i].join();
			}
			catch (InterruptedException e) {
				e.printStackTrace();
				System.exit(-1);
			}
		}
	}

	private static int getPosInt(Scanner in, String msg) {
		int i = -1;

		try {
			System.out.print(msg);
			i = in.nextInt();
			while (i < 0) {
				System.out.print("Please insert a positive number: ");
				i = in.nextInt();
			}
		} catch(NoSuchElementException e) {
			System.out.println("Please insert a positive number!");
			System.exit(1);
		}

		return i;


	}
}
