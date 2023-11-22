import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.file.Path;

public class FCTransfer implements Duplicator {
	public void duplicate(Path in, Path out, int size) throws IOException {
		RandomAccessFile fromFile = new RandomAccessFile(in.toString(), "rw");
		RandomAccessFile toFile = new RandomAccessFile(out.toString(), "rw");
		FileChannel fromChan = fromFile.getChannel();
		FileChannel toChan = toFile.getChannel();
		toChan.transferFrom(fromChan, 0, fromChan.size());
	}
}
