#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <queue> 
#include <list>
using namespace std;

int bankHours = 12;  //bank is open for 12 hours
int numOfNewCustomers, //num of customer arriving 0-3 customer/sec
customerHelpTime; //amount of time each customer takes with the teller 1-2sec
int currentTime = 7; //bank opens at 7:00am
int bankBalance = 1000; //bank starts with $1000 a day
string amPm = "am";
int transactID = 0;

//vvvvvvvvvvvvvvvvvvvvvv-CLASSES-vvvvvvvvvvvvvvvvvvvvvv
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
    void setWorkTime(int x){//keep track how much time a teller goes inactive
      timeWorked = x;
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
    void returnTeller(int x, int z){
      timeWorked = x;
      //idleTime = y;
      tellerID = z;
    }
};

class Transaction {
  int customerTransactionTime, tellerWorkTime, tellerID, transactionID;
  public:
    void setTransactionTime (int x, int y, int z){
      customerTransactionTime = x;
      tellerWorkTime = y;
      tellerID = z;
    }
    const int getTransactionTime(){
      return customerTransactionTime;
    }
    void updateTransactionTime(){
      customerTransactionTime--;
      tellerWorkTime++;
    }
    int getTellerID(){
      return tellerID;
    }
    int getTellerWorkTime(){
      return tellerWorkTime;
    }
    void setTransactionID(int x){
      transactionID = x;
    }
    int getTransactionID(){
      return transactionID;
    }
    bool operator == (const Transaction& s) const { return customerTransactionTime == s.customerTransactionTime && tellerWorkTime == s.tellerWorkTime && tellerID == s.tellerID; }
    bool operator != (const Transaction& s) const { return !operator==(s); }
};
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

queue<Customer> customerLine; //max of 20
queue<Teller> tellerLine; //max of 5 
queue<Teller> tellerInactive; //max of 5
list<Transaction> activeTransaction; //push teller and customer for transaction

//vvvvvvvvvvvvvvvvvvvvvv-Functions/Methods-vvvvvvvvvvvvvvvvvvvvvv
void initializeTellers(){
  for (int i = 0; i < 5; i++){//initialize all tellers
    Teller newTeller;
    newTeller.setTellerID(i + 1);
    newTeller.setWorkTime(0);
    tellerInactive.push(newTeller);
  }
}

void addCustomerToLine(){
  //check the customer line to see if its too long
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
}

void activateTeller(){
  //push new teller object into array with time stamp for teller
    if(customerLine.size() > 16 && tellerLine.size() == 4){
      tellerLine.push(tellerInactive.front());
      tellerInactive.pop();
      //newTeller.updateTimeWorked();
    } else if (customerLine.size() > 12 && tellerLine.size() == 3){
      //newTeller.updateTimeWorked();
      tellerLine.push(tellerInactive.front());
      tellerInactive.pop();
    } else if (customerLine.size() > 8 && tellerLine.size() == 2){
      //newTeller.updateTimeWorked();
      tellerLine.push(tellerInactive.front());
      tellerInactive.pop();
    } else if (customerLine.size() > 4 && tellerLine.size() == 1){
      //newTeller.updateTimeWorked();
      tellerLine.push(tellerInactive.front());
      tellerInactive.pop();
    }
}

void initializeTransaction(){
  //get the teller with the longest wait time
  for(int i = 0; i < tellerLine.size() + 1; i++){
    if(customerLine.size() >= 1){
      Transaction transaction;
      //set the transaction with (customerTransactionLength, tellerTotalWorkHours, tellerID)
      transaction.setTransactionTime(customerLine.front().getTime(), tellerLine.front().getTotalTimeWorked(), tellerLine.front().getTellerID());
      transactID++;
      transaction.setTransactionID(transactID);

      //always have at least 1 active teller
      if (tellerLine.size() > 0 ) {
        tellerLine.pop();
      }
      customerLine.pop();
      cout << "customer is being helped by teller\nnumber of customers in line: " << customerLine.size() << endl;
      activeTransaction.push_back(transaction);
    } 
  }
}

void startTransaction(){
  for (auto iter = activeTransaction.begin(); iter != activeTransaction.end();){    
    //deincrement transactionTimes and increment tellerWorkTime
    cout << "transactionID: " << iter->getTransactionID() << " transaction time: " << iter->getTransactionTime() << endl;
    iter->updateTransactionTime();
    //remove any finished transactions and update teller work time and customer payment
    if(iter->getTransactionTime() == 0){
      cout << "teller " << iter->getTellerID() << " is available and has worked " << iter->getTellerWorkTime() << " hours so far" << endl;
      //erase element but first return back teller to line and update total work time
      Teller newTeller;
      newTeller.returnTeller(iter->getTellerWorkTime(), iter->getTellerID());
      tellerLine.push(newTeller);
      iter = activeTransaction.erase(iter);
      bankBalance = bankBalance + 7;
    }
  }
}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int main ()
{
  initializeTellers();
  cout << "\n----------The Bank is now open-----------" << endl;

  tellerLine.push(tellerInactive.front());
  tellerInactive.pop();

  while(currentTime < 20){
    if(currentTime >= 12){
      amPm = "pm";
    }

    cout << "\nIt is " << currentTime << ":00" << amPm << endl;
    numOfNewCustomers = rand() % 4; //how many customer arrive per second
    cout << "number of customers arriving: " << numOfNewCustomers << endl;
    
    addCustomerToLine();
    cout << "number of customers in line: " << customerLine.size() << endl;

    activateTeller();
    cout << "There are " << tellerLine.size() << " tellers active" << endl;
    
    // need to do a loop with the number of tellers active to add to transaction
    // currently only one transaction is activated each loop instead of 3 when there are 3 tellers
    initializeTransaction();
    cout << "number of transactions active: " << activeTransaction.size() << endl;

    startTransaction();
    currentTime++;
  }

  cout << "\n----------The Bank is now closed----------\n\nBanks remaining balance is $" << bankBalance << endl;
}

// have teller spots and keep track how much money you spend on tellers per second(seen as an hour)
//must manage a budget of $1,000
//tellers make $5 a second
//each client helped makes the bank $7
//client line should not exceed 20 ppl
//clients will be helped first in, first out
//tellers with the longest wait time to help will serve next
//customers can take up to 3 seconds to be helped by teller
//add 1 teller for every 4 customers
//start with 1 teller
//teller will handle the first 4 then any after that will be adding a new teller to manage money

//NOTES TO SELF
// make sure that tellers are being held up by a certain amount of time due to customer transaction length
// transactionID is being used to monitor the transaction if it occurs once or twice a second/hour
