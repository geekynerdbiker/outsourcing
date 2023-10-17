from Task1 import clean, dictionarysort
from Task2 import Book
import numpy as np


def isnamechar(c):
    return str.isalpha(c) or (c in {' ', '.'})


def speaker_name(line):
    n = len(line)
    if (n > 1) and (line[n - 1] == '.') and line.isupper():
        return clean(line[0:n - 1], isnamechar)


class Play(Book):
    def __init__(self, name=None, author=None, text_format='Text', showtext=True):
        super(Play, self).__init__(name, author, text_format='Play')
        self.characters = set()
        self.currentspeaker = None
        self.dialogues = []

        self.talks_most = None
        self.talks_to = None
        self.talk_to_each_other = None

    def add(self, line):
        super(Play, self).add(line)
        l = line.strip('\n').split(' ')

        if '' in l:
            l.remove('')

        if len(l) == 1 and len(l[0]) > 0 and l[0][-1] == '.':
            if str.isalpha(l[0][:-1]) and str.isupper(l[0][:-1]):
                self.characters.add(l[0][:-1])
                self.dialogues.append(l[0][:-1])
        else:
            if len(line.strip('\n')) != 0:
                self.dialogues.append(line.strip('\n'))

        return

    def _count_talking(self):
        self.talks_most = {}
        self.talks_to = np.zeros((len(self.characters), len(self.characters)))

        for d in self.dialogues:
            if d in self.characters:
                if d in self.talks_most:
                    self.talks_most[d] += 1
                else:
                    self.talks_most[d] = 1

        self.talks_most = dictionarysort(self.talks_most)

        characters = list(self.characters)
        speaker, listener = -1, -1
        for i in range(len(self.dialogues)):
            if self.dialogues[i] not in characters:
                continue
            else:
                speaker = characters.index(self.dialogues[i])
            for j in range(i+1, len(self.dialogues)):
                if self.dialogues[j] not in characters:
                    continue
                else:
                    listener = characters.index(self.dialogues[j])
                    self.talks_to[speaker][listener] += 1
                    break
        return

    def _talk_to_each_other(self):
        return

    def analyse(self):
        super(Play, self).analyse()
        self._count_talking()
        self._talk_to_each_other()

    def __str__(self):
        result = super(Play, self).__str__()

        result += '\nMain characters: ' + str(self.talks_most)
        return result


IoBE_play = Play("Importance of Being Ernest", "Oscar Wilde")
IoBE_play.read_from_file("bae.txt")
IoBE_play.analyse()
print(IoBE_play)
