package com.example.myapplication;



import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.myapplication.data.Expense;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    ArrayList<Expense> expenses = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dasboard);

        ImageView expensesIV = findViewById(R.id.seeExpensesIV);
        expensesIV.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    Intent intent = new Intent(MainActivity.this, ListActivity.class);
                    startActivity(intent);
                } catch (Exception e) {
                    Log.e("MainActivity", "Error starting DashboardActivity", e);
                }
            }
        });
    }





}
