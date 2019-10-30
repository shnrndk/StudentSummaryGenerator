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

void savesummary(){
    int k=0;
    while(k<MAXSUBJECTS){
        int i=0;
        int noAs=0;
        int noBs=0;
        int noCs=0;
        int noDs=0;
        int noEs=0;
        if(subjectarray[k].stucountforsub==0){
            k++;
            continue;
        }

        while(i<MAXSTUDENTS){
            if(subjectarray[k].studentmarkdatabase[i][2]==65){
                noAs++;
            }else if(subjectarray[k].studentmarkdatabase[i][2]==66){
                noBs++;
            }else if(subjectarray[k].studentmarkdatabase[i][2]==67){
                noCs++;
            }else if(subjectarray[k].studentmarkdatabase[i][2]==68){
                noDs++;
            }else if(subjectarray[k].studentmarkdatabase[i][2]==69){
                noEs++;
            }
        
        i++;
        }
        float count=(float)subjectarray[k].stucountforsub;
        float percA=((float)noAs/count)*100;
        float percB=((float)noBs/count)*100;
        float percC=((float)noCs/count)*100;
        float percD=((float)noDs/count)*100;
        float percE=((float)noEs/count)*100;

        ofstream outfile;

        outfile.open("summdata.txt",ios_base::app);
        outfile <<subjectarray[k].subjectname<<" "<<subjectarray[k].stucountforsub<<" "<<" A "<<percA<<"% B "<<percB<<"%"<<" C "<<percC<<"%"<<" D "<<percD<<"%"<<" E "<<percE<<"%"<<endl;
        


        // ofstream file;
        // file.open ("StudentSummaryReport.txt");
        // file<<subjectarray[k].subjectname<<" "<<subjectarray[k].stucountforsub<<" "<<" A "<<percA<<"% B "<<percB<<"%"<<" C "<<percC<<"%"<<" D "<<percD<<"%"<<" E "<<percE<<"%"<<endl;
        // file.close();
        
        //cout<<subjectarray[k].subjectname<<" "<<subjectarray[k].stucountforsub<<" "<<" A "<<percA<<"% B "<<percB<<"%"<<" C "<<percC<<"%"<<" D "<<percD<<"%"<<" E "<<percE<<"%"<<endl;
    k++;
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