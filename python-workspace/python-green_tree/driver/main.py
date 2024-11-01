'''
Created on Mar 22, 2023

@author: wuwei
'''
# from edu.wmich.cs1120.SP23.PA3.treeCalculation.src.parser import Parser
# from edu.wmich.cs1120.SP23.PA3.treeCalculation.src.tree import Tree

from src2.second.Parser import ParserSecond
from src2.src.tree import Tree


def main():
    parser = ParserSecond()  # !!!!This one should be replaced!!!!!
    tree = Tree()
    parser.set_tree(tree)

    parser.readfromConsole()


if __name__ == "__main__":
    main()
