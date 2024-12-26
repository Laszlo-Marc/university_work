import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class RegularParallelMultiplier implements PolynomialMultiplier {
    private final int numThreads;

    public RegularParallelMultiplier(int numThreads) {
        this.numThreads = numThreads;
    }

    @Override
    public int[] multiply(int[] poly1, int[] poly2) {
        int n = poly1.length;
        int m = poly2.length;
        int[] result = new int[n + m - 1];

        ExecutorService executor = Executors.newFixedThreadPool(numThreads);

        for (int i = 0; i < n; i++) {
            int finalI = i;
            executor.submit(() -> {
                for (int j = 0; j < m; j++) {
                    synchronized (result) {
                        result[finalI + j] += poly1[finalI] * poly2[j];
                    }
                }
            });
        }

        executor.shutdown();
        while (!executor.isTerminated()) {
            // Wait for all threads to finish
        }

        return result;
    }
}