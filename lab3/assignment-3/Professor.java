public class Professor extends Applicant {
	Professor(int id, Lab lab) {
		super(id, lab);
	}

	public void run() {
		for(int i = 0; i < k; i++) {
			lab.getLab(this);
			try {
				Thread.sleep(time);
			}
			catch(InterruptedException e) {
				System.out.println("Sleep got interrupted!");
			}
			lab.leaveLab(this);
		}
	}
}
