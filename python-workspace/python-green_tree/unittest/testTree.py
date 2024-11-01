'''
Created on Mar 22, 2023

@author: wuwei
'''
import unittest
from edu.wmich.cs1120.SP23.PA3.treeCalculation.src.tree import Tree


class testTest(unittest.TestCase):
    
    def setUp(self):
        self.tree = Tree();
        self.testcases = [ [(1,2)],[(1,2),(1,3),(2,4)],[(1,2),(2,3),(2,4)]];
        self.outputs = [3, 8, 9];
        self.testcases_with_output = [ [(1,2),3],[(1,2),(1,3),(2,4),8],[(1,2),(2,3),(2,4),9]]
    
    def testCase1(self):
        #tree = Tree();
        self.tree.set_root(1, 2);
        self.tree.add(1,3);
        self.tree.add(2,4);
        total = self.tree.get_root().calculate_point();
        self.assertEqual(total, 8, "Calculation Failed");
        
"""    def testMorecases(self):
        for oneTree in self.testcases:
            first = True;
            for u,v in oneTree:
                if first == True:
                    self.tree.set_root(u, v);
                    first = False;
                else:
                    self.tree.add(u, v);
            total = self.tree.get_root().calculate_point();
            self.assertEqual(total, self.outputs[self.testcases.index(oneTree)], "Tree index "+str(self.testcases.index(oneTree))+" is not correct");
                
    def testCaseWithOutput(self):
        for oneTree in self.testcases_with_output:
            first = True;
            for u, v in oneTree[:len(oneTree)-1]:
                if first == True:
                    self.tree.set_root(u, v);
                    first = False;
                else:
                    self.tree.add(u, v);
            total = self.tree.get_root().calculate_point();
            self.assertEqual(total, oneTree[len(oneTree)-1], "Tree index "+str(self.testcases_with_output.index(oneTree))+" is not correct");
"""               