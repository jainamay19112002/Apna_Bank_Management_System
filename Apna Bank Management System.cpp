                                                    /*APNA BANK */

/*HEADER FILE*/
#include<bits/stdc++.h>
#include<fstream>
#include<iomanip>
#include<cctype>
using namespace std;

class Account{
    int acno;
	char name[50];
	int deposit;
	char type;
    public:
	//creating an account //
    void createaccount(){
        cout<<"\n Enter account number: ";
        cin>>acno;
        cout<<"\n Enter name of account holder: ";
        cin.getline(name,50);
        cout<<"\nEnter Type of The account (C/S) : "; /*C=current account || S=saving account */
	    cin>>type;
	    type=toupper(type);
	    cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	    cin>>deposit;
	    cout<<"\n\n\nAccount Created Sucessfully..";
}
//showing details of the account//
   void showaccount()const{
       cout<<"\naccount number: "<<acno;
       cout<<"\naccount holder name: "<<name;
       cout<<"\ntype of account: "<<type;
       cout<<"\nIntial amount: "<<deposit;

   }
   // modifying the details of the account//
   void modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}
//deposited amount//
void dep(int x){
	deposit+=x;
}
//withdrawal amount//
	
void draw(int x){
	deposit-=x;
}
	
void report() const{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

	
int retacno() const{
	return acno;
}

int retdeposit() const{
	return deposit;
}

char rettype() const{
	return type;
}
};
void write_account();	            //function to write record in binary file
void display_sp(int);	           //function to display account details given by user
void modify_account(int);	       //function to modify record of file
void delete_account(int);	      //function to delete record of file
void display_all();		          //function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();
int main(){
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\t APNA BANK";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	Account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.createaccount();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
	outFile.close();
}


//    	function to read specific record from file //

void display_sp(int n)
{
	Account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if(ac.retacno()==n)
		{
			ac.showaccount();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}



//    	function to modify record of file //

void modify_account(int n)
{
	bool found=false;
	Account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.retacno()==n)
		{
			ac.showaccount();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(Account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
 
//    	function to delete record of file //


void delete_account(int n)
{
	Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}


//    	function to display all accounts deposit list //


void display_all()
{
	Account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		ac.report();
	}
	inFile.close();
}


//    	function to deposit and withdraw amounts //

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	Account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.retacno()==n)
		{
			ac.showaccount();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}



//    	AN INTRODUCTION FUNCTION


void intro()
{
	cout<<"\n\n\n\t APNA";
	cout<<"\n\n\t BANK";
	cout<<"\n\n\t MANAGEMENT";
	cout<<"\n\n\t SYSTEM";
	
	cin.get();
}



