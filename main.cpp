#include <iostream>
#include<string>
#include<conio.h>
#include "TicketStock.cpp"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

bool login();
string getpass();
void header();

int main(int argc, char** argv) {
	//creat a new instance of a class TicketStock
	TicketStock ticketStock(argc ,argv);
	if(login()){
		ticketStock.loading("Welcome", 1, "full");
		system("cls");
		while(true){
			string select;
			
			header();
			//menu
			cout << "\t  *** Welcome to Movie Ticket Management System ***\n" << endl;
			cout << "\t\t*****************************" << endl;
			cout << "\t\t\tTicket Phase" << endl;
			cout << "\t\t*****************************" << endl;
			cout << "\t\t1. Add Ticket" << endl;
			cout << "\t\t2. Search" << endl;
			cout << "\t\t3. View Ticket List" << endl;
			cout << "\t\t4. Edit Ticket" << endl;
			cout << "\t\t5. Delete Ticket" << endl;
			cout << "\t\t6. Clear Ticket By Type" << endl;
			cout << "\t\t7. Clear Ticket" << endl << endl;		
			cout << "\t\t*****************************" << endl;
			cout << "\t\t01 >> Update Ticket Record" << endl << endl;
			cout << "\t\t*****************************" << endl;
			cout << "\t\t\tStock Phase" << endl;
			cout << "\t\t*****************************" << endl;
			cout << "\t\t8. Ticket In & Ticket Out" << endl;
			cout << "\t\t9. Ticket History" << endl;
			cout << "\t\t10. Clear Ticket History" << endl << endl;
			cout << "\t\t02 >> Update Ticket Record" << endl << endl;			
			cout << "\t\t0. Close Application" << endl;
			cout << "\n\tEnter your option >> ";
			cin >> select;
			fflush(stdin);
			system("cls");
			if (select.compare("1") == 0){
				//invoke method
				string medicType = ticketStock.getType(ticketStock.displayType("add"));
				if(medicType!="empty"){
					//invoke method
					ticketStock.addTicket(medicType);
				}
			}
			else if (select.compare("2") == 0){
				//invoke method
				ticketStock.stockRecord_medic(ticketStock.searchTicket());	
			}
			else if (select.compare("3") == 0){
				//invoke method
				ticketStock.viewTicket("id", 0, 0);
			}
			else if (select.compare("4") == 0){
				//invoke method
				ticketStock.editTicket();
			}
			else if (select.compare("5") == 0){
				//invoke method
				ticketStock.deleteTicket();
			}
			else if (select.compare("6") == 0){
				//invoke method
				ticketStock.clearTicketByType();
			}
			else if (select.compare("7") == 0){
				//invoke method
				ticketStock.clearTicket();
			}			
			else if (select.compare("8") == 0){
				string select;
				while(select.compare("0") != 0){
					system("cls");
					//menu for stock in and stock out
					cout << "\n\n";
					cout << "\t       *** Movie Ticket Management System ***\n" << endl;
					cout << "\t-----------------------------------------------"<<endl;
					cout << "\t\t Choose one type of Ticket \n";
					cout << "\t-----------------------------------------------\n"<<endl;
					cout << "\t\t    1. Ticket In "<<endl;
					cout << "\t\t    2. Ticket Out" << endl << endl;
					cout << "\t\t    0 >> Go Back" << endl;
					cout << "\n\tEnter your options >> " ;
					cin >> select;
					fflush(stdin);
					
					if(select.compare("1") == 0){
						//invoke method
						ticketStock.stockManage("in");
					}
					else if(select.compare("2") == 0){
						//invoke method
						ticketStock.stockManage("out");
					}
					else if(select.compare("0") != 0){
						cout << "\n\tPlease input proper selection!!!";
						getch();
					}
				}
			}
			else if (select.compare("9") == 0){
				//invoke method
				ticketStock.stockRecord_all("all", 0, 0);
			}
			else if (select.compare("10") == 0){
				//invoke method
				ticketStock.cleatStockHistory();
			}
			else if (select.compare("01") == 0){
				//invoke method
				ticketStock.updateTicket();
				ticketStock.loading("Updating", 3, "full");
			}
			else if (select.compare("02") == 0){
				//invoke method
				ticketStock.updateStock();
				ticketStock.loading("Updating", 3, "full");
			}
			else if (select.compare("0") == 0){
				break; //break the loop
			}
			else{
				cout << "\n\tPlease input proper selection!!!";
			}
			fflush(stdin);
			system("cls");
		}
	}
	return 0;
}
// function to display header
void header()
{
	cout << "\n\n\t----------------------------------------------" << endl;
	cout << "\t           Movie Ticket Management System" << endl;
	cout << "\t----------------------------------------------" << endl;
}
//function to check login
bool login()
{
	string pass;
	header();
	cout << "\n\n\t\t ******WELCOME BACK!!!******" <<endl;
	cout << "\n\n\t ENTER PASSWORD TO LOGIN : ";
	pass = getpass();
	if(pass.compare("1234") == 0){ //compare password
		system("cls");
		return true;
	}else
	{
		cout << "\n\n\t\t    WRONG PASSWORD!!!!"<<endl;
		cout << "\t\t    PLEASE TRY AGAIN...";
		getch();
		system("cls");
		login();
	}
}
//funvtion to get input password
string getpass(){
	const char BACKSPACE = 8;
	const char RETURN = 13;	
	unsigned char ch = 0;
	string password;

	while ((ch = getch()) != RETURN){
		if (ch == BACKSPACE){
        	if (password.length() != 0){
            	cout << "\b \b";
                password.resize(password.length()-1);
            }
        }
    	else{
        	password += ch;
        	cout << '*';
        }
	}
	cout << endl;
	return password;
}
