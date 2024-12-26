public class KaratsubaSequentialMultiplier implements PolynomialMultiplier {
    @Override
    public int[] multiply(int[] poly1, int[] poly2) {
        int n = poly1.length;
        int m = poly2.length;

        // Base case for recursion
        if (n == 1 || m == 1) {
            return new RegularSequentialMultiplier().multiply(poly1, poly2);
        }

        int halfSize = Math.min(n, m) / 2;

        // Split polynomials
        int[] A = new int[halfSize];
        int[] B = new int[n - halfSize];
        int[] C = new int[halfSize];
        int[] D = new int[m - halfSize];

        System.arraycopy(poly1, 0, A, 0, halfSize);
        System.arraycopy(poly1, halfSize, B, 0, n - halfSize);
        System.arraycopy(poly2, 0, C, 0, halfSize);
        System.arraycopy(poly2, halfSize, D, 0, m - halfSize);

        // Recursive multiplications
        int[] AC = multiply(A, C);
        int[] BD = multiply(B, D);
        int[] AplusB = addPolynomials(A, B);
        int[] CplusD = addPolynomials(C, D);
        int[] AplusB_CplusD = multiply(AplusB, CplusD);

        // Combine results
        int[] result = new int[n + m - 1];
        addToResult(result, AC, 0);
        addToResult(result, BD, 2 * halfSize);
        addToResult(result, subtractPolynomials(AplusB_CplusD, addPolynomials(AC, BD)), halfSize);

        return result;
    }

    private int[] addPolynomials(int[] poly1, int[] poly2) {
        int maxLength = Math.max(poly1.length, poly2.length);
        int[] result = new int[maxLength];
        for (int i = 0; i < poly1.length; i++) {
            result[i] += poly1[i];
        }
        for (int i = 0; i < poly2.length; i++) {
            result[i] += poly2[i];
        }
        return result;
    }

    private int[] subtractPolynomials(int[] poly1, int[] poly2) {
        int maxLength = Math.max(poly1.length, poly2.length);
        int[] result = new int[maxLength];
        for (int i = 0; i < poly1.length; i++) {
            result[i] += poly1[i];
        }
        for (int i = 0; i < poly2.length; i++) {
            result[i] -= poly2[i];
        }
        return result;
    }

    private void addToResult(int[] result, int[] toAdd, int offset) {
        for (int i = 0; i < toAdd.length; i++) {
            result[i + offset] += toAdd[i];
        }
    }
}
