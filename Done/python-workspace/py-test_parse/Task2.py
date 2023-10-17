from Task1 import Text


class Book(Text):
    def __init__(self, name=None, author=None, text_format='Book'):
        super(Book, self).__init__(name=name, author=author, text_format=text_format, showtext=False)
        return

    def read_from_file(self, filename):
        f = open(filename, 'r')

        line = None
        while line != '':
            line = f.readline()
            self.add(line)
        return


############################# Examples below #############################


# IoBE = Book(name='Importance of Being Ernest', author='Oscar Wilde')
# IoBE.read_from_file('importance_of_being_ernest.txt')
# print(IoBE.text[91:98])
#
# IoBE.analyse()
# print(IoBE)
