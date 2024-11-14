package com.example.myapplication.ui.expenselist;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.myapplication.R;
import com.example.myapplication.RecyclerViewInterface;
import com.example.myapplication.data.Expense;

import java.util.ArrayList;

public class ExpenseAdapter extends RecyclerView.Adapter<ExpenseAdapter.MyViewHolder> {
    private final RecyclerViewInterface recyclerViewInterface;
    private Context context;
    private ArrayList<Expense> expenses;


    public ExpenseAdapter(RecyclerViewInterface recyclerViewInterface, Context context, ArrayList<Expense> expenses) {
        this.recyclerViewInterface = recyclerViewInterface;
        this.context = context;
        this.expenses = expenses;
    }
    @NonNull
    @Override
    public ExpenseAdapter.MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        //This is where we inflate the layout and give a look to our rows
        LayoutInflater inflater = LayoutInflater.from(context);
        View view = inflater.inflate(R.layout.recycler_view_row, parent, false);
        return new ExpenseAdapter.MyViewHolder(view, recyclerViewInterface);
    }

    @Override
    public void onBindViewHolder(@NonNull ExpenseAdapter.MyViewHolder holder, int position) {
        //assigning values to the views we created in the recycler_view_row layout file
        //based on the position of the recycler view


        holder.tvExpenseCategory.setText(expenses.get(position).getCategory());
        holder.tvExpenseDate.setText(expenses.get(position).getDate());
        holder.tvExpenseAmount.setText(String.valueOf(expenses.get(position).getAmount()));
        holder.tvPaymentMethod.setText(expenses.get(position).getExpenseAccount());
        holder.ivExpenseCategoryImage.setImageResource(expenses.get(position).getImage());
    }

    @Override
    public int getItemCount() {
        return expenses.size();
    }
    public void updateExpenseList(ArrayList<Expense> updatedExpenses) {
        this.expenses.clear();
        this.expenses.addAll(updatedExpenses);
        notifyDataSetChanged();  // Notifies the adapter that the data has changed
    }

    public static class MyViewHolder extends RecyclerView.ViewHolder {
        //all the views that we will add in each row
        ImageView ivExpenseCategoryImage;
        TextView tvExpenseCategory;
        TextView tvExpenseDate;
        TextView tvExpenseAmount;
        TextView tvPaymentMethod;

        public MyViewHolder(@NonNull View itemView,RecyclerViewInterface recyclerViewInterface) {
            super(itemView);
            //here we are initializing our views

            ivExpenseCategoryImage = itemView.findViewById(R.id.imageView);
            tvExpenseCategory = itemView.findViewById(R.id.tvExpenseCategory);
            tvExpenseDate = itemView.findViewById(R.id.tvExpenseDate);
            tvExpenseAmount = itemView.findViewById(R.id.tvExpenseAmount);
            tvPaymentMethod = itemView.findViewById(R.id.tvPaymentMethod);
            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if(recyclerViewInterface != null) {
                        int pos = getAdapterPosition();
                        if(pos != RecyclerView.NO_POSITION) {
                            recyclerViewInterface.onItemClick(pos);
                        }
                    }
                }
            });
        }
    }
}
