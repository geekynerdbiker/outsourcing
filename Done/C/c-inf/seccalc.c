#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "calc.h"

int power(int a, int b) {
    double ans = 1;
    while (b > 0) {
        ans *= a;
        b--;
    }
    return ans;
}

pList add(pList,pList);
pList minus(pList a, pList b);
pList multiply(pList a, pList b);
pList division(pList a, pList b);

// 더하기 연산
pList add(pList a , pList b ) {
    pList answer;
    int one,two;
    
    one = (a-> head -> data != '-'?1:0);
    
    two = (b-> head -> data != '-'?1:0);
    
    if ( one == 1 && two == 1){
        if (isNode(a, '.') == 0){
            insertBack(a, makeNode('.'));
        }
        if (isNode(b, '.') == 0){
            insertBack(b, makeNode('.'));
        }
        int a_count = a->count;
        int b_count = b->count;
        int a_point = searchNode(a, '.');
        int b_point = searchNode(b, '.');
        int a_int_len = a_point - 1;
        int b_int_len = b_point - 1;
        int a_dec_len = a_count - a_point;
        int b_dec_len = b_count - b_point;
        if (a_int_len != b_int_len) {
            while ( a_int_len != b_int_len)
            {
                if (a_int_len > b_int_len) {
                    insertFront(b, makeNode('0'));
                    b_int_len++;
                }
                else if (a_int_len < b_int_len) {
                    insertFront(a, makeNode('0'));
                    a_int_len++;
                }
            }
        }
        if (a_dec_len != b_dec_len) {
            while (a_dec_len != b_dec_len)
            {
                if (a_dec_len > b_dec_len) {
                    insertBack(b, makeNode('0'));
                    b_dec_len++;
                }
                else if (a_dec_len < b_dec_len) {
                    insertBack(a, makeNode('0'));
                    a_dec_len++;
                }
            }
        }
        
        pList pst = makeList();
        pList answer = makeList();
        
        while (a->head != NULL){
            if ((a->head->data - '0' + b->head->data - '0') > 9) {
                insertBack(pst, makeNode('1'));
                insertBack(answer, makeNode((a->head->data - '0' + b->head->data - '0') % 10 + '0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if ((a->head->data - '0' + b->head->data - '0') < 10 && a->head->data - '0' + b->head->data - '0' > 0) {
                insertBack(pst , makeNode('0'));
                insertBack(answer, makeNode(a->head->data -'0' + b->head->data-'0'+'0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if ((a->head->data - '0' + b->head->data -'0') == 0){
                insertBack(pst, makeNode('0'));
                insertBack(answer, makeNode('0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if ((a->head->data - '0' +b->head->data - '0') == 10){
                insertBack(pst, makeNode('1'));
                insertBack(answer, makeNode('0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if (a->head->data == '.' && b->head->data  == '.') {
                insertBack(answer, makeNode('.'));
                deleteHead(a);
                deleteHead(b);
            }
        }
        insertBack(pst, makeNode('0'));
        int answer_Pointer = searchNode(answer,'.');
        insertMid(pst, answer_Pointer, makeNode('.'));
        
        if (isNode(pst, '1') == 0) {
            removeZero(answer);
            return answer;
        }
        else if (isNode(pst, '1') == 1) {
            return add(answer, pst);
        }
    }
    
    else if ( one == 1 && two == 0) {
        deleteHead(b);
        return minus(a,b);
    }
    else if ( one == 0 && two == 1) {
        deleteHead(a);
        return minus(b,a);
    }
    
    else {
        deleteHead(a);
        deleteHead(b);
        answer = add(a,b);
        insertFront(answer, makeNode('-'));
        return answer;
    }
    return answer;
}

// 빼기 연산
pList minus(pList a , pList b ) {
    pList answer;
    int one,two;
    one = (a-> head -> data != '-'?1:0);
    two = (b-> head -> data != '-'?1:0);
    char a_head = (a -> head -> data);
    char b_head = (b -> head -> data);
    
    if ( one == 1 && two == 1) {
        if (isNode(a, '.') == 0){
            insertBack(a, makeNode('.'));
        }
        if(isNode(b, '.') == 0){
            insertBack(b, makeNode('.'));
        }
        
        int a_count = a->count;
        int b_count = b->count;
        int a_point = searchNode(a, '.');
        int b_point = searchNode(b, '.');
        int a_int_len = a_point -1;
        int b_int_len = b_point -1;
        int a_dec_len = a_count - a_point;
        int b_dec_len = b_count - b_point;
        if ( a_int_len != b_int_len) {
            while (a_int_len != b_int_len) {
                if (a_int_len > b_int_len) {
                    insertFront(b, makeNode('0'));
                    b_int_len++;
                }
                else if (a_int_len < b_int_len) {
                    insertFront(a, makeNode('0'));
                    a_int_len++;
                }
            }
        }
        if ( a_dec_len != b_dec_len) {
            while (a_dec_len != b_dec_len) {
                if (a_dec_len > b_dec_len) {
                    insertBack(b, makeNode('0'));
                    b_dec_len++;
                }
                else if (a_dec_len < b_dec_len) {
                    insertBack(a, makeNode('0'));
                    a_dec_len++;
                }
            }
        }
        if (compareList(a,b) == 0) {
            answer = minus(b,a);
            insertFront(answer, makeNode('-'));
            return answer;
            
        }
        pList pst = makeList();
        answer = makeList();
        
        while (a->head != NULL) {
            if (a->head->data == '.' && b->head->data == '.'){
                insertBack(answer, makeNode('.'));
                deleteHead(a);
                deleteHead(b);
            }
            else if (a->head->data - b->head->data < 0) {
                insertBack(pst,makeNode('1'));
                insertBack(answer, makeNode( 10 - (b->head->data - a->head->data) + '0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if (a->head->data - b->head->data > 0) {
                insertBack(pst, makeNode('0'));
                insertBack(answer, makeNode(a->head->data - b->head->data +'0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if (a->head->data != '.' && b->head->data != '.' && a->head->data - b->head->data == 0) {
                insertBack(pst, makeNode('0'));
                insertBack(answer, makeNode('0'));
                deleteHead(a);
                deleteHead(b);
            }
        }
        insertBack(pst, makeNode('0'));
        int answer_Pointer = searchNode(answer, '.');
        insertMid(pst,answer_Pointer,makeNode('.'));
        if (isNode(pst, '1') == 0) {
            removeZero(answer);
            return answer;
        }
        else if (isNode(pst, '1') == 1) {
            return minus(answer, pst);
        }
    }
    else if ( one == 1 && two == 0) {
        deleteHead(b);
        return add(a, b);
    }
    else if ( one == 0 && two == 0) {
        deleteHead(b);
        return minus(a, b);
    }
    else {
        deleteHead(a);
        answer = add(a,b);
        insertFront(answer, makeNode('-'));
        return answer;
    }
    return answer;
}

// 곱하기 연산
pList multiply(pList a, pList b) {
    pList answer;
    int one, two;
    
    one = (a-> head -> data != '-' ? 1:0);
    
    two = (b-> head -> data != '-' ? 1:0);
    
    if ( one == 1 && two == 1){
        if (isNode(a, '.') == 0){
            insertBack(a, makeNode('.'));
        }
        if (isNode(b, '.') == 0){
            insertBack(b, makeNode('.'));
        }
        
        int a_count = a->count;
        int b_count = b->count;
        int a_point = searchNode(a, '.');
        int b_point = searchNode(b, '.');
        int a_int_len = a_point - 1;
        int b_int_len = b_point - 1;
        int a_dec_len = a_count - a_point;
        int b_dec_len = b_count - b_point;
        if (a_int_len != b_int_len) {
            while ( a_int_len != b_int_len)
            {
                if (a_int_len > b_int_len) {
                    insertFront(b, makeNode('0'));
                    b_int_len++;
                }
                else if (a_int_len < b_int_len) {
                    insertFront(a, makeNode('0'));
                    a_int_len++;
                }
            }
        }
        if (a_dec_len != b_dec_len) {
            while (a_dec_len != b_dec_len)
            {
                if (a_dec_len > b_dec_len) {
                    insertBack(b, makeNode('0'));
                    b_dec_len++;
                }
                else if (a_dec_len < b_dec_len) {
                    insertBack(a, makeNode('0'));
                    a_dec_len++;
                }
            }
        }
        
        pList pst = makeList();
        answer = makeList();
        
        while (a->head != NULL) {
            if ((a->head->data - '0') * (b->head->data - '0') > 9) {
                insertBack(pst, makeNode((a->head->data - '0') * (b->head->data - '0') / 10) + '0');
                insertBack(answer, makeNode((a->head->data - '0') * (b->head->data - '0') % 10) + '0');
                deleteHead(a);
                deleteHead(b);
            }
            else if ((a->head->data - '0') * (b->head->data - '0')  < 10 && (a->head->data - '0') * (b->head->data - '0') > 0) {
                insertBack(pst , makeNode('0'));
                insertBack(answer, makeNode((a->head->data - '0') * (b->head->data - '0') + '0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if ((a->head->data - '0') * (b->head->data - '0') == 0){
                insertBack(pst, makeNode('0'));
                insertBack(answer, makeNode('0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if (a->head->data == '.' && b->head->data  == '.') {
                insertBack(answer, makeNode('.'));
                deleteHead(a);
                deleteHead(b);
            }
        }
        insertBack(pst, makeNode('0'));
        int answer_Pointer = searchNode(answer,'.');
        insertMid(pst, answer_Pointer, makeNode('.'));
        if (isNode(pst, '1') == 1) {
            return multiply(answer, pst);
        }
        else {
            removeZero(answer);
            return answer;
        }
    }
    return answer;
}

// 나누기 연산
pList division(pList a, pList b) {
    pList answer;
    int one, two;
    
    one = (a-> head -> data != '-' ? 1:0);
    
    two = (b-> head -> data != '-' ? 1:0);
    
    if ( one == 1 && two == 1){
        if (isNode(a, '.') == 0){
            insertBack(a, makeNode('.'));
        }
        if (isNode(b, '.') == 0){
            insertBack(b, makeNode('.'));
        }
        
        int a_count = a->count;
        int b_count = b->count;
        int a_point = searchNode(a, '.');
        int b_point = searchNode(b, '.');
        int a_int_len = a_point - 1;
        int b_int_len = b_point - 1;
        int a_dec_len = a_count - a_point;
        int b_dec_len = b_count - b_point;
        if (a_int_len != b_int_len) {
            while ( a_int_len != b_int_len)
            {
                if (a_int_len > b_int_len) {
                    insertFront(b, makeNode('0'));
                    b_int_len++;
                }
                else if (a_int_len < b_int_len) {
                    insertFront(a, makeNode('0'));
                    a_int_len++;
                }
            }
        }
        if (a_dec_len != b_dec_len) {
            while (a_dec_len != b_dec_len)
            {
                if (a_dec_len > b_dec_len) {
                    insertBack(b, makeNode('0'));
                    b_dec_len++;
                }
                else if (a_dec_len < b_dec_len) {
                    insertBack(a, makeNode('0'));
                    a_dec_len++;
                }
            }
        }
        
        pList pst = makeList();
        answer = makeList();
        
        while (a->head != NULL) {
            if ((a->head->data - '0') * (b->head->data - '0') > 9) {
                insertBack(pst, makeNode((a->head->data - '0') * (b->head->data - '0') / 10) + '0');
                insertBack(answer, makeNode((a->head->data - '0') * (b->head->data - '0') % 10) + '0');
                deleteHead(a);
                deleteHead(b);
            }
            else if ((a->head->data - '0') * (b->head->data - '0')  < 10 && (a->head->data - '0') * (b->head->data - '0') > 0) {
                insertBack(pst , makeNode('0'));
                insertBack(answer, makeNode((a->head->data - '0') * (b->head->data - '0') + '0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if ((a->head->data - '0') * (b->head->data - '0') == 0){
                insertBack(pst, makeNode('0'));
                insertBack(answer, makeNode('0'));
                deleteHead(a);
                deleteHead(b);
            }
            else if (a->head->data == '.' && b->head->data  == '.') {
                insertBack(answer, makeNode('.'));
                deleteHead(a);
                deleteHead(b);
            }
        }
        insertBack(pst, makeNode('0'));
        int answer_Pointer = searchNode(answer,'.');
        insertMid(pst, answer_Pointer, makeNode('.'));
        if (isNode(pst, '1') == 1) {
            return multiply(answer, pst);
        }
        else {
            removeZero(answer);
            return answer;
        }
    }
    return answer;
}


pList seccalc(pList expr) {
    pNode curr = expr->head;
    struct nodeL* head = NULL;
    int word = 0;
    pList tempList,a,b;
    while(curr != NULL) {
        pList temp;
        if((isdigit(curr->data) || curr->data == '.') && word == 0) {
            tempList = makeList();
            insertBack(tempList, makeNode(curr->data));
            word = 1;
        }
        else if((isdigit(curr->data) || curr->data == '.') && word == 1) {
            insertBack(tempList, makeNode(curr->data));
        }
        else if(isspace(curr->data)) {
            pList pushList = tempList;
            if(tempList->count != 0)
                pushL(&head,pushList);
            word = 0;
        }
        else if(curr->data == '+') {
            a = popL(&head);
            b = popL(&head);
            temp = add(a,b);
            pushL(&head, temp);
        }
        else if(curr->data == '-') {
            b = popL(&head);
            a = popL(&head);
            temp = minus(a,b);
            pushL(&head, temp);
        }
        else if(curr->data == '*') {
            a = popL(&head);
            b = popL(&head);
            temp = multiply(a,b);
            pushL(&head, temp);
        }
        else if(curr->data == '/') {
            a = popL(&head);
            b = popL(&head);
            temp = division(a,b);
            pushL(&head, temp);
        }
        curr = curr->next;
    }
    pList answer = topL(head);
    return answer;
}


