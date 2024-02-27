class UI:
    def __init__(self,service):
       self.service=service

    def run(self):
        modified_sentence, score, sentence = self.service.select_random_word()
        print("Scrambled sentence: " + modified_sentence)
        print("Score: " + str(score))
        running=True
        swap_history=[]
        while running:
            command=input("Swap letters or undo: ")
            command_list=command.split()
            if command_list[0]=="swap":
                swap_history.append(sentence)
                swap_history.append(modified_sentence)
                word_index1=int(command_list[1])
                letter_index1=int(command_list[2])
                word_index2=int(command_list[4])
                letter_index2=int(command_list[5])
                modified_sentence=self.service.swapper(modified_sentence,word_index1,letter_index1,word_index2,letter_index2)
                swap_history.append(modified_sentence)
                score-=1
                print("Scrambled sentence: " + modified_sentence)
                print("Score: " + str(score))
                if score == 0:
                    print("Your score is 0.You lost!")
                    running=False
                if self.service.verifier(sentence, modified_sentence):
                    print("Your score is "+str(score)+".You won!")
                    running=False
            if command_list[0]=="undo":
                modified_sentence=swap_history[-1]
                print(modified_sentence)

