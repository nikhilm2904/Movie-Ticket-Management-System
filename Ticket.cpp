//Filename: Ticket.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "TicketDetail.cpp"
#include "TicketType.cpp"

using namespace std;

class Ticket: public TicketType{
	private:
		//stucture declaration
		struct ticket{
			TicketDetail ticketDetail;
			ticket *next;
		}medic, *curr, *head, *temp, *newPtr, *row, *prev;
		int test;
		
	public:
		//constructor for class Ticket
		Ticket(){
			test = 0;
		};
		
		//destructor for class Ticket
		~Ticket(){};
		
		//method to add a ticket record
		void addTicket(string type){
			add:
				system("cls");
				medic.ticketDetail.setType(type);
				medic.ticketDetail.printTicketType();
				cout << "-----------------------------------------------------------------" << endl;
				cin.sync();
				//ask input for ticket id
				int askInput = medic.ticketDetail.askId(test);
				if(askInput==1){
					string id = medic.ticketDetail.getId();
					if(this->searching(id)==true){
						TicketType::loading("Check id", 1, "");
						cout << endl << " The ID is already exist... Please try again..." << endl;
						getch();
						goto add;
					}else ++test;
					medic.ticketDetail.setId(id);
					medic.ticketDetail.setType(type);
				}else if(askInput==3){
					TicketType::alert(2, "Empty");
					goto add;
				}else if(askInput==4){
					TicketType::alert(3, "15");
					goto add;
				}
				//ask input for ticket title
				askInput = medic.ticketDetail.askTitle(test);
				if(askInput==1)
					++test;
				else if(askInput==3){
					TicketType::alert(2, "Empty");
					goto add;
				}else if(askInput==4){
					TicketType::alert(3, "18");
					goto add;
				}
				//ask input for ticket description
				askInput = medic.ticketDetail.askDescribe(test);
				if(askInput==1)
					++test;
				else if(askInput==4){
					TicketType::alert(3, "80");
					goto add;
				}
				//ask input for ticket purchase price
				askInput = medic.ticketDetail.askPurchasePrice(test);
				if(askInput==1)
					++test;
				else if(askInput==3){
					TicketType::alert(1, "price");
					goto add;
				}else if(askInput==4){
					TicketType::alert(3, "18");
					goto add;
				}
				//ask input for ticket sold out price
				askInput = medic.ticketDetail.askSoldOutPrice(test);
				if(askInput==1)
					++test;
				else if(askInput==3){
					TicketType::alert(1, "price");
					goto add;
				}else if(askInput==4){
					TicketType::alert(3, "18");
					goto add;
				}
				medic.ticketDetail.setQuantity(0);
			
			if(TicketType::openfw(1, "ticket_record.txt")=="0"){
				perror(" Error open file : ");
				system("pause");
			}else{
				this->writeToFile();
				w.close();
				this->updateTicket();
				TicketType::loading("Adding", 2, "");
				cout << endl << " Ticket : " << medic.ticketDetail.getTitle() << " add successful!!" << endl;
			}
			w.close();
			test = 0;
			cout << endl << "\t";
			system("pause");
		};
		
		//method to edit a ticket data
		void editTicket(){
			system("cls");
			if(this->ticketList()){
				string id;
				cout << endl << " Enter id to edit : ";
				getline(cin, id);
				TicketType::loading("Searching", 2, "");
				system("cls");
				string oldf = TicketType::openfr(1, "ticket_record.txt");
				if(oldf=="0"){
					cout << endl << endl << " Currently do not insert for any record..." << endl;
				}else{
					r.close();
					if(!searching(id)){
						cout << endl << endl << " The id " << id << " is not found... Please try again..." << endl;
					}else{
						TicketType::openfr(1, "ticket_record.txt");
						int choice=99;
						int type;
						string newf = TicketType::openfw(1, "temp.txt");
						r.seekg(0, ios::beg);
						while(this->readFromFile()){
							if(id==medic.ticketDetail.getId()){
								while(choice!=0){
									int askInput;
									system("cls");
									medic.ticketDetail.displayTicket(0);
									cout << "-------------------------------------------------------------------------" << endl << endl;
									cout << " Update for >> " << endl;
									cout << " 1. Title" << endl;
									cout << " 2. Type" << endl;
									cout << " 3. Language" << endl;
									cout << " 4. Buy in price" << endl;
									cout << " 5. Sold out price" << endl;
									cout << " 0. Save and Exit" << endl;
									cout << endl << " Enter your choice >> ";
									if(!(cin >> choice)){
										cin.clear();
										cin.ignore(1000,'\n');
									}
									cin.sync();
									if(choice==1){
										//code to edit title
										askInput = medic.ticketDetail.askTitle(1);
										if(askInput==3){
											TicketType::alert(2, "Empty");
										}else if(askInput==4){
											TicketType::alert(3, "18");
										}
									}else if(choice==2){
										//code to edit type
										int position = r.tellg();
										r.close();
										medic.ticketDetail.setType(TicketType::getType(TicketType::displayType("update")));
										TicketType::openfr(1, "ticket_record.txt");
										r.seekg(position, ios::beg);
									}else if(choice==3){
										//code to edit description
										askInput = medic.ticketDetail.askDescribe(2);
										if(askInput==4){
											TicketType::alert(3, "80");
										}
									}else if(choice==4){
										//code to edit buy in price
										askInput = medic.ticketDetail.askPurchasePrice(3);
										if(askInput==3){
											TicketType::alert(1, "price");
										}else if(askInput==4){
											TicketType::alert(3, "18");
										}
									}else if(choice==5){
										//code to edit sold out price
										askInput = medic.ticketDetail.askSoldOutPrice(4);
										if(askInput==3){
											TicketType::alert(1, "price");
										}else if(askInput==4){
											TicketType::alert(3, "18");
										}
									}else if(choice==0){
										break;
									}else{
										TicketType::alert(1, "choice");
									}
								}
							}
								this->writeToFile();
						}
						r.close();
						w.close();
						int test=0;
						if(remove(oldf.c_str()))
							perror(" Error remove file : ");
						else ++test;
						if(rename(newf.c_str(), oldf.c_str()))
							perror(" Error rename file : ");
						else ++test;
						if(test==2){
							this->updateTicket();
							TicketType::loading("Editing", 2, "");
							cout << endl << " Ticket id : " << id << " edited!!" << endl;
						}
					}
				}
				r.close();
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to manage quantity
		void manageQuantity(string id, int qty, string type){
			string oldf = openfr(1, "ticket_record.txt");
			string newf = openfw(1, "temp.txt");
			while(this->readFromFile()){
				if(medic.ticketDetail.getId()==id){
					if(type=="in")
						medic.ticketDetail.setQuantity((medic.ticketDetail.getQuantity() + qty));
					else if(type=="out")
						medic.ticketDetail.setQuantity((medic.ticketDetail.getQuantity() - qty));
				}
				this->writeToFile();
			}
			r.close();
			w.close();
			if(remove(oldf.c_str()))
				perror(" Error remove file : ");
			if(rename(newf.c_str(), oldf.c_str()))
				perror(" Error rename file : ");
			this->updateTicket();
		};
		
		//method to view all ticket record
		void viewTicket(string type, int count, int check){
			system("cls");
			int sorting = count % 2;
			int i=0;
			int colWidth=16, noWidth=4, titleWidth=20, descWidth=35, priceWidth=20;
			int width = (colWidth*2) + noWidth + (titleWidth*2) + descWidth + (priceWidth*2);
			int desc = noWidth + colWidth + (titleWidth*2) + descWidth;
			if(this->ticketListArrange(type, sorting)){
				
				//instruction
				cout << endl << "Enter 1 >> ID "; if(type=="id") this->displaySort(sorting); else cout << "\t\t";
				cout << "\tEnter 2 >> Title "; if(type=="title") this->displaySort(sorting); else cout << "\t";
				cout << "\tEnter 3 >> Type "; if(type=="type") this->displaySort(sorting); else cout << "\t";
				cout << "\tEnter 4 >> Quantity "; if(type=="qty") this->displaySort(sorting); else cout << "\t\t";
				cout << "\tEnter 0 >> exit" << endl;
				
				//table header
				cout << setfill('=') << setw(width) << "=" << endl;
				cout << setfill(' ') << fixed;
				cout << setw(noWidth) << "No." << setw(colWidth) << "ID" << setw(titleWidth)
					 << "Title" << setw(titleWidth) << "Type" << setw(descWidth)
					 << "Language" << setw(priceWidth) << "Purchase Price" << setw(priceWidth)
					 << "Sold Out Price" << setw(colWidth) << "Quantity" << endl;
				cout << setfill('-') << setw(width) << "-" << endl;
				cout << setfill(' ') << fixed;
				
				//table body
				curr=head;
				while(curr!=NULL){
					cout << setprecision(0) << setw(noWidth) << ++i << setw(colWidth) << curr->ticketDetail.getId() << setw(titleWidth)
						 << curr->ticketDetail.getTitle() << setw(titleWidth) << curr->ticketDetail.getType() << setw(descWidth)
						 << curr->ticketDetail.getDescribeRow1() << setprecision(2) << setw(priceWidth) << curr->ticketDetail.getPurchasePrice() << setprecision(2)
						 << setw(priceWidth) << curr->ticketDetail.getSoldOutPrice() << setprecision(0) << setw(colWidth) << curr->ticketDetail.getQuantity() << endl;
					cout << setw(desc) << curr->ticketDetail.getDescribeRow2() << endl;
					cout << setw(desc) << curr->ticketDetail.getDescribeRow3() << endl;
					curr=curr->next;
				}
				
				//table end line
				cout << setfill('=') << setw(width) << "=" << endl;
				
				cout << endl << " Enter choice >> ";
				char choice = getch();
				cout << choice << endl;
				if(choice!='0' && choice!='1' && choice!='2' && choice!='3' && choice!='4'){
					TicketType::alert(1, "choice");
					this->viewTicket("id", 0, 0);
				}else if(choice=='1'){
					if(check==choice)
						++count;
					else count=0;
					this->viewTicket("id", count, choice);
				}else if(choice=='2'){
					if(check==choice)
						++count;
					else count=0;
					this->viewTicket("title", count, choice);
				}else if(choice=='3'){
					if(check==choice)
						++count;
					else count=0;
					this->viewTicket("type", count, choice);
				}else if(choice=='4'){
					if(check==choice)
						++count;
					else count=0;
					this->viewTicket("qty", count, choice);
				}
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
				cout << endl << "\t";
				system("pause");
			}
		};
		
		//method to search a ticket detail
		string searchTicket(){
			system("cls");
			string id;
			if(this->ticketList()){
				cout << endl << " Enter id to search : ";
				getline(cin, id);
				TicketType::loading("Searching", 2, "");
				system("cls");
				if(TicketType::openfr(1, "ticket_record.txt")=="0"){
					cout << endl << endl << " Currently do not insert for any record..." << endl;
					id = "0";
				}else{
					r.close();
					if(!searching(id)){
						cout << endl << endl <<  " The Ticket : " << id << " is not found... Please try again..." << endl;
						id = "0";
					}else{
						medic.ticketDetail.displayTicket(1);
					}
				}
				r.close();
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
				id = "0";
			}
			return id;
		};
		
		//method to delete a ticket detail
		void deleteTicket(){
			system("cls");
			if(this->ticketList()){
				string id;
				cout << endl << " Enter id to delete : ";
				getline(cin, id);
				TicketType::loading("Searching", 2, "");
				system("cls");
				string oldf = TicketType::openfr(1, "ticket_record.txt");
				if(oldf=="0"){
					cout << endl << endl << " Currently do not insert for any record..." << endl;
				}else{
					r.close();
					if(!searching(id)){
						cout << endl << endl << " The id " << id << " is not found... Please try again..." << endl;
					}else{
						TicketType::openfr(1, "ticket_record.txt");
						char choose='0';
						string newf = TicketType::openfw(1, "temp.txt");
						r.seekg(0, ios::beg);
						while(this->readFromFile()==true){
							if(id==medic.ticketDetail.getId()){
								while(choose=='0'){
										medic.ticketDetail.displayTicket(0);
									cout << "-------------------------------------------------------------------------" << endl << endl;
									cout << endl << " Are you sure to delete the record? [Y/N] " << endl;
									choose = getch();
									if(choose=='N'||choose=='n'){
										cout << endl << " The record is still remain." << endl;
										this->writeToFile();
									}else if(choose!='Y'&&choose!='y'){
										TicketType::alert(1, "confirmation");
										system("cls");
										choose='0';
									}
								}
								
							}else
								this->writeToFile();
						}
						r.close();
						w.close();
						int test=0;
						if(remove(oldf.c_str()))
							perror(" Error remove file : ");
						else ++test;
						if(rename(newf.c_str(), oldf.c_str()))
							perror(" Error rename file : ");
						else ++test;
						string checkFile = openfr(1, "ticket_record.txt");
						if(this->readFromFile()==false){
							r.close();
							if(remove(checkFile.c_str()))
							perror(" Error remove file : ");
								else ++test;
						}
						r.close();
						
						if(test==2 && (choose=='Y'||choose=='y')){
							this->updateTicket();
							TicketType::loading("Deleting", 2, "");
							cout << endl << endl  << " Ticket id : " << id << " deleted!!" << endl;
						}else if(test==3 && (choose=='Y'||choose=='y')){
							this->updateTicket();
							TicketType::loading("Deleting", 2, "");
							cout << endl << endl  << " Ticket id : " << id << " deleted!!" << endl;
							cout << " There is no more record of in the file, the file had been removed!!" << endl;
						}
					}
				}
				r.close();
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to clear all ticket record
		void clearTicket(){
			if(this->ticketList()){
				char choose='0';
				while(choose=='0'){
					system("cls");
					cout << endl << " All the rocord can not be recovery after clear..." << endl;
					cout << " Are you sure to clear all the record? [Y/N]" << endl;
					choose = getch();
					if(choose=='Y' || choose=='y'){
						string delf=openfr(1, "ticket_record.txt");
						if(delf=="0"){
								cout << endl << endl << " Currently do not insert for any record..." << endl;
							r.close();
						}else{
							r.close();
							if(remove(delf.c_str()))
								perror(" Error remove file : ");
							else{
								if(remove("database/type_list.txt"))
									perror(" Error remove file : ");
								this->updateTicket();
								TicketType::loading("Processing", 2, "");
								cout << endl << endl  << " All the record had been clear..." << endl;
							}
						}
					}else if(choose=='N' || choose=='n'){
						cout << endl << endl  << " The record is still remain. Thank you!!" << endl;
					}else{
						TicketType::alert(1, "confirmation");
						choose='0';
					}
				}
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to clear ticket record by type
		void clearTicketByType(){
			if(this->ticketList()){
				char choose='0';
				while(choose=='0'){
					system("cls");
					cout << endl << " All the rocord can not be recovery after clear..." << endl;
					cout << " Are you sure to clear all the record? [Y/N]" << endl;
					choose = getch();
					if(choose=='Y' || choose=='y'){
						string oldf = TicketType::openfr(1, "ticket_record.txt");
						if(oldf=="0"){
							cout << endl << endl << " Currently do not insert for any record..." << endl;
						}else{
							r.close();
							string clear = TicketType::deleteType();
							if(clear!="0"){
								TicketType::openfr(1, "ticket_record.txt");
								string newf = TicketType::openfw(1, "temp.txt");
								r.seekg(0, ios::beg);
								while(this->readFromFile()==true){
									if(clear!=medic.ticketDetail.getType())
										this->writeToFile();
								}
								r.close();
								w.close();
								int test=0;
								if(remove(oldf.c_str()))
									perror(" Error remove file : ");
								else ++test;
								if(rename(newf.c_str(), oldf.c_str()))
									perror(" Error rename file : ");
								else ++test;
								string checkFile = openfr(1, "ticket_record.txt");
								if(this->readFromFile()==false){
									r.close();
									if(remove(checkFile.c_str()))
									perror(" Error remove file : ");
										else ++test;
								}
								r.close();
								if(test==2){
									this->updateTicket();
									TicketType::loading("Processing", 2, "");
									cout << endl << endl  << " Ticket record for type " << clear << " is clear!!" << endl;
								}else if(test==3){
									this->updateTicket();
									TicketType::loading("Processing", 2, "");
									cout << endl << endl  << " Ticket record for type " << clear << " is clear!!" << endl;
									cout << " There is no more record of in the file, the file had been removed!!" << endl;
								}
							}	
						}
						r.close();
					}else if(choose=='N' || choose=='n'){
						cout << endl << endl  << " The record is still remain. Thank you!!" << endl;
					}else{
						TicketType::alert(1, "confirmation");
						choose='0';
					}
				}
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to search for existence of a ticket
		bool searching(string id){
			if(openfr(1, "ticket_record.txt")!="0"){
				while(this->readFromFile()==true){
					if(id==medic.ticketDetail.getId()){
						r.close();
						return true;
					}
				}
			}
			r.close();
			return false;
		};
		
		//method to list all ticket with link-list
		bool ticketList(){
			if(openfr(1, "ticket_record.txt")!="0"){
				head=NULL;
				while(this->readFromFile()!=false){
					newPtr = new ticket;
					newPtr->ticketDetail = medic.ticketDetail;
					newPtr->next = NULL;
					
					if(head==NULL){
						head=newPtr;
						curr=head;
					}else{
						curr->next=newPtr;
						curr=newPtr;
					}
				}
				r.close();
				return true;
			}
			r.close();
			return false;
		};
		
		//method to arrange list
		bool ticketListArrange(string type, int sort){
			if(this->ticketList()){
				row=head;
				while(row!=NULL){
					curr=head;
					prev=NULL;
					while(curr->next!=NULL){
						//sort by id in ascending oder
						if(type=="id" && sort==0){
							if(curr->ticketDetail.getId() > curr->next->ticketDetail.getId()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by id in descending oder
						else if(type=="id" && sort==1){
								if(curr->ticketDetail.getId() < curr->next->ticketDetail.getId()){
									temp=curr->next;
									curr->next=temp->next;
									temp->next=curr;
									if(curr==head){
										head=temp;
										row=head;
									}
									else prev->next=temp;
								}else
									curr=curr->next;
						}
						//sort by title in ascending oder
						else if(type=="title" && sort==0){
							if(curr->ticketDetail.getTitle() > curr->next->ticketDetail.getTitle()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by title in descending oder
						else if(type=="title" && sort==1){
							if(curr->ticketDetail.getTitle() < curr->next->ticketDetail.getTitle()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by type in ascending oder
						else if(type=="type" && sort==0){
							if(curr->ticketDetail.getType() > curr->next->ticketDetail.getType()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by type in descending oder
						else if(type=="type" && sort==1){
							if(curr->ticketDetail.getType() < curr->next->ticketDetail.getType()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by quantity in ascending oder
						else if(type=="qty" && sort==0){
							if(curr->ticketDetail.getQuantity() > curr->next->ticketDetail.getQuantity()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by quantity in descending oder
						else if(type=="qty" && sort==1){
							if(curr->ticketDetail.getQuantity() < curr->next->ticketDetail.getQuantity()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						
						if(head->next==curr){
							prev=head;
						}else prev=prev->next;
					}
					row=row->next;
				}
				return true;
			}
			return false;
		};
		
		//method to save all ticket into file with table form
		void printTicket(string type, int sort){
			int i=0;
			int colWidth=16, noWidth=4, titleWidth=20, descWidth=35, priceWidth=20;
			int width = (colWidth*2) + noWidth + (titleWidth*2) + descWidth + (priceWidth*2);
			int desc = noWidth + colWidth + (titleWidth*2) + descWidth;
			
			this->ticketListArrange(type, sort);
			
			//table header
			w << setfill('=') << setw(width) << "=" << endl;
			w << setfill(' ') << fixed;
			w << setw(noWidth) << "No." << setw(colWidth) << "ID" << setw(titleWidth)
				 << "Title" << setw(titleWidth) << "Type" << setw(descWidth)
				 << "Language" << setw(priceWidth) << "Purchase Price" << setw(priceWidth)
				 << "Sold Out Price" << setw(colWidth) << "Quantity" << endl;
			w << setfill('-') << setw(width) << "-" << endl;
			w << setfill(' ') << fixed;
			
			//table body
			curr=head;
			while(curr!=NULL){
				w << setprecision(0) << setw(noWidth) << ++i << setw(colWidth) << curr->ticketDetail.getId() << setw(titleWidth)
					 << curr->ticketDetail.getTitle() << setw(titleWidth) << curr->ticketDetail.getType() << setw(descWidth)
					 << curr->ticketDetail.getDescribeRow1() << setprecision(2) << setw(priceWidth) << curr->ticketDetail.getPurchasePrice() << setprecision(2)
					 << setw(priceWidth) << curr->ticketDetail.getSoldOutPrice() << setprecision(0) << setw(colWidth) << curr->ticketDetail.getQuantity() << endl;
				w << setw(desc) << curr->ticketDetail.getDescribeRow2() << endl;
				w << setw(desc) << curr->ticketDetail.getDescribeRow3() << endl;
				curr=curr->next;
			}
			
			//table end line
			w << setfill('=') << setw(width) << "=" << endl;
		};
		
		//method to update file
		void updateTicket(){
			remove("record/ticket/ticket_record - by id (ASC).txt");
			remove("record/ticket/ticket_record - by id (DESC).txt");
			remove("record/ticket/ticket_record - by title (ASC).txt");
			remove("record/ticket/ticket_record - by title (DESC).txt");
			remove("record/ticket/ticket_record - by type (ASC).txt");
			remove("record/ticket/ticket_record - by type (DESC).txt");
			remove("record/ticket/ticket_record - by qty (ASC).txt");
			remove("record/ticket/ticket_record - by qty (DESC).txt");
			
			if(this->ticketList()){
				openfw(2, "ticket_record - by id (ASC).txt");
				this->printTicket("id", 0);
				w.close();
				openfw(2, "ticket_record - by id (DESC).txt");
				this->printTicket("id", 1);
				w.close();
				openfw(2, "ticket_record - by title (ASC).txt");
				this->printTicket("title", 0);
				w.close();
				openfw(2, "ticket_record - by title (DESC).txt");
				this->printTicket("title", 1);
				w.close();
				openfw(2, "ticket_record - by type (ASC).txt");
				this->printTicket("type", 0);
				w.close();
				openfw(2, "ticket_record - by type (DESC).txt");
				this->printTicket("type", 1);
				w.close();
				openfw(2, "ticket_record - by qty (ASC).txt");
				this->printTicket("qty", 0);
				w.close();
				openfw(2, "ticket_record - by qty (DESC).txt");
				this->printTicket("qty", 1);
				w.close();
			}
		};
		
		//method to print ticket into table by type
		void printTicketByType();
		
		//method to write ticket data into .txt file
		void writeToFile(){
			w << medic.ticketDetail.getId() << endl;
			w << medic.ticketDetail.getTitle() << endl;
			w << medic.ticketDetail.getType() << endl;
			w << medic.ticketDetail.getDescribeRow1() << endl;
			w << medic.ticketDetail.getDescribeRow2() << endl;
			w << medic.ticketDetail.getDescribeRow3() << endl;
			w << medic.ticketDetail.getPurchasePrice() << endl;
			w << medic.ticketDetail.getSoldOutPrice() << endl;
			w << medic.ticketDetail.getQuantity() << endl;
		};
		
		//method to read ticket data from .txt file
		bool readFromFile(){
			char* end;
			string empty, id, title, type, describe[3], pPrice="", sOutPrice="";
			double purchasePrice, soldOutPrice;
			int quantity;
			getline(r, id);
			getline(r, title);
			getline(r, type);
			getline(r, describe[0]);
			getline(r, describe[1]);
			getline(r, describe[2]);
			getline(r, pPrice);
			getline(r, sOutPrice);
			r >> quantity;
			getline(r, empty);
			
			purchasePrice = strtod(pPrice.c_str(), &end);
			soldOutPrice = strtod(sOutPrice.c_str(), &end);
			
			medic.ticketDetail.setId(id);
			if(medic.ticketDetail.getId()=="") return false;
			medic.ticketDetail.setTitle(title);
			medic.ticketDetail.setType(type);
			medic.ticketDetail.setDescribe(describe[0], 0);
			medic.ticketDetail.setDescribe(describe[1], 1);
			medic.ticketDetail.setDescribe(describe[2], 2);
			medic.ticketDetail.setPurchasePrice(purchasePrice);
			medic.ticketDetail.setSoldOutPrice(soldOutPrice);
			medic.ticketDetail.setQuantity(quantity);
			return true;
		};
		
		void displaySort(int sort){
			if(sort==0)
				cout << "(ASC)\t";
			else if(sort==1)
				cout << "(DESC)\t";
		};
};
