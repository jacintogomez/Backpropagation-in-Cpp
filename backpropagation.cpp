//
// Created by Jacinto Gomez on 3/26/24.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<float> vf;

class Grade{
public:
    Grade(float v,float w,float b):val(v),weight(w),bias(b){}
    float val;
    float weight;
    float bias;
};

class Student{
public:
    Student(string id,vf h,vf x,float f):netid(id),hws(h),exams(x),fin(f){}
    string netid;
    vf hws;
    vf exams;
    float fin;
};

int main(){
    ifstream infile;
    string filename="info.txt";
    cout<<"file name is "<<filename<<endl;
    infile.open(filename);
    while(!infile){
        cout<<"Failed to open"<<endl<<"Re-enter file name: ";
        cin>>filename;
        infile.clear();
        infile.open(filename);
    }
    float x,y,z,i=1;
    //float z;
    string j;
    while(infile>>x){
        infile.ignore(999,'\t');
        infile>>y;
        infile.ignore(999,'\t');
        infile>>z;
        cout<<i++<<". -> "<<x<<" "<<y<<" "<<z<<" "<<endl;
    }
    infile.close();
    return 0;
}