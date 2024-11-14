package com.example.myapplication;
import android.content.Intent;

import android.graphics.Canvas;
import android.os.Bundle;
import com.example.myapplication.data.Expense;
import com.example.myapplication.data.ExpenseManager;
import com.example.myapplication.ui.expenselist.ExpenseAdapter;
import com.example.myapplication.ui.expenselist.ExpenseViewModel;


import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.ItemTouchHelper;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Parcelable;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class ListActivity extends AppCompatActivity implements RecyclerViewInterface{

    ArrayList<Expense> expenseArrayList = new ArrayList<>();
    ExpenseAdapter expenseAdapter;
    private ExpenseViewModel expenseViewModel;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //Recycler view setup
        RecyclerView recyclerView = findViewById(R.id.expenseList);
        expenseAdapter = new ExpenseAdapter(this, this, expenseArrayList);
        recyclerView.setAdapter(expenseAdapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        //ViewModel setup
        expenseViewModel = new ViewModelProvider(this).get(ExpenseViewModel.class);
        expenseViewModel.getExpenses().observe(this, new Observer<ArrayList<Expense>>() {
            @Override
            public void onChanged(ArrayList<Expense> expenses) {
                // Update the adapter when data changes
                expenseAdapter.updateExpenseList(expenses);
            }
        });

        // Button logic
        setupButtons();
        setupSwipeToDeleteAndEdit(recyclerView);


    }


    //function for setting upp the add button and back button
    private void setupButtons() {
        ImageButton addButton = findViewById(R.id.addButton);
        addButton.setOnClickListener(v -> {
            Intent intent = new Intent(this, CreateExpenseActivity.class);
            startActivityForResult(intent, 1);
        });

        ImageButton backButton = findViewById(R.id.backButton);
        backButton.setOnClickListener(v -> {
            Intent intent = new Intent(ListActivity.this, MainActivity.class);
            startActivity(intent);
        });
    }
    //Function for setting up the swipe to delete and edit functionality
    private void setupSwipeToDeleteAndEdit(RecyclerView recyclerView) {
        ItemTouchHelper.SimpleCallback itemTouchHelperCallback = new ItemTouchHelper.SimpleCallback(0, ItemTouchHelper.RIGHT) {
            @Override
            public boolean onMove(RecyclerView recyclerView, RecyclerView.ViewHolder viewHolder, RecyclerView.ViewHolder target) {
                // No move action needed
                return false;
            }

            @Override
            public void onSwiped(RecyclerView.ViewHolder viewHolder, int direction) {
                int position = viewHolder.getAdapterPosition();
                showEditDeleteDialog(position);
            }

            @Override
            public void onChildDraw(Canvas c, RecyclerView recyclerView, RecyclerView.ViewHolder viewHolder,
                                    float dX, float dY, int actionState, boolean isCurrentlyActive) {
                // Optionally add visual indicators for swiping
                super.onChildDraw(c, recyclerView, viewHolder, dX, dY, actionState, isCurrentlyActive);
            }
        };
        new ItemTouchHelper(itemTouchHelperCallback).attachToRecyclerView(recyclerView);
    }

    //Function for showing the edit and delete dialog
    private void showEditDeleteDialog(int position) {
        new AlertDialog.Builder(this)
                .setTitle("Choose Action")
                .setMessage("Would you like to edit or delete this expense?")
                .setPositiveButton("Edit", (dialog, which) -> showEditDialog(position))
                .setNegativeButton("Delete", (dialog, which) -> {
                    // Show confirmation dialog for delete
                    new AlertDialog.Builder(ListActivity.this)
                            .setTitle("Delete Expense")
                            .setMessage("Are you sure you want to delete this expense?")
                            .setPositiveButton("Yes", (dialog1, which1) -> {
                               expenseViewModel.removeExpense(position);
                            })
                            .setNegativeButton("No", (dialog1, which1) -> expenseAdapter.notifyItemChanged(position)) // Undo the swipe action
                            .show();
                })
                .setOnCancelListener(dialog -> expenseAdapter.notifyItemChanged(position)) // Reset swipe state if dialog is cancelled
                .show();
    }
    //Function for showing the edit dialog
    private void showEditDialog(int position) {
        Expense expense = expenseViewModel.getExpenses().getValue().get(position);
        String[] options = {"Shopping", "Health", "Food", "Transport", "Utilities", "Shopping", "Health", "Entertainment", "Transport", "Other"};

        // Create a custom layout for the edit dialog
        View dialogView = getLayoutInflater().inflate(R.layout.dialog_edit_expense, null);
        EditText categoryInput = dialogView.findViewById(R.id.editCategory);
        EditText amountInput = dialogView.findViewById(R.id.editAmount);
        EditText dateInput = dialogView.findViewById(R.id.editDate);
        EditText descriptionInput = dialogView.findViewById(R.id.editDescription);
        EditText accountInput = dialogView.findViewById(R.id.editAccount);
        EditText merchantInput = dialogView.findViewById(R.id.editMerchant);


        categoryInput.setText(expense.getCategory());
        amountInput.setText(expense.getAmount());
        dateInput.setText(expense.getDate());
        descriptionInput.setText(expense.getDescription());
        accountInput.setText(expense.getExpenseAccount());
        merchantInput.setText(expense.getTransactionAccount());

        new AlertDialog.Builder(this)
                .setTitle("Edit Expense")
                .setView(dialogView)
                .setPositiveButton("Save", (dialog, which) -> {
                    // Validate input before updating the expense
                    String datePattern = "^([0-2][0-9]|(3)[0-1])\\.(0[1-9]|1[0-2])\\.(\\d{4})$";
                    Pattern pattern = Pattern.compile(datePattern);
                    Matcher matcher = pattern.matcher(dateInput.getText().toString());
                    String category = categoryInput.getText().toString();
                    String amount;
                    if(amountInput.getText().toString().charAt(0) == '$' && amountInput.getText().toString().length() > 1){
                        amount =amountInput.getText().toString();
                    }else{
                        amount = "$" + amountInput.getText().toString();
                    }
                    String date = dateInput.getText().toString();
                    String description = descriptionInput.getText().toString();
                    String account = accountInput.getText().toString();
                    String merchant = merchantInput.getText().toString();

                    // Perform validation
                    if (category.isEmpty() || amount.isEmpty() || date.isEmpty() || account.isEmpty()) {
                        Toast.makeText(ListActivity.this, "Please fill all required fields.", Toast.LENGTH_SHORT).show();
                        return;
                    }
                    if (Arrays.asList(options).contains(category) && !category.isEmpty() && !amount.isEmpty() && !date.isEmpty() && !account.isEmpty() && matcher.matches()) {
                        // Category is valid, perform actions
                        System.out.println("Category is valid");
                        expense.setImage(selectIcon(category));
                        expense.setCategory(category);
                        expense.setAmount(amount);
                        expense.setDate(date);
                        expense.setDescription(description);
                        expense.setExpenseAccount(account);
                        expense.setTransactionAccount(merchant);
                        expenseViewModel.updateExpense(position, expense);
                    } else {
                        // Category is invalid
                        Toast.makeText(ListActivity.this, "Please enter all information correctly. Category or date might be invalid!", Toast.LENGTH_SHORT).show();
                    }


                    // Update the expense in ViewModel

                })
                .setNegativeButton("Cancel", (dialog, which) -> expenseAdapter.notifyItemChanged(position)) // Reset swipe state
                .show();
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == 1 && resultCode == RESULT_OK && data != null) {
            String category = data.getStringExtra("Category");
            String amount = data.getStringExtra("Amount");
            String date = data.getStringExtra("Date");
            String description = data.getStringExtra("Description");
            String account = data.getStringExtra("Account");
            String merchant = data.getStringExtra("Merchant");
            if (category != null && amount != null && date != null && description != null && account != null && merchant != null) {

                Expense expense = new Expense(expenseArrayList.size() + 1, selectIcon(category), category, amount, date, description, account, merchant);
                expenseViewModel.addExpense(expense);
            }
        }
    }

    private int selectIcon(String category){
        switch (category) {
            case "Food":
                return R.drawable.food;
            case "Transport":
                return R.drawable.vehicles;
            case "Shopping":
                return R.drawable.shopping;
            case "Entertainment":
                return R.drawable.entertainment;
            case "Health":
                return R.drawable.healthcategory;
            case "Utilities":
                return R.drawable.utilities;
            default:
                return R.drawable.others;
        }
    }


    @Override
    public void onItemClick(int position) {
        Intent intent = new Intent(this, DetailsActivity.class);
        intent.putExtra("Category", expenseArrayList.get(position).getCategory());
        intent.putExtra("Amount", expenseArrayList.get(position).getAmount());
        intent.putExtra("Date", expenseArrayList.get(position).getDate());
        intent.putExtra("Description", expenseArrayList.get(position).getDescription());
        intent.putExtra("Account", expenseArrayList.get(position).getExpenseAccount());
        intent.putExtra("Merchant", expenseArrayList.get(position).getTransactionAccount());
        startActivity(intent);
    }


}