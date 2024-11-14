package com.example.myapplication.data;




import androidx.appcompat.app.AppCompatActivity;

import com.example.myapplication.R;
import com.example.myapplication.data.Expense;

import java.util.ArrayList;

public class ExpenseManager{
    private static ExpenseManager instance;
    private  ArrayList<Expense> expenses;


    private ExpenseManager() {
        expenses = setExpenseList();
    }

    public static ExpenseManager getInstance() {
        if (instance == null) {
            instance = new ExpenseManager();

        }
        return instance;
    }

    public ArrayList<Expense> getExpenses() {
        return expenses;
    }

    private ArrayList<Expense> setExpenseList(){
        ArrayList<Expense> expenses1 = new ArrayList<>();
        String[] dates = {  "10.09.2024", "25.02.2024", "13.03.2024", "05.04.2024", "21.05.2024", "07.06.2024", "14.07.2024", "29.08.2024", "12.09.2024", "03.10.2024"};
        String[] expenseAmounts = {"$200", "$100", "$70", "$150", "$200", "$200", "$200", "$200", "$200", "$200"};
        String[] expenseCategories = {"Shopping", "Health", "Food", "Transport", "Utilities", "Shopping", "Health", "Entertainment", "Transport", "Other"};
        String[] expenseDescriptions = {"Grocery shopping at SuperMart", "Monthly gym membership payment", "Dinner with friends at Italian Bistro", "Taxi fare to the airport", "Electricity bill for October", "New running shoes purchase", "Yearly health insurance premium", "Netflix subscription renewal", "Car fuel - gas station refill", "Gift for Mom birthday"};
        String[] expenseAccounts ={"Credit Card - Visa", "Debit Card - Main Bank Account", "Cash", "Wallet - PayPal", "Bank Account - Savings", "Bank Account - Savings", "Corporate Card", "Mobile Payment - Apple Pay", "Joint Account (with partner)", "Credit Card - MasterCard"};
        String[] expenseMerchants = {   "Mega Image", "18Gym", "Dautore Italian Bistro", "PrimaTaxi","Electrica", "SportVision", "ReginaMaria", "Netflix", "RomPetrol", "Obsentum"};
        int[] ExpenseIcons = {R.drawable.shopping,R.drawable.healthcategory,R.drawable.food,R.drawable.vehicles,R.drawable.utilities,R.drawable.shopping,R.drawable.healthcategory,R.drawable.entertainment,R.drawable.vehicles,R.drawable.others};
        for(int i = 0; i < dates.length; i++){
            Expense expense = new Expense(i,ExpenseIcons[i],expenseCategories[i],expenseAmounts[i],dates[i],expenseDescriptions[i],expenseAccounts[i], expenseMerchants[i]);
            expenses1.add(expense);
        }
        return expenses1;
    }
    public void addExpense(Expense expense) {
        expenses.add(expense);

    }

    public void updateExpense(int index, Expense expense) {
        if (index >= 0 && index < expenses.size()) {
            expenses.set(index, expense);

        }
    }

    public void removeExpense(int index) {
        if (index >= 0 && index < expenses.size()) {
            expenses.remove(index);

        }
    }
}
