#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <conio.h>
#include <ctime>
//#include <fstream>
#include <queue>
using namespace std;

string Month[12] ={"January","February","March","April","May","June","July","August","September","October","November","December"};
string Sports[7] = {"Futsal","Badminton","Netball","Bowling","Swimming","PingPong","Tennis"};

const int size = 10;
time_t rawtime;
struct tm* timeinfo;

ofstream out;
ifstream bout;

class Node
{
public:
string name,sportType,month,ic,borrowedItem;
int age,date,chin,chout,mon;
Node* link; // pointer to next node
};

class EquipmentList
{
private:
int front, back,count;
string items[size];
public:
EquipmentList()
{
front = 0;
back = size-1;
count = 0;
}

//25

// ~EquipmentList()
// {
// delete[] items;
// }

bool isEmpty()
{
return(count == 0);
}

void insertEq(string newItem)
{
back = (back+1) % size;
items[back] = newItem;
++count;
}

string getFront()
{
return items[front];
}

void removeEq()
{
front = (front+1) % size;
--count;
}

};

EquipmentList Ball;
EquipmentList rentedBall;

class List
{
private:

Node* head;
Node* borrowHead ;

public:

List(void)
{ 
head = NULL;
borrowHead = NULL;
}

~List() 
{
head = NULL;
borrowHead = NULL;
};

//26

Node* InsertNode(string, string, string, int, string, int ,int ,int);
Node* InsertNode(string, string, string, int, string, int ,int ,int,int);
Node* InsertBorrowNode(string, string, int, int, string);

void deleteNode(int);
void Find();
void FindName(string);
void FindIC(string);
void FindMonth(string);
void Sort();
void SortName(int);
void SortIC(int);
void SortAge(int);
void Delete();
void Insert();
void Rent();
void menu();

int displayBorrower();
int DisplayList();
};

Node* List::InsertNode(string n, string m, string s, int a, string i, int d, int ci, int co)
{
int currIndex = 0;
Node* currNode = head;
Node* prevNode = NULL;
while ((currNode && n>currNode->name)&&(currNode && s>currNode->sportType)&&(currNode && m>currNode->month)&&(currNode && a>currNode->age)&&(currNode && i>currNode->ic)&&(currNode && d>currNode->date)&&(currNode&& ci>currNode->chin)&&(currNode && co>currNode->chout))
{
prevNode = currNode;
currNode = currNode->link;
currIndex++;
}

Node* newNode = new Node;
newNode->name= n;
newNode->sportType= s;
newNode->month= m;
newNode->age= a;
newNode->ic= i;
newNode->date= d;
newNode->chin= ci;
newNode->chout= co;

//27

if(currIndex==0)
{
newNode->link=head;
head= newNode;
}
else
{
newNode->link= prevNode->link;
prevNode->link= newNode;
}
return newNode;
}

Node* List::InsertNode(string n, string m, string s, int a, string i, int d, int ci, int co,int index)
{
int currIndex = 1;
Node* currNode = head;
while ((currNode && index > currIndex))
{
currNode = currNode->link;
currIndex++;
}

if(index>0 && currNode == NULL)
{
    return NULL;
}
Node* newNode = new Node;
newNode->name= n;
newNode->sportType= s;
newNode->month= m;
newNode->age= a;
newNode->ic= i;
newNode->date= d;
newNode->chin= ci;
newNode->chout= co;

if(index==0)
{
newNode->link=head;
head = newNode;
}
else 
{
//28
newNode->link = currNode->link;
currNode->link = newNode;
}
return newNode;
}

Node* List::InsertBorrowNode(string n, string i, int m, int d, string b)
{
int currIndex = 0;
Node* currNode = borrowHead;
Node* prevNode = NULL;

while ((currNode && n>currNode->name)&&(currNode && i>currNode->ic)&&(currNode && d>currNode->date))
{
prevNode = currNode;
currNode = currNode->link;
currIndex++;
}

Node* newNode = new Node;
newNode->name= n;
newNode->mon= m;
newNode->ic= i;
newNode->date= d;
newNode->borrowedItem = b;

if(currIndex==0)
{
newNode->link=borrowHead;
borrowHead= newNode;
}
else
{
newNode->link= prevNode->link;
prevNode->link= newNode;
}
return newNode;
}

int List::DisplayList()
{
int num = 1;
//29
Node* currNode = head;

if(currNode)
{
cout << "\nCustomers List"<< "\n--------------";
cout << left << endl << setw(4) << "No" << setw(20) << "Name" << setw(6)<< "Age" << setw(22) << "Identification Card"<< setw(6) << "Date" << setw(10) << "Month" << setw(15) <<"Sport Type" << setw(6) << "Check In"<< setw(6) << "Check Out" << endl;
}

else
{
cout << "There are no customer record in the list.";
return 0;
}

while(currNode != NULL)
{
cout << left << " " << setw(3) << num << setw(20) << currNode->name <<setw(6) << currNode->age << setw(22) << currNode->ic<< setw(6) << currNode->date << setw(10) << currNode->month <<setw(15)<< currNode->sportType<< setw(6) << currNode->chin << setw(6) << currNode->chout <<endl;
currNode = currNode->link;
num++;
}

return num;
}

int List::displayBorrower()
{
int num = 1;
Node* currNode = borrowHead;

if(!currNode)
{
cout << "\nNo one has rented any equipment today yet.";
return 0;
}

else
//30
{
cout << left << endl << setw(4) << "No" << setw(20) << "Name" << setw(22)<< "Identification Card"<< setw(6) << "Date" << setw(10) << "Month" << setw(5) <<"Rented Item"<< endl;
}
while(currNode != NULL)
{
cout << left << " " << setw(3) << num << setw(20) << currNode->name <<setw(22) << currNode->ic<< setw(6) << currNode->date << setw(10) <<Month[currNode->mon] << currNode->borrowedItem << endl;
currNode = currNode->link;
num++;
}

return num;
}

void List::FindName(string N)
{
Node* currNode = head;
while (currNode && currNode ->name != N)
{
currNode = currNode ->link;
}

if (currNode)
{
cout << "Below is the information of " << N << ":" << endl << endl;
cout << "Name : " << currNode ->name << endl<< "Age : " << currNode ->age << endl<< "IC : " << currNode ->ic << endl<< "Sport : " << currNode ->sportType << endl<< "Date : " << currNode ->date << " " << currNode->month << endl<< "Checked in time : " << currNode ->chin << endl<< "Checked out time : " << currNode ->chout << endl<<endl;
}

else
cout << "There is no customer named " << N << " in the record." << endl <<endl;
getch();
//31
return;
}

void List::FindIC(string I)
{
Node* currNode = head;
while (currNode && currNode->ic != I) 
{
currNode = currNode->link;
}

if (currNode)
{
cout << "\nBelow is the information about the customer with IC " << I<< " :" << endl <<endl ;
cout << "Name : " << currNode->name << endl<< "Age : " << currNode->age << endl<< "IC : " << currNode->ic << endl<< "Sport : " << currNode->sportType << endl<< "Date : " << currNode->date << " " << currNode->month<< endl<< "Checked in time : " << currNode->chin << endl<< "Checked out time : " << currNode->chout << endl<<endl;
}
else
{
cout << "There is no customer with IC " << I << " in the record.\n";
}
getch();
return;
}

void List::FindMonth(string M)
{
Node* currNode = head;
int num = 0;

while (currNode)
{
if (currNode->month == M)
{
num++;

if (num == 1)
{
cout << "\nBelow is the customer(s) that used the sport centre in " << M << " :" << endl << endl;
//32
cout << left << setw(4) << "No" << setw(20) << "Name" <<setw(6) << "Age" << setw(22) << "Identification Card"<< setw(6) << "Date" << setw(10) << "Month" << setw(15) <<"Sport Type" << setw(6) << "Check In"<< setw(6) << "Check Out" << endl;
}
cout << left << setw(4) << num << setw(20) << currNode->name <<setw(6) << currNode->age << setw(22) << currNode->ic<< setw(6) << currNode->date << setw(10) << currNode->month <<setw(15)<< currNode->sportType<< setw(6) << currNode->chin << setw(6) << currNode->chout <<endl;
}
currNode = currNode->link;
}

if(num == 0)
{
    cout << "There is no customer enter the sport centre in " << M << ".";
}
cout << endl << endl;
getch();
return ;
}

void List::Find()
{
int ch,m;
string tempIC,tempName,tempMonth;

do
{
system("cls");
cout << "----------------------------------------------------------\n";
cout << " DATA SEARCHING\n";
cout << "----------------------------------------------------------\n";
cout << "\n\t\tChoose Your Option\n"<< "\t\t[1] Search by Name"<< "\n\t\t[2] Search by Identification Card"<< "\n\t\t[3] Search by Month"<<"\n\t\t-\n\t\t[0]Back\n\n";
cout << "Option: ";
cin >> ch;

switch(ch)
{
case 1 :
cin.ignore();
cout << "\nEnter Name: ";
//33
getline(cin,tempName,'\n');
cout << endl;
FindName(tempName);
break;

case 2:
cout << "\nEnter Identification Card: ";
cin >> tempIC;
FindIC(tempIC);
break;

case 3:
cout << "\n\t\t\nChoose which month";
cout << "\n\t\t[1] January"<< "\n\t\t[2] February"<< "\n\t\t[3] March"<< "\n\t\t[4] April"<< "\n\t\t[5] May"<< "\n\t\t[6] June"<< "\n\t\t[7] July"<< "\n\t\t[8] August"<< "\n\t\t[9] September"<< "\n\t\t[10] October"<< "\n\t\t[11] November"<< "\n\t\t[12] December"<< "\n\t\t-"<< "\n\t\t[0] Back";
cout << "\n\nOption: ";
cin >> m;

if(m == 0)
{
Find();
}

if(m < 1 || m > 12)
{
cout << "Invalid option ! Please try again." << endl;
getch();
Find();
}

FindMonth(Month[m-1]);
break;

case 0 :
return;

//34
default :
cout << "\nInvalid option ! Please try again." << endl;
getch();
}
}

while(ch!=0);
}
void List::Delete()
{
int ch;
system("cls");
cout << "----------------------------------------------------------\n";
cout << " DATA DELETION\n";
cout << "----------------------------------------------------------\n";
cout << "\nCurrent List :\n";
DisplayList();
cout << "\nSelect which customer record you want to delete ('0' to return)\nOption : ";
cin >> ch;
if(ch == 0)
{
    menu();
}

deleteNode(ch);
cout << "\nThe list after deletion process :\n";

DisplayList();
cout << endl;
cout << "Returning to main menu.";
getch();
menu();
}

void List::deleteNode(int a)
{
int currIndex = 1;
char choice;
Node* currNode = head;
Node* prevNode = NULL;

while (currNode && currIndex != a)
{
prevNode = currNode;
currNode = currNode->link;
currIndex++;
}

if(!currNode)
//35
{
cout << "\nThere is no number '" << a << "' in the list. Returning to main menu...\n\n";
getch();
menu();
}

cout << "\nDelete the record for " << currNode->name << " ? Option (Y/N) : ";
cin >> choice;
if(choice == 'N')
{
    Delete();
}
if (currNode)
{
if (prevNode)
{
prevNode->link = currNode->link;
delete currNode;
}
else
{
head = currNode->link;
delete currNode;
}
return ;
}
cout << "There is no number '" << a <<"' in the list.";
return;
}

void List::Insert()
{
string Iname,Imonth,Iic;
int Iage,Idate,Ichin,Ichout,ch,Inum,IsportType;
system("cls");
cout << "----------------------------------------------------------\n";
cout << " DATA INSERTION\n";
cout << "----------------------------------------------------------\n";
Inum = DisplayList();
cout << "\n\n\t\tChoose Your Option\n"<< "\t\t[1] Insert data in the beginning of the list"<< "\n\t\t[2] Insert data in the middle of the list"<< "\n\t\t[3] Insert data in the end of the list"<<"\n\t\t-\n\t\t[0]Back\n\n";
//36
cout << "Option: ";
cin >> ch;

if(ch<0 || ch>3)
{
cout << "\nInvalid option! Please try again.";
getch();
Insert();
}

if(ch==0)
{
    menu();
}

cout << "\nPlease fill the information for the new data :\n";
cin.ignore();
cout << "\nName : ";
getline(cin,Iname,'\n');
cout << "Age : ";
cin >> Iage;
cout << "IC : ";
cin >> Iic;
cout << "Sport Type : [1] Futsal\n"<< " [2] Badminton\n"<< " [3] Netball\n"<< " [4] Bowling\n"<< " [5] Swimming\n"<< " [6] Ping Pong\n"<< " [7] Tennis\n\n"<< " Choice: ";
cin >> IsportType;
cout << "\nDate of Check In and Check Out (i.e.: 7 January) : ";
cin >> Idate;
cin >> Imonth;
cout << "Check In time (24H) : ";
cin >> Ichin;
cout << "Check Out time (24H) : ";
cin >> Ichout;

if(ch == 1)
{
InsertNode(Iname,Imonth,Sports[IsportType-1],Iage,Iic,Idate,Ichin,Ichout);
}

if(ch == 2)
{
//37
InsertNode(Iname,Imonth,Sports[IsportType-1],Iage,Iic,Idate,Ichin,Ichout,(Inum/2)-1);
}

if(ch == 3)
{
InsertNode(Iname,Imonth,Sports[IsportType-1],Iage,Iic,Idate,Ichin,Ichout,Inum-1);
}

cout << "\nThe list after insertion process.\n";
DisplayList();
cout << "\nReturning to main menu.";
getch();
return;
}

void List::SortName(int choice)
{
if(choice==1)
{
    
	Node* temp = head;
	while (temp) {
		Node* min = temp;
		Node* r = temp->link;
		while (r) {
			if (min->name > r->name)
				min = r;

			r = r->link;
		}
		string x = temp->name;
		temp->name = min->name;
		min->name = x;
		temp = temp->link;
	
	}
}

else if(choice==2)
{
Node* temp = head;
	while (temp) {
		Node* max = temp;
		Node* r = temp->link;
		while (r) {
			if (max->name < r->name)
				max = r;
			r = r->link;
		}
		string x = temp->name;
		temp->name = max->name;
		max->name = x;
		temp = temp->link;
	
	}
}

cout << "\nSorting process successful. Please refer to the new list below. \n";
DisplayList();
getch();
Sort();
}

void List::SortIC(int choice)
{
if(choice==1)
{
    
	Node* temp = head;
	while (temp) {
		Node* min = temp;
		Node* r = temp->link;
		while (r) {
			if (min->ic > r->ic)
				min = r;

			r = r->link;
		}
		string x = temp->ic;
		temp->ic = min->ic;
		min->ic = x;
		temp = temp->link;
	
	}
}

else if(choice==2)
{
Node* temp = head;
	while (temp) {
		Node* max = temp;
		Node* r = temp->link;
		while (r) {
			if (max->ic < r->ic)
				max = r;
			r = r->link;
		}
		string x = temp->ic;
		temp->ic = max->ic;
		max->ic = x;
		temp = temp->link;
	
	}
}

cout << "\nSorting process successful. Please refer to the new list below. \n";
DisplayList();
getch();
Sort();
}

void List::SortAge(int choice)
{
if(choice==1)
{
    
	Node* temp = head;
	while (temp) {
		Node* min = temp;
		Node* r = temp->link;
		while (r) {
			if (min->age > r->age)
				min = r;

			r = r->link;
		}
		int x = temp->age;
		temp->age = min->age;
		min->age = x;
		temp = temp->link;
	
	}
}

else if(choice==2)
{
Node* temp = head;
	while (temp) {
		Node* max = temp;
		Node* r = temp->link;
		while (r) {
			if (max->age < r->age)
				max = r;
			r = r->link;
		}
		int x = temp->age;
		temp->age = max->age;
		max->age = x;
		temp = temp->link;
	
	}
}

cout << "\nSorting process successful. Please refer to the new list below. \n";
DisplayList();
getch();
Sort();
}

void List::Rent()
{
int ch,ch1;
string bName,bIC,bDay,bMonth;
system("cls");
cout << "----------------------------------------------------------\n";
cout << " Equipment Rental - " << timeinfo->tm_mday << " " <<Month[timeinfo->tm_mon];
cout << "\n----------------------------------------------------------\n";
cout << "\n\t\tChoose Your Option\n"<< "\t\t[1] Rent a futsal ball";
if(Ball.isEmpty())

cout << " [Not Available]";
cout << "\n\t\t[2] Rent a racket [Coming Soon]";
cout << "\n\t\t[3] Display rental record.";
cout << "\n\t\t-\n\t\t[0]Back\n\n"<< "Option: ";
cin >> ch;

if(ch==0)
menu();
//42
else if(ch==1)
{
    
if(Ball.isEmpty())
{
cout << "\nAll futsal balls have been rented for the day. Please try again tomorrow!";
getch();
}

else
{
cin.ignore();
cout << "\nPlease enter your information below."<< "\n\nName : ";
getline(cin,bName,'\n');
cout << "IC : ";
cin >> bIC;

InsertBorrowNode(bName,bIC,timeinfo->tm_mon,timeinfo->tm_mday,Ball.getFront());
out.open("RentedItem.txt",ios::app);

out << bName << endl << bIC << endl << Ball.getFront() << endl <<timeinfo->tm_mday << endl << timeinfo->tm_mon+1 << endl << endl;
out.close();
rentedBall.insertEq(Ball.getFront());
cout << "\nRent request successful! Please show the ticket below to the counter to retrieve your item.\n";
cout << left <<"\n\t\tX------------------------------------------------X"<< "\n\t\t| |"<< "\n\t\t|\t Name : " << setw(30) << bName << "|"<< "\n\t\t|\t IC : " << setw(30) << bIC << "|"<< "\n\t\t|\t Date : " << setw(2) << timeinfo->tm_mday << " " <<setw(27) << Month[timeinfo->tm_mon] << "|"<< "\n\t\t|\t Item : " << setw(30) << Ball.getFront() << "|"<< "\n\t\t| |"<< "\n\t\t| |"<< "\n\t\t| JAYPEE SPORTS CENTRE Sector 62 Noida |"<< "\n\t\t| |"<< "\n\t\tX------------------------------------------------X";
Ball.removeEq();
}
}

//43
else if(ch==3)
{
displayBorrower();
cout << endl;
}
else
cout << "\nInvalid option. Please try again.";
getch();
Rent();
}

void List::Sort()
{
int ch,ch1;
system("cls");
cout << "----------------------------------------------------------\n";
cout << " DATA SORTING\n";
cout << "----------------------------------------------------------\n";
cout << "\n\t\tChoose Your Option\n"<< "\t\t[1] Sort by Name"<< "\n\t\t[2] Sort by Identification Card"<< "\n\t\t[3] Sort by Age"<< "\n\t\t-\n\t\t[0]Back\n\n"<< "Option: ";
cin >> ch;

if(ch==0)
{
menu();
}
else if(ch==1)
{
cout << "\n\t\tChoose Your Option\n"<< "\t\t[1]Ascending Order\n\t\t[2]Descending Order\n\t\t-\n\t\t[0]Back\n\n";
cout << "Option: ";
cin >> ch1;

if(ch1==0)
{
Sort();
}

else if(ch1 == 1 || ch1 ==2)
{
SortName(ch1);
}

else
{
cout << "\nInvalid option ! Returning to sorting menu.";
}
//44
getch();
}

else if(ch==2)
{
cout << "\n\t\tChoose Your Option\n"<< "\t\t[1]Ascending Order\n\t\t[2]Descending Order\n\t\t-\n\t\t[0]Back\n\n";
cout << "Option: ";
cin >> ch1;

if(ch1==0)
{
Sort();
}

else if(ch1 == 1 || ch1 ==2)
{
SortIC(ch1);
}

else
{
cout << "\nInvalid option ! Returning to sorting menu.";
}
getch();
}

else if(ch==3)
{
cout << "\n\t\tChoose Your Option\n"<< "\t\t[1]Ascending Order\n\t\t[2]Descending Order\n\t\t-\n\t\t[0]Back\n\n";
cout << "Option: ";
cin >> ch1;

if(ch1==0)
{
Sort();
}
else if(ch1 == 1 || ch1 ==2)
{
    SortAge(ch1);
}
else
{
cout << "\nInvalid option ! Returning to sorting menu.";
}
}
else
{
cout << "\nInvalid option. Please try again.";
}
getch();
Sort();
}

void List::menu()
{
//45
int ch;
do
{
system("cls");
cout << "----------------------------------------------------------\n";
cout << " SPORTS CENTRE CUSTOMERS RECORD\n";
cout << "----------------------------------------------------------\n";
cout << "\n\t\tChoose Your Option\n"<< "\t\t[1] Data Display"<< "\n\t\t[2] Data Insertion"<< "\n\t\t[3] Data Sorting"<< "\n\t\t[4] Data Searching"<< "\n\t\t[5] Data Deletion"<< "\n\t\t[6] Daily Equipment Rental"<< "\n\t\t-\n\t\t[0]Exit\n\n";
cout << "Option: ";
cin >> ch;

switch(ch)
{
case 1 :
DisplayList();
cout << endl;
getch();
break;

case 2:
Insert();
break;

case 3:
Sort();
break;

case 4 :
Find();
break;

case 5:
Delete();
break;
case 6:

Rent();
break;

//46
case 0:
cout << endl << "Thank youuuuuuuu :)";
out.open("AvailableBall.txt",ios::out);

while(!Ball.isEmpty())
{
out << Ball.getFront() << endl;
Ball.removeEq();
}

out.close();
out.open("RentedBall.txt",ios::app);

while(!rentedBall.isEmpty())
{
out << rentedBall.getFront() << endl;
rentedBall.removeEq();
}

out.close();
exit(0);

default:
cout << "\nInvalid option! Please try again.";
getch();
}
}
while(ch!=0);
return;
}

int main()
{
List cust;
string inpName,inpIC,inpItem,usedBall;
int inpD, inpM;
string ballID[size] = {"Abidas B1","Abidas B2","Abidas B3","Abidas B4","Abidas B5","Naik B6","Naik B7","Naik B8","Naik B9","Naik B10"};
cust.InsertNode("Rohan Mehta","July","Futsal",28,"921",3,2100,2300);
cust.InsertNode("Radhika Goel","April","Badminton",19,"122",1,800,1100);
cust.InsertNode("Lakshya Gupta","May","Netball",24,"960",15,1500,1800);
cust.InsertNode("Shreya Chauhan","September","Bowling",18,"201",29,1100,1400);
//47
cust.InsertNode("Molshree Sharma","November","Swimming",32,"880",18,1400,1700);
cust.InsertNode("Siddhartha Katiyar","December","Badminton",25,"950",21,2000,2300);
cust.InsertNode("Harsh Sharma","February","Futsal",42,"780",9,2000,2300);
cust.InsertNode("Mihika Manuraj","January","Bowling",37,"831",8,1600,1900);
cust.InsertNode("Naman Chaudhary","July","Ping Pong",31,"890",14,900,1100);
cust.InsertNode("Vyomini Vats","May","Tennis",20,"100",16,800,1100);
//for(int i=0;i<size;i++)
//Ball.insertEq(ballID[i]);
// Get Local Time
time( &rawtime );

timeinfo = localtime( &rawtime );
// Get balls that are available for rent

bout.open("AvailableBall.txt");

while(bout.eof())
{
getline(bout,usedBall,'\n');

if(usedBall == "")
{
continue;
}
Ball.insertEq(usedBall);
}
bout.close();
// Get balls that are rented recently
bout.open("RentedBall.txt",ios::in);

while(bout.good())
{
getline(bout,usedBall,'\n');
rentedBall.insertEq(usedBall);
}

bout.close();
// Get list of Past Equipment Borrower

bout.open("RentedItem.txt",ios::in);

while(bout.good())
{
getline(bout,inpName,'\n');
if(inpName == "")
{
//48
continue;
}

getline(bout,inpIC,'\n');
getline(bout,inpItem,'\n');

bout >> inpD;
bout >> inpM;
cust.InsertBorrowNode(inpName,inpIC,inpM-1,inpD,inpItem);
}

bout.close();
// Check if day has changed, if yes, put yesterday's rented ball into available balls for rent

//queue
if(inpD!= timeinfo->tm_mday)
{
while(!rentedBall.isEmpty())
{
Ball.insertEq(rentedBall.getFront());
rentedBall.removeEq();
}
out.open("RentedBall.txt",ios::out);
out.close();
}
cust.menu();
return 0;
}