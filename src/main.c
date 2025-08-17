#include <bits/stdc++.h>
using namespace std;

struct Station {
    string name;
    Station* prev;
    Station* next;
    Station(string n): name(move(n)), prev(nullptr), next(nullptr) {}
};

class Route {
    Station* head = nullptr;
    Station* tail = nullptr;
    Station* current = nullptr;
    bool circular = false;

    Station* findNode(const string& name){
        for(Station* p=head; p; p=p->next){
            if(p->name == name) return p;
            if(circular && p->next==head) break;
        }
        return nullptr;
    }

    int length() const {
        if(!head) return 0;
        int cnt=0;
        const Station* p=head;
        do{ cnt++; p=p->next; } while(p && p!=head);
        return cnt;
    }

public:
    ~Route(){ clear(); }

    void setCircular(bool on){
        if(on == circular) return;
        circular = on;
        if(!head) return;
        if(circular){
            head->prev = tail;
            tail->next = head;
        } else {
            head->prev = nullptr;
            tail->next = nullptr;
        }
    }

    void addStation(const string& name, int pos=-1){
        Station* node = new Station(name);
        if(!head){
            head=tail=current=node;
        } else if(pos<=0){
            // push front
            node->next = head;
            head->prev = node;
            head = node;
        } else {
            // insert at position or end
            Station* p=head;
            int i=0;
            while(p->next && (pos<0 || i<pos-1)){ p=p->next; i++; }
            // insert after p
            node->next = p->next;
            node->prev = p;
            if(p->next) p->next->prev = node;
            p->next = node;
            if(p==tail) tail = node;
        }
        if(circular && head && tail){
            head->prev = tail;
            tail->next = head;
        }
        cout << "Added station: " << name << "\n";
    }

    void removeByName(const string& name){
        if(!head) { cout<<"No stations.\n"; return; }
        Station* p = head;
        while(true){
            if(p->name == name) break;
            p = p->next;
            if(!p || (circular && p==head)){ p=nullptr; break; }
        }
        if(!p){ cout<<"Not found.\n"; return; }

        if(p==head) head = (p->next==p? nullptr : p->next);
        if(p==tail) tail = (p->prev==p? nullptr : p->prev);

        if(p->prev) p->prev->next = p->next;
        if(p->next) p->next->prev = p->prev;

        if(circular && head && tail){
            head->prev = tail;
            tail->next = head;
        } else if(!head){
            circular = false; // no nodes
        }
        if(current==p) current = head;
        delete p;
        cout<<"Removed.\n";
    }

    void clear(){
        if(!head) return;
        if(circular){ // break cycle
            tail->next = nullptr;
            head->prev = nullptr;
        }
        while(head){
            Station* t=head; head=head->next; delete t;
        }
        tail = current = nullptr;
        circular = false;
    }

    void showRoute(){
        cout << "\n--- Route ---\n";
        if(!head){ cout<<"(empty)\n"; return; }
        Station* p=head;
        int i=0;
        do{
            cout << (p==current? "-> ":"   ") << i << ". " << p->name << (p==current? " (current)":"") << "\n";
            p=p->next; i++;
        } while(p && p!=head);
        cout << "Mode: " << (circular? "CIRCULAR":"LINEAR") << "\n";
        cout << "Stations: " << length() << "\n";
        cout << "-----------\n";
    }

    void setCurrentByName(const string& name){
        Station* n = findNode(name);
        if(n){ current=n; cout<<"Current set to "<<name<<"\n"; }
        else cout<<"Not found.\n";
    }

    void moveNext(){
        if(!current){ cout<<"No stations.\n"; return; }
        if(current->next){ current=current->next; }
        else if(circular){ current=head; }
        else { cout<<"At end of route.\n"; return; }
        cout<<"Now at: "<<current->name<<"\n";
    }

    void movePrev(){
        if(!current){ cout<<"No stations.\n"; return; }
        if(current->prev){ current=current->prev; }
        else if(circular){ current=tail; }
        else { cout<<"At start of route.\n"; return; }
        cout<<"Now at: "<<current->name<<"\n";
    }
};

class App {
    Route route;
public:
    void run(){
        while(true){
            cout << "\n==== Virtual Train Route Planner ====\n";
            cout << "1. Add station (front)\n";
            cout << "2. Add station (at position)\n";
            cout << "3. Remove station by name\n";
            cout << "4. Show route\n";
            cout << "5. Set current station by name\n";
            cout << "6. Next station\n";
            cout << "7. Prev station\n";
            cout << "8. Toggle circular mode\n";
            cout << "9. Clear route\n";
            cout << "0. Exit\n";
            cout << "Choose: ";
            int ch; if(!(cin>>ch)) return;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(ch==1){
                string name; cout<<"Station name: "; getline(cin,name);
                route.addStation(name, 0);
            } else if(ch==2){
                string name; cout<<"Station name: "; getline(cin,name);
                int pos; cout<<"Insert at position (0-based, end if too big): ";
                if(!(cin>>pos)) {pos=-1;} cin.ignore(numeric_limits<streamsize>::max(), '\n');
                route.addStation(name, pos);
            } else if(ch==3){
                string name; cout<<"Name to remove: "; getline(cin,name);
                route.removeByName(name);
            } else if(ch==4){
                route.showRoute();
            } else if(ch==5){
                string name; cout<<"Set current to: "; getline(cin,name);
                route.setCurrentByName(name);
            } else if(ch==6){
                route.moveNext();
            } else if(ch==7){
                route.movePrev();
            } else if(ch==8){
                static bool mode=false; mode=!mode;
                route.setCircular(mode);
                cout<<"Circular mode: "<<(mode?"ON":"OFF")<<"\n";
            } else if(ch==9){
                route.clear(); cout<<"Cleared.\n";
            } else if(ch==0){
                cout<<"Bye!\n"; return;
            } else {
                cout<<"Invalid.\n";
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    App app; app.run();
    return 0;
}
