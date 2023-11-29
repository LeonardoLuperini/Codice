import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

public class Client {
	public static final int DEFAULT_PORT = 4318;

	public static void main(String[] args) {
		int port = getPort(args, 0);
		System.out.println("Listening for connection on port " + port);

		Scanner scanner = new Scanner(System.in);
		SocketAddress sAddr = new InetSocketAddress(port);
		ByteBuffer buffer = ByteBuffer.allocate(1024);

		
		SocketChannel socket = openSocket(sAddr);
		
		try {

			while (true) {
				getMessage(scanner, buffer);
				socket.write(buffer);
				buffer.clear();

				socket.read(buffer);

				buffer.flip();
				byte[] data = new byte[buffer.remaining()];
				buffer.get(data);
				System.out.println(new String(data));
				buffer.clear();
			}
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
		finally {
			scanner.close();
		}

	}

	public static int getPort(String[] args, int i) {
		int port;
		try { port = Integer.parseInt(args[1]); }
		catch (RuntimeException ex) {port = DEFAULT_PORT;}
		return port;
	}

	public static void getMessage(Scanner scanner, ByteBuffer buffer) {
		String msg = "";

		if (scanner.hasNextLine()) msg = scanner.nextLine();

		buffer.put(msg.getBytes());
		buffer.position(0);
		buffer.limit(msg.length());
	}

	public static SocketChannel openSocket(SocketAddress sAddr) {
		for (int i = 0; i < 3; i++) {
			try {
				return SocketChannel.open(sAddr);
			} catch (IOException ioe) {
				try {Thread.sleep(1000);}
				catch (InterruptedException ie){}
			}
		}
		System.exit(1);
		return null;
	}
}
