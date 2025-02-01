import TopBar from "@/components/TopBar";
import { getCategoryIcon } from "@/constants/categoryIcons";
import { useRepo } from "@/context/Context";
import { useRouter } from "expo-router";
import { useSearchParams } from "expo-router/build/hooks";
import React from "react";
import { Text, View } from "react-native";
import ExpenseForm from "../components/ExpenseForm";
export default function UpdateExpenseScreen() {
  const router = useRouter();
  const { expenses, updateExpense } = useRepo();
  const searchParams = useSearchParams();
  const id = searchParams.get("id");

  const expense = expenses.find((e) => e.id === Number(id));

  if (!expense) {
    return (
      <View>
        <Text>Expense not found.</Text>
      </View>
    );
  }

  const handleSubmit = (data: any) => {
    console.log("Updating expense", data);
    const updateData = {
      ...data,
      icon: getCategoryIcon(data.category),
    };
    updateExpense({ ...expense, ...updateData });
    router.push("/");
  };

  return (
    <View style={{ flex: 1 }}>
      <TopBar title="Update Expense" />
      <ExpenseForm defaultValues={expense} onSubmit={handleSubmit} />
    </View>
  );
}
