import java.io.File;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Tester {
	public static void main(String[] args) throws IOException {
		Path[] paths = listFiles("./test");
		DuplicateFile fileDuplicator = new DuplicateFile();
		Path out;
		long time;
		for (int i = 0; i < DuplicateFile.NMETHODS; i++) {
			for (int j = 0; j < paths.length; j++){
				out = Paths.get("./test/" + getTxtName(paths[j]) + "_copy.txt");
				time = fileDuplicator.duplicate(paths[j], out);
				System.out.println("time elapsed: " + time + "ms");
				
			}
		}
	}

	static String getTxtName(Path path) {
		int n = path.getNameCount() - 1;
		return path.getName(n).toString().replace(".txt", "");
	}

	static Path[] listFiles(String dir) {
		File[] files = new File(dir).listFiles();
		int c = 0;
		for (int i = 0; i < files.length; i++) {
			if (files[i].isFile()) c++;
		}
		Path[] paths = new Path[c];
		
		for (int i = 0; i < files.length; i++) {
			if (files[i].isFile()) paths[i] = files[i].toPath();
		}
		 return paths;
	}
}
