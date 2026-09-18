#include <bits/stdc++.h>
using namespace std;

struct Event{
    long long t;
    string type,na,oa,np,op;
};

string get(string s,string k){
    string x="\""+k+"\":\"";
    size_t p=s.find(x);
    if(p==string::npos) return "";
    p+=x.size();
    size_t q=s.find("\"",p);
    return q==string::npos ? "" : s.substr(p,q-p);
}

long long timeMs(string s){
    if(s.size()<19) return -1;

    int h=stoi(s.substr(11,2));
    int m=stoi(s.substr(14,2));
    int sec=stoi(s.substr(17,2));
    int ms=0;

    size_t p=s.find(".",19);
    if(p!=string::npos){
        string x=s.substr(p+1,3);
        while(x.size()<3) x+="0";
        ms=stoi(x);
    }

    return h*3600000LL+m*60000LL+sec*1000LL+ms;
}

bool changed(Event &e){
    return (!e.np.empty() && !e.op.empty() && e.np!=e.op) ||
           (!e.na.empty() && !e.oa.empty() && e.na!=e.oa);
}

void readEvents(string paths,vector<Event>& a,int &total){
    size_t st=0;

    while(st<paths.size()){
        size_t en=paths.find(";",st);
        if(en==string::npos) en=paths.size();

        ifstream f(paths.substr(st,en-st));
        string line;

        while(getline(f,line)){
            Event e;
            e.t=timeMs(get(line,"timestamp_iso"));
            e.type=get(line,"event_type");

            size_t p=line.find("\"payload\":{");
            if(p!=string::npos){
                size_t x=line.find("\"new_app\":{",p);
                size_t y=line.find("\"previous_app\":{",p);

                if(x!=string::npos && y!=string::npos){
                    e.na=get(line.substr(x,y-x),"app_name");
                    e.np=get(line.substr(x,y-x),"process_name");
                    e.oa=get(line.substr(y),"app_name");
                    e.op=get(line.substr(y),"process_name");
                }
            }

            if(e.t!=-1){
                a.push_back(e);
                total++;
            }
        }

        st=en+1;
    }

    sort(a.begin(),a.end(),
        [](Event &a,Event &b){return a.t<b.t;});
}

int main(){

    ifstream mf("dataset_manifest.txt");
    ofstream out("segmentation_results.csv");

    if(!mf || !out){
        cout<<"File open error\n";
        return 1;
    }

    out<<"session,segment_id,start_ms,end_ms,duration_ms,event_count\n";

    string line;
    int sessions=0,total=0,segments=0;

    while(getline(mf,line)){

        if(line.empty()) continue;

        size_t p1=line.find("|");
        size_t p2=line.find("|",p1+1);

        string session=line.substr(0,p1);
        string paths=line.substr(p2+1);

        sessions++;

        vector<Event> e;
        readEvents(paths,e,total);

        if(e.empty()) continue;

        vector<long long> cut;
        long long last=-1;

        for(int i=1;i<(int)e.size();i++){

            long long gap=e[i].t-e[i-1].t;

            if(e[i].type!="app_switch" ||
               !changed(e[i]) ||
               gap<2500)
                continue;

            if(last==-1 || e[i].t-last>=15000){
                cut.push_back(e[i].t);
                last=e[i].t;
            }
        }

        int st=0,id=1;

        for(long long b:cut){

            int en=-1;

            for(int i=st;i<(int)e.size();i++){
                if(e[i].t>=b){
                    en=i-1;
                    break;
                }
            }

            if(en<st) continue;

            out<<session<<","
               <<id++<<","
               <<e[st].t<<","
               <<e[en].t<<","
               <<e[en].t-e[st].t<<","
               <<en-st+1<<"\n";

            segments++;

            for(int i=st;i<(int)e.size();i++){
                if(e[i].t>=b){
                    st=i;
                    break;
                }
            }
        }

        if(st<(int)e.size()){

            out<<session<<","
               <<id<<","
               <<e[st].t<<","
               <<e.back().t<<","
               <<e.back().t-e[st].t<<","
               <<e.size()-st<<"\n";

            segments++;
        }
    }

    cout<<"Sessions: "<<sessions<<"\n";
    cout<<"Events: "<<total<<"\n";
    cout<<"Segments: "<<segments<<"\n";

    return 0;
}