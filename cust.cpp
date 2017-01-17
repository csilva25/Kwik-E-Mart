#include "cust.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <assert.h>

using namespace std;

Cust::Cust(string name, bool robber, int arrival_time, int number_of_items)
    {
        m_name = name;
        m_robber = robber;
        m_arrival_time = arrival_time;
        m_number_of_items = number_of_items;
    }

void Cust::print_entered(ostream &os, int clock)
{
    assert(clock == m_arrival_time);
    os << clock << ": "<< m_name << " entered store"<<endl;
}

void Cust::print_shopping(ostream &os, int clock)
{
   
    os << clock << ": "<< m_name << " done shopping"<<endl;
}

void Cust::print_checker(ostream &os, int clock, int checker)
{
    
    os << clock << ": "<< m_name << " started checkout with checker "<< checker <<endl;
}
void Cust::print_leaving(ostream &os, int clock, int money, int checker)
{
    if (m_robber == true)
    {
        os << clock << ": " << m_name << " stole $"  << money << " and " << m_number_of_items;
        
        if (m_number_of_items < 2)
        {
            os << " item " << "from checker " << checker << endl;;
        }
            else
            {
            os<< " items " << "from checker " << checker << endl;
            }
    }
        else
        {
            os << clock << ": " <<m_name << " paid $" << m_number_of_items *3 << " for " <<m_number_of_items;
            
            if (m_number_of_items < 2)
            {
                os << " item " << "to checker " << checker << endl;;
            }
            else
            {
                os<< " items " << "to checker " << checker << endl;
            }
        }
    
        
}



void Cust::calc_checking_out(int clock)
{
    if (robber() == false)
    {
        m_leaving_time =  clock + ( 1 * m_number_of_items);
        
    }
    else
    {
        m_leaving_time = clock + 4;
    }
    
    
}

int Cust::calc_shopping_time()
{
    return m_arrival_time + (m_number_of_items * 2);
}

bool Cust::done_checkout(int clock)
{
    if (m_leaving_time == clock) {
        return true;
    }
    else
        return false;
}

bool Cust::robber()
{
    return m_robber;
}

int Cust::get_prio()
{
    return m_arrival_time;
}
int Cust::number_of_items()
{
    return m_number_of_items;
}
