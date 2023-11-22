import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.nio.channels.WritableByteChannel;
import java.nio.file.Path;

public class FCDuplicator implements Duplicator {
	ByteBuffer bb;

	public FCDuplicator (ByteBuffer bb) {
		this.bb = bb;
	}

	public void duplicate(Path in, Path out) throws IOException {
		long t0 = System.currentTimeMillis();
		System.out.println("\nin: " + in.toString() + " out: " + out.toString());
		ReadableByteChannel src = Channels.newChannel(new FileInputStream(in.toString()));
		WritableByteChannel dest = Channels.newChannel(new FileOutputStream(out.toString()));

		while (src.read(bb) != -1) {
			bb.flip();
			while (bb.hasRemaining()) dest.write(bb);
			bb.compact();
		}

		dest.close();
		src.close();
		long t1 = System.currentTimeMillis();
		return t1 - t0;
	}
}
