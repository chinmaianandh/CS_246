#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

struct course
{
    string sem;
    string c_num;
    string c_name;
    string cred;
    string grad;
};

struct stud
{
    string roll;
    string s_name;
    vector<course> C;
    vector<float> spi;
};

int find_stud(string a,vector<stud> s)
{
    int n=s.size();
    for(int i=0;i<n;i++)
    {
        if(s[i].roll==a) return i;
    }
    return -1;
}

int find_co(string a,vector<course> c)
{
    int n=c.size();
    for(int i=0;i<n;i++)
    {
        if(c[i].c_num==a) return i;
    }
    return -1;
}

int gra(string s)
{
    if(s=="AA") return 10;
    else if(s=="AB") return 9;
    else if(s=="BB") return 8;
    else if(s=="BC") return 7;
    else if(s=="CC") return 6;
    else if(s=="CD") return 5;
    else if(s=="DD") return 4;
    else return 0;
}

int main()
{
    vector<stud> out;
    vector<course> co;
    ifstream st;
    st.open("students.csv",ios::in);
    //cout<<"1"<<endl;
    while(!st.eof())
    {   
        string a;
        getline(st,a,',');
        //cout<<"3"<<endl;
        stud s;
        s.s_name=a;
        
        
        getline(st,a,'\n');
        s.roll=a;
        //cout<<s.s_name<<" "<<s.roll<<endl;
        out.push_back(s);
    }
    st.close();

    st.open("courses.csv",ios::in);
    while(!st.eof())
    {
        string a;
        getline(st,a,',');
        
        course sa;
        sa.sem=a;
        
        getline(st,a,',');
        
        sa.c_num=a;
        getline(st,a,',');

        sa.c_name=a;
        getline(st,a,',');
        
        getline(st,a,',');
        getline(st,a,',');
        getline(st,a,'\n');
        sa.cred=a;
        co.push_back(sa);
    }
    st.close();
    //cout<<"3rd input"<<endl;
    st.open("grades.csv",ios::in);
    while(!st.eof())
    {
        string a;
        getline(st,a,',');
        int si=find_stud(a,out);
        
        getline(st,a,',');
        int y=a.size();
        if(a[y-1]==' ') a=a.substr(0,y-1);
        int ci=find_co(a,co);
        //cout<<s.s_name<<" "<<s.roll<<endl;
        getline(st,a,'\n');
        co[ci].grad=a;
        out[si].C.push_back(co[ci]);
        //int x=out[si].C.size();
        //cout<<out[si].s_name<<" "<<out[si].C[x-1].sem<<" "<<out[si].C[x-1].c_num<<" "<<out[si].C[x-1].grad<<endl;
    }
    st.close();

    for(int i=0;i<out.size();i++)
    {
        ofstream op;
        op.open(out[i].roll+".txt",ios::out);
        op<<"Name: "<<out[i].s_name<<endl;
        op<<"Roll Number: "<<out[i].roll<<endl;
        bool flag=true;
        int k=1;
        int p=0;
        while(flag)
        {
            int sum=0;
            op<<endl<<"Semester-"<<k<<endl;
            op<<"Course Number |   Course Name | C | Grade"<<endl;
            k++;
            for(int j=p;j<out[i].C.size();j++)
            {  
                if(to_string(k)==out[i].C[j].sem)
                {
                    float sp=sum/(j-p);
                    out[i].spi.push_back(sp);
                    p=j;
                    break;
                }
                op<<out[i].C[j].sem<<"  "<<out[i].C[j].c_num<<"    "<<out[i].C[j].c_name<<"    "<<out[i].C[j].cred<<"     "<<out[i].C[j].grad<<endl;
                
                float fol=stof(out[i].C[j].cred);
                int lol=(int)fol;
                
                sum+=(lol*gra(out[i].C[j].grad));
                
                if(out[i].C.size()==j+1) flag=false;
            }    
        }
        op<<endl<<"Sem->    1   2   3   4   5   6   7   8"<<endl;
        op<<"SPI->  "<<out[i].spi[0]<<" "<<out[i].spi[1]<<" "<<out[i].spi[2]<<" "<<out[i].spi[3]<<" "<<out[i].spi[4]<<" "<<out[i].spi[5]<<" "<<out[i].spi[6]<<" "<<out[i].spi[7]<<endl;

    }
}
