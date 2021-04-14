package cz.vutbr.feec.utko.dsa.zapocet;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public enum VysledokTestu {
	POZITIVNY, NEGATIVNY;
	private static final List<VysledokTestu> VALUES =
    Collections.unmodifiableList(Arrays.asList(values()));
	private static final int SIZE = VALUES.size();
	private static final Random RANDOM = new Random();

	public static VysledokTestu randomVysledok()  {
		return VALUES.get(RANDOM.nextInt(SIZE));
	}

}

