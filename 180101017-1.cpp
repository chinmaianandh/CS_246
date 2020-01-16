#include <bits/stdc++.h> 
using namespace std;

class course{
             public:
		string name;
                string number;
                int credits;
                int sem;
};
class student{
              public:
		string name;
                string rollno;
		vector<string> courses;
                vector<string> grades;
};

void gen(student a , vector<course> cs)
                       {
                        vector<course> c;
			for(int i=0;i<a.courses.size();i++)
                           {
                            for(int j=0;j<cs.size();j++)
                               {
                                if(a.courses[i] == cs[j].number)
                                  {
				   c.push_back(cs[j]);
                                   break;
                                   }
                                }
                            }
                        float spi[8];
                        float semcredits[8];
                        float cpi[8];
			fstream fout;
			string s = a.rollno;
			s+=".txt";
                        fout.open(s, ios::out );
                        fout<<"Name:"<<a.name<<endl;
                        fout<<"Roll Number:"<<a.rollno<<endl;
			for(int i=1;i<9;i++)
                           {
                             spi[i-1]=0;
                             semcredits[i-1]=0;
                             fout<<endl<<"SEMISTER "<<i<<endl;
			     fout<<"Course Number\t"<<"|\t"<<"Course Name\t"<<"|\t"<<"C\t"<<"|\t"<<"Grade\t"<<endl;
			     for(int j=0;j<a.courses.size();j++)
				{
				  if(c[j].sem==i)
                                     {
                                      fout<<c[j].number<<"\t"<<c[j].name<<"\t"<<c[j].credits<<"\t"<<a.grades[j]<<"\t"<<endl;
                                      int P;
                                      if(a.grades[j]=="AA")
                                        P=10;
                                      else if(a.grades[j]=="AB")
					P=9;
                                      else if(a.grades[j]=="BB")
					P=8;
                                      else if(a.grades[j]=="BC")
					P=7;
                                      else if(a.grades[j]=="CC")
					P=6;
                                      else if(a.grades[j]=="CD")
					P=5;
                                      else if(a.grades[j]=="DD")
					P=4;
                                      spi[i-1]+=P*c[j].credits;
                                      semcredits[i-1]+=c[j].credits;
                                      }
                                 }
			     }
                             fout<<endl;
                        for(int i=1;i<9;i++)
                        fout<<i<<"  ";
                        fout<<endl;
                        fout<<"SPI ";
                        for(int i=1;i<9;i++)
                        fout<<spi[i-1]/semcredits[i-1]<<" ";
                        fout<<endl;
                        /*fout<<"CPI ";
                        for(int i=1;i<9;i++)
                        {float s1=0;
                        float s2=0;
                        s1+=spi[i-1];
                        s2+=semcredits[i-1];
                        fout<<s1/s2<<" ";}*/
			}
int main()
        {
         fstream f1;
         fstream f2;
         fstream f3;
         f1.open("students.csv", ios::in);
         vector<student>sd;
	 vector<string> row;
         student a; 
	 string line, word;
	 while (!f1.eof())
              { 
		row.clear();
		getline(f1, line);
		stringstream s(line);
		while (getline(s, word, ','))
                     {
			row.push_back(word); 
		      }
		a.rollno =row[1];
                a.name = row[0];
                sd.push_back(a);
              }
	f2.open("grades.csv", ios::in);
	 while (!f2.eof())
              { 
		row.clear();
		getline(f2, line);
		stringstream s(line);
		while (getline(s, word, ','))
                     {
			row.push_back(word); 
		      }
		for(int i=0;i<sd.size();i++)
		    {
		     if(sd[i].rollno == row[0])
                       {
                        sd[i].courses.push_back(row[1]);
                        sd[i].grades.push_back(row[2]);
                        break;
                        }
		     }
              }
	vector<course>cs;
        course c;
	f3.open("courses.csv", ios::in);
	while (!f3.eof())
              { 
		row.clear();
		getline(f3, line);
		stringstream s(line);
		while (getline(s, word, ','))
                     {
			row.push_back(word); 
		      }
		c.sem = stoi(row[0]);
                string k;
                if(row[1][5])
                   {
                    k=row[1];
                    }
                else{k=row[1]+=" ";}
                c.number = k;
		c.name = row[2];
		c.credits = stoi(row[6]);
                cs.push_back(c);
	       }
        for(int i=0;i<sd.size();i++)
        gen(sd[i] , cs);
	return 0;
}

