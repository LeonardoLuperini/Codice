import java.util.Random;

public class Person implements Runnable {
	int taskTime = new Random().nextInt(); 
	int id;

	public Person(int id) {
		this.id = id;
		if (taskTime < 0 ) {
			taskTime = taskTime * -1;
		}
	}

	public void safePrintln(String s) {
		synchronized (System.out) {
			System.out.println(s);
		}
	}

	public void run() {	
		for (int i = 0; i < taskTime; i++);
		safePrintln("I'm n." + id + " and i've finished");
	}
}
