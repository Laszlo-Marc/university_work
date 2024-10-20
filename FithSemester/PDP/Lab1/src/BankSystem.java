import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.atomic.AtomicInteger;

class BankAccount {
    private int balance;
    private List<String> log;
    private final Lock lock;

    public BankAccount(int initialBalance) {
        this.balance = initialBalance;
        this.log = new ArrayList<>();
        this.lock = new ReentrantLock();
    }

    public int getBalance() {
        return balance;
    }

    public void updateBalance(int amount) {
        this.balance += amount;
    }

    public void addLog(String entry) {
        this.log.add(entry);
    }

    public List<String> getLog() {
        return log;
    }

    public Lock getLock() {
        return lock;
    }
}

class Bank {
    private final List<BankAccount> accounts;
    private final AtomicInteger globalSerialNumber;

    public Bank(int numAccounts, int initialBalance) {
        accounts = new ArrayList<>();
        globalSerialNumber = new AtomicInteger(0);
        for (int i = 0; i < numAccounts; i++) {
            accounts.add(new BankAccount(initialBalance));
        }
    }

    public void transfer(int from, int to, int amount) {
        BankAccount accountFrom = accounts.get(from);
        BankAccount accountTo = accounts.get(to);

        Lock lock1 = accountFrom.getLock();
        Lock lock2 = accountTo.getLock();

        // Avoid deadlock by locking accounts in order
        if (from < to) {
            lock1.lock();
            lock2.lock();
        } else {
            lock2.lock();
            lock1.lock();
        }

        try {
            if (accountFrom.getBalance() >= amount) {
                accountFrom.updateBalance(-amount);
                accountTo.updateBalance(amount);

                int serial = globalSerialNumber.incrementAndGet();

                String logEntryFrom = "Transfer out: " + amount + " Serial: " + serial;
                String logEntryTo = "Transfer in: " + amount + " Serial: " + serial;

                accountFrom.addLog(logEntryFrom);
                accountTo.addLog(logEntryTo);

                System.out.println("Transferred " + amount + " from account " + from + " to account " + to);
            }
        } finally {
            lock1.unlock();
            lock2.unlock();
        }
    }

    public void checkConsistency() {
        int totalBalance = 0;
        boolean isLogConsistent = true;

        for (BankAccount account : accounts) {
            account.getLock().lock();
        }

        try {
            for (BankAccount account : accounts) {
                totalBalance += account.getBalance();

                // Verify log consistency
                List<String> log = account.getLog();
                for (String logEntry : log) {
                    if (!logEntry.contains("Serial")) {
                        isLogConsistent = false;
                        break;
                    }
                }
            }
            System.out.println("Consistency check: Total balance: " + totalBalance);
            if (isLogConsistent) {
                System.out.println("Log consistency check passed.");
            } else {
                System.out.println("Log consistency check failed.");
            }
        } finally {
            for (BankAccount account : accounts) {
                account.getLock().unlock();
            }
        }
    }

    public int getNumAccounts() {
        return accounts.size();
    }
}

class TransferTask implements Runnable {
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

public class BankSystem {
    public static void main(String[] args) {
        final int NUM_ACCOUNTS = 10;
        final int INITIAL_BALANCE = 1000;
        final int NUM_THREADS = 10;
        final int OPERATIONS_PER_THREAD = 10000;

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
