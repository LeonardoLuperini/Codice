import java.io.IOException;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class Client {
	public static void main(String[] args) {
		if (args.length != 2) {
			System.out.println("Error! When executing the client passa the ip and the port!");
			return;
		}
		try (Socket sok = new Socket(args[0], Integer.parseInt(args[1]));
			 Scanner kyb = new Scanner(System.in);
			 Scanner in = new Scanner(sok.getInputStream());
			 PrintWriter out = new PrintWriter(sok.getOutputStream(), true);
		) {
			
			String command;
			String reslut;
			boolean done;
			System.out.println("Welcome to Dungeon Adventures!");
			while (true) {
				command = enterTheDungeon(kyb, System.out);
				if (command.equals("no")) {
					out.println("close");
					throw new GameEnded();
				}
				done = false;
				while (!done) {
					System.out.println("Your HP is: " + askServ("p_hp", in, out));
					System.out.println("You have " + askServ("p_potion_level", in, out) + " ml of potion");
					System.out.println("Monster's HP: " + askServ("m_hp", in, out));
					System.out.println("What do you want to do?");
					System.out.println("Attack (attack), Drink a potion (potion) or exit the game (close)?");
					command = kyb.nextLine();
					while (!(command.equals("attack") ||
						   command.equals("potion") || 
						   command.equals("close"))) 
					{
						System.out.println("Insert a valid command!");
						System.out.println("What do you want to do?");
						System.out.println("Attack (attack), Drink a potion (potion) or exit the game (close)?");
						command = kyb.nextLine();
					}
					if (command.equals("attack")) System.out.println("CLING! ... CLANG!");
					else if (command.equals("potion")) System.out.println("SLURP!");

					reslut = askServ(command, in, out);
					if (reslut.equals("close")) throw new GameEnded();
					if (reslut.equals("win")) {
						System.out.println("CONGRATULATION! YOU DEFEATED THE MONSTER!");
						done = true;
						break;
					}
					if (reslut.equals("lost")) throw new GameEnded();
				}
				
			}
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
		catch (GameEnded ge) {
			System.out.println("You lost!");
			System.out.println("Game Ended!");
		}
	}

	private static String enterTheDungeon(Scanner kyb, PrintStream out) {
		String choice = "";
		boolean done = false;
		while (!done) {
			out.println("Do you want to challenge a monster? (yes) (no)");
			while (kyb.hasNextLine()) {
				choice = kyb.nextLine();
				if (!(choice.equals("yes") || choice.equals("no"))) {
					out.println("Error! Please write 'yes' or 'no'");
				}
				else {
					done = true;
					break;
				}
			}
		}
		return choice;
	}

	private static String askServ(String msg, Scanner in, PrintWriter out) {
		out.println(msg);
		return in.nextLine();
	}
}
