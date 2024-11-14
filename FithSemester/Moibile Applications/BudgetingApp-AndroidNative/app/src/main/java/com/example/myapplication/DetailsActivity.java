package com.example.myapplication;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class DetailsActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.expense_details);

        String category = getIntent().getStringExtra("Category");
        String amount = getIntent().getStringExtra("Amount");
        String date = getIntent().getStringExtra("Date");
        String description = getIntent().getStringExtra("Description");
        String expenseAccount=getIntent().getStringExtra("Account");
        String merchant=getIntent().getStringExtra("Merchant");
        TextView categoryTextView = findViewById(R.id.categoryTextView);
        TextView amountTextView = findViewById(R.id.amountTextView);
        TextView dateTextView = findViewById(R.id.dateTextView);
        TextView descriptionTextView = findViewById(R.id.descriptionTextView);
        TextView expenseAccountTextView=findViewById(R.id.expenseAccountTextView);
        TextView merchantTextView=findViewById(R.id.merchantTextView);
        categoryTextView.setText(category);
        amountTextView.setText(amount);
        dateTextView.setText(date);
        descriptionTextView.setText(description);
        expenseAccountTextView.setText(expenseAccount);
        merchantTextView.setText(merchant);

        Button backButton = findViewById(R.id.backButton);
        backButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Finish the current activity and return to the previous one
                finish();
            }
        });
    }


}
