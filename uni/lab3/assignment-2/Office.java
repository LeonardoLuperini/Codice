import java.util.concurrent.*;
import java.util.Scanner;
import java.util.NoSuchElementException;

public class Office {
	static final int N_COUNTERS = 4;
	static final int SR_CAPACITY = 4;
	public static void main(String[] args) throws InterruptedException {
		Scanner in = new Scanner(System.in);
		int nClients;
		try {
			System.out.println("How many clients are going to enter the office?");
			nClients = in.nextInt();
			while (nClients < 0) {
				System.out.print("Please insert a positive number: ");
				nClients = in.nextInt();
			}
		} catch(NoSuchElementException e) {
				System.out.println("Please insert a positive number!");
				return;
		}
		finally {
				in.close();
		}

		LinkedBlockingQueue<Person> firstRoom = new LinkedBlockingQueue<Person>();
		for (int i = 0; i < nClients; i++) {
			firstRoom.put(new Person(i+1));
		}

		BlockingQueue<Runnable> secondRoom = new ArrayBlockingQueue<Runnable>(SR_CAPACITY+1);
		ThreadPoolExecutor counters = new ThreadPoolExecutor(4, 4, 10, TimeUnit.SECONDS, secondRoom);
		counters.allowCoreThreadTimeOut(true);
		counters.prestartCoreThread();

		Person next = firstRoom.poll();
		boolean flag = false;
		while(firstRoom.size() > 0){
			if (flag) next = firstRoom.poll();
			try {
				counters.execute(next);
			}
			catch (RejectedExecutionException re) {
				Thread.sleep(500);
				flag = false;
				continue;
			} 
			flag = true;
		}
		counters.shutdown();
	}
}
