class Tree(object):
    def __init__(self, data, children=None, parent=None, files=None):
        self.data = data
        self.children = children or []
        self.files = files or []
        self.parent = parent

    def add_child(self, data):
        new_child = Tree(data, parent=self)
        self.children.append(new_child)
        return new_child

    def is_root(self):
        return self.parent is None

    def is_leaf(self):
        return not self.children

    def add_file(self, file):
        self.files.append(file)

    def __str__(self):
        if self.is_leaf():
            return str(self.data)
        return '{data} [{children}]'.format(data=self.data, children=', '.join(map(str, self.children)))