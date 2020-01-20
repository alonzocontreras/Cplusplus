#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <queue> 
#include <list>
using namespace std;

int bankHours = 12;  //bank is open for 12 hours
int numOfNewCustomers, //num of customer arriving 0-3 customer/sec
customerHelpTime; //amount of time each customer takes with the teller 1-2sec
int currentTime = 7; //bank opens at 7:00am
int bankBalance = 1000; //bank starts with $1000 a day
string amPm = "am";
int tellersActive = 1; //min of 1 and max of 5

class Customer {
  int transactionTime;

  public:
    void set_values(int x){
      transactionTime = x;
    }

    int getTime(){
      return transactionTime;
    }
};

class Teller {
  int timeWorked, idleTime, tellerID;

  public:
    void updateTimeWorked(){ //keep track how much each teller gets paid
      timeWorked++;
    }

    void setIdleTime(int x){//keep track how much time a teller goes inactive
      idleTime = x;
    }

    int getTotalTimeWorked(){
      return timeWorked;
    }

    void setTellerID(int x){
      tellerID = x;
    }

    int getTellerID(){
      return tellerID;
    }
};

class Transaction {
  int customerTransactionTime, tellerWorkTime, tellerID;

  public:
    void setTransactionTime (int x, int y, int z){
      customerTransactionTime = x;
      tellerWorkTime = y;
      tellerID = z;
    }
};

int main ()
{
  queue<Customer> customerLine; //max of 20
  queue<Teller> tellerLine; //max of 5 
  list<Teller> tellerInactive;
  Teller startTeller; //first teller starts with idle of 0
  startTeller.updateTimeWorked();
  startTeller.setTellerID(1);
  tellerLine.push(startTeller);
  queue<Transaction> activeTransaction; //push teller and customer for transaction

  cout << "\n----------The Bank is now open-----------" << endl;

  while(currentTime < 19){
    if(currentTime >= 12){
      amPm = "pm";
    }

    cout << "\nIt is " << currentTime << ":00" << amPm << endl;
    numOfNewCustomers = rand() % 4; //how many customer arrive per second
    cout << "number of customers arriving: " << numOfNewCustomers << endl;
    
    for (int i = numOfNewCustomers; i > 0; i--){
          customerHelpTime = rand() % 2 + 1;

          if(customerLine.size() >= 20){
            cout << "customer line is long, customers didnt bother geting in line" << endl;
            break;
          }

          Customer newCustomer; //new customer object
          //cout << "time to help customer: " << customerHelpTime << endl;
          newCustomer.set_values(customerHelpTime);
          customerLine.push(newCustomer);
    }

    cout << "number of customers in line: " << customerLine.size() << endl;

    //push new teller object into array with time stamp for teller
    if(customerLine.size() > 16 && tellersActive == 4){
      Teller newTeller;
      //cout << "--> Teller idleTime: " << clock() << endl;
      newTeller.updateTimeWorked();
      newTeller.setTellerID(5);
      tellerLine.push(newTeller);
      tellersActive++;
    } else if (customerLine.size() > 12 && tellersActive == 3){
      Teller newTeller;
      newTeller.updateTimeWorked();
      newTeller.setTellerID(4);
      tellerLine.push(newTeller);
      tellersActive++;
    } else if (customerLine.size() > 8 && tellersActive == 2){
      Teller newTeller;
      newTeller.updateTimeWorked();
      newTeller.setTellerID(3);
      tellerLine.push(newTeller);
      tellersActive++;
    } else if (customerLine.size() > 4 && tellersActive == 1){
      Teller newTeller;
      newTeller.updateTimeWorked();
      newTeller.setTellerID(2);
      tellerLine.push(newTeller);
      tellersActive++;
    }

    cout << "There are " << tellerLine.size() << " tellers active" << endl;

    //get the teller with the longest wait time
    if(customerLine.size() > 1){
      Transaction transaction;
      transaction.setTransactionTime(customerLine.front().getTime(), tellerLine.front().getTotalTimeWorked(), tellerLine.front().getTellerID());
      cout << "TellerID: " << tellerLine.front().getTellerID() << endl;
      if (tellerLine.size() > 1) {
        tellerLine.pop();
      }
      customerLine.pop();
    }
    
    //transaction.push();
    
    //said teller will pull the next customer from customerLine array

    // for (int i = 0; i < customerLine.size(); i++){
    //   cout << "customer " << i + 1 << ": " << customerLine[i].getTime() << "sec ";
    // }
    currentTime++;
  }

  cout << "\n----------The Bank is now closed----------\n\nBanks remaining balance is $" << bankBalance << endl;
}

// have teller spots and keep track how much money you spend on tellers per second(seen as an hour)
//must manage a budget of $1,000
//tellers make $5 an second
//each client helped makes the bank $7
//client line should not exceed 20 ppl
//clients will be helped first in, first out
//tellers with the longest wait time to help will serve next
//customers can take up to 3 seconds to be helped by teller

//add 1 teller for every 4 customers
//start with 1 teller
//teller will handle the first 4 then any after that will be adding a new teller to manage money
