//
// Created by Jacinto Gomez on 3/26/24.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<double> vd;

double relu(double z){
    if(z<0){return 0;}
    else{return z;}
}

double sigmoid(double z){
    double num=1.0,e=2.718;
    return num/(num+pow(e,-1*z));
}

class Neuron{
public:
    Neuron(int i):inputs(i){}
    Neuron(vd wts,double nw,double bi):weights(wts),neuron_weight(nw),bias(bi){
        cout<<"made neuron with weights: "<<wts[0]<<endl;
    }
    int inputs;
    double bias,z=0,result;
    double neuron_weight;
    vd weights;
    void activate(vd input){
        z=0;
        for(int x=0;x<input.size();x++){
            z+=weights[x]*input[x];
        }
        z+=bias;
        result=sigmoid(z);
    }
};

class Network{
public:
    Network(int i,int n):inputs(i),num_neurons(n){
        for(int x=0;x<num_neurons;x++){
            Neuron nk(inputs);
            neurons.push_back(nk);
        }
    }
    Network(vector<vd> wts,vd nw,vd bi,int i,int n):inputs(i),num_neurons(n){
        for(int x=0;x<num_neurons;x++){
            Neuron nk(wts[x],nw[x],bi[x]);
            neurons.push_back(nk);
        }
    }
    int inputs;
    int num_neurons;
    double network_bias=0.1;
    double prediction=0;
    double eta=0.01; //learning rate
    vd input;
    double actual;
    vector<Neuron> neurons;
    void forwardpropagation(){
        prediction=0;
        for(Neuron &n:neurons){
            n.activate(input);
            prediction+=n.result*n.neuron_weight;
        }
        prediction+=network_bias;
    }
    void backpropagation(){
        //int cost=pow((prediction-actual),2);
        double dcost_dpred=2*(prediction-actual); //also dcost_dnetbias, and dcost_dnetweight
        network_bias-=eta*dcost_dpred; //update final bias
        for(Neuron &n:neurons){
            n.result-=eta*dcost_dpred;
            n.neuron_weight-=eta*dcost_dpred;
            double z=n.z;
            double dpred_dg=sigmoid(z)*(1-sigmoid(z));
            double dcost_intermediate=dcost_dpred*n.neuron_weight*dpred_dg;
            n.bias-=eta*dcost_intermediate;
            for(int x=0;x<inputs;x++){
                n.weights[x]-=eta*dcost_intermediate*input[x];
                cout<<"w: "<<n.weights[x]<<endl;
            }
            cout<<"W: "<<n.neuron_weight<<endl;
            cout<<"b: "<<n.bias<<endl;
        }
        cout<<"B: "<<network_bias<<endl;
    }
};

class Student{
public:
//    Student(vd h,vd x,double f):hws(h),exams(x),fin(f){}
//    Student(string id,vd h,vd x,double f):netid(id),hws(h),exams(x),fin(f){}
    Student(vd w,double f):work(w),fin(f){}
    string netid;
    vd work;
    double fin;
};

vector<Student> read_in_data(){
    ifstream infile;
    string filename="test.txt";
    cout<<"file name is "<<filename<<endl;
    infile.open(filename);
    while(!infile){
        cout<<"Failed to open"<<endl<<"Re-enter file name: ";
        cin>>filename;
        infile.clear();
        infile.open(filename);
    }
    //double h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,e1,e2,f;
    double h1,h2,h3,f;
    vector<Student> studentdata;
    while(infile>>h1){
        //vd params={h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,e1,e2};
        infile.ignore(999,' ');
        infile>>h2;
        infile.ignore(999,' ');
        infile>>h3;
        infile.ignore(999,' ');
        infile>>f;
        vd params={h1,h2,h3};
        Student s(params,f);
        studentdata.push_back(s);
    }
    for(Student x:studentdata){
        for(double y:x.work){
            cout<<y<<" ";
        }
        cout<<x.fin<<endl;
    }
    infile.close();
    return studentdata;
}

int main(){
    vector<vd> nest={{0.1,0.15,0.1},{0.05,0.1,0.1}};
    vd wts={12,9};
    vd biases={0.1,0.1};
    vector<Student> data=read_in_data();
    int numof_neurons=2,numof_inputs=3,epochs=1;
    Network net(nest,wts,biases,numof_inputs,numof_neurons);
    for(int x=0;x<epochs;x++){
        net.input=data[x].work;
        net.actual=data[x].fin;
        net.forwardpropagation();
        net.backpropagation();
    }
    return 0;
}