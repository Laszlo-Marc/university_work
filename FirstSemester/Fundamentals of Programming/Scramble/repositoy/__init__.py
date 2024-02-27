import random


class Repository:
    def __init__(self,filename):
        self.filename=filename
        self.sentences=self.load()

    def load(self):
        sentences=[]
        with open(self.filename,"r") as f:
            for line in f:
                sentences.append(line.strip())
        return sentences


