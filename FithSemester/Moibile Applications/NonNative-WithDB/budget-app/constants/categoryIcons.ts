export const categoryIconMap: { [key: string]: string } = {
  Food: "bowl-food",
  Transport: "car",
  Shopping: "basket-shopping",
  Entertainment: "gamepad",
  Other: "spinner",
  Utilities: "gear",
  Health: "hospital",
};

export const getCategoryIcon = (category: string): string => {
  return categoryIconMap[category] || "question"; // default icon when category is not found
};
