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

	public static void main(String[] args) {
		int port = getPort(args, 0);
		System.out.println("Listening for connection on port " + port);

		// Initializations / Opening Server
		ServerSocketChannel ssc;
		Selector selector;
		try {
			ssc = ServerSocketChannel.open();
			selector = Selector.open();
			InetSocketAddress address = new InetSocketAddress(port);

			ssc.bind(address);
			ssc.configureBlocking(false);
			ssc.register(selector, SelectionKey.OP_ACCEPT);
		} catch (IOException ioe) {
			ioe.printStackTrace();
			return;
		}

		// Declaraion for while
		Set<SelectionKey> readyKeys;
		SocketChannel socket;
		ByteBuffer buffer;
		String msg;

		// Server loop
		while (true) {
			try {
				selector.select();
				readyKeys = selector.selectedKeys();
				for(SelectionKey key : readyKeys) {
					readyKeys.remove(key);
					try {
						if (key.isAcceptable()) {
							socket = ssc.accept();
							System.out.println("Accepted connection from " + socket);

							socket.configureBlocking(false);
							socket.register(selector, SelectionKey.OP_READ);
						}
						else if (key.isReadable()) {
							System.out.println("Sono dentro!");
							socket = (SocketChannel) key.channel();
							buffer = ByteBuffer.allocate(1024);

							if(socket.read(buffer)==-1) {
								System.out.println("Sono stronzo");
								key.cancel();
								continue;
							}

							buffer.flip();
							System.out.println(buffer);

							byte[] data = new byte[buffer.remaining()];
							buffer.get(data);
							msg = new String(data);

							System.out.println("recived: " + msg);
							msg = "echoed by server: " + msg;
							ByteBuffer buffer2 = ByteBuffer.wrap(msg.getBytes());
							System.out.println(buffer2);

							socket.write(buffer2);
						}
					} catch (Exception e) {
						e.printStackTrace();
						try {
							key.channel().close();
						}
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
