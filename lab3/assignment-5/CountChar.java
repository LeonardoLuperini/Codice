import java.io.IOException;
import java.io.FileWriter;
import java.io.FileReader;
import java.util.Scanner;
import java.util.NoSuchElementException;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.ConcurrentHashMap;

public class CountChar implements Runnable {
	private static final int NCORES = Runtime.getRuntime().availableProcessors();
	private String pathToFile;
	private static ConcurrentHashMap<String, Integer> hashMap = new ConcurrentHashMap<String, Integer>(52);

	public static void main(String[] args) throws InterruptedException {
		String[] files = getFiles();

		for (char i = 65; i <= 90; i++)
			hashMap.put(String.valueOf(i), 0);
		for (char i = 97; i <= 122; i++)
			hashMap.put(String.valueOf(i), 0);
		
		BlockingQueue<Runnable> queue = new LinkedBlockingQueue<Runnable>();
		ThreadPoolExecutor tPool = 
			new ThreadPoolExecutor(1, NCORES, 1000, TimeUnit.MILLISECONDS, queue);
		CountChar[] ccArray = new CountChar[files.length];
		for (int i = 0; i < files.length; i++) {
			ccArray[i] = new CountChar(files[i]);
		}
		for (int i = 0; i < files.length; i++) {
			tPool.execute(ccArray[i]);
		}
		tPool.shutdown();
		tPool.awaitTermination(1, TimeUnit.DAYS);

		try (FileWriter fw = new FileWriter("./results.txt");) {
			hashMap.forEach(Long.MAX_VALUE, (k, v) -> {
				try {
					fw.write(k+","+v+"\n");
				} catch (IOException e) {
					e.printStackTrace();
			}});
			fw.close();
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
		System.out.println("Done! Check results.txt");
	}

	public void run() {
		try (FileReader file = new FileReader(pathToFile);) {
			String key;
			int value;
			int c = 'a';
			while (c != -1) {
				c = file.read();
				if ((c >= 65 && c <=90) || (c >= 97 && c <= 122)) {
					key = String.valueOf((char)c);
					synchronized (hashMap) {
						value = hashMap.get(key);
						hashMap.put(key, value+1);
					}
				}
			}
		}
		catch (Exception e){
			e.printStackTrace();
		}
	}

	public CountChar(String pathToFile) {
		this.pathToFile = pathToFile;
	}

	private static int getPosInt(Scanner in, String msg) {
		int i = -1;

		try {
			System.out.print(msg);
			i = in.nextInt();
			while (i < 0) {
				System.out.print("Please insert a positive number: ");
				i = in.nextInt();
			}
		} catch(NoSuchElementException e) {
			System.out.println("Please insert a positive number!");
			System.exit(1);
		}
		finally {
			in.nextLine();
		}

		return i;
	}

	private static String[] getFiles() {
		Scanner in = new Scanner(System.in);
		System.out.println("Do you want to pass files or try the test folder? (0:files, 1:test folder)");
		int res = in.nextInt();
		if (res == 0) {
			int c = getPosInt(in, "How many files do you want to check? ");
			if (c==0) System.exit(1);
			String[] files = new String[c];
			System.out.println("Please write the path to a file and press enter for each file: ");
			for(int i = 0; i < c; i++) {
				files[i] = in.nextLine();
			}
			in.close();
			return files;
		}
		else if (res == 1) {
			String[] files = {"./test/text_1.txt",
				"./test/text_2.txt",
				"./test/text_3.txt",
				"./test/text_4.txt",
				"./test/text_5.txt",
				"./test/text_6.txt",
				"./test/text_7.txt",
				"./test/text_8.txt",
				"./test/text_9.txt",
				"./test/text_10.txt",
				"./test/text_11.txt",
				"./test/text_12.txt",
				"./test/text_13.txt",
				"./test/text_14.txt",
				"./test/text_15.txt",
				"./test/text_16.txt",
				"./test/text_17.txt",
				"./test/text_18.txt",
				"./test/text_19.txt",
				"./test/text_20.txt",
				"./test/text_21.txt",
				"./test/text_22.txt",
				"./test/text_23.txt",
				"./test/text_24.txt",
				"./test/text_25.txt",
			};
			in.close();
			return files;
		}
		else {
			in.close();
			System.exit(1);
			String[] files = {};
			return files;
		}
	}
}
