public class Lab {
	private boolean isProfWaiting = false;
	private boolean[] PCs = new boolean[20];

	Lab() {
		for (int i = 0; i < PCs.length; i++) {
			PCs[i] = true;
		}
	}

	public synchronized void getPC(Student s) {
		while (isProfWaiting || !isThereFree()) {
			try {
				System.out.println("Student-"+s.id+", waiting");
				System.out.flush();
				wait();
			}
			catch (InterruptedException e) {
				System.out.println("Wait got interrupted!");
			}
		}

		try {
			s.i = whichIsFree();
		}
		catch (ElementDoesNotExist e) {
			e.printStackTrace();
		}

		PCs[s.i] = false;
		System.out.println("Student-"+s.id+", working");
		System.out.flush();

	}

	public synchronized void leavePC(Student s) {
		System.out.println("Student-"+s.id+", finished");
		System.out.flush();
		PCs[s.i] = true;
		notifyAll();
	}

	public synchronized void getPC(TesisStudent ts) {
		while (isProfWaiting || !PCs[ts.i]) {
			try {
				System.out.println("Tesis student-"+ts.id+", waiting");
				System.out.flush();
				wait();
			}
			catch (InterruptedException e) {
				System.out.println("Wait got interrupted!");
			}
		}

		PCs[ts.i] = false;
		System.out.println("Tesis student-"+ts.id+", working");
		System.out.flush();
	}

	public synchronized void leavePC(TesisStudent ts) {
		System.out.println("Student-"+ts.id+", finished");
		System.out.flush();
		PCs[ts.i] = true;
		notifyAll();
	}

	public synchronized void getLab(Professor prof) {
		while (isProfWaiting) {
			try {
				System.out.println("Prof-"+prof.id+", waiting another prof");
				System.out.flush();
				wait();
			}
			catch (InterruptedException e) {
				System.out.println("Wait got interrupted!");
			}
		}
		while(!isAllFree()) {
			isProfWaiting = true;
			try {
				System.out.println("Prof-"+prof.id+", waiting student or tesis student");
				System.out.flush();
				wait();
			}
			catch (InterruptedException e) {
				System.out.println("Wait got interrupted!");
			}
		}
		isProfWaiting = false;

		occupyAll();
		System.out.println("Prof-"+prof.id+", working");
		System.out.flush();
	}

	public synchronized void leaveLab(Professor prof) {
		freeAll();
		System.out.println("Prof-"+prof.id+", finished");
		System.out.flush();
		notifyAll();

	}

	private void occupyAll() {
			for (int i = 0; i < PCs.length; i++) {
				PCs[i] = false;
			}
	}

	private void freeAll() {
			for (int i = 0; i < PCs.length; i++) {
				PCs[i] = true;
			}
	}

	private boolean isAllFree() {
		for (boolean i:PCs) {
			if (!i) return false;
		}
		return true;
	}

	private boolean isThereFree() {
		for (boolean i:PCs) {
			if (i) return true;
		}
		return false;
	}

	private int whichIsFree() throws ElementDoesNotExist {
		for (int i = 0; i < PCs.length; i++) {
			if (PCs[i]) return i;
		}
		throw new ElementDoesNotExist();
	}
}

class ElementDoesNotExist extends Exception {}
