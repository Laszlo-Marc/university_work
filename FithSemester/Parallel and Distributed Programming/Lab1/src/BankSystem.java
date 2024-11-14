import java.util.ArrayList;
import java.util.List;

public class BankSystem {
    public static void main(String[] args) {
        final int NUM_ACCOUNTS = 10;
        final int INITIAL_BALANCE = 1000;
        final int NUM_THREADS = 10;
        final int OPERATIONS_PER_THREAD = 100000;

        Bank bank = new Bank(NUM_ACCOUNTS, INITIAL_BALANCE);

        // Create and start threads
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < NUM_THREADS; i++) {
            Thread thread = new Thread(new TransferTask(bank, OPERATIONS_PER_THREAD));
            threads.add(thread);
            thread.start();
        }

        // Wait for all threads to complete
        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Perform final consistency check
        bank.checkConsistency();
    }
}