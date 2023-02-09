package cz.cvut.fel.pjv;

public class BruteForceAttacker extends Thief {
    private char[] pswdToBrute;
    private char[] characters;
    private int sizeOfPassword;

    @Override
    public void breakPassword(int sizeOfPassword) {
        pswdToBrute = new char[sizeOfPassword];
        this.sizeOfPassword = sizeOfPassword;
        characters = getCharacters();

        if (tryOpen(pswdToBrute)) {
            return;
        }

        try {
            for (int i = 0; i < characters.length; i++) {
                brute(1, characters[i]);
            }
        } catch (Exception e) {}
    }
    
    public void brute(int level, char character) throws Exception {
        pswdToBrute[level - 1] = character;

        if (level == sizeOfPassword) {
            boolean result = tryOpen(pswdToBrute);

            if (result == true) {
                throw new Exception();
            }

            return;
        }

        for (int i = 0; i < characters.length; i++) {
            brute(level + 1, characters[i]);
        }
    }
}
