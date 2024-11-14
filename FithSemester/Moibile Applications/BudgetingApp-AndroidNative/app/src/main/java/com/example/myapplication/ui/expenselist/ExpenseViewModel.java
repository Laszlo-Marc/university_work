package com.example.myapplication.ui.expenselist;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;
import java.util.ArrayList;
import com.example.myapplication.data.Expense;
import com.example.myapplication.data.ExpenseManager;

public class ExpenseViewModel extends ViewModel {
    private final MutableLiveData<ArrayList<Expense>> expensesLiveData;

    public ExpenseViewModel() {
        expensesLiveData = new MutableLiveData<>(new ArrayList<>());
        loadInitialExpenses();  // Optional: load initial data
    }

    public LiveData<ArrayList<Expense>> getExpenses() {
        return expensesLiveData;
    }

    private void loadInitialExpenses() {
        ArrayList<Expense> initialExpenses = ExpenseManager.getInstance().getExpenses();
        expensesLiveData.getValue().addAll(initialExpenses);  // Modify existing list directly
        expensesLiveData.setValue(expensesLiveData.getValue());  // Notify observers of the change
    }

    public void addExpense(Expense expense) {
        ExpenseManager.getInstance().addExpense(expense); // Persist the change
        expensesLiveData.setValue(ExpenseManager.getInstance().getExpenses());
    }

    public void updateExpense(int position, Expense expense) {
        ExpenseManager.getInstance().updateExpense(position, expense); // Persist the change
        expensesLiveData.setValue(ExpenseManager.getInstance().getExpenses());
    }

    public void removeExpense(int position) {
        ExpenseManager.getInstance().removeExpense(position); // Persist the change
        expensesLiveData.setValue(ExpenseManager.getInstance().getExpenses());
    }
}

