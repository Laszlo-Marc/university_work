import random


class TextRepo:
    def __init__(self, filename):
        self.filename = filename
        self.sentences = []

    def add_initial(self):
        sentences = ["anna has apples","patricia has spears", "cars are fast", "planes are quick"]
        for sentence in sentences:
            self.add_sentence(sentence)

    def load_sentences(self):
        sentences = []
        try:
            with open(self.filename, 'r') as f:
                for line in f:
                    sentence = line.strip()
                    sentences.append(sentence)
            return sentences
        except FileNotFoundError:
            return []

    def add_sentence(self, sentence):
        self.sentences.append(sentence)
        self.save_sentences()


    def save_sentences(self):
        with open(self.filename, 'w') as f:
            for sentence in self.sentences:
                f.write(f'{sentence}\n')

    def choose_random(self):
        self.sentences = self.load_sentences()
        random_ind = random.randint(0, len(self.sentences)-1)
        random_s = self.sentences[random_ind]
        return random_s

    def create_display(self,sentence):
        new = sentence.split(" ")
        modified = ""
        seen_letters = []
        for x in new:
            for let in x:
                if let != x[0] and let != x[len(x)-1] and let not in seen_letters:
                    x = x.replace(let, "_")
                    seen_letters.append(x[0])
                    seen_letters.append(x[len(x)-1])
            modified = modified + " " + x
        return modified

    def modify_hidden(self,letter,hidden,right):
        real_string = right.split(" ")
        hang_string = hidden.split(" ")
        x = 0
        hang_modified = ""
        for i in range(len(real_string)):
            for j in range(len(real_string[i])):
                if letter == real_string[i][j]:
                    hang_string[i] = hang_string[i].replace(hang_string[i][j],letter)
            hang_modified = hang_modified + " " + hang_string[i]
        return hang_modified




