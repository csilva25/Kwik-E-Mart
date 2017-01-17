

#include <iostream>
#include <string>
#include "pqueue.h"
#include "cust.h"

using namespace std;

Pqueue::Pqueue()
{
    m_head = NULL;
}

Pqueue::~Pqueue()
{
    Node *ptr = m_head;
    while (ptr != NULL)
    {
        Node *temp;
        
        temp = ptr;
        ptr = ptr->m_next;
        delete temp;
    }
}

void Pqueue::enqueue(Cust *cust,int prio)
{
    if (m_head == NULL || m_head-> m_prio > prio)
    {
        m_head = new Node (cust,m_head, prio);
        m_size = m_size + 1;
    }
    else
    {
        Node *temp = m_head;
        while (temp->m_next != NULL && temp->m_next->m_prio <= prio)
        {
            temp = temp->m_next;
        }
        temp->m_next = new Node (cust,temp->m_next,prio);
    }
}

 bool Pqueue::empty()
{
    if (m_head == NULL)
    {
        return true;
    }
        return false;
}


//bool Pqueue::pop(double &value)
Cust *Pqueue::dequeue()
{
    if(m_head == NULL)
    {
        return NULL;
    }
    else
    {
    Cust * cust = m_head->m_cust;
    Node *temp = m_head;
    m_head = m_head->m_next;
    delete temp;
    m_size = m_size - 1;
    return cust;
    }
    
}

int Pqueue::get_prio()
{
    if(m_head == NULL)
    {
        return -1;
    }
    return m_head -> m_prio;
}

int Pqueue::get_size()
{
    Node *counter = m_head;
    int number = 0;
    while (counter != NULL)
    {
        number++;
        counter = counter->m_next;
    }
    return number;
    //return m_size;
}

/*
void Pqueue::checker(ostream &os, int number_of_checkers)
{
    int money[number_of_checkers];
    Cust *checkers [number_of_checkers];
    for (int i = 0; i < number_of_checkers; i++)
    {
        checkers[i] = NULL;
        money[i] = 100;
    
    }
};
*/




