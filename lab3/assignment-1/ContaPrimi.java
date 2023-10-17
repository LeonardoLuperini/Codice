public class ContaPrimi implements Runnable {
	public boolean isPrime(int n) {
		if (n < 2) {
			return false;
		}
		if (n % 2 == 0 && n != 2) return false;

		for (int i = 3; i <= Math.sqrt(n); i = i + 2) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}

	public void run() {
		int counter = 0;
		for(int n = 2; n < 10_000_000; n++) {
			if (isPrime(n)) {
				counter++;
			}
		}
		System.out.println("Ho trovato " + counter + " numeri primi da 2 a 10_000_000");
	}
}
