package cz.cvut.fel.pjv;

public class Main {
    public static void main(String[] args) {
        int[] values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        TreeImpl tree = new TreeImpl();
        tree.setTree(values);
        System.out.println(tree);
        System.out.println(tree.getRoot().getValue());
    }
}
