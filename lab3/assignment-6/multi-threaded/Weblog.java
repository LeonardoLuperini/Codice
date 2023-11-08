import java.util.Scanner;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.io.File;
import java.io.FileNotFoundException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.List;
import java.util.ArrayList;

public class Weblog {
	public static void main(String[] args) throws InterruptedException {
		if (args.length != 1) {
			System.out.println("Please re-run the program like: Weblog [fileneme]");
			System.exit(1);
		}

		File file = new File(args[0]);
		try (Scanner scanner = new Scanner(file);) {
			BlockingQueue<Runnable> queue = new LinkedBlockingQueue<Runnable>();
			List<String> lineList = new ArrayList<String>();
			List<String> ipStringList = new ArrayList<String>();
			List<String> hostNameList = new ArrayList<String>();
			ThreadPoolExecutor tp = 
				new ThreadPoolExecutor(20, Integer.MAX_VALUE, 1000, TimeUnit.MILLISECONDS, queue);

			for (int i = 0; scanner.hasNextLine(); i++) {
				lineList.add(scanner.nextLine());
				ipStringList.add(lineList.get(i).substring(0, lineList.get(i).indexOf(' ')));
				hostNameList.add(new String());
				tp.execute(new TranslateIp(ipStringList.get(i), hostNameList, i));
			}
			tp.shutdown();
			tp.awaitTermination(1, TimeUnit.DAYS);

			for (int i = 0; i < ipStringList.size(); i++) {
				System.out.println(lineList.get(i).replaceAll(ipStringList.get(i), hostNameList.get(i)));
			}
		}
		catch (FileNotFoundException fnfe) {
			System.out.println("This file-path: "+ args[0] + "does not exeist!");
			System.exit(1);
		}
	}
}

class TranslateIp implements Runnable {
	String ipString;
	List<String> hostNameList;
	int i;
	TranslateIp(String ipString, List<String> hostNameList, int i) {
		this.ipString = ipString;
		this.hostNameList = hostNameList;
		this.i = i;
	}

	public void run() {
		try {
			InetAddress ip = InetAddress.getByName(ipString);
			hostNameList.set(i, ip.getHostName());
			if (hostNameList.get(i).compareTo(ipString) == 0) {
				hostNameList.set(i, "[HostName is the same as the ip]");
			}
		}
		catch (UnknownHostException uhe) {
			hostNameList.set(i, "[Unknown IPAddress]");
		}
	}
}
