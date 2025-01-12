#define SPEED 40
#include <iostream>
#include <cstring>
#include <ctime>
#include <queue>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

enum class CabSize:int {
    Small = 4,
    Large = 7
};

string changeUppercase(const string &str) {
    string str1=str;
    for (char &c : str1) {
        c = toupper(c);
    }
    return str1;
}

bool ifpairExists(pair<string, int> p, list<pair<string, int>>& l) {
    for (const auto& item : l) {
        if (item == p) {
            return true;
        }
    }
    return false;
}

class Graph {
private:
    int V;
    unordered_map<string, unordered_map<string, float>> adj;

public:
    Graph(int V) : V(V) {}

    void addEdge(string u, string v, float weight) {
        adj[u][v] = weight;
        adj[v][u] = weight;
    }

vector<pair<string, float>> dijkstra(string src, string dest) {
    
    unordered_map<string, float> dist;
    unordered_map<string, string> prev;
    //To 'explore' nodes in order of distance from source
    priority_queue<pair<float, string>, vector<pair<float, string>>, greater<pair<float, string>>> pq;

    for (auto it = adj.begin(); it != adj.end(); ++it) {
        const auto& u = *it;
        dist[u.first] = 9999999999;
    }

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        //Pop node with minimum distance from pq
        float u_dist = pq.top().first;
        string u = pq.top().second;
        pq.pop();

        if (u == dest) {
            break;
        }
    //Explore neighbours of current node
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        string v = it->first;
        float v_dist = it->second;
        float alt = u_dist + v_dist; //alt is tentative distance to neighbour
        if (alt < dist[v]) {
            //Update distance from previous node for neighbour
            dist[v] = alt;
            prev[v] = u;
            pq.push(make_pair(alt, v));
        }
    }
    }
    //Reconstruct path
    vector<pair<string, float>> path;
    string u = dest;
    while (prev.count(u)) {
        path.emplace_back(u, dist[u]);
        u = prev[u];
    }
    path.emplace_back(src, 0);
    reverse(path.begin(), path.end());

    return path;
}

vector<vector<pair<string, float>>> yenKSP(string src, string dest, int K) {
        //List of kth shortest paths
        vector<vector<pair<string, float>>> paths;
        //First shortest path
        vector<pair<string, float>> shortestPath = dijkstra(src, dest);

        paths.push_back(shortestPath);

        //Find (K-1) more paths
        for (int k = 1; k < K; k++) {
            vector<vector<pair<string, float>>> candidates;

            for (int i = 0; i < paths[k - 1].size() - 1; i++) {
                string u = paths[k - 1][i].first;
                string v = paths[k - 1][i + 1].first;

                //Copy current graph
                Graph g = *this;
                //Remove edge from previous path
                g.removeEdge(u, v);

                //Calculate new path after removing edge
                vector<pair<string, float>> path = g.dijkstra(src, dest);
                
                if (!path.empty()) {
                    path.insert(path.begin(), paths[k - 1].begin(), paths[k - 1].begin() + i + 1); //combine paths
                    candidates.push_back(path);
                }
            }

            if (candidates.empty()) {
                break;
            }

            //Sort candidates by distance
            for (int i = 0; i < candidates.size() - 1; i++) {
                for (int j = 0; j < candidates.size() - i - 1; j++) {
                    float aDist = 0.0, bDist = 0.0;
                    for (const auto& p : candidates[j]) {
                        aDist += p.second;
                    }
                    for (const auto& p : candidates[j + 1]) {
                        bDist += p.second;
                    }
                    if (aDist > bDist) {
                        swap(candidates[j], candidates[j + 1]);
                    }
                }
            }

            //Add new path if unique
            bool foundNewPath = true;
            for (const auto& path : paths) {
                if (path == candidates[0]) {
                    foundNewPath = false;
                    break;
                }
            }

            if (foundNewPath) {
                paths.push_back(candidates[0]);
            }
        }

        return paths;
    }

private:
    void removeEdge(string u, string v) {
        adj[u].erase(v); //remove u-v
        adj[v].erase(u); //remove v-u
    }
};



// CLASS TIME 
class Time{
        public:
            int hour;
            int minute;
            int second;
            Time();
            Time(int h, int m, int s);
            Time(const Time& T);
            ~Time();
            void displayTime() const;
            Time currDifference()const;
            Time operator+(const Time T2) const;
            Time operator-(const Time T2) const;
            Time addTime(int h,int m,int s);
            Time subtractTime(int h, int m, int s);
            bool operator<(const Time& other) const;
            bool isValidTime() const;
};

// Default Constructor
Time::Time(){
     hour=0;
     minute=0;
     second=0;
}

// Parameterised Constructor
Time :: Time(int h, int m, int s){
        if ((h>=0 && h<=23) && (m>=0 && m <=59) && (s>=0&&s<=59)){
                    hour=h;
                    minute=m;
                    second=s;
        }
        else {
                cout << "Invalid time arguments." << endl;
        }
}

// Copy Constructor
Time:: Time(const Time &T){
        hour=T.hour;
        minute=T.minute;
        second=T.second;
}

// Destructor
Time:: ~Time(){
}

// Function to display time format
void Time::displayTime() const{
        int arr[3]={hour,minute,second};
        for(int i=0;i<3;++i){
                if( i==0){
                        if (arr[i]==24){
                                cout << "00" << ":";
                        }
                }
                if (arr[i]<10){
                        if( i==2){
                                cout << "0" << arr[i];
                        }
                        else{
                             cout << "0" << arr[i] << ":";
                        }
                }
                else {
                        if( i==2){
                                cout << arr[i];
                        }
                        else{
                            cout << arr[i] << ":";
                        }
                }
        }
}
//Function to calculate the time difference with the current time
Time Time::currDifference() const {
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    int currentTotalSeconds = localTime->tm_hour * 3600 + localTime->tm_min * 60 + localTime->tm_sec;

    int storedTotalSeconds = hour * 3600 + minute * 60 + second;

    int differenceSeconds =  storedTotalSeconds-currentTotalSeconds;

    Time diff;
    diff.hour = differenceSeconds / 3600;
    differenceSeconds %= 3600;
    diff.minute = differenceSeconds / 60;
    diff.second = differenceSeconds % 60;

    return diff;
}

// Operator '+' Overloading
Time Time::operator+(const Time T2) const{
           Time sum;
           int s,m,h;
           s=T2.second+this->second;
           if (s<60){
                   sum.second=s;
           }
           else{
                   int n=s-60;
                   sum.minute+=(n/60);
                   sum.second=59;
           }
           m=T2.minute+this->minute;
           if (m<60){
                   sum.minute=m;
           }
           else{
                   int q=m-60;
                   sum.hour+=(q/60);
                   sum.minute=59;
           }
           h=T2.hour+this->hour;
           if(h>24){
                   int t=h-24;
                   h=t;
           }
           sum.hour=h;
           return sum;
}

//Overator '-' overloading 
Time Time::operator-(const Time T2) const{
        int totalSeconds1 = hour * 3600 + minute * 60 + second;
        int totalSeconds2 = T2.hour * 3600 + T2.minute * 60 + T2.second;
        int differenceSeconds = totalSeconds1 - totalSeconds2;

        if (differenceSeconds < 0) {
            differenceSeconds += 24 * 3600; 
        }

        Time diff;
        diff.hour = differenceSeconds / 3600;
        differenceSeconds %= 3600;
        diff.minute = differenceSeconds / 60;
        diff.second = differenceSeconds % 60;

        return diff;
}
// Function to add time to the current time
Time Time:: addTime(int h,int m, int s){
        this->second+=s;
        this->minute=this->minute+m+second/60;
        this->hour=this->hour+h+minute/60;
        second %= 60;
        minute %= 60;
        hour %= 24;
        return *this;
}
// Function to do subtract time from the current time
Time Time:: subtractTime(int h, int m, int s) {
        second -= s;
        minute -= m;
        hour -= h;
        while (second < 0) {
            second += 60;
            minute--;
        }
        while (minute < 0) {
            minute += 60;
            hour--;
        }
        while (hour < 0) {
            hour+= 24; 
        }

        return *this;
 }

// Operator '<' Overloading        
bool Time ::operator<( const Time& other) const {
    int h1=this->hour;
    int h2=other.hour;
    if (this->hour == 0 && other.hour<10){
            h1=this->hour;
    }
    else if (this->hour==0 && other.hour > 10){
            h1=24;
    }
    else if (other.hour==0 && this->hour<10){
            h2=other.hour;
    }
    else if(other.hour==0 && this->hour>10){
            h2=24;
    }
    int totalSecondsThis = h1 * 3600 + minute * 60 + second;
    int totalSecondsOther = h2 * 3600 + other.minute * 60 + other.second;

    return totalSecondsThis < totalSecondsOther;
    }

// Function to check whether the entered time is valid or not
bool Time:: isValidTime() const{
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        Time compare_t(localTime->tm_hour,localTime->tm_min,localTime->tm_sec);
        if (compare_t < (*this) && this->hour <=23 && this->minute <=59 && this->second<=59 && this->hour>=0 && this->minute>=0 && this->second>=0){
                return true;
        }
        else { 
                return false;
        }
}

class User;

class Request{
     public:
        string name;
        string user;
        string location;
        Time reporting_time;
        CabSize cab_size;
        Request();
        ~Request();
        Request(const string& n, const string& u, const  string& l, Time t, CabSize c);
        void displayRequest();
        friend User;
};

Request :: Request(){}

Request :: Request(const string& n, const string& u, const string& l, Time t, CabSize c){
        name=n;
        user=u;
        location=l;
        reporting_time=t;
        cab_size=c;
}

Request :: ~Request(){}

void Request::displayRequest() {
    cout << "Name: " << name << endl;
    cout << "User: " << user << endl;
    cout << "Location: " << location << endl;
    cout << "Reporting Time: ";
    reporting_time.displayTime(); 
    cout << "Cab Size: ";
    switch (cab_size) {
        case CabSize::Small:
            cout << "Small" << endl;
            break;
        case CabSize::Large:
            cout << "Large" << endl;
            break;
    }
}

bool checkLocation(const string& s, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            if (cell == s) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

class User {
    friend Request;
private:
    string name;
    string Id;
public:
    User(){
        setName();
        setId();
    }
    User(string& newName, string& newId):name(newName), Id(newId) {}
    // Getters (Accessors)
    string getName() {
        return name;
    }
    string getId(){
        return Id;
    }
    // Setters (Mutators)
    void setName() {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin,name);
    }
    void setId() {
        cout << "Enter ID: ";
        cin.ignore();
        getline(cin,Id);
    }
    // Function to book a ride request
    Request bookRequest() {
           string loc;
           string l;
           bool ans1=false;
           while (ans1==false){
                 cout << "Enter valid destination: " ;
                 getline(cin,loc);
                 l=changeUppercase(loc);
                 ans1=checkLocation(l,"places_and_connections-2.csv");
           }
           int h,m;
           bool ans=false;
           Time t;
           while ( ans==false){
                   cout << "Enter hour: " ;
                   cin >> h;
                   if (h==0){
                           h+=24;
                   }
                   cout << "Enter minutes: " ;
                   cin >> m;
                   Time check_t(h,m,0);
                   t=check_t;
                   ans=check_t.isValidTime();
           }
           int cabSizeInt;
           cout << "Enter preferred cab size (4 for Small, 7 for Large): ";
           cin >> cabSizeInt;
           cin.ignore();
           CabSize cabSize;
           if (cabSizeInt == 4) {
                         cabSize = CabSize::Small;
                 }
           else if (cabSizeInt == 7) {
                       cabSize = CabSize::Large;
                  } 
           else {
               cout << "Invalid input. ";
               return Request(); 
            }
           string location=changeUppercase(l);
           string n=changeUppercase(getName());
           string i=changeUppercase(getId());
           Request r(n, i, location, t, cabSize);
           this->writeRequestToCSV("requests-1.csv",r);
           return r;
           } 
    // Function to transfer the ride request to the CSV file
    void writeRequestToCSV(const string& filename, const Request& request) {
    ofstream file(filename, ios::app);  
    if (file.is_open()) {
        file << request.name << "," << request.user << "," << request.location << ","
             << request.reporting_time.hour << ":" << request.reporting_time.minute << ","
             << static_cast<int>(request.cab_size) << "\n";
        file.close();
    } else {
        cout << "Unable to open the file." << endl;
    }
  }

  // Function to check whether the request exists in the CSV file
  bool isRequest(const string& name) {
    string s=changeUppercase(name);
    ifstream file("requests-1.csv");
    if (!file.is_open()) {
        cout << "Unable to open the file." << endl;
        return false; 
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string requestName;
        getline(ss, requestName, ',');
        requestName.erase(0, requestName.find_first_not_of(" \t\r\n"));
        requestName.erase(requestName.find_last_not_of(" \t\r\n") + 1);
        if (requestName == s) {
            file.close();
            return true; 
        }
    }

    file.close();
    return false; 
}

// Function to find the ride request in the CSV file
   static Request findRequest(const string &name) {
    string s=changeUppercase(name);
    ifstream file("requests-1.csv");
    if (!file.is_open()) {
        cout << "Unable to open the file." << endl;
        return Request(); 
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string requestName;
        getline(ss, requestName, ',');
        requestName.erase(0, requestName.find_first_not_of(" \t\r\n"));
        requestName.erase(requestName.find_last_not_of(" \t\r\n") + 1);
        if (requestName == s) {
            string user, location, timeStr;
            int cabSizeInt, hour, minute;
            char comma;
            getline(ss, user, ',');
            getline(ss, location, ',');
            getline(ss, timeStr, ',');
            ss >> cabSizeInt;
            ss.ignore(); 
            sscanf(timeStr.c_str(), "%d:%d", &hour, &minute);

            Time reportingTime(hour, minute, 0);
            CabSize cabSize = (cabSizeInt == 4) ? CabSize::Small : CabSize::Large;
            file.close();
            return Request(name, user, location, reportingTime, cabSize);
        }
    }

    file.close();
    return Request();
}

};

// Class UserGroup
class UserGroup{
      public:
         CabSize cab_size;
         Time time_slot;
         vector <pair < Time, Request > > v; 
         UserGroup();
         UserGroup(CabSize c,Time t);
         ~UserGroup();
         void displayUserGroup();
         void addToGroup(const pair<Time, Request>& newPair);
         bool isGroupFull();
         const string& findUser(const string& name); 
         bool checkOne() const;

};

UserGroup::UserGroup(){}

UserGroup::UserGroup(CabSize c,Time t):time_slot(t),cab_size(c){}

UserGroup::~UserGroup(){}

// Function to display the details of UserGroup class
void UserGroup::displayUserGroup() {
    cout << "Cab Size: " << static_cast<int>(cab_size) << endl;
    cout << "Time Slot: From ";
    Time upper=time_slot.addTime(0,20,0);
    Time lower=time_slot.subtractTime(0,40,0);
    lower.displayTime();
    cout << " to " ;
    upper.displayTime();
    cout << "\n";
    cout << "\n     Users:      " << endl;
    cout << endl;
    for (const auto& pair : v) {
        cout << "Name: " << pair.second.name << " | " ;
        cout << "UserId: " << pair.second.user << " | ";
        cout << "Location: " << pair.second.location << " | ";
        cout << "Time: " ;
        pair.first.displayTime();
        cout << " | \n";
        cout << endl;
    }
}

// Function to add ride requests to the group 
void UserGroup::addToGroup(const pair<Time, Request>& newPair) {
    v.push_back(newPair);
}
// Function to find users in the group
const string& UserGroup::findUser(const string& name) {
    static const string empty_location = ""; 

    for (const auto& pair : v) {
        if (pair.second.user == name) {
            return pair.second.location;
        }
    }

    return empty_location;
}

// Function to validate whether the group is full or not
bool UserGroup::isGroupFull() {
    return v.size() == static_cast<size_t>(cab_size);
}

bool UserGroup::checkOne() const{
         return v.size() <= 1;
 }

struct CompareTime {
    bool operator()(const pair<Time, Request>& p1, const pair<Time, Request>& p2) const {
        return p2.first < p1.first;  
    }   
};

// Function to read requests from file
void readRequestsFromFile(const string& filename, priority_queue<pair<Time, Request>, vector<pair<Time, Request>>, CompareTime>& pq) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string name, user, location;
        int hour, minute;
        int cabSizeInt;

        getline(ss, name, ',');
        getline(ss, user, ',');
        getline(ss, location, ',');
        ss >> hour;
        ss.ignore();
        ss >> minute;
        ss.ignore(); 
        ss >> cabSizeInt;

        CabSize cabSize;
        if (cabSizeInt == 4) {
            cabSize = CabSize::Small;
        } else if (cabSizeInt == 7) {
            cabSize = CabSize::Large;
        } else {
            cout << "Invalid cab size: " << cabSizeInt << endl;
            continue; 
        }

        Time reportingTime(hour, minute, 0);

        Request request(name, user, location, reportingTime, cabSize);

        pq.push(make_pair(reportingTime, request));
    }

    file.close();
}

// User-Grouping Algorithm
list <pair<list<pair<string,int> >, UserGroup > > UserGroupingAlgorithm(priority_queue<pair<Time, Request>, vector<pair<Time, Request>>, CompareTime> pq, Request &r, Graph &g){
  Time c_time=r.reporting_time;
  Time upper=c_time.addTime(0,20,0);
  Time lower=c_time.subtractTime(0,40,0);
 
  list < pair<list<pair<string, int> >,UserGroup > >  path_list;

  list <pair <Time,Request> > temp_list;
  list <pair<Time,Request> > new_list;
  while(!pq.empty()){
          new_list.push_back(pq.top());
          pq.pop();
  }

  list <pair <Time,Request> > :: iterator new_it=new_list.begin();
  pair <Time,Request> pair1=make_pair(r.reporting_time,r);
  while(new_it!=new_list.end()){
          if (new_it->first < upper && lower < new_it->first){
                  temp_list.push_back(*new_it);
          }
          new_it++;
  }
   

  string desired_dest=r.location;
  vector <vector <pair <string,float> > > paths=g.yenKSP("PLAKSHA", desired_dest, 2);
  vector <vector <pair <string, float > > > :: iterator v_main=paths.begin();
  while(v_main!=paths.end()){
          vector < pair < string, float > > :: iterator v_mini=v_main->begin();
          list <pair<string,int> > l;
          UserGroup g(r.cab_size, r.reporting_time);
          while(v_mini!=v_main->end()){
                      list <pair<Time, Request> >:: iterator lit = temp_list.begin();
                      while(lit!=temp_list.end()){
                              if (lit->second.location==v_mini->first){
                                      float time=(v_mini->second/SPEED);
                                      int m=static_cast<int>(time*60);
                                      if (g.isGroupFull()==false){
                                              g.addToGroup(*lit);
                                      }
                                      pair <string,int> p=make_pair(lit->second.location,m);
                                      if ( ifpairExists(p,l)==false){
                                              l.push_back(p);
                                      }
                              }
                              lit++;
                      }
          v_mini++;
          }
          pair <list<pair<string,int> > , UserGroup > p_main=make_pair(l,g);
          path_list.push_back(p_main);
          v_main++;
  }
  return path_list;
}

// Display Function
void displayOptions(list < pair<list<pair<string, int> >,UserGroup > >  path_list,Request &r){
  list < pair <list<pair<string, int> >,UserGroup> >  :: iterator main_it=path_list.begin();
  int count=1;
  while(main_it!=path_list.end()){
                   cout << "\nOPTION " << count << " : " << endl;
                   if (main_it->second.checkOne() == true) {
                           cout << "\nNo carpoolers found, you have an option to travel alone :(." << endl;
                           cout << "\nYour cab details are as follows. \n" << endl;
                           main_it->second.displayUserGroup();
                   }
                   else {
                           cout << "Carpoolers found !\n " << endl;
                           main_it->second.displayUserGroup();
                   }
                   list <pair<string,int>> ::iterator s_it=main_it->first.begin();
                   cout << "The path of the cab:" << endl;
                   cout << "\nPlaksha->" ;
                   while(s_it!=main_it->first.end()){
                           cout << s_it->first << "(" << s_it->second << " minutes to reach) ->";
                   s_it++;
                   }
                   cout << "\n" ;
                   main_it++;
                   count++;
  }
}

// Function to determine the most optimised route choice 
void mostOptimisedChoice(list < pair<list<pair<string, int> >,UserGroup > >  path_list,Request &r){
  list < pair<list<pair<string, int> >, UserGroup> >  :: iterator main_it2=path_list.begin();
  int min_t=10000;
  while(main_it2!=path_list.end()){
         list <pair<string,int> > ::iterator s_it2=main_it2->first.begin();
         while(s_it2!=main_it2->first.end()){
                 if (s_it2->first ==r.location){
                         if(min_t > s_it2->second){
                                min_t=s_it2->second;
                         }

                 }
                 s_it2++;
         }
         main_it2++;
  }


  list < pair<list<pair<string, int> >, UserGroup> >  :: iterator main_it3=path_list.begin();
  while(main_it3!=path_list.end()){
         list <pair<string,int> > ::iterator s_it3=main_it3->first.begin();
         while(s_it3!=main_it3->first.end()){
                 if (s_it3->first ==r.location){
                         if(min_t==s_it3->second){
                                cout << "THE MOST OPTIMISING CHOICE: " << endl;
                                cout << "\n You will reach in " << min_t << " minutes!" << endl;
                                if (main_it3->second.checkOne() == true){
                                        cout << "\nIn this option, you will unfortunately not have any carpoolers. :( " << endl;
                                        cout << "\nYour cab details are as follows.\n " << endl;
                                        main_it3->second.displayUserGroup();
                                }
                                else{
                                        cout << "\nYour carpooling details are...\n " << endl;
                                        main_it3->second.displayUserGroup();
                                }
                                break;
                         }

                 }
                 s_it3++;
         }
         main_it3++;
  }
}


