//
// Created by Jacinto Gomez on 3/26/24.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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
    void display(){
        int c=1;
        for(double w:work){
            cout<<"HW"<<c<<": "<<w<<endl;
            c++;
        }
        cout<<"Final: "<<fin<<endl<<endl;
    }
};

void print2(vector<Student> j){
    for(Student s:j){
        s.display();
    }
}

vector<Student> read_in_data(){
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
    double h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,e1,e2,f;
    //double h1,h2,h3,f;
    //double h1,h2,f;
    vector<Student> studentdata;
    int c=0;
    while((infile>>h1)&&c<5){
        c++;
        vd params={h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,e1,e2};
        infile.ignore(999,'\t');
        infile>>h2;
        infile.ignore(999,'\t');
        infile>>h3;
        infile.ignore(999,'\t');
        infile>>h4;
        infile.ignore(999,'\t');
        infile>>h5;
        infile.ignore(999,'\t');
        infile>>h6;
        infile.ignore(999,'\t');
        infile>>h7;
        infile.ignore(999,'\t');
        infile>>h8;
        infile.ignore(999,'\t');
        infile>>h9;
        infile.ignore(999,'\t');
        infile>>h10;
        infile.ignore(999,'\t');
        infile>>e1;
        infile.ignore(999,'\t');
        infile>>e2;
        infile.ignore(999,'\t');
        infile>>f;
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
    //weights of each input
    vector<vd> nest={{0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4},
                     {0.1,0.3,0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1,0.3,0.2,0.4}
    };
    //weights of neuron output
    vd wts={0.2,0.4,-0.1,-0.3,-0.2,-0.4,0.1};
    //biases added at each neuron
    vd biases={-15,-15,-10,-10,-10,-15,-15};
    //bias added to final sum of all neurons
    double netbias=-5;
    vector<Student> data=read_in_data();
    cout<<"size is: "<<data.size()<<endl;
    print2(data);
    // int numof_neurons=7,numof_inputs=12,epochs=100;
    // Network net(nest,wts,biases,numof_inputs,numof_neurons,netbias);
    // if(numof_neurons!=nest.size()||numof_neurons!=wts.size()||numof_inputs!=biases.size()||numof_inputs!=nest[0].size()){
    //     cout<<"Dimensional mismatch";
    //     exit(1);
    // }
    // for(int x=0;x<epochs;x++){
    //     for(Student s:data){
    //         net.input=s.work;
    //         net.actual=s.fin;
    //         net.forwardpropagation();
    //         net.backpropagation();
    //     }
    // }
    // net.display_parameters();
    return 0;
}