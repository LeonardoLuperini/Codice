import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

import java.util.Scanner;

public class Game implements Runnable {
	Socket sok;
	Player p;
	Monster m;
	Scanner in;
	PrintWriter out;

	public Game(Socket sok) {
		this.sok = sok;
		p = new Player();
		m = new Monster();
	}

	public void run() {
		try (Scanner in = new Scanner(sok.getInputStream());
			 PrintWriter out = new PrintWriter(sok.getOutputStream(), true);
		) {
			String msg;
			int m_dmg;
			int p_dmg;
			while (in.hasNextLine()) {
				msg = in.nextLine();
				if (msg.equals("close")) {out.println("close");break;}
				else if (msg.equals("p_hp")) out.println(p.getHp());
				else if (msg.equals("m_hp")) out.println(m.getHp());
				else if (msg.equals("p_potion_level")) out.println(p.getPotion_level());
				else if (msg.equals("attack")) {
					m_dmg = 5 + (int)(Math.random()*6);
					p_dmg = 1 + (int)(Math.random()*25);
					p.updateHp(-m_dmg);
					m.updateHp(-p_dmg);
					if (p.getHp() == 0) {
						out.println("lost");
						break;
					}
					else if (m.getHp() == 0) {
						out.println("win");
						m = new Monster();
					}
					else out.println("continue");
				}
				else if (msg.equals("potion")) {
					p.usePotion();
					out.println("potion");
				}
				else {
					System.out.println("Unkown message: " + msg);
					break;
				}
			}
		} 
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
		System.out.println("A game as ended!");
	}

}

class GameEnded extends Exception {}
