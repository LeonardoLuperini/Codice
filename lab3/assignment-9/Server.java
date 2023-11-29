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
							SelectionKey key2 = socket.register(selector, SelectionKey.OP_READ);
							key2.attach(ByteBuffer.allocate(1024));
						}
						else if (key.isReadable()) {
							socket = (SocketChannel) key.channel();
							buffer = (ByteBuffer) key.attachment();

							if(socket.read(buffer)==-1) {
								key.cancel();
								continue;
							}

							buffer.flip();

							byte[] data = new byte[buffer.remaining()];
							buffer.get(data);
							msg = new String(data);
							buffer.clear();

							msg = "echoed by server: " + msg;
							buffer.put(msg.getBytes());
							buffer.position(0);
							buffer.limit(msg.length());

							socket.write(buffer);
							buffer.clear();
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
