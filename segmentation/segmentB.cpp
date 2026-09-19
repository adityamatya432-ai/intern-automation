#include <bits/stdc++.h>
using namespace std;

struct E{
    long long t;
    string type,na,oa,np,op;
};

string get(string s,string k){
    string x="\""+k+"\":\"";
    size_t p=s.find(x);
    if(p==string::npos) return "";
    p+=x.size();
    size_t q=s.find("\"",p);
    return q==string::npos?"":s.substr(p,q-p);
}

long long timeMs(string s){
    if(s.size()<19) return -1;
    int h=stoi(s.substr(11,2));
    int m=stoi(s.substr(14,2));
    int z=stoi(s.substr(17,2));
    int ms=0;
    size_t p=s.find(".",19);
    if(p!=string::npos){
        string x=s.substr(p+1,3);
        while(x.size()<3)x+="0";
        ms=stoi(x);
    }
    return h*3600000LL+m*60000LL+z*1000LL+ms;
}

bool changed(E &e){
    return (!e.np.empty()&&!e.op.empty()&&e.np!=e.op) ||
           (!e.na.empty()&&!e.oa.empty()&&e.na!=e.oa);
}

void readEvents(string paths,vector<E>& a){

    size_t st=0;

    while(st<paths.size()){

        size_t en=paths.find(";",st);
        if(en==string::npos) en=paths.size();

        ifstream f(paths.substr(st,en-st));
        string line;

        while(getline(f,line)){

            E e;
            e.t=timeMs(get(line,"timestamp_iso"));
            e.type=get(line,"event_type");

            size_t p=line.find("\"payload\":{");

            if(p!=string::npos){

                size_t x=line.find("\"new_app\":{",p);
                size_t y=line.find("\"previous_app\":{",p);

                if(x!=string::npos&&y!=string::npos){

                    string a1=line.substr(x,y-x);
                    string a2=line.substr(y);

                    e.na=get(a1,"app_name");
                    e.np=get(a1,"process_name");
                    e.oa=get(a2,"app_name");
                    e.op=get(a2,"process_name");
                }
            }

            if(e.t!=-1) a.push_back(e);
        }

        st=en+1;
    }

    sort(a.begin(),a.end(),
         [](E&a,E&b){return a.t<b.t;});
}

int main(){

    ifstream mf("dataset_b_manifest.txt");

    if(!mf){
        cout<<"Cannot open dataset_b_manifest.txt\n";
        return 1;
    }

    ofstream out("dataset_b_segments.csv");

    out<<"session,segment_id,start_ms,end_ms,duration_ms,event_count\n";

    string line;
    int total=0,segments=0;

    while(getline(mf,line)){

        if(line.empty()) continue;

        size_t p=line.find("|");

        string session=line.substr(0,p);
        string paths=line.substr(p+1);

        vector<E> e;
        readEvents(paths,e);

        if(e.empty()) continue;

        total+=e.size();

        vector<long long> cut;
        long long last=-1;

        for(int i=1;i<e.size();i++){

            long long gap=e[i].t-e[i-1].t;

            if(e[i].type=="app_switch" &&
               changed(e[i]) &&
               gap>=2500 &&
               (last==-1 || e[i].t-last>=15000)){

                cut.push_back(e[i].t);
                last=e[i].t;
            }
        }

        int st=0,id=1;

        for(long long b:cut){

            int en=-1;

            for(int i=st;i<e.size();i++){

                if(e[i].t>=b){
                    en=i-1;
                    break;
                }
            }
            if(en<st) continue;

            if(e[en].t > e[st].t){

                out<<session<<","<<id++<<","
                <<e[st].t<<","
                <<e[en].t<<","
                <<e[en].t-e[st].t<<","
                <<en-st+1<<"\n";

                segments++;
            }

            for(int i=st;i<e.size();i++){

                if(e[i].t>=b){
                    st=i;
                    break;
                }
            }
        }

        if(st<e.size() && e.back().t > e[st].t){

            out<<session<<","<<id<<","
            <<e[st].t<<","
            <<e.back().t<<","
            <<e.back().t-e[st].t<<","
            <<e.size()-st<<"\n";

            segments++;
        }
    }

    cout<<"Dataset B events: "<<total<<"\n";
    cout<<"Dataset B segments: "<<segments<<"\n";
    cout<<"Output: dataset_b_segments.csv\n";

    return 0;
}