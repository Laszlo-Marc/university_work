import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ScalarProduct {

    private static final int[] vectorA = {1, 2, 3, 4, 5, 6, 7};
    private static final int[] vectorB = {4, 5, 6, 7, 8, 9, 10};

    private static final Lock lock = new ReentrantLock();
    private static final Condition productAvailable = lock.newCondition();
    private static int product = 0;
    private static boolean productReady = false;
    private static int scalarProduct = 0;
    private static final int length = Math.min(vectorA.length, vectorB.length);

    public static void main(String[] args) {
        // Threads to calculate the scalar product concurrently
        Thread producer = new Thread(new Producer());
        Thread consumer = new Thread(new Consumer());

        producer.start();
        consumer.start();

        try {
            producer.join();
            consumer.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("The scalar product is: " + scalarProduct);
    }

    // Producer class calculates the element-wise product of vectorA[i] and vectorB[i]
    static class Producer implements Runnable {
        @Override
        public void run() {
            for (int i = 0; i < length; i++) {
                lock.lock();
                try {
                    product = vectorA[i] * vectorB[i]; // Calculate product of the current pair
                    System.out.println("Term 1: " + vectorA[i] + "\t" + "Term 2: " + vectorB[i] + "\t" + "Product: " + product);
                    productReady = true; // Flag to indicate the product is ready
                    System.out.println("Signaling consumer...");
                    productAvailable.signal(); // Signal the consumer to process the product

                } finally {
                    lock.unlock();
                }

                // Producer waits for consumer to consume the product before producing the next one
                lock.lock();
                try {
                    while (productReady) { // Wait for the consumer to reset productReady
                        System.out.println("Awaiting consumer...");
                        productAvailable.await(); // Await the consumer's signal
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                } finally {
                    lock.unlock();
                }
            }
        }
    }

    // Consumer class waits for the producer's signal, then adds the product to scalarProduct
    static class Consumer implements Runnable {
        @Override
        public void run() {
            for (int i = 0; i < length; i++) {
                lock.lock(); // Lock access to shared resources
                try {
                    while (!productReady) { // Wait until the producer has a new product ready
                        productAvailable.await(); // Await producer's signal
                    }
                    scalarProduct += product; // Add the product to the scalar product sum
                    System.out.println("Scalar product: " + scalarProduct);
                    productReady = false; // Reset flag for the producer
                    System.out.println("Signaling product...");
                    productAvailable.signal(); // Signal the producer to proceed with the next product
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                } finally {
                    lock.unlock();
                }
            }
        }
    }
}
