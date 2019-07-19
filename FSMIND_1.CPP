#include<time.h>
#include<iostream.h> 
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip.h>
#include<stdlib.h>
#include<string.h>
#define mmax 10
#define max 97
#define recsize 350
#define datafile "pharmacy.txt"
#define indexfile "medicine.txt"
char b[15] ;
static char        buf[17];
fstream stdfile,file,indfile;
 int i,indsize,item;
 char buffer[200],itid[15],na[20],pr[5],md[11],ed[11];

 void opener(fstream& sfile,const char* fn, int mode) {
	 sfile.open(fn, mode);
	 if (!sfile)
	 {
		 cout << "Unable to open the file  \n";
		 exit(1);
	 }
 }

void primary()
 {
	char a[15];
	time_t now = time(0);
	tm *ltm = localtime(&now);
	itoa(1900+ltm->tm_year,a,10);
	strcpy(b,a);
	itoa(1+ltm->tm_mon,a,10);
	strcat(b,a);
	itoa(ltm->tm_mday,a,10);
	strcat(b,a);
	itoa(ltm->tm_hour,a,10);
	strcat(b,a);
	itoa(ltm->tm_min,a,10);
	strcat(b,a);
	itoa(ltm->tm_sec,a,10);
	strcat(b,a);
}

 class medicine {
 public:   char itemid[15],name[25],price[5],mdate[11],edate[11];

 void initial();
 void write(int);
 void delete1();
 float getprice(char*);
// void insert();
void ftoa(float f);
 int hash(char[]);
 int search(char*);
  void remove(int,char[]);
 };

void medicine ::ftoa(float f)
{

    char *            cp = buf;
    unsigned long    l, rem;

    if(f < 0) {
	*cp++ = '-';
	f = -f;
    }
    l = (unsigned long)f;
    f -= (float)l;
    rem = (unsigned long)(f * 1e6);
    sprintf(cp, "%lu.%6.6lu", l, rem);
}

 class pharmacy {
 char orderid[15];
 int n,items;
 float amount;
 public:   char* order();
 void pack();
 void pinitial();
 friend int search(char*);
 void recDisp(int,char[]);
 void dataDisp(char*);
 void store(int addr);
 int hashp(char[]);
 };



 void medicine:: remove(int addr,char key[])
 {
	int b,g,i,a;
	char dummy[150];
	file.open(indexfile,ios::in|ios::out);
	file.seekg(addr,ios::beg);
	file.getline(dummy,150,'*');
	a=file.tellg();
	file.seekg(addr,ios::beg);
	file.getline(dummy,150,'*');
		file.getline(itemid,15,'|');
		if(strcmp(key,itemid)==0)
		{

				file.getline(name,25,'|');
				file.getline(price,5,'|');
				file.getline(mdate,11,'|');
				file.getline(dummy,150,'|');
				file.getline(edate,11,'|');
				g=file.tellg();
		}
		else
		{
			file.close();
			return;
		}
		a=a-2;
		file.seekp(a,ios::beg);
		b=g-a;
		for(i=0;i<=b;i++)
		file<<"#";


		a=addr/350;
		file.seekg(a*recsize,ios::beg);
		file.getline(dummy,3,'#');
		b=atoi(dummy);
		b=b-1;
		file.seekp(a*recsize,ios::beg);
		file<<b;

		file.close();
 }


void pharmacy::pinitial()
{
	int i,j;
	file.open(datafile,ios::app|ios::nocreate);
	if(!file)
	{
		   file.open(datafile,ios::out);
		   if(!file)
		   {
				cout<<"unable to open a file \n";
				exit(1);
		   }
		   for(i=0;i<max;i++)
		   {
			  file.seekp(i*recsize,ios::beg);
			  for(j=0;j<recsize-2;j++)
				  file<<"#";
			  file<<endl;
		   }
		   cout<<"empty file created \n";
	}
	 file.close();
}

float medicine::getprice(char* key)
 {
	  int found=0,j,i,addr,a ,m,g;
	char dummy[150],c[3],kk[20];
	float b;
	addr=hash(key);
	i=addr;
	stpcpy(kk,key);
	file.open(indexfile,ios::in|ios::out);
	do
	{
		m=i*recsize;
		file.seekg(m,ios::beg);
		file.getline(c,3,'#');
		a=atoi(c);
		if(a==0)
			break;
		file.seekg(m,ios::beg);
		for(j=0;j<3;j++)
		{
		file.getline(dummy,150,'*');
		file.getline(itemid,15,'|');
		if(strcmp(kk,itemid)==0)
		{

				file.getline(name,25,'|');
				file.getline(price,5,'|');
				strcpy(pr,price);
				b=atof(pr);
				file.getline(mdate,11,'|');
			    file.getline(dummy,150,'|');
				file.getline(dummy,150,'|');
				file.getline(edate,11,'|');
				found=1;

				file.close();
				return b;
		}
		}
		if(found==0)
		{
			i++;
			if(i%max==0)
				i=0;
		}
	}while(i!=addr);
	file.close();
	return -1;
 }

 int medicine:: search(char* key)
 {
 int found=0,j,i,addr,a ,m,aa,g;
	char dummy[150],c[3];
	addr=hash(key);
	i=addr;
	file.open(indexfile,ios::in|ios::out);
	do
	{
		m=i*recsize;
		file.seekg(m,ios::beg);
		file.getline(c,3,'#');
		a=atoi(c);
		if(a==0)
			break;
		file.seekg(m,ios::beg);
		for(j=0;j<3;j++)
		{
			aa=file.tellg();
		file.getline(dummy,150,'*');
		file.getline(itemid,15,'|');
		if(strcmp(key,itemid)==0)
		{

				file.getline(name,25,'|');
				strcpy(na,name);
				file.getline(price,5,'|');
				strcpy(pr,price);
				file.getline(mdate,11,'|');
				strcpy(md,mdate);
			       file.getline(dummy,150,'|');
				//file.getline(dummy,150,'|');
				file.getline(edate,11,'|');
				strcpy(ed,edate);
				found=1;
				cout<<setw(10)<<"Item id"<<setw(15)<<"name"<<setw(10)<<"price"<<setw(25)<<"Manufature Date"<<setw(15)<<"Expire Date"<<"\n";
				cout<<setw(10)<<itemid<<setw(15)<<na<<setw(10)<<pr<<setw(25)<<md<<setw(15)<<ed<<endl;


				file.close();
				return aa;
		}
		}
		if(found==0)
		{
			i++;
			if(i%max==0)
				i=0;
		}
	}while(i!=addr);
	if(found==0)
		cout<<"\n Record Does not exists in hash file\n";
	file.close();
	return -1;
 }

char* pharmacy::order()
 {
	medicine in;
	char d[150],m,dd[3],v[5];
	int flag,addr;
	float p;
	system("cls");
	strcpy(buffer,"");
	strcpy(d,"|");
	n=0;
	amount = 0;
	primary();
	strcpy(orderid,b);
	cout<<"\tThe Invoice Number ="<<orderid<<endl;
	a:cout<<"\n\t\tEnter the Item id \n";
	  cin>>itid;
	  flag=in.search(itid);
	if(flag==-1)
	{
		cout<<"\t\tThe Item is not present in the store";
		goto a;
	}
	n++;
	cout<<"\t\tHow many do u want";
	cin>>item;
	p=atof(pr);
	amount=amount+item*p;
	strcat(d,itid); strcat(d,"|");
	strcat(d,na); strcat(d,"|");
	itoa(item,v,10);
	strcat(d,v); strcat(d,"|");

	cout<<"\t\tDo you add another item (y/n)";
	cin>>m;
	if(m=='y' || m=='Y')
		goto a;
	else{
		strcpy(buffer, orderid); strcat(buffer, "|");
		itoa(n, dd, 10);
		strcat(buffer, dd); strcat(buffer,d );
		in.ftoa(amount);
		//itoa(amount, dd, 10);
		strcat(buffer, buf); strcat(buffer, "|");
		addr=hashp(orderid);
		store(addr);
		dataDisp(orderid);

	return orderid;
	}
}

int medicine:: hash(char key[])
 {
	 char cc[20];
	 strcpy(cc,key);
	 int i = 0, sum = 0;
	 while (cc[i] != '\0')
	 {
		 sum = sum + cc[i] - 48;
		 i++;
	 }
	 return sum % max;
 }

 int pharmacy:: hashp(char key[])
 {
	 int i = 0, sum = 0;
	 while (key[i] != '\0')
	 {
		 sum = sum + key[i] - 48;
		 i++;
	 }
	 return sum % max;
 }

 void pharmacy::store(int addr)
 {
	char dummy[10];
	int flag=0,i;
	file.open(datafile,ios::in|ios::out);
	file.seekg(addr*recsize,ios::beg);
	file.getline(dummy,5,'\n');
	if(strcmp(dummy,"####")==0)
	{
		 file.seekp(addr*recsize,ios::beg);
		 file<<buffer;
		 flag=1;
		 cout<<"\t\t The Record is Updated in the file\n";
	}
	else
	{
		for(i=addr+1; i!=addr; i++)
		{
			if(i%max==0)
				i=0;
			file.seekg(i*recsize,ios::beg);
			file.getline(dummy,5,'\n');
			if(strcmp(dummy,"####")==0)
			{
				cout<<"\n Collision has occored\n";
				cout<<"Home address is "<<addr<<"actual address is"<<i<<"\n";
				file.seekp(i*recsize,ios::beg);
				file<<buffer;
				flag=1;
				break;
			}
		}
	}

	if(i==addr && (!flag))
			cout<<"hash File is full, Record cannot be inserted\n";
		file.close();

 }

 void medicine::write(int addr)
{
	char dummy[10],c[3];
	 int flag = 0,j, i,a,m;
	 m=addr*recsize;
	 file.open(indexfile, ios::in | ios::out);
	 file.seekg(m,ios::beg);
	 file.getline(c,3,'#');
	 a=atoi(c);
	 if(a<3)
	 {
		m=m+3;
		for(j=0;j<3;j++){
	 file.seekg(m,ios::beg);
	 file.getline(dummy,5,'\n');
	if(strcmp(dummy,"####")==0)
	{
		 file.seekp(m,ios::beg);
		 file<<buffer;
		 flag=1;
		 cout<<"\t\t Record is Updated to file at"<<m<<"\n";
		 file.seekp(addr*recsize,ios::beg);
		 file<<a+1;
		 break;
		}else
		{m=m+103;}
	}
	}

	if(flag==0)
	{

		for(i=addr+1; i!=addr; i++)
		{
			if(i%max==0)
				i=0;
			m=i*recsize;
				file.seekg(m,ios::beg);
				file.getline(c,3,'#');
			a=atoi(c);
			if(a<3)
				{
					m=m+3;
					for(j=0;j<3;j++){
					file.seekg(m,ios::beg);
					file.getline(dummy,5,'\n');
					if(strcmp(dummy,"####")==0)
					{
						file.seekp(m,ios::beg);
						file<<buffer;
						flag=1;
						cout<<"\t\t Record is Updated to file at"<<m<<"\n";
						file.seekp(i*recsize,ios::beg);
						file<<a+1;
						break;
					}else
						{m=m+103;}
					}
					if(flag==1)
					{
						cout<<"\n Collision has occored\n";
						cout<<"Home address is "<<addr*recsize <<"actual address is"<<m<<"\n";
						break;
					}
					
				}
		
		}
	}
	if (i == addr && (!flag))
		 cout << "hash File is full, Record cannot be inserted\n";
	 file.close();
	 return;
}

 

 void medicine::initial()
 {
 int i,j;
	file.open(indexfile,ios::app|ios::nocreate);
	if(!file)
	{
		   file.open(indexfile,ios::out);
		   if(!file)
		   {
				cout<<"unable to open a file\n";
				exit(1);
		   }
		   for(i=0;i<max;i++)
		   {
			  file.seekp(i*recsize,ios::beg);
			  file<<0;
			  for(j=0;j<recsize-2;j++)
				  file<<"#";
			  file<<endl;
		   }
		   cout<<"empty file created\n";
	}
	 file.close();
  }

  void pharmacy::dataDisp(char* orid)
 {
	 int i,addr,found=0,aa,ii,j;
	 float b;
	 medicine in;
	 char v[5], a[5], d[2],key[20],m[200],mm[15],itemid[20],nam[20],dummy[10];
	 system("cls");
	 addr=hashp(orid);
	i=addr;
	stdfile.open(datafile,ios::in|ios::out);
	do
	{
		stdfile.seekg(i*recsize,ios::beg);
		stdfile.getline(dummy,5,'\n');
		if(strcmp(dummy,"####")==0)
			break;
		stdfile.seekg(i*recsize,ios::beg);
		stdfile.getline(key,15,'|');
		if(strcmp(key,orid)==0)
		{
			found=1;
			cout<<"\t\t ****************************************\n";
			cout<<"\t\t\t\tINVOICE\n";
			cout<<"\t\t ****************************************\n";
			cout << "\t\t THE ORDER ID IS=" << key << endl<<"\n";
			cout << " ==========================================================================\n";
			 cout << "Item id" << "\t\t" << "Name of Product" << "\t\t" << "Quantity" << "\t"<<"price"<<"\t      " << "Amount" << endl;
			 cout << "==========================================================================\n";
			 stdfile.getline(d, 2, '|');
			 n = atoi(d);
			  stdfile.getline(dummy,15,'|');
			 for (j = 0; j < n; j++)
			 {

				 stdfile.getline(itemid, 15, '|');
				  b=in.getprice(itemid);
				 stdfile.getline(nam, 25, '|');
				 stdfile.getline(v, 5, '|');
				 ii = atoi(v);
				 cout << itemid << "\t\t" << nam << "\t\t\t" << ii << "\t\t" <<b<<"\t\t" <<b*ii<<endl;
			 }
			 stdfile.getline(a, 5, '|');
			 cout << "\n\t\t\t\t\t THE TOTAL AMOUNT=" << a << endl<<"\n";
			 stdfile.close();
			 cout<<"Please enter 1 to contuene";
			 do{
			 cin>>aa;
			 if(aa==1)
			 return;
		       }while(1);

		}
		else
		{
			i++;
			if(i%max==0)
				i=0;
		}
	}while(i!=addr);
	if(found==0){
		cout<<"\n Record Does not exists in hash file\n";
	getch();}
	stdfile.close();
	return;

 }

//medicine::



int  main( ) // Main function
{

	pharmacy pp;
	medicine in;
	int option,flag;
	char key[20],k[20],ch;
	system("cls");
	pp.pinitial();
	in.initial();
	textcolor(8);
	textbackground(BLUE);


	do{
    cout<<"\n";
    cout<<"\t\t ================================================\n";
	cout<<"\t\t|         Pharmacy Billing System             |\n";
	cout<<"\t\t ================================================\n";

	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t1. Take an Order \t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t2. Add an new medicine to the list \t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t3. Search the medicine in the list\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t4. Delete the medicine in the list\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t5. Modify the medicine in the list\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t6. Search the Order \t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t7. EXIT \t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";

	cout<<"\t\tInput number Associated with Action: ";
	cin>>option;
	switch(option)
	{
		case 1:
			pp.order();
			system("cls");
			break;
		case 2:
			medicine in;
	 char dd[20],d[]="",price[5],id[20],name[20],edate[20],mdate[20];
	 int addr,p=1,j;
	 system("cls");
	 strcpy(buffer,"");
	cout<<"\t\t\t ****************************************\n";
	cout<<"\t\t\t\tEnter the Product Details\n";
	cout<<"\t\t\t ****************************************\n";

	 pp:cout << "\t\tEnter the item id ";
	cin >> id;
	 strcpy(d,id);
	 p=1 ;
	if(strlen(d)==7){
  if(!(d[0] >= '0' && d[0] <= '9'))
	{
	p=0;
	}
	for(j=1;j<4;j++){
  if (!((d[j] >= 'a' && d[j] <= 'z') || (d[j] >= 'A' && d[j] <= 'Z'))) {
		p=0;
	}
	for(j=4;j<7;j++)
	{
		if(!(d[j] >= '0' && d[j] <= '9'))
		{
			p=0;
		}
	}
   }
	}
   else{
   p=0;}
	if(p==0)
	{
		cout<<"Not the valid format\n";
		goto pp;
	}


	if(in.getprice(id) == -1)
	{
	 cout << "\t\tEnter the name ";
	 cin >> name;
	 cout << "\t\tEnter the price ";
	 cin >> price;
	 cout<<"\t\t Enter the Manufature date";
	 gets(mdate);
	 cout<<"\t\t Enter the Expire date";
	 gets(edate);
		strcat(buffer,"*");
		strcat(buffer, id); strcat(buffer, "|");
		strcat(buffer, name); strcat(buffer,"|" );
		strcat(buffer, price); strcat(buffer, "|");
		strcat(buffer, mdate); strcat(buffer, "|");
		strcat(buffer, edate); strcat(buffer, "|");
		addr = in.hash(id);
		in.write(addr);
		getch();
		system("cls");
		break;
	}
	else
	{
		cout<<"Item is Present in the file";
	getch();
	system("cls");
	break;
    }
		case 3:
			cout<<"\t\tEnter the Item key you wish to Search ";
			gets(key);
			flag=in.search(key);
			break;

		case 4:
			cout<<"\t\tEnter the Key you wish to delete";
			gets(k);
			flag=in.search(k);
			if(flag==-1)
				cout<<"The record is not present";
			else
			{
			cout<<"\t\tDo you Wish to delete (y/n)";
	        cin>>ch;
	        if(ch=='y' || ch=='Y')
			{in.remove(flag,k);
			cout<<"\t\tRecord is Delete\n";
			}else cout<<"\t\tRecord is not Delete";
			
			}
			break;
		case 5:
			cout<<"\t\tEnter the Key you wish to Modify";
			gets(key);
			flag=in.search(key);
			if(flag==-1)
				cout<<"\t\tThe record is not present";
			else
			{
				cout<<"\t\tDo you Wish to modifi (y/n)";
	        cin>>ch;
	        if(ch=='y' || ch=='Y')
			{in.remove(flag,k);

			
			
			in.remove(flag,key);
			system("cls");
	 strcpy(buffer,"");
	cout<<"\t\t\t ****************************************\n";
	cout<<"\t\t\t\tEnter the Modify Product Details\n";
	cout<<"\t\t\t ****************************************\n";

	 pq:cout << "\t\tEnter the item id ";
	cin >> id;
	 strcpy(d,id);
	 p=1 ;
	if(strlen(d)==7){
  if(!(d[0] >= '0' && d[0] <= '9'))
	{
	p=0;
	}
	for(j=1;j<4;j++){
  if (!((d[j] >= 'a' && d[j] <= 'z') || (d[j] >= 'A' && d[j] <= 'Z'))) {
		p=0;
	}
	for(j=4;j<7;j++)
	{
		if(!(d[j] >= '0' && d[j] <= '9'))
		{
			p=0;
		}
	}
   }
	}
   else{
   p=0;}
	if(p==0)
	{
		cout<<"Not the valid format\n";
		goto pq;
	}


	if(in.getprice(id) == -1)
	{
	 cout << "\t\tEnter the name ";
	 cin >> name;
	 cout << "\t\tEnter the price ";
	 cin >> price;
	 cout<<"\t\t Enter the Manufature date";
	 gets(mdate);
	 cout<<"\t\t Enter the Expire date";
	 gets(edate);
		strcat(buffer,"*");
		strcat(buffer, id); strcat(buffer, "|");
		strcat(buffer, name); strcat(buffer,"|" );
		strcat(buffer, price); strcat(buffer, "|");
		strcat(buffer, mdate); strcat(buffer, "|");
		strcat(buffer, edate); strcat(buffer, "|");
		addr = in.hash(id);
		in.write(addr);
		getch();
		system("cls");
		break;
	}
	else
	{
		cout<<"Item is Present in the file";
	getch();
	system("cls");
	break;
    }
	}else cout<<"Record is not Delete";	
	}

			break;

		case 6:
			cout<<"\t\tEnter the key";
			gets(k);
			pp.dataDisp(k);
			system("cls");
			break;
		default:exit(0);
		cout<<"thank you"<<endl;
		getch();
		return 1;

	}

	}while(1) ;
	
	

 }

//end  main