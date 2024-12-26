public class Main {
    public static void main(String[] args) {
        int[] poly1 = new int[1000];
        int[] poly2 = new int[1000];
        for (int i = 0; i < 1000; i++) {
            poly1[i] = i + 1;
            poly2[i] = i + 1;
        }



        int numThreads = 4;
        // Regular Sequential
        PolynomialMultiplier regularSequential = new RegularSequentialMultiplier();
        long startTime = System.nanoTime();
        int[] resultRegularSequential = regularSequential.multiply(poly1, poly2);
        long endTime = System.nanoTime();
        System.out.println("Regular Sequential took: " + (endTime - startTime)/ 1_000_000 + " ms");

        // Regular Parallel
        PolynomialMultiplier regularParallel = new RegularParallelMultiplier(numThreads);
        startTime = System.nanoTime();
        int[] resultRegularParallel = regularParallel.multiply(poly1, poly2);
        endTime = System.nanoTime();
        System.out.println("Regular Parallel took: " + (endTime - startTime)/ 1_000_000 + " ms");

        // Karatsuba Sequential
        PolynomialMultiplier karatsubaSequential = new KaratsubaSequentialMultiplier();
        startTime = System.nanoTime();
        int[] resultKaratsubaSequential = karatsubaSequential.multiply(poly1, poly2);
        endTime = System.nanoTime();
        System.out.println("Karatsuba Sequential took: " + (endTime - startTime)/ 1_000_000 + " ms");

        // Karatsuba Parallel
        PolynomialMultiplier karatsubaParallel = new KaratsubaParallelMultiplier();
        startTime = System.nanoTime();
        int[] resultKaratsubaParallel = karatsubaParallel.multiply(poly1, poly2);
        endTime = System.nanoTime();
        System.out.println("Karatsuba Parallel took: " + (endTime - startTime)/ 1_000_000 + " ms");

        // Print results (just for verification)
        //System.out.println("Regular Sequential Result: ");
        //printPolynomial(resultRegularSequential);
        //System.out.println("Regular Parallel Result: ");
        //printPolynomial(resultRegularParallel);
        //System.out.println("Karatsuba Sequential Result: ");
        //printPolynomial(resultKaratsubaSequential);
        //System.out.println("Karatsuba Parallel Result: ");
        //printPolynomial(resultKaratsubaParallel);
    }

    // Helper method to print polynomial results
    private static void printPolynomial(int[] result) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < result.length; i++) {
            sb.append(result[i]);
            if (i < result.length - 1) sb.append("x^" + (result.length - 1 - i) + " + ");
        }
        System.out.println(sb.toString());
    }
}
