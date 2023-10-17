//
//  Cube.cpp
//  cpp-cube
//
//  Created by Jacob An on 2022/06/10.
//

#include <stdio.h>
#include "Cube.h"

Block::Block() {
    head = NULL;
}

void Block::insertBlock(int z, int y) {
    Node* cur = head;
    
    for (int x = 0; x < 3; x++) {
        Node* add = new Node(z,y,x);
        
        if (x == 0) {
            head = add;
            cur = add;
        } else {
            add->left = cur;
            cur->right = add;
            cur = cur->right;
        }
    }
}

Node* Block::getHead() {
    return head;
}

void Block::print() {
    Node* cur = head;
    
    while(cur != NULL) {
        cout << cur->z << " " << cur->y << " " << cur->x << " ";
        cur = cur->right;
    }
}

Node* Surface::getHead() {
    return head;
}

void Surface::insertSurface(int z) {
    a.insertBlock(z, 0);
    b.insertBlock(z, 1);
    c.insertBlock(z, 2);
    
    head = a.getHead();
    Node* cur1 = a.getHead();
    Node* cur2 = b.getHead();
    
    cur1->front = cur2;
    cur2->behind = cur1;
    cur1 = cur1->right;
    cur2 = cur2->right;
    cur1->front = cur2;
    cur2->behind = cur1;
    cur1 = cur1->right;
    cur2 = cur2->right;
    cur1->front = cur2;
    cur2->behind = cur1;
    
    cur2 = b.getHead();
    Node* cur3 = c.getHead();
    cur2->front = cur3;
    cur3->behind = cur2;
    cur2 = cur2->right;
    cur3 = cur3->right;
    cur2->front = cur3;
    cur3->behind = cur2;
    cur2 = cur2->right;
    cur3 = cur3->right;
    cur2->front = cur3;
    cur3->behind = cur2;
}

Node* Cube::getHead() {
    return head;
}

BST* Cube::getMin(BST* target) {
    if (target == NULL)
        return NULL;
    
    if (target->left == NULL)
        return target;
    else
        return getMin(target->left);
}

void Cube::initCube() {
    a.insertSurface(0);
    b.insertSurface(1);
    c.insertSurface(2);
    head = a.getHead();
    Node* cur1 = a.getHead();
    Node* cur2 = b.getHead();
    
    for (int i = 0; i < 9; i++) {
        cur1->down = cur2;
        cur2->up = cur1;
        
        if (i % 3 == 2) {
            cur1 = cur1->left->left->front;
            cur2 = cur2->left->left->front;
        } else {
            cur1 = cur1->right;
            cur2 = cur2->right;
        }
    }
    
    cur2 = b.getHead();
    Node* cur3 = c.getHead();
    
    for (int i = 0; i < 9; i++) {
        cur2->down = cur3;
        cur3->up = cur2;
        
        if (i % 3 == 2) {
            cur2 = cur2->left->left->front;
            cur3 = cur3->left->left->front;
        } else {
            cur2 = cur2->right;
            cur3 = cur3->right;
        }
    }
}

void Cube::insert(int x, int y, int z, char name[50]) {
    Node* cur = head;
    BST* bst;
    
    while (cur != NULL) {
        if (z > cur->z)
            cur = cur->down;
        else if (z < cur->z)
            cur = cur->up;
        else {
            if (y > cur->y)
                cur = cur->front;
            else if (y < cur->y)
                cur = cur->behind;
            else {
                if (x > cur->x)
                    cur = cur->right;
                else if (x < cur->x)
                    cur = cur->left;
                else {
                    if (cur->word == NULL) {
                        BST* add = new BST(name);
                        cur->word = add;
                        cur->count += 1;
                        return;
                    } else {
                        bst = cur->word;
                        while (bst != NULL) {
                            if (strcmp(bst->n, name) < 0) {
                                if (bst->right == NULL) {
                                    BST* add = new BST(name);
                                    bst->right = add;
                                    cur->count += 1;
                                    return;
                                } else bst = bst->right;
                            } else if (strcmp(bst->n, name) > 0) {
                                if (bst->left == NULL) {
                                    BST* add = new BST(name);
                                    bst->left = add;
                                    cur->count += 1;
                                    return;
                                }
                                else bst = bst->left;
                            }
                            else if (strcmp(bst->n, name) == 0)
                                return;
                        }
                    }
                    
                }
            }
        }
    }
}

void Cube::remove(int x, int y, int z, char name[50]) {
    Node* cur = head;
    
    while(cur != NULL) {
        if (z > cur->z)
            cur = cur->down;
        else if (z < cur->z)
            cur = cur->up;
        else {
            if (y > cur->y)
                cur = cur->front;
            else if (y < cur->y)
                cur = cur->behind;
            else {
                if (x > cur->x)
                    cur = cur->right;
                else if (x < cur->x)
                    cur = cur->left;
                else {
                    if (fineName(cur->word, name) != NULL) {
                        removeBSTNode(cur, cur->word, NULL, name);
                        return;
                    } else {
                        return;
                    }
                }
            }
        }
    }
}

BST* Cube::removeBSTNode(Node* N, BST* bst, BST* par, char name[50]) {
    static int cnt = 0;
    
    if (bst == NULL)
        return NULL;
    
    BST* par_Node = par;
    
    if (strcmp(bst->n,name) > 0) {
        par_Node = bst;
        cnt = 1;
        bst = removeBSTNode(N, bst->left, par_Node, name);
    } else if (strcmp(bst->n,name) < 0) {
        par_Node = bst;
        cnt = 2;
        bst = removeBSTNode(N, bst->right, par_Node, name);
    }
    else if (strcmp(bst->n,name) == 0) {
        if (par_Node == NULL) {
            if (bst->left == NULL && bst->right == NULL) {
                N->word = bst->left;
                N->count--;
                delete bst;
                return bst;
            } else if (bst->left == NULL && bst->right != NULL) {
                N->word = bst->right;
                N->count--;
                delete bst;
                return bst;
            } else if (bst->left != NULL && bst->right == NULL) {
                N->word = bst->left;
                N->count--;
                delete bst;
                return bst;
            } else if (bst->left != NULL && bst->right != NULL) {
                BST* temp = getMin(bst->right);
                strcpy(bst->n, temp->n);
                bst = removeBSTNode(N, bst, par_Node, temp->n);
                return bst;
            }
        } else {
            if (bst->left == NULL && bst->right == NULL) {
                if (cnt == 1) {
                    par_Node->left = bst->right;
                } else if (cnt == 2) {
                    par_Node->right = bst->right;
                }
                N->count--;
                delete bst;
                return bst;
            } else if (bst->left == NULL && bst->right != NULL) {
                if (cnt == 1) {
                    par_Node->left = bst->right;
                } else if (cnt == 2) {
                    par_Node->right = bst->right;
                }
                N->count--;
                delete bst;
                return bst;
                
            } else if (bst->left != NULL && bst->right == NULL) {
                if (cnt == 1) {
                    par_Node->left = bst->left;
                } else if (cnt == 2) {
                    par_Node->right = bst->left;
                }
                
                N->count--;
                delete bst;
                return bst;
            } else if (bst->left != NULL && bst->right != NULL) {
                BST* temp = getMin(bst->right);
                strcpy(bst->n, temp->n);
                N->count--;
                return bst;
            }
        }
        
    }
    
    return bst;
}

void Cube::find(char name[50]) {
    Node* cur = head;
    
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
            if (fineName(cur->word, name) != NULL)
                cout << cur->z << cur->y << cur->x <<'\n';
            if (i % 3 == 2)
                cur = cur->left->left->down;
            else
                cur = cur->right;
        }
        if (j == 0)
            cur = head->front;
        else if (j == 1)
            cur = head->front->front;
    }
}

BST* Cube::fineName(BST* p, char name[50]) {
    while (p != NULL) {
        if (strcmp(p->n, name) < 0)
            p = p->right;
        else if (strcmp(p->n, name) > 0)
            p = p->left;
        else if (strcmp(p->n, name) == 0)
            return p;
    }
    return p;
}

Node* Cube::findNode(int x, int y, int z) {
    Node* cur = head;
    
    while (cur != NULL) {
        if (z > cur->z)
            cur = cur->down;
        else if (z < cur->z)
            cur = cur->up;
        else {
            if (y > cur->y)
                cur = cur->front;
            else if (y < cur->y)
                cur = cur->behind;
            else {
                if (x > cur->x)
                    cur = cur->right;
                else if (x < cur->x)
                    cur = cur->left;
                else
                    return cur;
            }
        }
    }
    return NULL;
}

void Cube::print(int x, int y, int z) {
    BST* bst = findNode(z, y, x)->word;
    
    cout << "preorder : ";
    preorder(bst);
    cout << '\n';
    cout << "postorder : ";
    postorder(bst);
    cout << '\n';
    cout << "inorder : ";
    inorder(bst);
    cout << '\n';
    
    return;
}

void Cube::postorder(BST* p) {
    if (p != NULL) {
        postorder(p->left);
        postorder(p->right);
        cout << p->n << " ";
    }
    return;
}

void Cube::inorder(BST* p) {
    if (p != NULL) {
        inorder(p->left);
        cout << p->n << " ";
        inorder(p->right);
    }
    return;
}

void Cube::preorder(BST* p) {
    if (p != NULL) {
        cout << p->n << " ";
        preorder(p->left);
        preorder(p->right);
    }
    return;
}


void Cube::printAll() {
    Node* cur = head;
    
    for (int j = 0; j < 3; j++) {
        for(int i = 0; i < 8; i++) {
            cout << cur->count << " " ;
            
            if (i % 3 == 2) {
                cur = cur->left->left->down;
                cout << "\n";
            } else {
                cur = cur->right;
            }
        }
        
        cout << cur->count << "\n\n" ;
        
        if (j == 0)
            cur = head->front;
        else if (j == 1)
            cur = head->front->front;
    }
}

void Cube::exchange(int x1, int y1, int z1, int x2, int y2, int z2) {
    Node* ch1 = findNode(z1,y1,x1);
    Node* ch2 = findNode(z2,y2,x2);
    
    Node* change_Node = new Node(z2,y2,x2);
    change_Node->word = ch2->word;
    change_Node->count = ch2->count;
    
    if (z1 == 0 && y1 == 0 && x1 == 0)
        head = change_Node;
    else if (z2 == 0 && y2 == 0 && x2 == 0)
        head = ch1;
    
    if (ch1->right != NULL)
        ch1->right->left = change_Node;
    if (ch1->left != NULL)
        ch1->left->right = change_Node;
    if (ch1->up != NULL)
        ch1->up->down = change_Node;
    if (ch1->down != NULL)
        ch1->down->up = change_Node;
    if (ch1->behind != NULL)
        ch1->behind->front = change_Node;
    if (ch1->front != NULL)
        ch1->front->behind = change_Node;
    if (ch2->right != NULL)
        ch2->right->left = ch1;
    if (ch2->left != NULL)
        ch2->left->right = ch1;
    if (ch2->up != NULL)
        ch2->up->down = ch1;
    if (ch2->down != NULL)
        ch2->down->up = ch1;
    if (ch2->behind != NULL)
        ch2->behind->front = ch1;
    if (ch2->front != NULL)
        ch2->front->behind = ch1;
    
    change_Node->right = ch1->right;
    change_Node->left = ch1->left;
    change_Node->up = ch1->up;
    change_Node->down = ch1->down;
    change_Node->behind = ch1->behind;
    change_Node->front = ch1->front;
    
    
    ch1->right = ch2->right;
    ch1->left = ch2->left;
    ch1->up = ch2->up;
    ch1->down = ch2->down;
    ch1->behind = ch2->behind;
    ch1->front = ch2->front;
    
    change_Node->z = ch1->z; change_Node->y = ch1->y; change_Node->x = ch1->x;
    ch1->z = ch2->z; ch1->y = ch2->y; ch1->x = ch2->x;
    
    delete ch2;
    
    return;
}

void Cube::turn(int place, int clock, int spin) {
    if (place == 0) {
        if (clock == 0) {
            if (spin == 0) {
                exchange(0, 0, 0, 0, 0, 2);
                exchange(1, 0, 0, 1, 0, 2);
                exchange(2, 0, 0, 2, 0, 2);
                exchange(0, 0, 1, 1, 0, 2);
                exchange(1, 0, 0, 2, 0, 1);
                exchange(0, 0, 0, 2, 0, 2);
            } else if (spin == 1) {
                exchange(0, 1, 0, 0, 1, 2);
                exchange(1, 1, 0, 1, 1, 2);
                exchange(2, 1, 0, 2, 1, 2);
                exchange(0, 1, 1, 1, 1, 2);
                exchange(1, 1, 0, 2, 1, 1);
                exchange(0, 1, 0, 2, 1, 2);
            } else if (spin == 2) {
                exchange(0, 2, 0, 0, 2, 2);
                exchange(1, 2, 0, 1, 2, 2);
                exchange(2, 2, 0, 2, 2, 2);
                exchange(0, 2, 1, 1, 2, 2);
                exchange(1, 2, 0, 2, 2, 1);
                exchange(0, 2, 0, 2, 2, 2);
            } else return;
        } else if (clock == 1) {
            if (spin == 0) {
                exchange(0, 0, 0, 2, 0, 0);
                exchange(0, 0, 1, 2, 0, 1);
                exchange(0, 0, 2, 2, 0, 2);
                exchange(1, 0, 0, 2, 0, 1);
                exchange(0, 0, 1, 1, 0, 2);
                exchange(0, 0, 0, 2, 0, 2);
            } else if (spin == 1) {
                exchange(0, 1, 0, 2, 1, 0);
                exchange(0, 1, 1, 2, 1, 1);
                exchange(0, 1, 2, 2, 1, 2);
                exchange(1, 1, 0, 2, 1, 1);
                exchange(0, 1, 1, 1, 1, 2);
                exchange(0, 1, 0, 2, 1, 2);
            } else if (spin == 2) {
                exchange(0, 2, 0, 2, 2, 0);
                exchange(0, 2, 1, 2, 2, 1);
                exchange(0, 2, 2, 2, 2, 2);
                exchange(1, 2, 0, 2, 2, 1);
                exchange(0, 2, 1, 1, 2, 2);
                exchange(0, 2, 0, 2, 2, 2);
            }
        } else return;
    }
    else if (place == 1) {
        if (clock == 1) {
            if (spin == 0) {
                exchange(0, 2, 0, 0, 0, 0);
                exchange(0, 2, 1, 0, 0, 1);
                exchange(0, 2, 2, 0, 0, 2);
                exchange(0, 1, 0, 0, 0, 1);
                exchange(0, 2, 1, 0, 1, 2);
                exchange(0, 2, 0, 0, 0, 2);
            } else if (spin == 1) {
                exchange(1, 2, 0, 1, 0, 0);
                exchange(1, 2, 1, 1, 0, 1);
                exchange(1, 2, 2, 1, 0, 2);
                exchange(1, 1, 0, 1, 0, 1);
                exchange(1, 2, 1, 1, 1, 2);
                exchange(1, 2, 0, 1, 0, 2);
            } else if (spin == 2) {
                exchange(2, 2, 0, 2, 0, 0);
                exchange(2, 2, 1, 2, 0, 1);
                exchange(2, 2, 2, 2, 0, 2);
                exchange(2, 1, 0, 2, 0, 1);
                exchange(2, 2, 1, 2, 1, 2);
                exchange(2, 2, 0, 2, 0, 2);
            } else return;
        } else if (clock == 0) {
            if (spin == 0) {
                exchange(0, 2, 0, 0, 2, 2);
                exchange(0, 1, 0, 0, 1, 2);
                exchange(0, 0, 0, 0, 0, 2);
                exchange(0, 1, 0, 0, 0, 1);
                exchange(0, 2, 1, 0, 1, 2);
                exchange(0, 2, 0, 0, 0, 2);
            } else if (spin == 1) {
                exchange(1, 2, 0, 1, 2, 2);
                exchange(1, 1, 0, 1, 1, 2);
                exchange(1, 0, 0, 1, 0, 2);
                exchange(1, 1, 0, 1, 0, 1);
                exchange(1, 2, 1, 1, 1, 2);
                exchange(1, 2, 0, 1, 0, 2);
            } else if (spin == 2) {
                exchange(2, 2, 0, 2, 2, 2);
                exchange(2, 1, 0, 2, 1, 2);
                exchange(2, 0, 0, 2, 0, 2);
                exchange(2, 1, 0, 2, 0, 1);
                exchange(2, 2, 1, 2, 1, 2);
                exchange(2, 2, 0, 2, 0, 2);
            }
        } else return;
    }
    else if (place == 2) {
        if (clock == 0) {
            if (spin == 0) {
                exchange(0, 0, 0, 0, 2, 0);
                exchange(1, 0, 0, 1, 2, 0);
                exchange(2, 0, 0, 2, 2, 0);
                exchange(1, 0, 0, 2, 1, 0);
                exchange(0, 1, 0, 1, 2, 0);
                exchange(0, 0, 0, 2, 2, 0);
            } else if (spin == 1) {
                exchange(0, 0, 1, 0, 2, 1);
                exchange(1, 0, 1, 1, 2, 1);
                exchange(2, 0, 1, 2, 2, 1);
                exchange(1, 0, 1, 2, 1, 1);
                exchange(0, 1, 1, 1, 2, 1);
                exchange(0, 0, 1, 2, 2, 1);
            } else if (spin == 2) {
                exchange(0, 0, 2, 0, 2, 2);
                exchange(1, 0, 2, 1, 2, 2);
                exchange(2, 0, 2, 2, 2, 2);
                exchange(1, 0, 2, 2, 1, 2);
                exchange(0, 1, 2, 1, 2, 2);
                exchange(0, 0, 2, 2, 2, 2);
            } else return;
        } else if (clock == 1) {
            if (spin == 0) {
                exchange(0, 0, 0, 2, 0, 0);
                exchange(0, 1, 0, 2, 1, 0);
                exchange(0, 2, 0, 2, 2, 0);
                exchange(1, 0, 0, 2, 1, 0);
                exchange(0, 1, 0, 1, 2, 0);
                exchange(0, 0, 0, 2, 2, 0);
            } else if (spin == 1) {
                exchange(0, 0, 1, 2, 0, 1);
                exchange(0, 1, 1, 2, 1, 1);
                exchange(0, 2, 1, 2, 2, 1);
                exchange(1, 0, 1, 2, 1, 1);
                exchange(0, 1, 1, 1, 2, 1);
                exchange(0, 0, 1, 2, 2, 1);
            } else if (spin == 2) {
                exchange(0, 0, 2, 2, 0, 2);
                exchange(0, 1, 2, 2, 1, 2);
                exchange(0, 2, 2, 2, 2, 2);
                exchange(1, 0, 2, 2, 1, 2);
                exchange(0, 1, 2, 1, 2, 2);
                exchange(0, 0, 2, 2, 2, 2);
            }
        } else return;
    }
    else return;
}
