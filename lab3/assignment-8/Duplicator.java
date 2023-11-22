import java.io.IOException;
import java.nio.file.Path;

public interface Duplicator {
	public void duplicate(Path in, Path out) throws IOException;
}
