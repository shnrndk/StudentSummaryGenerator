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

void getdata(){
    ifstream myFileStream("A.txt");
    if(!myFileStream.is_open()){
        cout<<"File failed to open"<<endl;
        return;
    }
    string column1,column2;
    string line;
    int i=0;

    while(getline(myFileStream,line)){
        stringstream sso(line);
        getline(sso,column1,' ');
        getline(sso,column2,' ');
        aPair.first=column1;
        aPair.second=atoi(column2.c_str());
        inputdata.push_back(aPair);
    }
    myFileStream.close();
    //cout<<"Data is successfully Inserted\n";
    return;
}
void initializedatabase(){
    int i=0;
    int k=0;
    
    while(i<inputdata.size()){
        int stucount=inputdata[i].second;
        int j=i;
        int ptr=0;
        subjectarray[k].set_subname(inputdata[j].first);
        subjectarray[k].set_stucount(inputdata[j].second);
        while(ptr<=stucount){
            int index=atoi(inputdata[j].first.c_str());
            int mark=inputdata[j].second;
            subjectarray[k].set_marks(ptr,index,mark);
            
            ptr++;
            j++;
        }
        i+=(stucount+1);
        k++;
        
    }
}

void DispSubSummary(string subname){
    int k=0;
    while(k<MAXSUBJECTS){
        if(subname==subjectarray[k].get_subname()){
            subjectarray[k].DisplaySubjectSummary();
            return;
        }
    k++;
    }
    cout<<"Cannot Find the Subject!";
    return; //Represent Cannot Find the Subject;
}

void DiplaySubject(string subname){
    int k=0;
    while(k<MAXSUBJECTS){
        if(subname==subjectarray[k].get_subname()){
            subjectarray[k].Displaysubject();
            return;
        }
    k++;
    }
    cout<<"Cannot Find the Subject!";
     //Represent Cannot Find the Subject;
    
}

void DisplayStudent(int index){
    int k=0;
    cout<<"\n  **DETAILS OF STUDENT "<<index<<"**"<<endl;
    
    int flag=0;
    while(k<MAXSUBJECTS){
        int i=0;
        while(i<MAXSTUDENTS){
            if(subjectarray[k].studentmarkdatabase[i][0]==index){
                int mark=subjectarray[k].studentmarkdatabase[i][1];
                int grade=subjectarray[k].studentmarkdatabase[i][2];
                cout<<"SUBJECT-> "<<subjectarray[k].get_subname()<<"| MARK-> "<<mark<<"| GRADE-> "<<(char)grade<<endl;
                flag=1;
                break;
            }
        
        i++;
        }
    k++;
    }
    if(flag==0){
        cout<<"Error! Cannot Find the Requested Index No";
    }else{
        stringstream ss;
        ss<<index;
        string str=ss.str();
        cout<<"\nYEAR OF THE STUDENT -> "<<"20"<<str[0]<<str[1]<<endl;
    }

    
    cout<<"\n------------------------------------------";
    return;
}

void initializegrades(){
    int k=0;

    while(k<MAXSUBJECTS){
        int ptr=1;
        while(ptr<MAXSTUDENTS){
            int score=subjectarray[k].studentmarkdatabase[ptr][1];
            if(score>=70){
                subjectarray[k].studentmarkdatabase[ptr][2]=65;
            }else if(score>=55){
                subjectarray[k].studentmarkdatabase[ptr][2]=66;
            }else if(score>=40){
                subjectarray[k].studentmarkdatabase[ptr][2]=67;
            }else if(score>=30){
                subjectarray[k].studentmarkdatabase[ptr][2]=68;
            }else if(score>0){
                subjectarray[k].studentmarkdatabase[ptr][2]=70;
            }
            ptr++;
        }
        k++;    
    }
    
   
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
