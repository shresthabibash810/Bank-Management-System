/* BANK MANAGEMENT SYSTEM
   Made By: Bibash Shrestha
   BSc(Hons).Computing L3 Section C
   The British College
*/

                                         //Start Of Program
//Header Files

#include<iostream> //cout->output cin->input
#include<fstream> // File System ifstream(read) ofsream(write) fstream(both read and write)
#include<iomanip> //manipulator header files and using
#include<windows.h>// using for system coloring
using namespace std;



//Making Class Object named Account
class Account{
protected:
   int account_no;
    float balance;



public:

int no_deposits = 0;
int no_withdrawals = 0;
float monthly_servicecharge_rate = 0.25;

//Default Constructor
Account(){};

//Parameterized Constructor to accept account no, balance
Account(int acc_no, float bal){
     account_no=acc_no;
     balance=bal;


}
//Virtual Function for depositing an amount
virtual void makeDeposit(int x){
    balance = balance + x;
}
//Virtual Function for withdrawing an amount
virtual void makeWithdrawal(int x){
    balance = balance - x;
}
//Virtual Function for calculating an monthly interest and added to balance
virtual void calcInt(){
      float annualir, monthlyir, rate;

    rate=7.33;
    annualir=(balance*rate*1)/100;
    monthlyir=(annualir/12);
    int fin=balance + monthlyir;
    cout<<"\n Balance after Interest rate: "<<fin<<endl;

}
//Virtual Function for Monthly Service Charges
virtual void monthlyProc(int x, int y){
    float m_s_c_fromDeposit = ((0.25/100)*x);
    float m_s_c_fromWithdrawal = ((0.25 / 100)*y);
    float monthly_service_charge = m_s_c_fromDeposit + m_s_c_fromWithdrawal;
    cout << "Monthly service charge = "<<monthly_service_charge<<endl;
    int fin = balance - monthly_service_charge;
    cout << "Your total balance after deducting service charge will be: "<<fin<<endl;
}

};
//Creating saving account class which is inherited from Account class
//Due to inheritance, Saving class get accessed to Account class's Protected and Public Data
class Saving : public Account {


public:

//Printing this all in display statistics of file handeling portion
void display(){
    string status(int n);

    cout<<account_no<<setw(15)<<" "<<no_deposits<<setw(15)<<" "<<no_withdrawals<<setw(15)<<" "<<balance<<setw(10)<<" "<<status(account_no)<<endl;
}

void create(){ //Creating an account
	cout<<"Enter the Account No: "<<endl;
	cin>>account_no;
	cout<<"Enter Initial Balance: "<<endl;;
	cin>>balance;cout<<endl;
	cout<<"Your Account Has Been Created Successfully!!!"<<endl<<endl;
}

void show(){ //Showing an Account Information
	cout<<"Account No : "<<account_no<<endl;
	cout<<"Number of Deposits : "<<no_deposits<<endl;
	cout<<"Number of Withdrawals : "<<no_withdrawals<<endl;
	cout<<"Total Balance : "<<balance<<endl;

}

void modify(){ //Modifying an account balance for admin
    cout<<"Account No : "<<account_no<<endl;
	cout<<"Enter Modified Balance: "<<endl;
	cin>>balance;
	cout<<"Modified Successfully!!!!!"<<endl;
}

int return_account_no(){ //returning acc no and implementing in File Function
    return account_no;
}

int return_balance(){//returing balance
    return balance;
}
};

//Function Declaration for File Handeling
void store_account(); //function to write record in binary format and append format
void store_modify_account(int);//function modify account of a file
void delete_account(int); //function to delete account of a file
void dispay_stats();//function to display all information of file
void deposit(int); //function to display deposit of a file
void withdraw(int);//function to display withdraw of a file
void display_from_file(int);//function to display information of respective account no
string status(int);//function to check status is whether active or inactive


//Here Starts a Main Functions


int main(){
    system ("color 30"); //First Digit Background whereas Second Digit Foreground



int choice,user,num;
//Making Intro BackGround
cout<<"         Welcome to Bank Of TBC"<<endl;
cout<<"          Thapathali,Kathmandu"<<endl;
cout<<"         9840000001,9840000002"<<endl<<endl;
cout<<"Are you Admin(1) or Customer(2)?"<<endl;
cin>>user;
cout<<endl;
if (user == 1){ //Creating Menu Driven Program for Admin(1)
do{
    cout<<"List of Functions : "<<endl;
    cout<<"-------------------"<<endl;
    cout<<"1. Modify Account                2. Delete Account"<<endl;
    cout<<"3. View Stats                    4. Exit"<<endl<<endl;
    cout<<"Enter from 1 to 4: ";
    cin>>choice;
    cout<<endl;
    switch(choice){
        case 1:
            cout<<"Enter Account no: "<<endl;
            cin>>num;
            cout<<endl;
            store_modify_account(num);
            break;
        case 2:
            cout<<"Enter Account no: "<<endl;
            cin>>num;
            cout<<endl;
            delete_account(num);
            break;
        case 3:
            dispay_stats();
            break;
        case 4:
            cout<<"Good Work Admin!!"<<endl<<endl;

            break;
        default:
            cout<<"Enter valid number:"<<endl<<endl;
    }
}while(choice != 4);
}else if (user == 2){ //Creating Menu Driven for Customer (2)
do{
    cout<<"List of Functions : "<<endl;
    cout<<"-------------------"<<endl;
    cout<<"1. Add Account                   2. Withdraw"<<endl;
    cout<<"3. Deposit                       4. View Balance"<<endl;
    cout<<"5. Exit"<<endl<<endl;
    cout<<"Enter from 1 to 5: ";
    cin>>choice;
    cout<<endl;
    switch(choice){
        case 1:
            store_account();
            break;
        case 2:
            cout<<"Enter Account no: "<<endl;
            cin>>num;cout<<endl;
            withdraw(num);
            break;
        case 3:
            cout<<"Enter Account no: "<<endl;
            cin>>num;cout<<endl;
            deposit(num);
            break;
        case 4:
            cout<<"Enter Account no: "<<endl;
            cin>>num;cout<<endl;
            display_from_file(num);
            break;
       case 5:
            cout<<"Thank you for visiting Bank of TBC"<<endl<<endl;
            cout<<"Visit Again For Withdrawing and Depositing an amount"<<endl<<endl;
            break;
        default:
            cout<<"Enter valid number:"<<endl<<endl;
    }
}while(choice != 5);
}else{
cout<<"Enter Valid Data!!!"<<endl;
}
return 0;
}
//Creating File Function
void store_account(){
   /*This function is responsible for storing an account in a
   file called "Account.txt".
   */
    Saving acc;
	ofstream Out;
	Out.open("Account.txt",ios::binary|ios::app);//opening file in binary and append mode 
	acc.create();
	Out.write((char *)(&acc), sizeof(Saving));//writing in File
	Out.close();//closing a file
}

void store_modify_account(int a){
    //This function is responsible for modifying accounts from the "Account.txt" file.

    int x=1;
	Saving acc;
	fstream In;//both read and write
    In.open("Account.txt",ios::binary|ios::in|ios::out);//opening file in binary mode for input and output
	if(!In) 
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	while(!In.eof() && x==1)
	{
		long position;
		position=In.tellg();
		In.read((char *) (&acc), sizeof(Saving));
		if(acc.return_account_no()==a)
		{
			acc.show();
			cout<<"Enter The New Details of account: "<<endl;
			acc.modify();
		    In.seekg(position);
		    In.write((char *) (&acc), sizeof(Saving));
		    cout<<"Account Data Updated"<<endl;
		    x=x-1;
		  }
	}
	In.close();//closing a file
	if(x==1)
		cout<<"Account No. Not Found "<<endl;
}

void delete_account(int a){
    //This function is responsible for deleting accounts from the "Account.txt" file.

    Saving acc;
	ifstream in; //read
	ofstream out; //write
	in.open("Account.txt",ios::binary); //opening in binary mode
	if(!in)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	out.open("Temp.txt",ios::binary); //opening in binary mode
	in.seekg(0,ios::beg);//Go to start of file
	while(in.read((char *) (&acc), sizeof(Saving)))
	{
		if(acc.return_account_no()!=a)
		{
			out.write((char *) (&acc), sizeof(Saving));
		}
	}
    in.close();
	out.close();
	remove("Account.txt");
	rename("Temp.txt","Account.txt");
	cout<<"Account Deleted .."<<endl;
}

void dispay_stats(){
    /*This function is responsible for displaying the accounts
    stored in the "Account.txt" file.
    */
    Saving acc;
	ifstream in;
	in.open("Account.txt",ios::binary);//opening in binary mode
	if(!in)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	cout<<"                 ACCOUNT HOLDER LIST"<<endl;;
	cout<<"----------------------------------------------------------------------"<<endl;
	cout<<"Account no.      No_Deposit      No_Withdraw      Balance     Status"<<endl;
	cout<<"----------------------------------------------------------------------"<<endl;
	while(in.read((char *) (&acc), sizeof(Saving)))
	{
		acc.display();
	}
	in.close();
}

void deposit(int a){
    /*This function is responsible for depositing a specified
    amount to an account with a specified account number.
	*/
    int deposit;
	int x=1;
	Saving acc;
	fstream File;
    File.open("Account.txt", ios::binary|ios::in|ios::out);//opening in binary, input and output mode
	if(!File)
	{
		cout<<"File could not be open !!"<<endl<<endl;
		return;
	}
	while(!File.eof() && x==1)
	{
		long position;
		position=File.tellg();
		File.read((char *) (&acc), sizeof(Saving));//reading a file
		if(acc.return_account_no()==a)
		{
			acc.show();
				cout<<"To Deposit Amount"<<endl;
				cout<<"------------------"<<endl<<endl;
				cout<<"Enter The amount to be deposited: ";
				cin>>deposit;
				acc.makeDeposit(deposit);
				acc.no_deposits += 1;

            File.seekg(position);//Go back to position
			File.write((char *) (&acc), sizeof(Saving)); //Writing in a file
			cout<<"Amount Successfully Deposited!!!"<<endl<<endl;
			x=x-1;
		}
	}
File.close();
	if(x==1)
		cout<<"Account No. Not Found"<<endl;

}

string status(int a){ //Status is stored in file and it is implemented in Withdraw
    /*This function is responsible for returning the status of
    an account with a specified account number. */
    int i=1;
    Saving acc;
    string b;
    ifstream in;//read
    in.open("Account.txt", ios::binary|ios::in);//open in binary mode and input
    while(!in.eof() && i==1){
    in.read((char *) (&acc), sizeof(Saving));
    if(acc.return_account_no() == a){
            int a = acc.return_balance();
        if(a<25){
            b = "INACTIVE";
        }else{
            b = "ACTIVE";
        }
        i=i-1;
    }
    }
    in.close();
    if(i==1)
		cout<<"Account no. Not Found "<<endl;
return b;
}


void withdraw(int a){
    //This function is for  responsible for withdrawing an amount form acc no.
    int withdraw;
	int x=1;
	Saving acc;
	fstream File;
    File.open("Account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	while(!File.eof() && x==1)
	{
		long position;
		position=File.tellg();
		File.read((char *) (&acc), sizeof(Saving));
		if(acc.return_account_no()==a)
		{
		    string y = status(a); //implementing the string status(int a) function in here
			acc.show();
			if(y == "INACTIVE"){
                    cout<<"Account must have more than 25$ to withdraw again!!!"<<endl<<endl;
				}else{
				cout<<"To Withdraw Amount"<<endl;
				cout<<"-------------------"<<endl<<endl;
				cout<<"Enter The amount to be withdrawn: ";
				cin>>withdraw;cout<<endl;
				int a = acc.return_balance()-withdraw;
				if(a<0){
                    cout<<"Insufficient Balance"<<endl<<endl;
				}else if(a<25){
                    cout<<"Your Account will be Inactive if you withdraw."<<endl<<endl;
                    cout<<"Do you want to continue? Yes(1)/No(2)"<<endl;
                    int b;
                    cin>>b;
                    if (b == 1){
                        acc.makeWithdrawal(withdraw);
                        acc.no_withdrawals += 1;
                        cout<<"Amount Successfully Withdrawn!!!"<<endl<<endl;
                    }else if(b == 2){
                        return;
                    }else{
                        cout<<"Enter Valid Data"<<endl;
                    }
				}else{
				acc.makeWithdrawal(withdraw);
				acc.no_withdrawals += 1;
				cout<<"Amount Successfully Withdrawn!!!"<<endl<<endl;
				}
				}
			File.seekg(position);

			File.write((char *) (&acc), sizeof(Saving));

			x=x-1;
		}
	}
File.close();
	if(x==1)
		cout<<"Account No. Not Found"<<endl;

}
void display_from_file(int a){
	/*This function is responsible for displaying the details of
	an account with a specified account number from the "Account.txt"
	file.
	*/
	Saving acc;
	int x=1;
	ifstream in;
	in.open("Account.txt",ios::binary);//open in binary mode
	if(!in)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	cout<<"Account Details: "<<endl;
    	while(in.read((char *) (&acc), sizeof(Saving)))
	{
		if(acc.return_account_no()==a)

		{

			acc.show();//calling acc.show

			acc.calcInt(); //calling balance after monthly interest
			acc.monthlyProc(1,1);//calling monthly service charges and declare 1 for both withdraw and deposit monthly charges.
			x=x-1;
		}
	}
    in.close();
	if(x==1)
		cout<<"Account No. Not Found"<<endl;
}

                              //End of Program

