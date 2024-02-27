class Expense:
    def __init__(self,day,type,amount):
        self.__day=day
        self.__amount=amount
        self.__type=type

    def get_day(self):
        return self.__day
    def get_amount(self):
        return self.__amount
    def get_type(self):
        return self.__type
