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

bool nestdimensionalerror(vector<vd> nest,int ni){
    for(vd n:nest){
        if(n.size()!=ni){return true;}
    }
    return false;
}

int main(){
    vector<vd> nest={{-5.3868,-24.9274,-19.9819,-25.8103,-19.2335,-22.3166,-21.9545,-19.5335,-19.6888,-18.8335,-21.1011,-15.9814},{-2.71893,-10.1903,-8.19222,-10.499,-8.05626,-9.45514,-9.24615,-8.35626,-8.12873,-7.65626,-9.04076,-6.41186},{8.80433,0.3,0.2,0.4,-0.1,327.257,228.617,166.673,297.925,0.3,1.36758,-50.0398},{4.75236,0.409121,0.296434,0.503972,0.00293241,74.6466,196.504,257.73,267.703,267.899,1.29606,-49.22},{3.88102,0.30528,0.204664,0.405028,-0.0950249,302.561,-0.196194,-0.401175,0.104145,0.30394,1.28586,-49.6332},{11.5636,14.8018,16.86,14.9927,15.0138,13.5978,13.6978,-0.4,14.8664,17.6722,8.47585,1.78978},{-1.73865,-5.27713,-4.26161,-5.39439,-4.32985,-5.16723,-5.00929,-4.63008,-4.27472,-3.92981,-4.9553,-3.22161}};
    vd wts={4.36882,4.79879,-3.1651,14.1583,19.6101,21.4348,4.20477};
    vd biases={-15.2819,-15.1299,-6.80918,-7.45537,-7.17583,-14.843,-15.0771};
    vd hws={73.75,99.5,97.75,69.5,97.5,96.5,93.5,84.75,81.5,90,88,81};
    double netbias=-0.966243;
    int numof_neurons=7,numof_inputs=12;
    Network net(nest,wts,biases,numof_inputs,numof_neurons,netbias);
    if(numof_inputs!=hws.size()||numof_neurons!=nest.size()||numof_neurons!=wts.size()||numof_neurons!=biases.size()||nestdimensionalerror(nest,numof_inputs)){
        cout<<numof_inputs<<" vs "<<hws.size()<<endl;
        cout<<numof_neurons<<" vs "<<nest.size()<<endl;
        cout<<numof_neurons<<" vs "<<wts.size()<<endl;
        cout<<numof_inputs<<" vs "<<biases.size()<<endl;
        cout<<"Dimensional mismatch";
        exit(1);
    }
    net.input=hws;
    //will predict the equivalent of net.actual
    net.forwardpropagation();
    cout<<"Prediction is: "<<net.prediction<<"%"<<endl;
    return 0;
}