#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <stdlib.h>
#include <cmath>
using namespace std;
const int MAXSUBJECTS=10;
const int MAXSTUDENTS=100;

vector< pair<string,int> > inputdata;
pair<string,int> aPair;

class Subject{
private:
    int stucountforsub;
    string subjectname;
    int studentmarkdatabase[MAXSTUDENTS][3];
    int subavg;
public:
    void set_stucount(int count);
    void set_subname(string sname);
    void set_marks(int position,int index,int score);
    string get_subname();
    void Displaysubject();
    //void DisplayStudentDetails(int index);
    void DisplaySubjectSummary();
friend void initializegrades();
friend void DisplayStudent(int index);
friend void savesummary();
friend void sortarray();
};

void Subject::set_subname(string sname){subjectname=sname;}
void Subject::set_stucount(int count){stucountforsub=count;}
void Subject::set_marks(int position,int index,int score){
    studentmarkdatabase[position][0]=index;
    studentmarkdatabase[position][1]=score;
}
string Subject::get_subname(){return subjectname;}
Subject subjectarray[MAXSUBJECTS];

void Subject::Displaysubject(){
    cout<<"SUBJECT NAME - "<<subjectname<<endl;
    cout<<"NO OF STUDENTS PER THIS SUBJECT - "<<stucountforsub<<endl;
    int ptr=1;
    cout<<endl;
    cout<<"**STUDENT GRADE TABLE**"<<endl;
    
    cout<<" INDEX   "<<"|"<<"SCORE"<<"|"<<"GRADE"<<endl;
    while(ptr<=stucountforsub){
        cout<<studentmarkdatabase[ptr][0]<<" | "<<studentmarkdatabase[ptr][1]<<" | "<<(char)studentmarkdatabase[ptr][2]<<endl;
        ptr++;
    }
    return;
}

void Subject::DisplaySubjectSummary(){
    cout<<"\n**SUBJECT SUMMARY**"<<endl;
    cout<<"\nSUBJECT NAME - "<<subjectname<<endl;
    cout<<"NO OF STUDENTS PER THIS SUBJECT - "<<stucountforsub<<endl;
    //Calculating the average
    int ptr=1;
    int totalofallstudents=0;
    while(ptr<=stucountforsub){
        totalofallstudents+=studentmarkdatabase[ptr][1];
        ptr++;
    }
    int avg=totalofallstudents/stucountforsub;
    cout<<"\nSTUDENT MARKS AVERAGE FOR THE SUBJECT "<<subjectname<<" -> "<<avg<<endl;

    //Caluculating the Standard Deviation
    ptr=1;
    int temp=0;
    int squarestore=0;
    int var=0;
    while(ptr<=stucountforsub){
        temp=studentmarkdatabase[ptr][1]-avg;
        squarestore=temp*temp;
        var+=squarestore;
        ptr++;
    }
    cout<<"STUDENT MARKS STANDARD DEVIATION FOR THE SUBJECT "<<subjectname<<" -> "<<sqrt(var)<<endl;
    return;
}





void sortarray(){
    for(int k=0;k<MAXSUBJECTS;k++){
        for(int j=1;j<subjectarray[k].stucountforsub;j++){
        int min=subjectarray[k].studentmarkdatabase[j][0];
        int temparray[3];
        int ptr;

        for(int i=j;i<subjectarray[k].stucountforsub;i++){
            if(min>subjectarray[k].studentmarkdatabase[i][0]){
                min=subjectarray[k].studentmarkdatabase[i][0];
                ptr=i;
            }
        }
        if(min!=subjectarray[k].studentmarkdatabase[j][0]){
            temparray[0]=subjectarray[k].studentmarkdatabase[j][0];
            temparray[1]=subjectarray[k].studentmarkdatabase[j][1];
            temparray[2]=subjectarray[k].studentmarkdatabase[j][2];

            subjectarray[k].studentmarkdatabase[j][0]=subjectarray[k].studentmarkdatabase[ptr][0];
            subjectarray[k].studentmarkdatabase[j][1]=subjectarray[k].studentmarkdatabase[ptr][1];
            subjectarray[k].studentmarkdatabase[j][2]=subjectarray[k].studentmarkdatabase[ptr][2];
            
            subjectarray[k].studentmarkdatabase[ptr][0]=temparray[0];
            subjectarray[k].studentmarkdatabase[ptr][1]=temparray[1];
            subjectarray[k].studentmarkdatabase[ptr][2]=temparray[2];
        }
    }
    }

}

int main(){
    getdata();
    initializedatabase();
    initializegrades();
    sortarray();
    int x=0;
    do{
        cout<<"\n***STUDENT MARKS DATABASE***\n"<<endl;
        cout<<"1.Display Subject"<<endl;
        cout<<"2.Display Student"<<endl;
        cout<<"3.Display Subject Summary"<<endl;
        cout<<"4.Save Summaries"<<endl;
        cout<<"5.Exit Program"<<endl;
        cout<<"Pls Enter Your Choice : ";
        
        cin>>x;
        switch(x){
            case 1:{
                        cout<<"Enter the Subject Code Without Spaces: ";
                        string temp3;
                        cin>>temp3;
                        DiplaySubject(temp3);
                        cout<<"\nReturn to Main Meny Press 0 and Press Enter: ";
                        int x;
                        cin>>x;
                        if(x==0){
                            break;
                        }else{
                            break;
                        }

                        
                    }
            case 2:{
                        cout<<"Enter the Index No Of the Student: ";
                        int temp1;
                        cin>>temp1;
                        DisplayStudent(temp1);
                        cout<<"-----------------------------------------------";
                        cout<<"\nReturn to Main Meny Press 0 and Press Enter: ";
                        int x;
                        cin>>x;
                        if(x==0){
                            break;
                        }else{
                            break;
                        }
                        break;
                    }
            case 3: {
                        cout<<"Enter the Subject Code Without Spaces: ";
                        string temp2;
                        cin>>temp2;
                        DispSubSummary(temp2); 
                        cout<<"-----------------------------------------------";
                        cout<<"\nReturn to Main Meny Press 0 and Press Enter: ";
                        int x;
                        cin>>x;
                        if(x==0){
                            break;
                        }else{
                            break;
                        }
                        break;
                    }
            case 4:
                    savesummary();
                    break;
            default:{
                    cout<<"Pls Enter A valid Choice!\n";
                    cout<<"\nReturn to Main Meny Press 0 and Press Enter: ";
                        int x;
                        cin>>x;
                        if(x==0){
                            break;
                        }else{
                            break;
                        }
                        break;
                    break;
                    }
        }
    }while(x!=5);

    
    return 0;
}
