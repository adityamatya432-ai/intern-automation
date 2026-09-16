#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

string getValue(string text, string key) {
    string target = "\"" + key + "\":\"";
    int start = text.find(target);

    if (start == string::npos)
        return "";

    start += target.length();

    int end = text.find("\"", start);

    if (end == string::npos)
        return "";

    return text.substr(start, end - start);
}

string getGTValue(string line, string key) {
    string target = "\"" + key + "\": \"";
    int start = line.find(target);

    if (start == string::npos)
        return "";

    start += target.length();

    int end = line.find("\"", start);

    if (end == string::npos)
        return "";

    return line.substr(start, end - start);
}

long long getTime(string time) {

    if (time.empty())
        return -1;

    int h = stoi(time.substr(11, 2));
    int m = stoi(time.substr(14, 2));
    int s = stoi(time.substr(17, 2));

    int ms = 0;

    size_t dot = time.find(".", 19);

    if (dot != string::npos) {

        string x = time.substr(dot + 1, 3);

        while (x.length() < 3)
            x += "0";

        ms = stoi(x);
    }

    return h * 3600000LL
         + m * 60000LL
         + s * 1000LL
         + ms;
}

long long eventTime(string line) {
    return getTime(getValue(line, "timestamp_iso"));
}

long long gtTime(string line) {
    return getTime(getGTValue(line, "ts_utc"));
}

struct Event {
    long long time;
    string type;

    string newApp;
    string newProcess;

    string oldApp;
    string oldProcess;
};

int countMatches(vector<long long>& candidates,
                 vector<long long>& gt) {

    vector<bool> used(candidates.size(), false);

    int matched = 0;

    for (int g = 0; g < gt.size(); g++) {

        int best = -1;
        long long bestDiff = 10000;

        for (int i = 0; i < candidates.size(); i++) {

            if (used[i])
                continue;

            long long diff =
                llabs(candidates[i] - gt[g]);

            if (diff < bestDiff) {
                bestDiff = diff;
                best = i;
            }
        }

        if (best != -1) {
            used[best] = true;
            matched++;
        }
    }

    return matched;
}

int main() {

    ifstream manifest("dataset_manifest.txt");

    if (!manifest.is_open()) {
        cout << "Could not open dataset_manifest.txt\n";
        return 1;
    }

    string line;

    int totalSessions = 0;
    int totalEvents = 0;
    int totalCandidates = 0;
    int totalMatches = 0;

    while (getline(manifest, line)) {

        if (line.empty())
            continue;

        totalSessions++;

        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);

        string gtPath =
            line.substr(
                p1 + 1,
                p2 - p1 - 1
            );

        string eventPaths =
            line.substr(p2 + 1);

        vector<long long> gtTimes;

        ifstream gtFile(gtPath);

        while (getline(gtFile, line)) {

            if (getGTValue(line, "event")
                == "process_switched_out") {

                long long t = gtTime(line);

                if (t != -1)
                    gtTimes.push_back(t);
            }
        }

        gtFile.close();

        vector<Event> events;

        int start = 0;

        while (start < eventPaths.length()) {

            int end =
                eventPaths.find(";", start);

            if (end == string::npos)
                end = eventPaths.length();

            string path =
                eventPaths.substr(
                    start,
                    end - start
                );

            ifstream file(path);

            while (getline(file, line)) {

                long long t = eventTime(line);

                if (t == -1)
                    continue;

                Event e;

                e.time = t;
                e.type =
                    getValue(line, "event_type");

                int payloadPos =
                    line.find("\"payload\":{");

                if (payloadPos != string::npos) {

                    int newPos =
                        line.find(
                            "\"new_app\":{",
                            payloadPos
                        );

                    int oldPos =
                        line.find(
                            "\"previous_app\":{",
                            payloadPos
                        );

                    if (newPos != string::npos &&
                        oldPos != string::npos) {

                        string newPart =
                            line.substr(
                                newPos,
                                oldPos - newPos
                            );

                        string oldPart =
                            line.substr(oldPos);

                        e.newApp =
                            getValue(
                                newPart,
                                "app_name"
                            );

                        e.newProcess =
                            getValue(
                                newPart,
                                "process_name"
                            );

                        e.oldApp =
                            getValue(
                                oldPart,
                                "app_name"
                            );

                        e.oldProcess =
                            getValue(
                                oldPart,
                                "process_name"
                            );
                    }
                }

                events.push_back(e);
                totalEvents++;
            }

            file.close();

            start = end + 1;
        }

        vector<long long> candidates;

        for (int i = 1; i < events.size(); i++) {

            if (events[i].type != "app_switch")
                continue;

            bool changed = false;

            if (!events[i].newProcess.empty() &&
                !events[i].oldProcess.empty() &&
                events[i].newProcess !=
                events[i].oldProcess) {

                changed = true;
            }

            else if (!events[i].newApp.empty() &&
                     !events[i].oldApp.empty() &&
                     events[i].newApp !=
                     events[i].oldApp) {

                changed = true;
            }

            if (!changed)
                continue;

            long long gap =
                events[i].time -
                events[i - 1].time;

            if (gap >= 5000)
                candidates.push_back(
                    events[i].time
                );
        }

        int matches =
            countMatches(
                candidates,
                gtTimes
            );

        totalCandidates +=
            candidates.size();

        totalMatches += matches;
    }

    manifest.close();

    cout << "\n====================================\n";
    cout << "PROCESS CHANGE + 5 SEC GAP TEST\n";
    cout << "====================================\n";

    cout << "Sessions: "
         << totalSessions << endl;

    cout << "Events: "
         << totalEvents << endl;

    cout << "Candidates: "
         << totalCandidates << endl;

    cout << "GT matched: "
         << totalMatches << endl;

    cout << "False positives: "
         << totalCandidates - totalMatches
         << endl;

    return 0;
}