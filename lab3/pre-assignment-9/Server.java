import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Set;


public class Server {
	public static final int DEFAULT_PORT = 4318;
	public static final String DEFAULT_ADDRESS = "0.0.0.0";

	public static void main(String[] args) {
		int port = getPort(args, 0);
		System.out.println("Listening for connection on port " + port);

		// Initializations / Opening Server
		ServerSocketChannel ssc;
		Selector selector;
		try {
			ssc = ServerSocketChannel.open();
			selector = Selector.open();
			InetSocketAddress address = new InetSocketAddress(DEFAULT_ADDRESS, port);

			ssc.bind(address);
			ssc.configureBlocking(false);
			ssc.register(selector, SelectionKey.OP_ACCEPT);
		} catch (IOException ioe) {
			ioe.printStackTrace();
			return;
		}

		// Declaraion for while
		Set<SelectionKey> readyKeys;
		SelectionKey newKey;
		SocketChannel client;
		ByteBuffer output;
		int value;

		// Server loop
		while (true) {
			try {
				selector.select();
				readyKeys = selector.selectedKeys();
				for (SelectionKey key : readyKeys) {
					try {
						if (key.isAcceptable()) {
							client = ssc.accept();
							System.out.println("Accepted connection from " + client);

							client.configureBlocking(false);
							newKey = client.register(selector, SelectionKey.OP_WRITE);

							output = ByteBuffer.allocate(Integer.SIZE);
							output.putInt(0);
							output.flip();
							newKey.attach(output);
						}
						else if (key.isWritable()) {
							client = (SocketChannel) key.channel();
							output = (ByteBuffer) key.attachment();
							if (!output.hasRemaining()) {
								output.rewind();
								value = output.getInt();
								output.clear();
								output.putInt(value + 1);
								output.flip();
							}
							client.write(output);
						}
						readyKeys.remove(key);
					} catch (Exception e) {
						try { key.channel().close(); }
						catch (IOException ioe) { ioe.printStackTrace(); }
						return;
					}
				}
			} catch (IOException ioe) {
				ioe.printStackTrace();
				break;
			}
		}
	}

	public static int getPort(String[] args, int i) {
		int port;
		try {port = Integer.parseInt(args[i]);}
		catch (RuntimeException ex) {port = DEFAULT_PORT;}
		return port;
	}
}
