import java.nio.file.Path;
import java.util.zip.GZIPOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class Gzip implements Runnable {
	Path srcPath;
	Path tarPath;

	Gzip(Path srcPath, Path tarPath) {
		this.srcPath = srcPath;
		this.tarPath = tarPath;
	}

	public void run() {
		try (
			GZIPOutputStream outFile = new GZIPOutputStream(
				new FileOutputStream(tarPath.toFile()));
			FileInputStream inFile = new FileInputStream(srcPath.toFile())) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = inFile.read(buffer)) > 0) {
                outFile.write(buffer, 0, len);
            }
		}
		catch(IOException ioe) {
			ioe.printStackTrace();
		}
	}
}
