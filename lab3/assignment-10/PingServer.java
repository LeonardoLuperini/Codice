import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Random;

public class PingServer {
	static int port;
	static Random random;

	public static void main(String[] args) throws Exception {
		getParams(args);

		InetAddress addr = InetAddress.getByName("localhost");
		DatagramSocket socket = new DatagramSocket(port, addr); 

		byte[] dataRecive = new byte[1024];

		try {
			while (true) {
				DatagramPacket request = new DatagramPacket(
											dataRecive, dataRecive.length);
				socket.receive(request);

				if (!gotAPacket()) continue;

				String got = new String(dataRecive);
				System.out.println("got: " + got);

				DatagramPacket response = new DatagramPacket(
										dataRecive, dataRecive.length,
										request.getAddress(), request.getPort());
				artificalRetard();
				socket.send(response);
			}
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
		finally {
			socket.close();
		}
	}

	public static void getParams(String[] args) {
		if (args.length != 2 && args.length != 1) {
			System.out.println("Usage: PingServer [port] [seed](opstonal)");
			System.exit(1);
		}

		try {
			port = Integer.parseInt(args[0]);
		} catch (NumberFormatException nfe) {
			System.out.println("ERR -arg 0");
			System.exit(1);
		}
		if (args.length == 2) {
			try {
				int seed = Integer.parseInt(args[1]);
				random = new Random(seed);
			} catch (NumberFormatException nfe) {
				System.out.println("ERR -arg 1");
				System.exit(1);
			}
		}
		else random = new Random(0);
	}

	public static int randInt(int min, int max) {
		return random.nextInt(max) + min;
	}

	public static boolean gotAPacket() {
		int n = randInt(1, 4);
		return (n != 1);
	}
	
	public static void artificalRetard() throws Exception {
		Thread.sleep(randInt(50, 2000));
	}
}
