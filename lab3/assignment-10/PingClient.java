import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.text.DecimalFormat;

public class PingClient {
	static final int PKT_TO_SEND = 10;
	static InetAddress server;
	static int port;

	public static void main(String[] args) throws Exception {
		getParams(args);

		DatagramSocket socket = new DatagramSocket(0);

		byte[] dataSend = new byte[1024];
		byte[] dataRecive = new byte[1024];

		String msg;
		byte[] msgBytes;
		long t0, t1;
		long[] times = new long[PKT_TO_SEND];
		boolean skip;
		socket.setSoTimeout(4000);
		for (int i = 0; i < PKT_TO_SEND; i++) {
			skip = false;
			t0 = System.currentTimeMillis();
			msg = "PING " + i + " " + t0;

			msgBytes = msg.getBytes();
			for (int j = 0; j < msgBytes.length; j++) {
				dataSend[j] = msgBytes[j];
			}

			DatagramPacket request = new DatagramPacket(dataSend, dataSend.length, server, port);
			DatagramPacket result = new DatagramPacket(dataRecive, dataRecive.length);

			socket.send(request);
			try {
				socket.receive(result);
			} catch (SocketTimeoutException e) {
				skip = true;
			}
			t1 = System.currentTimeMillis();
			if (!skip) times[i] = t1-t0;
			else times[i] = -1;
			System.out.format(msg + " %-5s (ms)%n", rTT(t0, t1));
		}
		DecimalFormat myFormatter = new DecimalFormat("###.00");
		String avg = myFormatter.format(avg(times));
		long min = min(times);
		long max = max(times);
		int nRecived = gEZ(times);
		System.out.println("\t\t----PING Statistics----");
		System.out.format("%d packets transmitted, %d packets recived, %d%% packets loss\n", PKT_TO_SEND, nRecived, ((PKT_TO_SEND-nRecived)*100)/PKT_TO_SEND);
		System.out.format("round-trip (ms) min/avg/max = %d/%s/%d\n", min, avg, max);

		socket.close();
	}

	private static void getParams(String[] args) {
		if (args.length != 2) {
			System.out.println("Usage: PingClient [address name] [port]");
			System.exit(1);
		}

		try {
			server = InetAddress.getByName(args[0]);
		}
		catch (UnknownHostException uhe) {
			System.out.println("ERR -arg 0");
			System.exit(1);
		}
		try {
			port = Integer.parseInt(args[1]);
		} catch (NumberFormatException nfe) {
			System.out.println("ERR -arg 1");
			System.exit(1);
		}
	}

	private static String rTT(long t0, long t1) {
		if (t1 - t0 >= 2000) return "*";
		else return "" + (t1-t0);
	}
	private static float avg(long[] array) {
		float res = 0;
		for (int i = 0; i < array.length; i++) {
			res += array[i];
		}
		return (float)(((float)res)/((float)array.length));
	}

	private static long min(long[] array) {
		long m = Long.MAX_VALUE;
		for (int i = 0; i < array.length; i++) {
			if (array[i] >= 0 && array[i] < m) m = array[i]; 
		}
		return m;
	}

	private static long max(long[] array) {
		long m = Long.MIN_VALUE;
		for (int i = 0; i < array.length; i++) {
			if (array[i] >= 0 && array[i] > m) m = array[i]; 
		}
		return m;
	}
	
	// greater Equal Zero
	private static int gEZ(long[] array) {
		int c = 0;
		for (int i = 0; i < array.length; i++) {
			if (array[i] >= 0) c++;  
		}
		return c;
	}
}
