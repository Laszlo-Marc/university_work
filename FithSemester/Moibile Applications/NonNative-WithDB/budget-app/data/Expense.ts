export default class Expense {
  constructor(
    public id: number,
    public category: string,
    public description: string,
    public amount: number,
    public date: Date,
    public transactionAccount: string,
    public merchant: string,
    public icon: string
  ) {}
}
