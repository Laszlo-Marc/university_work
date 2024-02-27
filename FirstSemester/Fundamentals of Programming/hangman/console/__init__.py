from repo import TextRepo


class UI:
    def __init__(self):
        self.repo = TextRepo("sentences.txt")

    def add_sentence(self,sentence):
        self.repo.add_sentence(sentence)

    def print(self):
        print("1.Add a sentence")
        print("2.Start playing")

    def run(self):
        self.repo.add_initial()
        right_sentence = self.repo.choose_random()
        hidden = self.repo.create_display(right_sentence).strip()
        wrong_guesses = 0
        hangman = ['h','a','n','g','m','a','n']
        done = ""

        self.print()
        try:
            opt = int(input("Your choice: "))
        except TypeError:
            print("Not an option!")
        while True:
            if opt == 1:
                try:
                    sentence = input("Your sentence: ")
                except TypeError:
                    print("Invalid input!")
                check_list = self.repo.load_sentences()
                if sentence not in check_list:
                    self.add_sentence(sentence)
                else:
                    print("Sentence already exists")
                self.print()
                opt = int(input("Your choice: "))
            if opt == 2:
                print(hidden)
                letter = input("Your guess: ")
                if type(letter)!=str:
                    print("Invalid input!")
                if letter in right_sentence:
                    hidden = self.repo.modify_hidden(letter,hidden,right_sentence)
                    print(hidden)
                    if hidden == right_sentence:
                        print("You win!")
                else:
                    done = done + hangman[wrong_guesses]
                    wrong_guesses+=1
                    print(done)
                    if done == "hangman":
                        print("You lost")
                        return False

