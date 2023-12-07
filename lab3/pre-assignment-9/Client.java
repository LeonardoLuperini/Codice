import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.channels.SocketChannel;

public class Client {
	public static final int DEFAULT_PORT = 4318;
	public static final String DEFAULT_ADDRESS = "0.0.0.0";
	public static void main(String[] args) {
		int port = getPort(args, 0);

		System.out.println("Listening for connection on port " + port);

		try {
			SocketAddress sAddr = new InetSocketAddress(DEFAULT_ADDRESS, port);
			SocketChannel client = SocketChannel.open(sAddr);
			ByteBuffer buffer = ByteBuffer.allocate(4);
			IntBuffer view = buffer.asIntBuffer();

			int actual;
			for (int expected = 0; ; expected++){
				client.read(buffer);
				actual = view.get();

				if (actual != expected) {
					System.err.println("Expected " + expected + " but got " + actual);
					break;
				}
				else System.out.println(actual);

				buffer.clear();
				view.rewind();
			}
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	public static int getPort(String[] args, int i) {
		int port;
		try { port = Integer.parseInt(args[1]); }
		catch (RuntimeException ex) {port = DEFAULT_PORT;}
		return port;
	}
}
