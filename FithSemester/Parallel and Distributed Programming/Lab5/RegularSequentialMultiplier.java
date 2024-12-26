public class RegularSequentialMultiplier implements PolynomialMultiplier {
    @Override
    public int[] multiply(int[] poly1, int[] poly2) {
        int n = poly1.length;
        int m = poly2.length;
        int[] result = new int[n + m - 1];


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result[i + j] += poly1[i] * poly2[j];
            }
        }

        return result;
    }
}
