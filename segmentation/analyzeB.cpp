#include <bits/stdc++.h>
using namespace std;

struct S{
    string session;
    long long start,end;
    int events;
};

int main(){

    ifstream f("dataset_b_segments.csv");
    string line;
    getline(f,line);

    vector<S> a;

    while(getline(f,line)){

        stringstream ss(line);
        string session,id,s,e,d,c;

        getline(ss,session,',');
        getline(ss,id,',');
        getline(ss,s,',');
        getline(ss,e,',');
        getline(ss,d,',');
        getline(ss,c,',');

        a.push_back({
            session,
            stoll(s),
            stoll(e),
            stoi(c)
        });
    }

    map<string,vector<long long>> times;

    long long totalTime=0;

    for(auto x:a){

        long long d=x.end-x.start;

        totalTime+=d;
        times[x.session].push_back(d);
    }

    cout<<"\n============================\n";
    cout<<"DATASET B ANALYSIS\n";
    cout<<"============================\n";

    cout<<"Total segments : "<<a.size()<<"\n";

    cout<<"Total time     : "
        <<totalTime/1000<<" sec\n";

    double avg =
        a.empty()?0:
        (double)totalTime/a.size();

    cout<<"Average time   : "
        <<avg/1000<<" sec\n";

    cout<<"\nSESSION-WISE\n";

    for(auto x:times){

        long long sum=0;

        for(long long d:x.second)
            sum+=d;

        cout<<x.first
            <<" -> segments="<<x.second.size()
            <<", avg="<<(sum/x.second.size())/1000
            <<" sec\n";
    }

    cout<<"============================\n";

    return 0;
}