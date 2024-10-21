import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BankAccount {
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
