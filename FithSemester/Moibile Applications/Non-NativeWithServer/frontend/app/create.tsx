import { useRouter } from "expo-router";
import React from "react";
import { View } from "react-native";
import ExpenseForm from "../components/ExpenseForm";
import TopBar from "../components/TopBar";
import { getCategoryIcon } from "../constants/categoryIcons";
import { useRepo } from "../context/Context";
export default function CreateExpenseScreen() {
  const router = useRouter();
  const { expenses, addExpense } = useRepo();

  const handleSubmit = async (data: any) => {
    const expense = {
      ...data,
      icon: getCategoryIcon(data.category),
    };
    await addExpense(expense);
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
