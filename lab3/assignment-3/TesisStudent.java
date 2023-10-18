import java.util.concurrent.ThreadLocalRandom;

public class TesisStudent extends Applicant {
	int i;

	TesisStudent(int id, Lab lab) {
		super(id, lab);
		i = ThreadLocalRandom.current().nextInt() % 20;
		if (i < 0) {
			i *= -1;
		}
	}

	public void run() {
		for(int j = 0; j < k; j++) {
			lab.getPC(this);
			try {
				Thread.sleep(time);
			}
			catch(InterruptedException e) {
				System.out.println("Sleep got interrupted!");
			}
			lab.leavePC(this);
		}
	}
}
