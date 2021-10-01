/*
Made by Anuran Roy (https://github.com/anuran-roy)
*/

#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include <chrono>
#include <thread>

#define ll long long int
using namespace std;

hash<string> hashfunc;

typedef struct content // The metadata of a block
{
    string lastblock;
    ll bno;
} block;

string getTime(){ // method to get the current time
    return to_string(time(nullptr));
}

void proofOfWork(int time){ // a simple proof-of-work algorithm
    cout << "\nSolving the proof of work puzzle worth " << time/1000 << "seconds...\n\n";
    this_thread::sleep_for(chrono::milliseconds(time));
}

int digits(ll t){
    int i = 0;

    while(t>0){
        ++i;
        t = (int)t/10;
    }

    return i;
}

ll applyLock(){
    srand(0);

    return rand()%20+10;
}

class Transaction // The smallest unit of a blockchain - The Transaction
{
    public:
    Transaction(){

    }
    Transaction(string sender, string receiver, float amt)
    {
        senderAddress = sender;
        receiverAddress = receiver;
        amount = amt;
    }
    
    void printDetails(){
        cout << "Sender:\t" << senderAddress << endl;
        cout << "Receiver:\t" << receiverAddress << endl;
        cout << "Amount:\t" << amount << endl;
    }
    float getAmount(){
        return amount;
    }
    string getReceiver(){
        return receiverAddress;
    }
    string getSender(){
        return senderAddress;
    }
    protected:
    string senderAddress;
    string receiverAddress;
    float amount;
};

class Node // The encapsulation of a Transaction
{
    public:
    Node(const Transaction &a, ll num, string lastblock){
        nodeTransaction = a;
        current.lastblock = lastblock;
        current.bno = num;
    }
    block getDetails(){
        return current;
    }
    void printDetails(){
        cout << "\nTransaction Info:\n";
        nodeTransaction.printDetails();

        cout << "\n\nBlock Info:\n";
        cout << "Block number:\n" << current.bno << endl;
        cout << "Hash of last block:\n" << current.lastblock << endl;
    }
    Transaction getTransaction(){
        return nodeTransaction;
    }
    private:
    Transaction nodeTransaction;
    block current;

};

string hashNode(Node a){
    block details = a.getDetails();
    string t = getTime() + details.lastblock + to_string(details.bno);

    return to_string(hashfunc(t));

}

bool NodeEquals(Node a, Node b){
        bool resp = false;
        string t1_sender = a.getTransaction().getSender();
        string t1_receiver = a.getTransaction().getReceiver();
        float t1_amount = a.getTransaction().getAmount();

        string t2_sender = b.getTransaction().getSender();
        string t2_receiver = b.getTransaction().getReceiver();
        float t2_amount = b.getTransaction().getAmount();

        ll t1_bno = a.getDetails().bno;
        string t1_lastblock = a.getDetails().lastblock;

        ll t2_bno = b.getDetails().bno;
        string t2_lastblock = b.getDetails().lastblock;

        if(t1_sender == t2_sender)
        {
            if(t1_receiver == t2_receiver)
            {
                if(t1_amount == t2_amount)
                {
                    if(t1_bno == t2_bno)
                    {
                        if(t1_lastblock == t2_lastblock)
                        {
                            resp = true;
                        }
                    }
                }
            }
        }

        return resp;
    }
class Ledger // The sequenced chain of blocks
{
    public:
    vector<Node> getLedger()
    {
        return ledger;
    }
    void setLedger(vector<Node> &a)
    {
        ledger.assign(a.begin(), a.end());
    }
    void addToLedger(const Node &a)
    {
        const Node b = a;
        ledger.push_back(b);
    }
    ll ledgerLength(){
        return ledger.size();
    }
    void printInstance(int i){
        ledger[i].printDetails();
    }
    Node getInstance(int i){
        return ledger[i];
    }
    private:
    vector<Node> ledger;
};

class User // A user in the blockchain network
{
    public:
    User(string seed, float amt){
        address = to_string(hashfunc(seed));
        balance = amt;
        lastTransactionTime = time(0);
        lockTime = 0;
    }
    string getAddress(){
        return address;
    }
    bool receiveToken(float amt){      
        if(amt >= 0.0){
            balance += amt;
            return true;
        }
        else{
            cout << "\n\nCannot receive negative amount of tokens.\n\n";
            return false;
        }
    }
    bool sendToken(float amt){
        if(amt <= balance && amt>=0.0){
            balance -= amt*1.0;
            return true;
        }
        else{
            return false;
        }
    }
    void setUserLedger(const vector<Node> &a)
    {
        ledgerCopy.assign(a.begin(), a.end());
    }
    void getDetails(){
        cout << "\nUser address:\t" << address;
        cout << "\nBalance:\t" << balance << "\n\n";
        cout << "\nLedger details for user:" << endl;
        for(int i=0; i<ledgerCopy.size(); i++)
            ledgerCopy[i].printDetails();
    }
    void printLedger(){
        for(int i=0; i<ledgerCopy.size(); i++)
            ledgerCopy[i].printDetails();
    }
    vector<Node> getUserLedger(){
        return ledgerCopy;
    }
    void setLock(ll t){
        lockTime = t;
    }
    bool PoET(ll time){ // PoET = Proof of Elapsed Time
        if( time > (lockTime + lastTransactionTime)){
            lastTransactionTime = time;
            return true;
        }
        else{
            return false;
        }
    }
    private:
    string address;
    float balance;
    vector<Node> ledgerCopy;
    ll lastTransactionTime;
    ll lockTime;
};

class UserList
{

    public:
    vector<User> getUsersList(){
        return users;
    }
    void addNewUser(User &a){
        users.push_back(a);
    }
    User getUser(string hash){
        for(int i=0; i<users.size(); i++){
            if(users[i].getAddress() == hash){
                return users[i];
            }
        }

        return User("", 0.0);
    }
    User getUser(int i){
        if(i < users.size() && i > 0){
            return users[i];
        }
        else{
            return User("", 0.0);
        }
    }
    ll size(){
        return users.size();
    }


    private:
    vector<User> users;
};

User makeUser(float amt){
    string seed;
    cout << "\n\nEnter seed phrase:\n\n";
    cin >> seed;
    User newUser = User(seed, amt);
    return newUser;
}

bool compareLedgers(User a, User b){
    // cout << "\ncompareLedgers() invoked!\n";
    vector<Node> l1;
    // cout << "Going to invoke assign() for l1\n\n";
    l1 = a.getUserLedger();
    // l1.assign(a.getUserLedger().begin(), a.getUserLedger().end());
    vector<Node> l2;
    // cout << "Going to invoke assign() for l2\n\n";
    l2 = b.getUserLedger();
    // l2.assign(b.getUserLedger().begin(), b.getUserLedger().end());

    if (l1.size() == l2.size()){
        for(int i = 0; i < l1.size(); i++){
            if (NodeEquals(l1[i],l2[i])){
                cout << "";
            }
            else{
                return false;
            }
        }
        return true;
    }
    return false;
}

class Miner{
    public:
    Miner(string seed){
        timejoined = time(0);
        rate = 10;
        balance = 0.0;
        address = to_string(hashfunc(seed));
    }
    string getAddress(){
        return address;
    }
    bool receiveToken(float amt){      
        if(amt >= 0.0){
            balance += amt;
            return true;
        }
        else{
            cout << "\n\nCannot receive negative amount of tokens.\n\n";
            return false;
        }
    }
    bool sendToken(float amt){
        if(amt <= balance && amt>=0.0){
            balance -= amt*1.0;
            return true;
        }
        else{
            return false;
        }
    }
    void rateUpdate(){
        rate *= exp(1.5*(timejoined - time(0))/pow(10, digits(time(0)+1)));
    }
    void reward(){
        if(balance == 0.0){
            balance += 1.0;
        }
        else{
            balance += balance*rate/10;
        }
    }
    void setMinerLedger(const vector<Node> &a)
    {
        ledgerCopy.assign(a.begin(), a.end());
    }
    void getDetails(){
        cout << "\nMiner address:\t" << address;
        cout << "\nBalance:\t" << balance << "\n\n";
        cout << "\nLedger details for user:" << endl;
        for(int i=0; i<ledgerCopy.size(); i++)
            ledgerCopy[i].printDetails();
    }
    void printLedger(){
        for(int i=0; i<ledgerCopy.size(); i++)
            ledgerCopy[i].printDetails();
    }
    vector<Node> getMinerLedger(){
        return ledgerCopy;
    }

    private:
    ll timejoined;
    string address;
    float rate;
    float balance;
    vector<Node> ledgerCopy;
    ll lastTransactionTime;

};
class MinerList{
    public:
    vector<Miner> getMinersList(){
        return miners;
    }
    void addNewMiner(Miner &a){
        miners.push_back(a);
    }
    Miner getMiner(string hash){
        for(int i=0; i<miners.size(); i++){
            if(miners[i].getAddress() == hash){
                return miners[i];
            }
        }

        return Miner("");
    }
    Miner getMiner(int i){
        if(i < miners.size() && i > 0){
            return miners[i];
        }
        else{
            return Miner("");
        }
    }
    ll size(){
        return miners.size();
    }


    private:
    vector<Miner> miners;
};
class Contract: protected Transaction{ 
// You can customize this class by extending it, but it should always inherit Transaction.
// Also, it MUST contain the boolean functions validate() and must call bool transit().
// An atomic contract (ie., the most basic contract) involves two users and a transaction. 
    public:
    Contract(){
        // num = 0;
    }
    bool validate(User &a, User &b, Node &n){
        // num++;
        // if (num%2)
        //     return false;
        // else{
        //     if(transit(a, b, n.getTransaction().getAmount())){
        //         return true;
        //     }
        //     else{
        //         return false;
        //     }
        // }
        if(transit(a, b, n.getTransaction().getAmount())){
            return true;
        }
        else{
            return false;
        }
    }
    protected:
    bool transit(User &sender, User &receiver, float amt){
        srand(time(0));

        ll locktime = applyLock();
        ll timeNow = time(0);
        if(sender.PoET(timeNow) && receiver.PoET(timeNow))
        {
            if(sender.sendToken(amt)){
                receiver.receiveToken(amt);

                sender.setLock(locktime);
                receiver.setLock(locktime);
                cout << "\n\nTransaction complete!\n\n";
                cout << "A lock time of " << locktime << " seconds has been set on the users.\n\n";
                return true;
            }
            else{
                cout << "\n\nTransaction couldn't be completed. Check the balance of sender, and the amount of tokens sent.\n\n";
                return false;
            }
        }
        else{
            cout << "\nThe sender and/or the receiver isn't ready for the transaction to take place.\n";
            return false;
        }
    }
    // int num;

};


Node makeNode(string usr1, string usr2, float amt, string THash, ll bnum)
{
    Transaction tx = Transaction(usr1, usr2, amt);
    Node nNode = Node(tx, bnum, THash);

    return nNode;
}

User voting(UserList &a)
{
    // User c1 = a.getUser(0);
    // User c2 = a.getUser(1);
    int mostCommon;
    ll lsize = a.size();
    ll maxcount = 0;
    ll count = 0;
    for(int i = 0; i < lsize; i++){
        for(int j = 0; j < lsize; j++){
            if(compareLedgers(a.getUser(i), a.getUser(j))){
                count++;
                if(count > maxcount){
                    maxcount = count;
                    mostCommon = i;
                }
            }
        }
    }

    return a.getUser(mostCommon);
}

int main2()
{
    Ledger ledgerInstance = Ledger();
    UserList userslist = UserList();
    
    cout << "\nEnter number of mock transactions to generate:\n";
    int n;
    cin >> n;

    Node genesisBlock = Node(Transaction("__init__","__init__",0.00), 1, to_string(hashfunc("0")));    
    cout << "\n" << "Genesis block:\nHash: " << hashNode(genesisBlock) << "\n";
    string THash = hashNode(genesisBlock);
    Contract democontract = Contract();

    cout << "\n\nEnter balance of sender to initialize with:";
    float a;
    cin >> a;
    User u1 = makeUser(a);
    userslist.addNewUser(u1);
    string sender = u1.getAddress();

    cout << "\n\nEnter balance of receiver to initialize with:";
    cin >> a;
    User u2 = makeUser(a);
    userslist.addNewUser(u2);
    string receiver = u2.getAddress();

    cout << "\n\nEnter amount to initialize the third user with:";
    cin >> a;
    User u3 = makeUser(a);
    userslist.addNewUser(u3);
    string observer = u3.getAddress();

    ledgerInstance.addToLedger(genesisBlock);

    for(int i = 0; i < n-1; i++){
        cout << "\n\n-----------------------------\n\nMaking new block..." << endl;
        // Transaction tx = Transaction("abc", "def", 0.00);
        cout << "Hash of last block: " << THash << endl;

        // tx.printDetails();
        cout << "Enter amount to be transacted for Transaction ID " << to_string(i+1) << ":\n";
        cin >> a;
        Node nd = makeNode(sender, receiver, a*1.00, THash, i+2);
        nd.printDetails();
        if(democontract.validate(u1, u2, nd)){
            THash = hashNode(nd);
            cout << "Hash of current block: " << THash << "\n\n-----------------------------\n\n";
            ledgerInstance.addToLedger(nd);
        }
        else{
            cout << "Block is not valid according to contract. Discarding block...\n\n-----------------------------\n\n";
        }
        // proofOfWork(5000);

        u1.setUserLedger(ledgerInstance.getLedger());
        u2.setUserLedger(ledgerInstance.getLedger());

          
    }
    cout << "\n\n--------------------------------- Printing Ledger ---------------------------------" << endl;
    for(int i = 0; i < ledgerInstance.ledgerLength(); i++){
        cout << "\n\n---------------------------------" << endl;
        if(i > 0){
            ledgerInstance.printInstance(i);
        }
        else{
            cout << "\n\nGenesis block (Block #1)";
        }
        cout << "\n\n---------------------------------" << endl;

         
    }
    
    cout << "\n========================================\nBalance of sender now: " << endl;
    u1.getDetails();
    
    cout << "\n========================================\nBalance of receiver now: " << endl;
    u2.getDetails();

    cout << "\n\nAre the ledgers same?\n\n";
    cout << compareLedgers(u1, u2) << endl;



    return 0;
}
int main1(){
    UserList userslist = UserList();

    while(true){
        cout << "Menu: \n1. Make a new user\n2. Make a new transaction\n3. View ledger\n\nEnter your choice:\t";
        int ch;
        cin >> ch;

        switch(ch){
            case 1:{
                cout << "\n\nEnter balance of sender to initialize with:";
                float a;
                cin >> a;
                User u = makeUser(a);

                if(userslist.size() == 0){

                }
                userslist.addNewUser(u);
                break;
            }
            case 2:{
                cout << "";
                break;
            }
            case 3:{
                userslist.getUser(0).printLedger();
                break;
            }
            default:{
                cout << "\nInvalid choice. Try again.\n";
                break;
            }
        }
    }
    return 0;
}
int main(){
    int a = main2();
    int b = main1();
}