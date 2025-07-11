#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
using namespace std;

class Manager
{
    private:
    int dd,mm,yy;
    char type[50];
    char head[150];
    float amount;
    friend void showTransaction();
    friend void showTotalSaving();
    friend void showTransaction_inrange();
    public:
    void getIncome(char *h,float a,int d,int m,int y)
    {
        strcpy(type,"Income");
        strcpy(head,h);
        amount=a;
        dd=d;
        mm=m;
        yy=y;
    }
    void getExpense(char *h,float a,int d,int m,int y)
    {
        strcpy(type,"Expense");
        strcpy(head,h);
        amount=a;
        dd=d;
        mm=m;
        yy=y;
    }
    void getSaving(char *h,float a,int d,int m,int y)
    {
        strcpy(type,"Saving");
        strcpy(head,h);
        amount=a;
        dd=d;
        mm=m;
        yy=y;
    }
    void display()
    {
        cout<<endl<<dd<<"-"<<mm<<"-"<<yy<<"\t"<<setw(21)<<type<<setw(44)<<head<<setw(39)<<amount;
    }
};

Manager obj;

void recordExpense()
{
    char he[50];
    float amt;
    int d,m,y;
    cout<<"Enter Head name :";
    cin>>he;
    cout<<"Enter Amount :";
    cin>>amt;
    cout<<"Enter Date in DD-MM-YY :";
    cin>>d>>m>>y;
    obj.getExpense(he,amt,d,m,y);
    fstream wr;
    wr.open("transaction.txt",ios::app);
    wr.write((char *)&obj,sizeof(obj));
    wr.close();
    cout<<endl<<"Expense Recorded";
}
void recordIncome()
{
    char he[50];
    float amt;
    int d,m,y;
    cout<<"Enter Head name :";
    cin>>he;
    cout<<"Enter Amount :";
    cin>>amt;
    cout<<"Enter Date in DD-MM-YY :";
    cin>>d>>m>>y;
    obj.getIncome(he,amt,d,m,y);
    fstream wr;
    wr.open("transaction.txt",ios::app);
    wr.write((char *)&obj,sizeof(obj));
    wr.close();
    cout<<endl<<"Income Recorded";
}
void recordSaving()
{
    char he[50];
    float amt;
    int d,m,y;
    cout<<"Enter Head name :";
    cin>>he;
    cout<<"Enter Amount :";
    cin>>amt;
    cout<<"Enter Date in DD-MM-YY :";
    cin>>d>>m>>y;
    obj.getSaving(he,amt,d,m,y);
    fstream wr;
    wr.open("transaction.txt",ios::app);
    wr.write((char *)&obj,sizeof(obj));
    wr.close();
    cout<<endl<<"Saving Recorded";
}

void showTransaction()
{
    fstream rd;
    float total_income=0,total_expense=0,total_saving=0;
    rd.open("transaction.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg();
    int n=size/sizeof(obj);
    rd.seekg(0,ios::beg);
    int m,y;
    cout<<"Enter month and year";
    cin>>m>>y;
    cout<<endl<<"Dated"<<"\t\t\t\tType"<<"\t\t\t\t\tHead name"<<"\t\t\t\tTransaction Amount";
    cout<<endl<<"----------------------------------------------------------------------------------------------------------------------------------";
    for(int i=1;i<=n;i++)     
    {
       rd.read((char *)&obj,sizeof(obj));
       if(obj.mm==m && obj.yy==y)
       {
       if(strcmp(obj.type,"Income")==0)
        {
            total_income=total_income+obj.amount;
        }
        else if(strcmp(obj.type,"Expense")==0)
        {
            total_expense=total_expense+obj.amount;
        }
        else 
        {                    
            total_saving=total_saving+obj.amount;
        }
       obj.display();
       }

    }
          
    float net=total_income-total_expense-total_saving; 
     cout<<endl<<"----------------------------------------------------------------------------------------------------------------------------------";
     cout<<endl<<"Total Income: "<<total_income<<"\t\tTotal Expense: "<<total_expense<<"\t\tTotal Saving: "<<total_saving<<endl;
     cout<<"Net is: "<<net;
     cout<<endl<<"----------------------------------------------------------------------------------------------------------------------------------";

}

void showTotalSaving()
{
    fstream rd;
    float total_income=0,total_expense=0,total_saving=0;
    rd.open("transaction.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg();
    int n=size/sizeof(obj);
    rd.seekg(0,ios::beg);
     for(int i=1;i<=n;i++)
     {
        rd.read((char *)&obj,sizeof(obj));
        if(strcmp(obj.type,"Saving")==0)
        {
             total_saving=total_saving+obj.amount;
        }
     }
       cout<<"Total Saving is"<<" "<<total_saving<<endl;
}
void showTransaction_inrange()
{
    fstream rd;
    float total_income=0,total_expense=0,total_saving=0;
    int range;
    rd.open("transaction.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg();
    int n=size/sizeof(obj);
    rd.seekg(0,ios::beg);
    int m,m1;
    cout<<"Enter Starting month of range";
    cin>>m;
    cout<<"Enter Ending month of range";
    cin>>m1;
    cout<<endl<<"Dated"<<"\t\t\t\tType"<<"\t\t\t\t\tHead name"<<"\t\t\t\tTransaction Amount";
    cout<<endl<<"------------------------------------------------------------------------------------------------------------------------------------";
    for(int i=1;i<=n;i++)
    {
        rd.read((char *)&obj,sizeof(obj));
        if(obj.mm>=m && obj.mm<=m1)
        {

          if(strcmp(obj.type,"Income")==0)
        {
            total_income=total_income+obj.amount;
        }
        else if(strcmp(obj.type,"Expense")==0)
        {
            total_expense=total_expense+obj.amount;
        }
        else 
        {                    
            total_saving=total_saving+obj.amount;
        }

            obj.display();
       }
       
    }
     float net=total_income-total_expense-total_saving; 
     cout<<endl<<"-------------------------------------------------------------------------------------------------------------------------------------";
     cout<<endl<<"Total Income: "<<total_income<<"\t\t\t\tTotal Expense: "<<total_expense<<"\t\t\t\t\t\tTotal Saving: "<<total_saving<<endl;
     cout<<"Net is: "<<net;
     cout<<endl<<"-------------------------------------------------------------------------------------------------------------------------------------"; 
    
 }

int main()
{
   int e=0;
   while(e==0)
   {
    cout<<endl<<"Press 1 to Record  Expense";
    cout<<endl<<"Press 2 to Record Income";
    cout<<endl<<"Press 3 to Record Saving";
    cout<<endl<<"Press 4 to Show Transaction ";
    cout<<endl<<"Press 5 to Show Total Saving";
    cout<<endl<<"Press 6 to Show Transaction in range";
    cout<<endl<<"Press 7 to Exit";
    int choice;
    cout<<endl<<"Enter choice";
    cin>>choice;
    switch(choice)
    { 
        case 1:
        {
            recordExpense();
            break;
        }
        case 2:
        {
            recordIncome();
            break;
        }
        case 3:
        {
            recordSaving();
            break;
        }
        case 4:
        {
            showTransaction();
            break;
        }
        case 5:
        {
            showTotalSaving();
            break;
        }
        case 6:
        {
            showTransaction_inrange();
            break;
        }
        case 7:
        {
            e=1;
        }
    }

   }
}

