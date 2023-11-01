import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.nio.file.Files;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.io.IOException;
import java.util.concurrent.TimeUnit;
import java.util.Scanner;
import java.util.NoSuchElementException;

public class Main {
	private static final int NCORES = Runtime.getRuntime().availableProcessors();

	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		LinkedList<String> list = new LinkedList<String>();
		int c = getPosInt(in, "How many foledrs do you want to heve their files zipped?: ");
		System.out.println(c);
		in.nextLine();
		for (int i = 0; i < c; i++){
			list.add(in.nextLine());
		}
		in.close();
		list.forEach(x -> System.out.println(x));
		if (c == 0) return;

		Path[] paths = new Path[c];

		for (int i = 0; i < list.size(); i++) {
			paths[i] = Paths.get(list.get(i));
		}

		List<Path> srcs = listFiles(paths[0], ".gz");
		for (int i = 1; i < paths.length; i++) {
			srcs.addAll(listFiles(paths[i], ".gz"));
		}
		List<Path> zOut = changeExtension(srcs, ".gz");

		BlockingQueue<Runnable> queue = new LinkedBlockingQueue<Runnable>();

		ThreadPoolExecutor tPool = 
			new ThreadPoolExecutor(1, NCORES, 1000, TimeUnit.MILLISECONDS, queue);
		for (int i = 0; i < srcs.size(); i++) {
			tPool.execute(new Gzip(srcs.get(i), zOut.get(i)));
		}
		tPool.shutdown();
	}

	private static List<Path> listFiles(Path path, String ignExt) throws IOException {
		List<Path> res;

        try (Stream<Path> walk = Files.walk(path)) {
            res = walk.filter(Files::isRegularFile)
					.filter(p -> !(p.getFileName().toString().endsWith(ignExt)))
                    .collect(Collectors.toList());
        }
		return res;
	}

	// Does not handle things like .gitignore
	private static List<Path> changeExtension(List<Path> src, String newExt) {
		List<Path> temp = new ArrayList<Path>();
		String tStr;

		for (int i = 0; i < src.size(); i++) {
			tStr = src.get(i).toString();
			temp.add(
				Paths.get(tStr.replace(tStr.substring(tStr.lastIndexOf('.')), ".gz")));
		}

		return temp;
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

		return i;
	}
}
