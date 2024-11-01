wordsplitters = {'-', '–', '—', ' '}
punctuations = wordsplitters.union({'.', '?', '!', ',', ';', ':'})

commonwords = {'that', 'with', 'they', 'have', 'this', 'from', 'word', 'what', 'some', 'other', 'were',
               'there', 'when', 'your', 'said', 'each', 'which', 'their', 'time', 'will', 'about', 'many',
               'then', 'them', 'write', 'would', 'like', 'these', 'long', 'make', 'thing', 'look', 'more',
               'could', 'come', 'sound', 'most', 'people', 'over', 'know', 'than', 'call', 'first', 'down',
               'only', 'back', 'after', 'year', 'came', 'name', 'very', 'much', 'want', 'well', 'also',
               'while', 'must', 'dont', 'work', 'should', 'always', 'never', 'dear', 'miss', 'been', 'here', 'think'}


def dictionarysort(dictionary):
    return dict(sorted(dictionary.items(), key=lambda x: x[1], reverse=True))


# Task 1.a
def clean(text, criteria):
    for c in text:
        if not criteria(c):
            text = text.replace(c, '')

    return text


# Task 1.a
def istextchar(c):
    return str.isalpha(c)


# Task 1.b
def iswordchar(c):
    return str.isalpha(c) or c in wordsplitters


# Task 1.b
def isuncommon(word):
    return word in commonwords and len(word > 3)


# Task 1.b
def topitems(sorteddictionary, n=10):
    d = list(sorteddictionary.items())[:n]
    return dict(d)


class Text(object):
    def __init__(self, name=None, author=None, text_format='Text', showtext=True):
        self.text_format = text_format
        self.name = name
        self.author = author
        self.showtext = showtext

        self.text = []

        self.wordlist = []
        self.wordcount = {}
        self.uncommonwordcount = {}
        self.topwords = None

    # Task 1.a
    def add(self, line):
        s = ''

        for c in line:
            if not str.isalnum(c) and c not in wordsplitters and c not in punctuations:
                line = line.replace(c, '')

        self.text.append(line)

    # Tasks 1.a and 1.b
    def __str__(self):
        result = ''

        if self.text_format == 'Text':
            result = result + 'Text by ' + self.author + ': '
        elif self.text_format == 'Quotes':
            result = result + 'Quotes by ' + self.author + ': '
        elif self.text_format == 'Poem':
            result = result + 'Poem "' + self.name + '" by ' + self.author
        elif self.text_format == 'Book':
            result = result + 'Book "' + self.name + '" by ' + self.author
        elif self.text_format == 'Play':
            result = result + 'Play "' + self.name + '" by ' + self.author

        if self.showtext:
            for i in self.text:
                result += i + '\n'
        else:
            result += '\n'
        result += 'Most frequent words: ' + str(self.topwords)
        return result

    def __repr__(self):
        return str(self)

    # Task 1.b
    def _splitwords(self):
        self.wordlist = []

        for line in self.text:
            words = line.split(' ')
            for word in words:
                w = str.lower(word)
                for c in w:
                    if c in wordsplitters:
                        w = w.replace(c, ' ')
                    elif not str.isalpha(c):
                        w = w.replace(c, '')
                w = w.split(' ')
                for i in w:
                    if len(i) < 1:
                        continue
                    if i not in self.wordlist:
                        self.wordlist.append(i)
        return

    # Task 1.b
    def _countwords(self):
        self.wordcount = {}

        for line in self.text:
            words = line.split(' ')
            for word in words:
                w = str.lower(word)
                for c in w:
                    if c in wordsplitters:
                        w = w.replace(c, ' ')
                    elif not str.isalpha(c):
                        w = w.replace(c, '')
                w = w.split(' ')
                for i in w:
                    if len(i) < 1:
                        continue
                    if i in self.wordcount:
                        self.wordcount[i] += 1
                    else:
                        self.wordcount[i] = 1

        self.wordcount = dictionarysort(self.wordcount)
        return

    # Task 1.b
    def _countuncommonwords(self):
        self.uncommonwordcount = {}

        for key in self.wordcount:
            if key not in commonwords:
                self.uncommonwordcount[key] = self.wordcount[key]

        self.uncommonwordcount = dictionarysort(self.uncommonwordcount)
        return

        # Task 1.b

    def _findtopwords(self):
        self.topwords = {}

        for key in self.uncommonwordcount:
            if len(key) > 3:
                self.topwords[key] = self.wordcount[key]

        self.topwords = topitems(dictionarysort(self.topwords))
        return

    def analyse(self):
        self._splitwords()
        self._countwords()
        self._countuncommonwords()
        self._findtopwords()

############################# Examples below #############################

# ps2106 = Text(author='ps2106')
# ps2106.add('I don’t play accurately—even you can play accurately! Don’t you think? Perhaps you dont. ')
# ps2106.add('But I can accurately state that 1*2+3*1-4*1=1! Even you can verify this. ')
# ps2106.add('***This _text_ also has <mind-numbing> use of #symbols# such @this, [this] and (this!).')
# # print(ps2106)
# # print('')
#
# BFQ = Text(author='Franklin', text_format='Quotes')
# BFQ.add('Love your Enemies, for they tell you your Faults.')
# BFQ.add('There never was a good war or a bad peace.')
# # print(BFQ)
# # print('')
#
# ALS = Text(name='Auld Lang Syne', text_format='Poem', author='Burns', showtext=False)
# ALS.add('Should Old Acquaintance be forgot,')
# ALS.add('and never thought upon;')
# # print(ALS)
#
# ps2106.analyse()
# print('ps2106 words: ' + str(ps2106.wordcount))
# print(ps2106)
# print('')
#
# BFQ.analyse()
# print('BFQ words: ' + str(BFQ.wordcount))
# print(BFQ)
# print('')
#
# ALS.analyse()
# print('ALS words: ' + str(ALS.wordcount))
# print(ALS)
# print('')
