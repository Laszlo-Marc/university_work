import TopBar from "@/components/TopBar";
import { getCategoryIcon } from "@/constants/categoryIcons";
import { useRepo } from "@/context/RepoContext";
import { useRouter } from "expo-router";
import React from "react";
import { View } from "react-native";
import ExpenseForm from "../components/ExpenseForm";
export default function CreateExpenseScreen() {
  const router = useRouter();
  const { expenses, addExpense } = useRepo();

  const handleSubmit = (data: any) => {
    const expense = {
      ...data,
      id: expenses.length + 1,
      icon: getCategoryIcon(data.category),
    };
    console.log("Calling addExpense", expense);
    addExpense(expense);
    router.push("/");
  };

  return (
    <View style={{ flex: 1 }}>
      <TopBar title="Create Expense" />
      <View style={{ flex: 1 }}>
        <ExpenseForm
          onSubmit={handleSubmit}
          defaultValues={{
            category: "",
            description: "",
            amount: 0,
            date: new Date(),
            transactionAccount: "",
            merchant: "",
          }}
        />
      </View>
    </View>
  );
}
