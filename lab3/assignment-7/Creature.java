public abstract class Creature {
	protected int hp;

	void updateHp(int number) {
		if (hp + number >= 0)
			hp += number;
		else hp = 0;
	}

	int getHp() {
		return hp;
	}
}
