import java.io.IOException;
import java.net.ServerSocket;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.ThreadPoolExecutor;

public class Server {
	public static void main(String[] argv) {
		ThreadPoolExecutor pool = new ThreadPoolExecutor(1, Integer.MAX_VALUE, 1000, TimeUnit.MILLISECONDS, new LinkedBlockingQueue<Runnable>());
		try (ServerSocket listener = new ServerSocket(4318);) {
			System.out.println("Server started");
			System.out.println("\tip: " + listener.getInetAddress());
			System.out.println("\tport: " + listener.getLocalPort());
			while (true) {
				pool.execute(new Game(listener.accept()));
			}
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
		finally {
			pool.shutdown();
		}
	}
}
