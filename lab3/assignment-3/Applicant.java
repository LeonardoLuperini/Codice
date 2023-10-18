import java.util.concurrent.ThreadLocalRandom;

public abstract class Applicant implements Runnable {
	int id;
	int k;
	int time;
	Lab lab;

	Applicant(int id, Lab lab) {
		k = (ThreadLocalRandom.current().nextInt() % 5) + 1;
		if (k<0) k *= -1;
		time = (ThreadLocalRandom.current().nextInt() % 1000) + 500;
		if (time<0) time *= -1;
		this.lab = lab;
		this.id = id;
	}
}
