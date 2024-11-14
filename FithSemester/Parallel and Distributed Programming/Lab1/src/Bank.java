import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;

public class Bank {
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
