public class Player extends Creature {
	private int potion_level;

	public Player () {
		hp = 40 + (int)(Math.random() * 11);
		potion_level = 40 + (int)(Math.random() * 11);
	}

	void usePotion() {
		int drinked;
		if (potion_level < 5) {
			drinked = potion_level;
		}
		else {
			drinked = 5 + (int)(Math.random()*(potion_level-5));
		}

		potion_level -= drinked;
		this.updateHp(drinked);
	}

	int getPotion_level() {
		return potion_level;
	}
}
