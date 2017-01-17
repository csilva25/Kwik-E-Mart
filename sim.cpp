#include "cust.h"
#include "pqueue.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
using namespace std;

//void run_simulation(Pqueue &arrival_q, int number_of_checkers, int time_return_break, ostream &fout);

typedef struct checkers
{
    int money_in_reg;
    int time_return_break;
    Cust * customer;
    int m_time;

    
}checker;

bool legal_int(char *str)
{
    char* temp = str;
while (*temp != 0)
{
    if ( isdigit(*temp ) == false )
    {
        return false;
    }
    temp ++;
    
}
    return true;
}




void run_simulation(Pqueue &arrival_q, int number_of_checkers, int time_return_break, ostream &fout)
{
    Pqueue shopping_q;
    Pqueue checkout_q;
    int clock = 0;
    checker* checkers = new checker [number_of_checkers];
    for (int i = 0 ; i < number_of_checkers; i ++)
    {
        checkers[i].money_in_reg = 100;
        checkers[i].time_return_break = 0;
        checkers[i].customer = NULL;
        checkers[i].m_time = 0;
        
    }
    
    
    int number_of_customers = arrival_q.get_size();
    

    
    for (clock = 0; number_of_customers > 0 ; clock ++)
    {
        
        while (arrival_q.empty() !=true && arrival_q.get_prio() == clock)
        {
            Cust * temp = arrival_q.dequeue();
            temp -> print_entered(fout, clock);
            shopping_q.enqueue(temp, temp->calc_shopping_time());
        }
        
        while(shopping_q.empty() !=true && shopping_q.get_prio() == clock)
        {
            Cust * temp = shopping_q.dequeue();
            temp -> print_shopping(fout,  clock);
            checkout_q.enqueue(temp,0);
        }

        
        
        for (int i = 0; i <  number_of_checkers ; i++)
        {
          //  cerr<< i <<endl;
            
            if (checkers[i].customer !=NULL && checkers[i].customer -> done_checkout( clock))
            {
                
               // cerr<<" pring leaving IF loop" <<endl;
                
              checkers[i].customer->print_leaving(fout, clock, checkers[i].money_in_reg,i);
                
                if (checkers[i].customer -> robber() == true)
                {
                    
                    checkers[i].money_in_reg = 0;
                    checkers[i].m_time = clock + time_return_break;
                   // cerr << checkers[i].money_in_reg<<endl;

                    
                }
                else
                {
                    
                    checkers[i].money_in_reg += (checkers[i].customer->number_of_items()*3);
                    //cerr << checkers[i].money_in_reg<<endl;
                }
                
               // delete checkers[i].customer;
                number_of_customers--;
                checkers[i].customer = NULL;
            }
        }
        for (int i = 0; i <number_of_checkers; i++)
        {
            //cerr<< "checkout for loop"<<endl;
            if (checkout_q.empty() == false && checkers[i].customer == NULL && checkers[i].m_time <= clock)
            {
                //cerr<<"check out IF loop" <<endl;
                
                checkers[i].customer = checkout_q.dequeue();
                checkers[i].customer -> print_checker(fout , clock , i);
                checkers[i].customer -> calc_checking_out(clock);
            }
        }


       // exit(1);
    
    }

    for (int i = 0; i < number_of_checkers; i++)
    {
        fout <<  "registers[" <<  i << "] = $" << checkers[i].money_in_reg <<endl;
    }
    fout << "time = " <<clock<<endl;

}




int main(int argc, char *argv[])
{
    
    
    if (argc != 5)
    {
        //Must specify input and output file.
        cerr << "Error: invalid number of command line arguments." << endl;
        exit(1);
    }
    
    Pqueue arrival_q;
    string name;
    string shopper;
    bool robber;
    int arrival_time = 0;
    int number_of_items = 0;
    int number_of_customers = 0;
 //   int time_return_break=0;
    
    ifstream my_ifile(argv[3], ios::in);
    ofstream my_ofile(argv[4], ios::out);
   
    if (!my_ifile)
    {
        //Could not open input file
        cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
        exit(1);
    }
   
    else if (atoi(argv[2]) < 0)
    {
        cerr << "Error: invalid checker break duration specified." << endl;
        exit(1);
    }
    else if(legal_int(argv[1])==false)
    {
        cerr << "Error: invalid number of checkers specified." << endl;
        exit(1);
        
    }
    else if (atoi(argv[1]) < 1)
    {
        cerr << "Error: invalid number of checkers specified." << endl;
        exit(1);
    }
    
    else if (!my_ofile)
    {
        //Could not open output file
        cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
        exit(1);
    }
    else if (!my_ofile || !my_ifile)
    {
        //Must specify input and output file.
        cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
        cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
        exit(1);
    }
    int count = 0;
    while (my_ifile >> name)
    {
        
        my_ifile >> shopper;
        
        if (shopper == "shopper")
        {
            robber = false;
        }
        else{
            robber = true;
        }
        my_ifile >> arrival_time;
        my_ifile >> number_of_items;
    
        arrival_q.enqueue(new Cust(name, robber, arrival_time, number_of_items), arrival_time);
        number_of_customers ++;
        count ++;
        //cerr<<count<<endl;
    
    /*
     1.read customers one at a time
     2. create new customer objects
     customer cust = new customer (name,type,time,items)
     3.insert customer in priority (arrival queue) queue
     */
    
    }
    
    
    run_simulation( arrival_q,  atoi(argv[1]),  atoi(argv[2]),  my_ofile);

}

 /*
    for (int clock = 1; number_of_customers > 0; clock ++)
    {
        if (arrival_time == clock)
        {
            add_customer.dequeue();//1
            cout<< name << "entered store."<<endl; //2
            add_shopper.enqueue (*cust,  prio) //4
            
  
            
            1. remove cus from arrival que
            2. print "enter store"
            3. calculate when theyre done shipping (time + shopping) -> int time
            4. place them in a shopping que
        }
        if (time = clock)
        {
            1. remove from shoppin
  g que
            2."done shopping"
            3. checkout - q
        }
    }
  
    
    while (arrival_q.get_prio() == clock)
    {
        Cust *cur_cust = arrival_q.dequeue();
        cur_cust->print_entered(ostream &os, int clock);
        shopping_q.enqueue( cur_cust , cur_cust -> done_shopping_time());
    }
    
    return 0;
  */

  
