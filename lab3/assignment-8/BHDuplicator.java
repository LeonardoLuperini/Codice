import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Path;

public class BHDuplicator implements Duplicator {
	public void duplicate(Path in, Path out, int size) throws IOException {
		FileInputStream is = new FileInputStream(in.toString());
		FileOutputStream os = new FileOutputStream(out.toString());
		int bRead = 0;
		while ((bRead = is.read()) != -1) {
			os.write(bRead);
		}
	}
}
