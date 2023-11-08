import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.io.File;
import java.io.FileNotFoundException;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class Weblog {
	public static void main(String[] args) throws InterruptedException {
		if (args.length != 1) {
			System.out.println("Please re-run the program like: Weblog [fileneme]");
			System.exit(1);
		}

		File file = new File(args[0]);
		try (Scanner scanner = new Scanner(file);) {
			String line, ipString;
			ExecutorService tp = Executors.newFixedThreadPool(32);
			while (scanner.hasNextLine()) {
				line = scanner.nextLine();
				ipString = line.substring(0, line.indexOf(' '));
				tp.execute(new TranslateIp(ipString, line));
			}
			tp.shutdown();
		}
		catch (FileNotFoundException fnfe) {
			System.out.println("This file-path: "+ args[0] + "does not exeist!");
			System.exit(1);
		}
	}
}

class TranslateIp implements Runnable {
	String ipString, line, hostName;

	TranslateIp(String ipString, String line) {
		this.ipString = ipString;
		this.line = line;
	}

	public void run() {
		try {
			InetAddress ip = InetAddress.getByName(ipString);
			hostName = ip.getHostName();
			if (hostName.compareTo(ipString) == 0) {
				hostName = "[HostName is the same as the ip]";
			}
		}
		catch (UnknownHostException uhe) {
			hostName = "[Unknown IPAddress]";
		}
		
		System.out.println(line.replaceAll(ipString, hostName));
	}
}
