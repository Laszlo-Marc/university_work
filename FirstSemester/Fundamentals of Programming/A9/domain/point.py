class Point:
    def __init__(self, x, y):
        self.__x = x
        self.__y = y

    def get_x(self):
        """
        Getter method for the x coordinate
        :return: x
        """
        return self.__x

    def get_y(self):
        """
        Getter method for the y coordinate
        :return: y
        """
        return self.__y