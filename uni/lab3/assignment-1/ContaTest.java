import java.util.Scanner;
import java.util.NoSuchElementException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ContaTest {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int nThreads, nTask;
		try {
			System.out.println("How many task you want to execute?");
			nTask = in.nextInt();
			while (nTask < 0) {
				System.out.print("Please insert a positive number: ");
				nTask = in.nextInt();
			}
			System.out.println("How many thread you want to use?");
			nThreads = in.nextInt();
			while (nThreads < 0) {
				System.out.print("Please insert a positive number: ");
				nThreads = in.nextInt();
			}
			in.close();
		} catch(NoSuchElementException e) {
				System.out.println("Please insert a positive number!");
				in.close();
				return;
		}

		ExecutorService service = Executors.newFixedThreadPool(nThreads);
		for (int i = 0; i < nTask; i++) {
			service.execute(new ContaPrimi());
		}
		service.shutdown();
		return;
	}
}
