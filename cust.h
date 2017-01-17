#ifndef CUST_H
#define CUST_H

#include <string>
#include <iostream>
using namespace std;

class Cust
{
   public:
   Cust(string name, bool robber, int arrival_time, int number_of_items);
  // ~Cust();
    void print_entered(ostream &os, int clock);
    void print_shopping(ostream &os, int clock);
    void print_checker(ostream &os, int clock, int checker);
    void print_leaving(ostream &os, int clock, int money, int checker);
    void calc_checking_out(int clock);
    int calc_shopping_time();
    bool done_checkout(int clock);
    //void checkout(int checkout);
    bool robber();
    int get_prio();
    int number_of_items();
    
    private:
    string m_name;
    bool m_robber;
    int m_arrival_time;
    int m_number_of_items;
    int m_leaving_time;
    
};

#endif