#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include<vector>

using namespace std;

string getValue(string line, string key) {

    string target = "\"" + key + "\":\"";
    int start = line.find(target);

    if (start == string::npos)
        return "";

    start += target.length();

    int end = line.find("\"", start);

    if (end == string::npos)
        return "";

    return line.substr(start, end - start);
}

long long getTime(string line) {

    string target = "\"timestamp_ms\":";
    int start = line.find(target);

    if (start == string::npos)
        return -1;

    start += target.length();

    int end = line.find(",", start);

    if (end == string::npos)
        return -1;

    return stoll(line.substr(start, end - start));
}

string getApp(string line) {

    string target = "\"app_name\":\"";
    int start = line.find(target);

    if (start == string::npos)
        return "";

    start += target.length();

    int end = line.find("\"", start);

    if (end == string::npos)
        return "";

    return line.substr(start, end - start);
}

int main() {

    vector<string> paths = {
        R"(C:\Users\aditya\Downloads\events (2).jsonl)",
        R"(C:\Users\aditya\Downloads\events (4).jsonl)"
    };

    string line;

    long long previousTime = -1;

    string previousApp = "";
    string previousWindow = "";

    int totalEvents = 0;
    int candidates = 0;

    map<string, int> eventCount;

    for (string path : paths) {

        cout << "\nReading: " << path << endl;
        ifstream file(path);
        if (!file.is_open()) {
            cout << "File not found: " << path << endl;
            continue;
        }

        while (getline(file, line)) {

            if (line.empty())
                continue;

            totalEvents++;

            string eventType = getValue(line, "event_type");
            string app = getApp(line);
            string window = getValue(line, "window_title");
            string timestamp = getValue(line, "timestamp_iso");

            long long currentTime = getTime(line);

            eventCount[eventType]++;

            bool gap = false;
            bool appChange = false;
            bool windowChange = false;

            if (previousTime != -1) {

                long long difference = currentTime - previousTime;

                if (difference >= 5000)
                    gap = true;
            }

            if (!app.empty() && !previousApp.empty() && app != previousApp) {
                appChange = true;
            }

            if (!window.empty() &&
                !previousWindow.empty() &&
                window != previousWindow) {

                windowChange = true;
            }

            if (gap && (appChange || windowChange)) {

                candidates++;

                cout << "Boundary candidate at: "
                    << timestamp
                    << endl;

                cout << "Signals: ";

                if (gap)
                    cout << "TIME_GAP ";

                if (appChange)
                    cout << "APP_CHANGE ";

                if (windowChange)
                    cout << "WINDOW_CHANGE ";

                cout << "\n\n";
            }

            previousTime = currentTime;

            if (!app.empty())
                previousApp = app;

            if (!window.empty())
                previousWindow = window;

        }
        file.close();
    }

    cout << "\nTotal events: "
         << totalEvents
         << endl;

    cout << "Candidate boundaries: "
         << candidates
         << endl;

    cout << "\nEvent counts:\n";

    for (auto x : eventCount) {
        cout << x.first
             << " : "
             << x.second
             << endl;
    }

    return 0;
}