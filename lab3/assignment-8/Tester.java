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
		int[] sizes = {64, 1024, 4096};
		for (int i = 0; i < DuplicateFile.NMETHODS; i++) {
			fileDuplicator.setMethod(i);
			System.out.println("Now you are using " + fileDuplicator.getCurrentMethodName());
			for (int j = 0; j < sizes.length; j++){
				if (i != 2 && i != 4) {
					System.out.println("\n--buffer size: " + sizes[j]);
				}
				for (int k = 0; k < paths.length; k++){
					out = Paths.get("./test/" + getTxtName(paths[k]) + "_copy.txt");
					time = fileDuplicator.duplicate(paths[k], out, sizes[j]);
					System.out.println("time elapsed: " + time + "ms");
					
				}
				if (i == 2 || i == 4) break;
			}
			System.out.print("\n\n");
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


/* 
Now you are using FCDuplicator (indirect)

--buffer size: 64

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 1050ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 344ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 2ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 11ms

--buffer size: 1024

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 116ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 36ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 0ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 1ms

--buffer size: 4096

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 54ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 19ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 1ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 1ms


Now you are using FCDuplicator (direct)

--buffer size: 64

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 993ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 331ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 1ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 11ms

--buffer size: 1024

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 94ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 32ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 0ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 1ms

--buffer size: 4096

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 48ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 16ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 0ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 1ms


Now you are using FCTransfer

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 14ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 4ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 1ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 0ms


Now you are using BBDuplicator

--buffer size: 64

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 1661ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 371ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 1ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 10ms

--buffer size: 1024

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 126ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 42ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 0ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 1ms

--buffer size: 4096

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 82ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 27ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 0ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 1ms


Now you are using BHDuplicator

in: ./test/biblex3.txt out: ./test/biblex3_copy.txt
time elapsed: 55487ms

in: ./test/bible.txt out: ./test/bible_copy.txt
time elapsed: 18458ms

in: ./test/bible14k.txt out: ./test/bible14k_copy.txt
time elapsed: 59ms

in: ./test/bible130k.txt out: ./test/bible130k_copy.txt
time elapsed: 570ms

Questo era l'output del progrmma sul mio pc come può vedere 
buffer più grossi velocizzano la copia e il metodo più veloce è stato il 3
cioè quello che fa utilizzo del transferTo
*/
