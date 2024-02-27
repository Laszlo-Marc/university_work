import random


class Service:
    def __init__(self,repo):
        self.repo=repo

    def select_random_word(self):
        sentence = random.choice(self.repo.sentences)
        words = sentence.split()
        modified_sentence=[]
        score=0
        for word in words:
            score=score+len(word)
            if len(word)>2:
                for x in range(len(word) - 2):
                    i = random.randint(1, len(word) - 2)
                    j = random.randint(1, len(word) - 2)
                    word_list = list(word)
                    while i == j :
                        i = random.randint(1, len(word) - 1)
                        j = random.randint(1, len(word) - 1)
                    word_list[i], word_list[j] = word_list[j], word_list[i]
                    modified_word = ''.join(word_list)
                modified_sentence.append(modified_word)
            else:
                modified_sentence.append(word)
        modified_sentence=' '.join(modified_sentence)
        return modified_sentence,score,sentence

    def verifier(self,og_sentence,scrambled):
        if scrambled==og_sentence:
            return True
        return False

    def swapper(self,sentence,word_index1,letter_index1,word_index2,letter_index2):
        words=sentence.split()
        if words[word_index1]==words[word_index2]:
            dont=True
        else:
            dont=False
        wordlist1=list(words[word_index1])
        wordlist2=list(words[word_index2])

        temp=wordlist1[letter_index1]
        wordlist1[letter_index1]=wordlist2[letter_index2]
        wordlist2[letter_index2]=temp

        temp = wordlist1[letter_index2]
        wordlist1[letter_index2] = wordlist2[letter_index2]
        wordlist2[letter_index2] = temp

        if dont:
            words[word_index1]=''.join(wordlist1)
        else:
            words[word_index1] = ''.join(wordlist1)
            words[word_index2]=''.join(wordlist2)

        swapped=' '.join(words)

        return swapped

