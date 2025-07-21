#include<iostream>
#include<fstream>
#include<stdio.h>
#include<iomanip>
#include<string.h>
using namespace std;

class student
{
    public:
    int rollno;
    int id;
    char name[50];
    char fname[50];
    char mname[50];
    char degree[40];
    int semester;
    public:
    friend void remove_student();
    friend void edit_student();
    void accept()
    {
        cout<<endl<<"Enter Roll no";
        cin>>rollno;
        cout<<"Enter Student ID";
        cin>>id;
        cout<<"Enter Student Name";
        cin>>name;
        cout<<"Enter Father Name";
        cin>>fname;
        cout<<"Enter Mother Name";
        cin>>mname;
        cout<<"Enter Degree";
         cin>>degree;
        cout<<"Enter Semester";
        cin>>semester;
    }
    void display()
    {
        cout<<endl<<rollno<<setw(20)<<id<<setw(30)<<name<<setw(30)<<fname<<setw(30)<<mname<<setw(20)<<degree<<setw(10)<<semester;
    }
};

student s1;   //global object--that can be accessed by any function

void add_student()
{ 
     s1.accept();
     fstream wr;
     wr.open("my students.txt",ios::app);
     wr.write((char *)&s1,sizeof(s1));
     wr.close();
     cout<<"Student Data written successfully";
}

void remove_student()
{
    fstream rd,wr;
    rd.open("my students.txt",ios::in);
    wr.open("temp.txt",ios::out);
    rd.seekg(0,ios::end);
    int size=rd.tellg();       
    int n=size/sizeof(s1);
    rd.seekg(0,ios::beg);
    int rno;
    cout<<endl<<"Enter Roll Number to be Searched and Removed";
    cin>>rno;
    for(int i=1;i<=n;i++)
    {
        rd.read((char *)&s1,sizeof(s1));
        if(s1.rollno==rno)
        {
            cout<<endl<<"Removed";
        }
        else
        {
            wr.write((char *)&s1,sizeof(s1));
        }
    }
      wr.close();
      rd.close();
      remove("my students.txt");
      rename("temp.txt","my students.txt");
}
void edit_student()
{
    fstream rd,wr;
    rd.open("my students.txt",ios::in);
    wr.open("temp.txt",ios::out);
    rd.seekg(0,ios::end);
    int size=rd.tellg();       
    int n=size/sizeof(s1);
    rd.seekg(0,ios::beg);
    int rno;
    cout<<endl<<"Enter Roll Number to be Searched and Updated";
    cin>>rno;
    for(int i=1;i<=n;i++)
    {
        rd.read((char *)&s1,sizeof(s1));
        if(s1.rollno==rno)
        {
            s1.accept();
            wr.write((char *)&s1,sizeof(s1));
            cout<<endl<<"Updated";
        }
        else
        {
            wr.write((char *)&s1,sizeof(s1));
        }
    }
      wr.close();
      rd.close();
      remove("my students.txt");
      rename("temp.txt","my students.txt");
}

void show_student()
{
    fstream rd;
    rd.open("my students.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg();
    int n=size/sizeof(s1);
    rd.seekg(0,ios::beg);
    cout<<endl<<"Roll No."<<setw(18)<<"Student ID"<<setw(29)<<"Student Name"<<setw(29)<<"Father Name"<<setw(29)<<"Mother Name"<<setw(16)<<"Degree"<<setw(18)<<"Semester";
    cout<<endl<<"----------------------------------------------------------------------------------------------------------------------------------------------------";
    for(int i=1;i<=n;i++)
    {
        rd.read((char *)&s1,sizeof(s1));
        s1.display();
    }
    
}

class mark_attendance
{
    int dd,mm,yy;
    int rollno;
    friend void view_attendance_date();
    friend void view_attendance_rollno();
    public:
    void init(int d,int m, int y,int r)
    {
        dd=d;
        mm=m;
        yy=y;
        rollno=r;
    }
    void display()
    {
        cout<<endl<<dd<<"-"<<mm<<"-"<<yy<<setw(10)<<rollno;
        fstream rd;
        rd.open("my students.txt",ios::in);
        rd.seekg(0,ios::end);
        int size=rd.tellg()/sizeof(s1);
        rd.seekg(0,ios::beg);
        for(int i=1;i<=size;i++)
        {
            rd.read((char *)&s1,sizeof(s1));
            if(rollno==s1.rollno)
            {
                cout<<setw(12)<<s1.id<<setw(21)<<s1.name<<setw(21)<<s1.fname<<setw(21)<<s1.mname<<setw(18)<<s1.degree<<setw(10)<<s1.semester<<endl;

            }
        }
    }

 void display(char *p,int s)
    {
        fstream rd;
        rd.open("my students.txt",ios::in);
        rd.seekg(0,ios::end);
        int size=rd.tellg()/sizeof(s1);
        rd.seekg(0,ios::beg);
        for(int i=1;i<=size;i++)
        {
            rd.read((char *)&s1,sizeof(s1));
            if(strcmp(s1.degree,p)==0 && s1.semester==s)
            {
               cout<<endl<<dd<<"-"<<mm<<"-"<<yy<<setw(14)<<s1.rollno<<setw(14)<<s1.id<<setw(20)<<s1.name<<setw(20)<<s1.fname<<setw(20)<<s1.mname<<setw(18)<<s1.degree<<setw(12)<<s1.semester;

            }
        }
    }

};
mark_attendance m1;

class attendance
{
    public:
    int dd,mm,yy;
    int arr[50];
    void accept()
    {
        int p,count=0;
        cout<<endl<<"Enter Date in DD MM YY";
        cin>>dd>>mm>>yy;
        cout<<endl<<"Enter Roll No's of Present Students followed by -1";
        for(int i=0;i<=49;i++)
        {
            cin>>p;
            if(p==-1)
            {
                break;
            }
            arr[i]=p;
            count++;
        }
        fstream wr;
        wr.open("attendance_data.txt",ios::app);
        for(int j=0;j<count;j++)
        {
            m1.init(dd,mm,yy,arr[j]);
            wr.write((char *)&m1,sizeof(m1));
        }
        wr.close();
    }
};

void view_attendance()
{
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"No. of Students Present are "<<size<<endl;
    rd.seekg(0,ios::beg);
    cout<<endl<<"Dated"<<setw(16)<<"Roll no."<<setw(14)<<"Student ID"<<setw(18)<<"Student Name"<<setw(20)<<"Father Name"<<setw(20)<<"Mother Name"<<setw(15)<<"Degree"<<setw(17)<<"Semester";
    cout<<endl<<"------------------------------------------------------------------------------------------------------------------------------";
    for(int i=1;i<=size;i++)
    {
        rd.read((char*)&m1,sizeof(m1));
        m1.display();
    }

}

void view_attendance_date()
{
    int d,m,y;
    cout<<"Enter Date, Month and Year";
    cin>>d>>m>>y;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"No. of Objects are "<<size<<endl;
    rd.seekg(0,ios::beg);
    cout<<endl<<"Dated"<<setw(16)<<"Roll no."<<setw(14)<<"Student ID"<<setw(18)<<"Student Name"<<setw(20)<<"Father Name"<<setw(20)<<"Mother Name"<<setw(15)<<"Degree"<<setw(17)<<"Semester"<<endl;
    cout<<endl<<"------------------------------------------------------------------------------------------------------------------------------";
    for(int i=1;i<=size;i++)
    {
        rd.read((char*)&m1,sizeof(m1));
        if(m1.dd==d && m1.mm==m && m1.yy==y)
        {
             m1.display();                                                     
        }
    }
}

void view_attendance_degSem()
{
    char degree[50];
    int semester;
    cout<<"Enter Degree Name and Semester";
    cin>>degree>>semester;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"No. of Objects are "<<size<<endl;
    rd.seekg(0,ios::beg);
    cout<<endl<<"Dated"<<setw(20)<<"Roll no."<<setw(14)<<"Student ID"<<setw(18)<<"Student Name"<<setw(20)<<"Father Name"<<setw(20)<<"Mother Name"<<setw(15)<<"Degree"<<setw(17)<<"Semester";
    cout<<endl<<"-----------------------------------------------------------------------------------------------------------------------------------";
    for(int i=1;i<=size;i++)
    {
        rd.read((char*)&m1,sizeof(m1));
        m1.display(degree,semester);
    }
}

void view_attendance_rollno()
{
    int rno;
    cout<<"Enter Roll Number";
    cin>>rno;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"No. of Students Present are "<<size<<endl;
    rd.seekg(0,ios::beg);
    cout<<endl<<"Dated"<<setw(18)<<"Roll no."<<setw(14)<<"Student ID"<<setw(18)<<"Student Name"<<setw(20)<<"Father Name"<<setw(20)<<"Mother Name"<<setw(15)<<"Degree"<<setw(17)<<"Semester";
    cout<<endl<<"------------------------------------------------------------------------------------------------------------------------------";
    for(int i=1;i<=size;i++)
    {
        rd.read((char*)&m1,sizeof(m1));
        if(m1.rollno==rno)
        {
        m1.display();
        }
    }
}

int main()
{
    int e=0;
    while(e==0)
    {
    cout<<endl<<"*******************************************# WELCOME TO ATTENDANCE MANAGEMENT #*********************************************";
    cout<<endl<<"Press 1 to Add New Student";
    cout<<endl<<"Press 2 to View all Students";     
    cout<<endl<<"Press 3 to Remove Student";
    cout<<endl<<"Press 4 to Edit Student";
    cout<<endl<<"Press 5 to Mark Bulk Attendance";
    cout<<endl<<"Press 6 to View Attendance";
    cout<<endl<<"Press 7 to View Attendance by Date";
    cout<<endl<<"Press 8 to View Attendance by Degree and Semester";
    cout<<endl<<"Press 9 to View Attenndance by Roll no.";
    cout<<endl<<"Press 10 to Exit";
    cout<<endl<<"****************************************************************************************************************************";
    int choice;
    cout<<endl<<"Enter choice";
    cin>>choice;
    if(choice==1)
    {
        add_student();
    }   
    else if(choice==2)
    {
        show_student();
    }
    else if(choice==3)
    {
        remove_student();
    }
    else if(choice==4)
    {
        edit_student();
    }
    else if(choice==5)
    {
        attendance o1;
        o1.accept();
    }
    else if(choice==6)
    {
        view_attendance();
    }
    else if(choice==7)
    {
        view_attendance_date();
    }
    else if(choice==8)
    {
       view_attendance_degSem();
    }
    else if(choice==9)
    {
        view_attendance_rollno();
    }
      else
     {
         e=1;
     }
    }
}

