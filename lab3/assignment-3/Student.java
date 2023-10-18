public class Student extends Applicant {
	int i;
	Student(int id, Lab lab) {
		super(id, lab);
	}

	public void run() {
		for(int i = 0; i < k; i++) {
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
