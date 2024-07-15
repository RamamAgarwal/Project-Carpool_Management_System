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
#include "Classes_Final3.C"
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <sstream>

void displayMainMenu(){
        cout << " 1. Add Request. " << endl;
        cout << " 2. Look at available carpoolers. " << endl;
        cout << " 3. Display most time saving route. " << endl;
        cout << " 4. Exit ! ( Press 0 ) " << endl;
        return;
}

int main(void){

        Graph g(10);

        ifstream file("places_and_connections-2.csv");
        if (file.is_open()) {
             string line;
             getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string place1, place2;
            float distance;
            char comma;

            getline(ss, place1, ',');
            getline(ss, place2, ',');
            ss >> distance;

            g.addEdge(place1, place1, 0); 
            g.addEdge(place2, place2, 0); 
            g.addEdge(place1, place2, distance);
        }   

        file.close();
        }
        else {
        cout << "Unable to open the file." << endl;
        return 1;
        }

        char ch='Y';
        while (ch=='Y'){
                cout << "\n 🚕  Welcome to our Carpooling Algorithm ! 🚕\n" << endl;
                cout << "\n Do you wish to..?\n " << endl;
                displayMainMenu();
                int main_choice;
                cout << "\nEnter choice: ";
                cin >> main_choice;
                if (main_choice==1){
                            User u;
                            u.bookRequest();
                            cout << "\nRequest added 🙌 ! " << endl;
                            ch='Y';
                }
                else if( main_choice==2){
                             string n;
                             cout << "\nEnter name of the user looking for carpoolers: " ;
                             cin.ignore();
                             getline(cin,n);
                             Request r=User::findRequest(n);
                             if (r.name==""){
                                        cout << "No such request by this user exists :( " << endl;
                              }
                             else {
                                    cout << r.name << "'s request found! " << endl;
                                    cout << "\nFinding most suitable carpoolers and routes...\n" << endl;
                                    priority_queue<pair<Time, Request>, vector<pair<Time, Request>>, CompareTime> pq;
                                    readRequestsFromFile("requests-1.csv", pq);  
                                    list <pair<list<pair<string,int> >, UserGroup > > path_list;
                                    path_list=UserGroupingAlgorithm(pq, r, g);
                                    cout << "\nDisplaying all options found...\n " << endl;
                                    cout <<"\n";
                                    displayOptions(path_list,r);
                              }
                              ch='Y';
                }
                 else if( main_choice==3){
                             string name;
                             cout << "\nEnter name of the user looking for carpoolers: " ;
                             cin.ignore();
                             getline(cin,name);
                             Request r=User::findRequest(name);
                             if (r.name==""){
                                        cout << "No such request by this user exists. :(" << endl;
                              }
                             else {
                                    cout << r.name << "'s request found! " << endl;
                                    cout << "\nFinding most suitable carpoolers and routes...\n" << endl;
                                    priority_queue<pair<Time, Request>, vector<pair<Time, Request>>, CompareTime> pq;
                                    readRequestsFromFile("requests-1.csv", pq);
                                    list <pair<list<pair<string,int> >, UserGroup > > path_list;
                                    path_list=UserGroupingAlgorithm(pq, r, g);
                                    cout << "\nDisplaying the most time saving option...\n " << endl;
                                    cout <<"\n";
                                    mostOptimisedChoice(path_list,r);
                              }
                              ch='Y';
                }
                else if(main_choice==4){
                        cout << "\nExiting Program ! Thank you." << endl;
                        ch='N';
                }
                else{
                        cout << "Invalid choice entered. Exiting program....."<< endl;
                        ch='N';
                }
        }
        return 0;
}


