import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Path;

public class DuplicateFile {
	public static final int NMETHODS = 2;
	private static final int BBDIM = 1024;
	Duplicator dup;

	public DuplicateFile() {
		dup = new FCDuplicator(ByteBuffer.allocate(1024));
	}

	public long duplicate(Path in, Path out) throws IOException {
		return dup.duplicate(in, out);
	}

	public void setMethod(int i) {
		if (i == 0) {
			dup = new FCDuplicator(ByteBuffer.allocate(BBDIM));
		}
		else if (i == 1) {
			dup = new FCDuplicator(ByteBuffer.allocateDirect(BBDIM));
		}
	}
}
