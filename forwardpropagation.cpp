//
// Created by Jacinto Gomez on 3/26/24.
//

#include <iostream>
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
    vd input;
    vector<Neuron> neurons;
    void forwardpropagation(){
        prediction=0;
        for(Neuron &n:neurons){
            n.activate(input);
            prediction+=n.result*n.neuron_weight;
        }
        prediction+=network_bias;
    }
};

class Student{
public:
    Student(vd w,double f):work(w),fin(f){}
    string netid;
    vd work;
    double fin;
};

int main(){
    vector<vd> nest={{9.98448,20.969},{10.9845,21.969}};
    vd wts={5.52272,5.52272};
    vd biases={-33.7031,-48.7031};
    vd hws={5,10};
    double netbias=3.38449;
    int numof_neurons=nest.size(),numof_inputs=nest[0].size();
    Network net(nest,wts,biases,numof_inputs,numof_neurons,netbias);
    net.input=hws;
    net.forwardpropagation();
    cout<<"Prediction is: "<<net.prediction;
    return 0;
}