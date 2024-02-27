from repo import TextRepo


class Service:
    def __init__(self):
        self.repo = TextRepo

    def add_sentence(self,sentence):
        self.repo.add_sentence(sentence)

