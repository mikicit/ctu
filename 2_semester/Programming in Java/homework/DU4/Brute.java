import java.util.Arrays;

public class Brute {
    private char[] pswdToBrute = new char[5];
    private int sizeOfPassword = 5;
    private char[] characters = {'a', 'b', 'c', 'd'};
    private char[] password = {'b', 'a', 'c', 'b', 'a'};

    public static void main(String[] args) {
        Brute brute = new Brute();
        brute.start();
    }

    public void start() {
        try {
            for (int i = 0; i < characters.length; i++) {
                brute(1, characters[i]);
            }
        } catch (Exception e) {

        }
    }

    public void brute(int level, char character) throws Exception {
        pswdToBrute[level - 1] = character;

        if (level == sizeOfPassword) {
            System.out.println(pswdToBrute);
            
            if (Arrays.equals(password, pswdToBrute)) {
                System.out.println("Done! " + String.valueOf(pswdToBrute));
                throw new Exception();
            }

            return;
        }

        for (int i = 0; i < characters.length; i++) {
            brute(level + 1, characters[i]);
        }
    }
}
