import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.nio.channels.WritableByteChannel;
import java.nio.file.Path;

public class FCDuplicator implements Duplicator {
	String mode;
	ByteBuffer bb;

	public FCDuplicator (String mode) {
		this.mode = mode;
	}

	public void duplicate(Path in, Path out, int size) throws IOException {
		if (mode.equals("direct")) bb = ByteBuffer.allocateDirect(size);
		else bb = ByteBuffer.allocate(size);
		ReadableByteChannel src = Channels.newChannel(new FileInputStream(in.toString()));
		WritableByteChannel dest = Channels.newChannel(new FileOutputStream(out.toString()));

		while (src.read(bb) != -1) {
			bb.flip();
			while (bb.hasRemaining()) dest.write(bb);
			bb.compact();
		}

		dest.close();
		src.close();
	}
}
