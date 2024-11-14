package com.example.myapplication.data;

public class Expense {
    // Attributes
     int id;
     int image;
     String category; // e.g., food, transport
     String amount;
     String date; // Consider using a Date type or LocalDate for date handling
     String description; // Optional field for additional details
     String expenseAccount; // Account from which the money was spent
     String transactionAccount; // Account with which the transaction has been made

    // Constructor
    public Expense(int id,int image, String transactionCategory, String amount, String date, String description, String expenseAccount, String transactionAccount) {
        this.id = id;
        this.image=image;
        this.category = transactionCategory;
        this.amount = amount;
        this.date = date;
        this.description = description;
        this.expenseAccount= expenseAccount;
        this.transactionAccount = transactionAccount;
    }

    // Getters and Setters
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getCategory() {
        return category;
    }


    public String getAmount() {
        return amount;
    }


    public String getDate() {
        return date;
    }



    public String getExpenseAccount() {
        return expenseAccount;
    }


    public int getImage() {
        return image;
    }


    public String getDescription() {
        return description;
    }

    public String getTransactionAccount() {
        return transactionAccount;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public void setAmount(String amount) {
        this.amount = amount;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setExpenseAccount(String expenseAccount) {
        this.expenseAccount = expenseAccount;
    }

    public void setTransactionAccount(String transactionAccount) {
        this.transactionAccount = transactionAccount;
    }

    public void setImage(int image) {
        this.image = image;
    }
}
