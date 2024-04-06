//
// Created by Jacinto Gomez on 3/26/24.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<double> vd;

void print(vd j){
    cout<<"{";
    for(int k=0;k<j.size()-1;k++){
        cout<<j[k]<<",";
    }
    cout<<j[j.size()-1]<<"}"<<endl;
}

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
    Neuron(vd wts,double nw,double bi,int i):weights(wts),neuron_weight(nw),bias(bi),inputs(i){}
    int inputs;
    double bias,z=0,result;
    double neuron_weight;
    vd weights;
    void activate(vd input){
        z=0;
        for(int x=0;x<input.size();x++){
            z+=weights[x]*input[x];;
        }
        z+=bias;
        cout<<"pre-sigmoid is "<<z<<endl;
        result=sigmoid(z);
        cout<<"result is "<<result<<endl;
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
    Network(vector<vd> wts,vd nw,vd bi,int i,int n,double nb):inputs(i),num_neurons(n),network_bias(nb){
        for(int x=0;x<num_neurons;x++){
            Neuron nk(wts[x],nw[x],bi[x],i);
            neurons.push_back(nk);
        }
    }
    int inputs;
    int num_neurons;
    double network_bias;
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
        cout<<"prediction is "<<prediction<<endl;
    }
    void backpropagation(){
        //int cost=pow((prediction-actual),2); //cost function
        double dcost_dpred=2*(prediction-actual); //also dcost_dnetbias, and dcost_dnetweight
        cout<<"dcostpred is "<<dcost_dpred<<endl;
        cout<<"prediction is "<<prediction<<endl;
        cout<<"prediction is "<<prediction<<endl;
        network_bias-=eta*dcost_dpred; //update final bias
        for(Neuron &n:neurons){
            n.neuron_weight-=eta*dcost_dpred*n.result;
            double z=n.z;
            double dpred_dg=sigmoid(z)*(1-sigmoid(z));
            double dcost_intermediate=dcost_dpred*n.neuron_weight*dpred_dg;
            n.bias-=eta*dcost_intermediate;
            for(int x=0;x<inputs;x++){
                n.weights[x]-=eta*dcost_intermediate*input[x];
            }
        }
    }
    void display_parameters(){
        vd weights;
        vd biases;
        int cw=1,cb=1;
        for(Neuron n:neurons){
            for(double w:n.weights){
                cout<<"w"<<cw<<" = "<<w<<endl;
                weights.push_back(w);
                cw++;
            }
            cout<<"b"<<cb<<" = "<<n.bias<<endl;
            cb++;
        }
        for(Neuron n:neurons){
            cout<<"w"<<cw<<" = "<<n.neuron_weight<<endl;
            weights.push_back(n.neuron_weight);
            biases.push_back(n.bias);
            cw++;
        }
        biases.push_back(network_bias);
        cout<<"b"<<cb<<" = "<<network_bias<<endl;
        cout<<"Copy and paste these as the vector initializations in forwardpropagation.cpp:"<<endl;
        cout<<"Weights: ";
        print(weights);
        cout<<"Biases: ";
        print(biases);
    }
};

class Student{
public:
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
//    double h1,h2,h3,f;
    double h1,h2,f;
    vector<Student> studentdata;
    while(infile>>h1){
        //vd params={h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,e1,e2};
        infile.ignore(999,' ');
        infile>>h2;
//        infile.ignore(999,' ');
//        infile>>h3;
        infile.ignore(999,' ');
        infile>>f;
        vd params={h1,h2};
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
    vector<vd> nest={{1.0,3.0},{2.0,4.0}};
    vd wts={5.0,5.0};
    vd biases={-35.5,-50.5};
    double netbias=2.0;
    vector<Student> data=read_in_data();
    int numof_neurons=2,numof_inputs=2,epochs=1;
    Network net(nest,wts,biases,numof_inputs,numof_neurons,netbias);
    for(int x=0;x<epochs;x++){
        for(Student s:data){
            net.input=s.work;
            net.actual=s.fin;
            net.forwardpropagation();
            net.backpropagation();
        }
    }
    net.display_parameters();
    return 0;
}