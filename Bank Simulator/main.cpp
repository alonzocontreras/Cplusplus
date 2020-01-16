{\rtf1\ansi\ansicpg1252\cocoartf2511
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;}
{\colortbl;\red255\green255\blue255;\red0\green0\blue255;\red255\green255\blue254;\red0\green0\blue0;
\red144\green1\blue18;\red19\green120\blue72;\red154\green154\blue154;}
{\*\expandedcolortbl;;\cssrgb\c0\c0\c100000;\cssrgb\c100000\c100000\c99608;\cssrgb\c0\c0\c0;
\cssrgb\c63922\c8235\c8235;\cssrgb\c3529\c53333\c35294;\cssrgb\c66667\c66667\c66667;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\sl420\partightenfactor0

\f0\fs28 \cf2 \cb3 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 #include\cf4 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 iostream\cf2 \strokec2 >\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf4 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 string\cf2 \strokec2 >\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf4 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 time.h\cf2 \strokec2 >\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf4 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 stdlib.h\cf2 \strokec2 >\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf4 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 vector\cf2 \strokec2 >\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf4 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 queue\cf2 \strokec2 >\cf4 \strokec4  \cb1 \
\cf2 \cb3 \strokec2 using\cf4 \strokec4  \cf2 \strokec2 namespace\cf4 \strokec4  std;\cb1 \
\
\cf2 \cb3 \strokec2 int\cf4 \strokec4  bankHours = \cf6 \strokec6 12\cf4 \strokec4 ;  \cf7 \strokec7 //bank is open for 12 hours\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 int\cf4 \strokec4  numOfNewCustomers, \cf7 \strokec7 //num of customer arriving 0-3 customer/sec\cf4 \cb1 \strokec4 \
\pard\pardeftab720\sl420\partightenfactor0
\cf4 \cb3 customerHelpTime; \cf7 \strokec7 //amount of time each customer takes with the teller 1-2sec\cf4 \cb1 \strokec4 \
\pard\pardeftab720\sl420\partightenfactor0
\cf2 \cb3 \strokec2 int\cf4 \strokec4  currentTime = \cf6 \strokec6 7\cf4 \strokec4 ; \cf7 \strokec7 //bank opens at 7:00am\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 int\cf4 \strokec4  bankBalance = \cf6 \strokec6 1000\cf4 \strokec4 ; \cf7 \strokec7 //bank starts with $1000 a day\cf4 \cb1 \strokec4 \
\pard\pardeftab720\sl420\partightenfactor0
\cf4 \cb3 string amPm = \cf5 \strokec5 "am"\cf4 \strokec4 ;\cb1 \
\pard\pardeftab720\sl420\partightenfactor0
\cf2 \cb3 \strokec2 int\cf4 \strokec4  tellersActive = \cf6 \strokec6 1\cf4 \strokec4 ; \cf7 \strokec7 //min of 1 and max of 5\cf4 \cb1 \strokec4 \
\
\cf2 \cb3 \strokec2 class\cf4 \strokec4  Customer \{\cb1 \
\pard\pardeftab720\sl420\partightenfactor0
\cf4 \cb3   \cf2 \strokec2 int\cf4 \strokec4  transactionTime;\cb1 \
\
\cb3   \cf2 \strokec2 public\cf4 \strokec4 :\cb1 \
\cb3     \cf2 \strokec2 void\cf4 \strokec4  set_values(\cf2 \strokec2 int\cf4 \strokec4  x)\{\cb1 \
\cb3       transactionTime = x;\cb1 \
\cb3     \}\cb1 \
\
\cb3     \cf2 \strokec2 int\cf4 \strokec4  getTime()\{\cb1 \
\cb3       \cf2 \strokec2 return\cf4 \strokec4  transactionTime;\cb1 \
\cb3     \}\cb1 \
\cb3 \};\cb1 \
\
\pard\pardeftab720\sl420\partightenfactor0
\cf2 \cb3 \strokec2 class\cf4 \strokec4  Teller \{\cb1 \
\pard\pardeftab720\sl420\partightenfactor0
\cf4 \cb3   \cf2 \strokec2 int\cf4 \strokec4  idleTime;\cb1 \
\
\cb3   \cf2 \strokec2 public\cf4 \strokec4 :\cb1 \
\cb3     \cf2 \strokec2 void\cf4 \strokec4  set_values(\cf2 \strokec2 int\cf4 \strokec4  x)\{\cb1 \
\cb3       idleTime = x;\cb1 \
\cb3     \}\cb1 \
\
\cb3     \cf2 \strokec2 int\cf4 \strokec4  getIdleTime()\{\cb1 \
\cb3       \cf2 \strokec2 return\cf4 \strokec4  idleTime;\cb1 \
\cb3     \}\cb1 \
\cb3 \};\cb1 \
\
\pard\pardeftab720\sl420\partightenfactor0
\cf2 \cb3 \strokec2 int\cf4 \strokec4  main ()\cb1 \
\pard\pardeftab720\sl420\partightenfactor0
\cf4 \cb3 \{\cb1 \
\cb3   vector<Customer> customerLine; \cf7 \strokec7 //max of 20\cf4 \cb1 \strokec4 \
\cb3   queue<Teller> tellerLine; \cf7 \strokec7 //max of 5 \cf4 \cb1 \strokec4 \
\cb3   Teller startTeller; \cf7 \strokec7 //first teller starts with idle of 0\cf4 \cb1 \strokec4 \
\cb3   startTeller.set_values(\cf6 \strokec6 0\cf4 \strokec4 );\cb1 \
\cb3   tellerLine.push(startTeller);\cb1 \
\
\cb3   cout << \cf5 \strokec5 "\\n----------The Bank is now open-----------"\cf4 \strokec4  << endl;\cb1 \
\
\cb3   \cf2 \strokec2 while\cf4 \strokec4 (currentTime < \cf6 \strokec6 19\cf4 \strokec4 )\{\cb1 \
\cb3     \cf2 \strokec2 if\cf4 \strokec4 (currentTime >= \cf6 \strokec6 12\cf4 \strokec4 )\{\cb1 \
\cb3       amPm = \cf5 \strokec5 "pm"\cf4 \strokec4 ;\cb1 \
\cb3     \}\cb1 \
\
\cb3     cout << \cf5 \strokec5 "\\nIt is "\cf4 \strokec4  << currentTime << \cf5 \strokec5 ":00"\cf4 \strokec4  << amPm << endl;\cb1 \
\cb3     numOfNewCustomers = rand() % \cf6 \strokec6 4\cf4 \strokec4 ; \cf7 \strokec7 //how many customer arrive per second\cf4 \cb1 \strokec4 \
\cb3     cout << \cf5 \strokec5 "number of customers arriving: "\cf4 \strokec4  << numOfNewCustomers << endl;\cb1 \
\cb3     \cb1 \
\cb3     \cf2 \strokec2 for\cf4 \strokec4  (\cf2 \strokec2 int\cf4 \strokec4  i = numOfNewCustomers; i > \cf6 \strokec6 0\cf4 \strokec4 ; i--)\{\cb1 \
\cb3           customerHelpTime = rand() % \cf6 \strokec6 2\cf4 \strokec4  + \cf6 \strokec6 1\cf4 \strokec4 ;\cb1 \
\
\cb3           \cf2 \strokec2 if\cf4 \strokec4 (customerLine.size() >= \cf6 \strokec6 20\cf4 \strokec4 )\{\cb1 \
\cb3             cout << \cf5 \strokec5 "customer line is long, customers didnt bother geting in line"\cf4 \strokec4  << endl;\cb1 \
\cb3             \cf2 \strokec2 break\cf4 \strokec4 ;\cb1 \
\cb3           \}\cb1 \
\
\cb3           Customer newCustomer; \cf7 \strokec7 //new customer object\cf4 \cb1 \strokec4 \
\cb3           \cf7 \strokec7 //cout << "time to help customer: " << customerHelpTime << endl;\cf4 \cb1 \strokec4 \
\cb3           newCustomer.set_values(customerHelpTime);\cb1 \
\cb3           customerLine.push_back(newCustomer);\cb1 \
\cb3     \}\cb1 \
\
\cb3     cout << \cf5 \strokec5 "number of customers in line: "\cf4 \strokec4  << customerLine.size() << endl;\cb1 \
\
\cb3     \cf7 \strokec7 //push new teller object into array with time stamp for teller\cf4 \cb1 \strokec4 \
\cb3     \cf2 \strokec2 if\cf4 \strokec4 (customerLine.size() > \cf6 \strokec6 16\cf4 \strokec4  && tellersActive < \cf6 \strokec6 5\cf4 \strokec4 )\{\cb1 \
\cb3       Teller newTeller;\cb1 \
\cb3       \cf7 \strokec7 //cout << "--> Teller idleTime: " << clock() << endl;\cf4 \cb1 \strokec4 \
\cb3       newTeller.set_values(clock());\cb1 \
\cb3       tellerLine.push(newTeller);\cb1 \
\cb3       tellersActive++;\cb1 \
\cb3     \} \cb1 \
\cb3     \cf7 \strokec7 // else if (customerLine.size() > 12 && tellersActive < 5)\{\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   Teller newTeller;\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   newTeller.set_values(clock());\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   tellerLine.push(newTeller);\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   tellersActive++;\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 // \} else if (customerLine.size() > 8 && tellersActive < 5)\{\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   Teller newTeller;\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   newTeller.set_values(clock());\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   tellerLine.push(newTeller);\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   tellersActive++;\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 // \} else if (customerLine.size() > 4 && tellersActive < 5)\{\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   Teller newTeller;\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   newTeller.set_values(clock());\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   tellerLine.push(newTeller);\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   tellersActive++;\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 // \}\cf4 \cb1 \strokec4 \
\
\cb3     cout << \cf5 \strokec5 "There are "\cf4 \strokec4  << tellerLine.size() << \cf5 \strokec5 " tellers active"\cf4 \strokec4  << endl;\cb1 \
\
\cb3     \cf7 \strokec7 //get the teller with the longest wait time\cf4 \cb1 \strokec4 \
\cb3     \cb1 \
\cb3     \cf7 \strokec7 //said teller will pull the next customer from customerLine array\cf4 \cb1 \strokec4 \
\
\cb3     \cf7 \strokec7 // for (int i = 0; i < customerLine.size(); i++)\{\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 //   cout << "customer " << i + 1 << ": " << customerLine[i].getTime() << "sec ";\cf4 \cb1 \strokec4 \
\cb3     \cf7 \strokec7 // \}\cf4 \cb1 \strokec4 \
\cb3     currentTime++;\cb1 \
\cb3   \}\cb1 \
\
\cb3   cout << \cf5 \strokec5 "\\n----------The Bank is now closed----------\\n\\nBanks remaining balance is $"\cf4 \strokec4  << bankBalance << endl;\cb1 \
\cb3 \}\cb1 \
\
\pard\pardeftab720\sl420\partightenfactor0
\cf7 \cb3 \strokec7 // have teller spots and keep track how much money you spend on tellers per second(seen as an hour)\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //must manage a budget of $1,000\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //tellers make $5 an second\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //each client helped makes the bank $7\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //client line should not exceed 20 ppl\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //clients will be helped first in, first out\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //tellers with the longest wait time to help will serve next\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //customers can take up to 3 seconds to be helped by teller\cf4 \cb1 \strokec4 \
\
\cf7 \cb3 \strokec7 //add 1 teller for every 4 customers\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //start with 1 teller\cf4 \cb1 \strokec4 \
\cf7 \cb3 \strokec7 //teller will handle the first 4 then any after that will be adding a new teller to manage money\cf4 \cb1 \strokec4 \
}