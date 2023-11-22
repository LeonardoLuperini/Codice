import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Path;


public class BBDuplicator implements Duplicator {
	public void duplicate(Path in, Path out, int size) throws IOException {
		BufferedInputStream bis = new BufferedInputStream(new FileInputStream(in.toString()), size); 
		BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(out.toString()), size); 
		int bRead = 0;
		while ((bRead = bis.read()) != -1) {
			bos.write(bRead);
		}
	}
}
