#include<iostream>
#include<fstream>
#include<conio.h>
#include<list>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;


void printCourses()
{
    ifstream fin;
    fin.open("courses.txt");
    string course;
    int n=0;
    vector<string>v;
    getline(fin,course);
    
    while(fin)
    {
        n++;
        v.push_back(course);       
        getline(fin,course);
    }

    cout<<"Total courses: "<<n<<endl;
    cout<<"Course list:\n\n";
    for(string course: v)
    {
        cout<<course<<endl;
    }

    fin.close();
        
}

void addCourses()
{
    ofstream fout;
    fout.open("courses.txt",ios::app);
    
    string course;
    cout<<"Enter the courses you want to add:\n";
    cout<<"(Press 0 to stop..)\n\n";
    cin.ignore();
    getline(cin,course);
    
    while(course!="0")
    {
        fout<<course<<endl;
        getline(cin,course);
    }
    cout<<"\nCourses added!!\n\n";

    fout.close();

}

void printStudents()
{
    ifstream fin;
    fin.open("students.txt");
    vector<string>students;
    vector<string> sub[100];
    string course;
    int s=0;
    getline(fin,course);
    while(fin)
    {
        if(course=="")
            s++;
        else if(course[course.length()-1]==':')
            students.push_back(course);
        else
            sub[s].push_back(course);
        getline(fin,course);
    }
    cout<<"Total Students: "<<s<<endl<<endl;

    for(int i=0;i<s;i++)
    {
        cout<<students[i]<<endl;
        for(int j=0;j<sub[i].size();j++)
            cout<<sub[i][j]<<endl;
        cout<<endl;
    }

    fin.close();

}

void addStudents()
{
    ofstream fout;
    fout.open("students.txt",ios::app);
    char choice='y';
    string student,course;
    do
    {
        system("cls");
        cin.ignore();
        cout<<"Enter student name: ";
        getline(cin,student);
        fout<<student<<":\n";
        cout<<"\nEnter the courses of the student:\n";
        cout<<"(Press 0 to stop..)\n\n";
        getline(cin,course);
        
        while(course!="0")
        {
            fout<<course<<endl;
            getline(cin,course);
        }
        fout<<endl;
        cout<<"\nStudent added!!\n\n";

        cout<<"Do you want to enter more students?\nEnter (Y/N):  ";
        cin>>choice;

    } while (choice=='y'|| choice=='Y');
    
    fout.close();
}

void graphColoring(list<int>adj[],int V,int result[])
{
    result[0]=0;
    for(int u=1;u<V;u++)
        result[u]=-1;
    bool available[V];
    for(int i=0;i<V;i++)
        available[i]=true;
    for(int u=1;u<V;u++)
    {
        list<int>::iterator i;
        for(i=adj[u].begin();i!=adj[u].end();i++)
            if(result[*i]!=-1)
                available[result[*i]]=false;
        int col;
        for(col=0;col<V;col++)
            if(available[col]!=false)
                break;
        result[u]=col;
        for(i=adj[u].begin();i!=adj[u].end();i++)
            if(result[*i]!=-1)
                available[result[*i]]=true;
    }

}


bool hasEdge(list<int>adj[], int c1,int c2)
{
    for(auto i=adj[c1].begin();i!=adj[c1].end();i++)
        if(*i==c2)
            return true;
    return false;

}

void generateExamTimetable()
{
    int maxCourses=1;
    cout<<"Enter max. no. of courses in a day:  ";
    cin>>maxCourses;
    while(maxCourses<1)
    {
        cout<<"Max no. of courses can't be less than 1 !!";
        cout<<"\nEnter again !!";
        getch();
        system("cls");
        cout<<"Enter max. no. of courses in a day:  ";
        cin>>maxCourses;
    }
    cout<<"\n\n";
    
    ifstream fin;
    fin.open("courses.txt");
    
    vector<string>v;
    map<string,int>m;

    string course;
    int n=0;
    getline(fin,course);
    
    while(fin)
    {
        n++;
        v.push_back(course);
        m[course]=n-1;        
        getline(fin,course);
    }
    fin.close();
    // cout<<n<<endl;
    
    list<int>adj[n];
    fin.open("students.txt");
    vector<string> sub[100];
    
    int s=0;
    getline(fin,course);
    while(fin)
    {
        if(course=="")
            s++;
        else if(course[course.length()-1]!=':')
            sub[s].push_back(course);
        getline(fin,course);
    }
    // cout<<s<<endl;

    // for(int i=0;i<s;i++)
    // {
    //     for(int j=0;j<sub[i].size();j++)
    //         cout<<sub[i][j]<<"    ";
    //     cout<<endl;
    // }

    for(int i=0;i<s;i++)
    {
        for(int j=0;j<sub[i].size();j++)
        {
            string x=sub[i][j];
            for(int k=0;k<sub[i].size();k++)
            {
                int c1=m[sub[i][j]],c2=m[sub[i][k]];
                if(sub[i][k]!=x && !hasEdge(adj,c1,c2))
                    adj[c1].push_back(c2);
            }
        }
    }

    // for(int u=0;u<n;u++)
    // {
    //     for(auto i=adj[u].begin();i!=adj[u].end();i++)
    //         cout<<*i<<" ";
    //     cout<<endl;
    // }

    fin.close();

    int result[n];

    graphColoring(adj,n,result);

    // for(int u=0;u<n;u++)
    //     cout<<u<<"->"<<result[u]<<endl;

    vector<vector<int>>subjects(n);
    for(int i=0;i<n;i++)
    {
        subjects[result[i]].push_back(i);
    }

    int index;
    for(index=0; index<subjects.size(); index++)
    {
        if(subjects[index].size()==0)
            break;
    }
    subjects.erase(subjects.begin()+index, subjects.end());

    for(int i=0;i<subjects.size();i++)
    {
        if(subjects[i].size()>maxCourses)
        {
            subjects.push_back(vector<int>(subjects[i].size()-maxCourses));
            copy(subjects[i].begin()+maxCourses, subjects[i].end(), subjects[subjects.size()-1].begin());
            subjects[i].erase(subjects[i].begin()+maxCourses, subjects[i].end());
        }
    }

    cout<<"Suggested Exam Timetable:\n\n";
    for(int i=0;i<subjects.size();i++)
    {
        if(subjects[i].size()==0)
            break;
        cout<<"Day "<<i+1<<":"<<endl;
        for(int j:subjects[i])
            cout<<v[j]<<endl;
        cout<<endl;
    }



}

int main()
{
    system("cls");
    int choice;
    do
    {
        system("cls");
        cout<<"Menu\n";
        cout<<"1. See courses"<<endl;
        cout<<"2. Add new courses"<<endl;
        cout<<"3. See students with their courses"<<endl;
        cout<<"4. Add new students"<<endl;
        cout<<"5. Generate exam timetable"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"\nSelect an option:  ";
        cin>>choice;

        switch(choice)
        {
            case 1:
            {
                system("cls");
                printCourses();
                getch();
                break;
            }

            case 2:
            {
                system("cls");
                addCourses();
                getch();
                break;
            }

            case 3:
            {
                system("cls");
                printStudents();
                getch();
                break;
            }

            case 4:
            {
                system("cls");
                addStudents();
                getch();
                break;
            }

            case 5:
            {
                system("cls");
                generateExamTimetable();
                getch();
                break;
            }

            case 6:
            {
                system("cls");
                cout<<"\n\n----------Thank you-----------\n\n";
                getch();
                break;
            }

            default:
            {
                cout<<"Wrong choice!!!\n";
                cout<<"Please enter again.\n";
                getch();
            }

        }

    }while(choice!=6);

}