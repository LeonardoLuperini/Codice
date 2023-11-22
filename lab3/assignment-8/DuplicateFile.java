import java.io.IOException;
import java.nio.file.Path;

public class DuplicateFile {
	public static final int NMETHODS = 5;
	private int method = 0;
	Duplicator dup;

	public DuplicateFile() {
		dup = new FCDuplicator("indirect");
	}

	public long duplicate(Path in, Path out, int size) throws IOException {
		System.out.println("\nin: " + in.toString() + " out: " + out.toString());

		long t0 = System.currentTimeMillis();
		dup.duplicate(in, out, size);
		long t1 = System.currentTimeMillis();

		return t1 - t0;
	}

	public void setMethod(int i) {
		method = i;
		if (i == 0) {
			dup = new FCDuplicator("indirect");
		}
		else if (i == 1) {
			dup = new FCDuplicator("direct");
		}
		else if (i == 2) {
			dup = new FCTransfer();
		}
		else if (i == 3) {
			dup = new BBDuplicator();
		}
		else if (i == 4) {
			dup = new BHDuplicator();
		}
	}

	public String getCurrentMethodName() {
		if (method == 0) {
			return "FCDuplicator (indirect)";
		}
		else if (method == 1) {
			return "FCDuplicator (direct)";
		}
		else if (method == 2) {
			return "FCTransfer";
		}
		else if (method == 3) {
			return "BBDuplicator";
		}
		else if (method == 4) {
			return "BHDuplicator";
		}
		else return "ERROR";
	}
}
