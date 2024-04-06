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
        print(weights);
        print(biases);
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

int main(){
    vector<vd> nest={{1.0,3.0},{2.0,4.0}};
    vd wts={5.0,5.0};
    vd biases={-35.5,-50.5};
    double netbias=2.0;
    int numof_neurons=nest.size(),numof_inputs=nest[0].size();
    Network net(nest,wts,biases,numof_inputs,numof_neurons,netbias);
    net.forwardpropagation();
    cout<<"Prediction is: "<<net.prediction;
    return 0;
}