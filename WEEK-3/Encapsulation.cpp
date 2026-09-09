#include<iostream>
#include<string>
using namespace std;
 class BankAccount{
    private: 
           string owner;
           double balance;
    public: 
        void open(const string &name, double intial){
            owner = name;
            balance =(intial>0)?intial :0;
        }
        void deposit(double amt)
        {
            if(amt>0)balance+=amt;
        }
      bool withdraw(double amt)
      {
        if(amt>0 && amt<=balance)
        {
            balance-=amt;
            return true;
        }
        return false;
      }  
     
 double getBalance () const{
    return balance;

 }
 string getOwner() const
 {
    return owner;
 }
};
int main(){
    BankAccount a;
    a.open("Asha",1000);
    a.deposit(500);
    if(!a.withdraw(2000))
    cout<<"WITHDRAW DENIED(insuffeceinet)\n";
a.withdraw(300);
cout<<a.getOwner()<<"balance"
<<a.getBalance()<<endl;
return 0;
}