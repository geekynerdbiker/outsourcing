class CharField:
    def __init__(self, max_length=10):
        self.type = 'TEXT'

class BooleanField:
    def __init__(self, default=False):
        self.type = 'INTEGER'
        self.default = default

class IntegerField:
    def __init__(self, default=0):
        self.type = 'INTEGER'

class FloatField:
    def __init__(self, default=0.1):
        self.type = 'REAL'
class EmailField:
    def __init__(self, unique=False):
        self.type = 'TEXT',
        self.unique = unique

def instanceof(field):
    fields = (CharField, BooleanField, EmailField, IntegerField, FloatField)
    if isinstance(field, fields):
        return True
    return False