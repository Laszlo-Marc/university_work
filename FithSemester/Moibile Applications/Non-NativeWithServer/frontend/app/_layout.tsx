import { Stack } from "expo-router";
import React from "react";
import { RepoProvider } from "../context/Context";
export default function RootLayout() {
  return (
    <RepoProvider>
      <Stack
        screenOptions={{
          headerShown: false,
          contentStyle: { backgroundColor: "#f5f5f5" },
        }}
      >
        <Stack.Screen name="index" options={{ title: "Expenses" }} />
        <Stack.Screen name="details" options={{ title: "Expense Details" }} />
        <Stack.Screen name="create" options={{ title: "Create Expense" }} />
        <Stack.Screen name="update" options={{ title: "Update Expense" }} />
      </Stack>
    </RepoProvider>
  );
}
