package com.example.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import com.example.myapplication.data.Expense;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CreateExpenseActivity extends AppCompatActivity {

    private EditText etAmount, etDate, etDescription, etMerchant;
    private Button btnSave;
    private TextView dropdownTrigger,accountDropdownTrigger;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_expense);
        etAmount = findViewById(R.id.etAmount);
        etDate = findViewById(R.id.etDate);
        etDescription = findViewById(R.id.etDescription);
        etMerchant = findViewById(R.id.etMerchant);
        btnSave = findViewById(R.id.btnSave);
        dropdownTrigger = findViewById(R.id.dropdownTrigger);
        accountDropdownTrigger=findViewById(R.id.accountDropdownTrigger);

        // Setup dropdown logic
        setupAccountDropdown();
        setupCategoryDropdown();

        Log.d("CreateExpenseActivity", "btnSave initialized: " + (btnSave != null));

        Button backButton = findViewById(R.id.backButton);
        backButton.setOnClickListener(v -> {
            Intent intent = new Intent(CreateExpenseActivity.this, ListActivity.class);
            startActivity(intent);
        });

        btnSave.setOnClickListener(v -> {
            if (validateInputs()) {
                Intent resultIntent = new Intent();
                resultIntent.putExtra("Category", dropdownTrigger.getText().toString());
                resultIntent.putExtra("Amount","$" + etAmount.getText().toString());
                resultIntent.putExtra("Date", etDate.getText().toString());
                resultIntent.putExtra("Description", etDescription.getText().toString());
                resultIntent.putExtra("Account", accountDropdownTrigger.getText().toString());
                resultIntent.putExtra("Merchant", etMerchant.getText().toString());
                setResult(RESULT_OK, resultIntent);
                finish();
            } else {
                Toast.makeText(CreateExpenseActivity.this, "Please fill all fields correctly.", Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void setupCategoryDropdown() {
        TextView dropdownTrigger = findViewById(R.id.dropdownTrigger);
        String[] options = {"Shopping", "Health", "Food", "Transport", "Utilities", "Shopping", "Health", "Entertainment", "Transport", "Other"};
        final AtomicInteger checkedItem = new AtomicInteger(-1);

        dropdownTrigger.setOnClickListener(v -> {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("Select Category")
                    .setSingleChoiceItems(options, checkedItem.get(), (dialog, which) -> {
                        checkedItem.set(which);
                    })
                    .setPositiveButton("OK", (dialog, id) -> {
                        if (checkedItem.get() != -1) {
                            dropdownTrigger.setText(options[checkedItem.get()]);
                        } else {
                            dropdownTrigger.setText("Select an category");
                        }
                    })
                    .setNegativeButton("Cancel", (dialog, id) -> dialog.dismiss());

            builder.create().show();
        });
    }

    private void setupAccountDropdown() {
        TextView accountDropdownTrigger = findViewById(R.id.accountDropdownTrigger); // Set this to your Account dropdown TextView

        String[] accounts ={"Credit Card - Visa", "Debit Card - Main Bank Account", "Cash", "Wallet - PayPal", "Bank Account - Savings", "Bank Account - Savings", "Corporate Card", "Mobile Payment - Apple Pay", "Joint Account (with partner)", "Credit Card - MasterCard"};
        final AtomicInteger checkedItem = new AtomicInteger(-1);

        accountDropdownTrigger.setOnClickListener(v -> {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("Select Account")
                    .setSingleChoiceItems(accounts, checkedItem.get(), (dialog, which) -> {
                        // Update the checkedItem when a user selects an option
                        checkedItem.set(which);  // Modify the value inside the AtomicInteger
                    })
                    .setPositiveButton("OK", (dialog, id) -> {
                        // Use the selected item (checkedItem) after user clicks "OK"
                        if (checkedItem.get() != -1) {
                            accountDropdownTrigger.setText(accounts[checkedItem.get()]); // Update the TextView with the selected option
                        } else {
                            accountDropdownTrigger.setText("Select an account");
                        }
                    })
                    .setNegativeButton("Cancel", (dialog, id) -> dialog.dismiss());

            builder.create().show();
        });
    }



    private boolean validateInputs() {
        // Regular expression to validate date in dd.MM.yyyy format
        String datePattern = "^([0-2][0-9]|(3)[0-1])\\.(0[1-9]|1[0-2])\\.(\\d{4})$";
        Pattern pattern = Pattern.compile(datePattern);
        Matcher matcher = pattern.matcher(etDate.getText().toString());

        // Check if all fields are not empty and the date is in the correct format
        return !dropdownTrigger.getText().toString().isEmpty() &&
                !etAmount.getText().toString().isEmpty() &&
                !etDate.getText().toString().isEmpty() &&
                matcher.matches() && // Date must match the dd.MM.yyyy format
                !etDescription.getText().toString().isEmpty() &&
                !accountDropdownTrigger.getText().toString().isEmpty() &&
                !etMerchant.getText().toString().isEmpty();
    }
}