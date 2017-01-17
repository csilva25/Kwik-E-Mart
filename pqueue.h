#ifndef PQUEUE_H
#define PQUEUE_H
#include <iostream>
#include <string>
#include "cust.h"

using namespace std;

class Pqueue
{
public:
    Pqueue();
    ~Pqueue();
    Cust *dequeue();
    void enqueue(Cust *cust, int priority);
    int get_prio();
    bool empty();
    void checker(ostream & os, int number_of_checkers);
    void print();
    int get_size();
    
    
private:
    
    class Node
    {
    public:
        Node (Cust* cust, Node* next, int prio)
        {m_next=next; m_cust=cust; m_prio=prio;}
        
        Cust *m_cust;
        Node *m_next;
        int m_prio = 0;
    };
    
    Node *m_head;
    int m_size = 0;
    
};



#endif