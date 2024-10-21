import java.util.Random;

public class TransferTask implements Runnable {
    private final Bank bank;
    private final int numOperations;
    private final Random random = new Random();

    public TransferTask(Bank bank, int numOperations) {
        this.bank = bank;
        this.numOperations = numOperations;
    }

    @Override
    public void run() {
        int numAccounts = bank.getNumAccounts();

        for (int i = 0; i < numOperations; i++) {
            int from = random.nextInt(numAccounts);
            int to;
            do {
                to = random.nextInt(numAccounts);
            } while (from == to);

            int amount = random.nextInt(100) + 1;
            bank.transfer(from, to, amount);
        }
    }
}