#include <bits/stdc++.h>
using namespace std;

class LRU
{
    int capacity;
    deque<int> q;
    int pagefaults;
    deque<int>::iterator itr;
    vector<int> v;

    public:
        LRU(){
            capacity=pagefaults=0;
            q.clear();
        }
        LRU(int c){
            capacity = c;
            pagefaults = 0;
            q.clear();
        }

        void input()
        {
            int n;
            cout<<"Enter the number of pages\n";
            cin>>n;
            for(int i=0;i<n;i++){
            cout<<"Enter the element\n";
            int p;
            cin>>p;
            v.push_back(p);
            }
        }

        void func()
        {
            for(int i=0;i<v.size();i++){
                itr = find(q.begin(),q.end(),v[i]);

                if(!(itr!=q.end())){
                    pagefaults++;       // page not found

                    // hence insert that page
                    if(q.size()==capacity){
                        // cout<<"Removing least recently used page: "<<q.front()<<"\n";
                        q.erase(q.begin());      // least recently used
                        q.push_back(v[i]);
                    }
                    else{
                        q.push_back(v[i]);
                    }
                }
                else{
                    // element has been used before
                    q.erase(itr);
                    q.push_back(v[i]);
                }
            }
            cout<<"The number of page faults = "<<pagefaults<<"\n";
        }

        void display()
        {
            cout<<"The queue currently is: ";
            for(int i=0;i<capacity;i++){
                cout<<q[i]<<" ";
            }
            cout<<"\n";
        }
};

class FIFO
{
    int capacity;
    unordered_set<int> s;
    deque<int> q;
    int pagefaults;
    deque<int>::iterator itr;
    vector<int> v;

    public:
        FIFO(){
            capacity=pagefaults=0;
        }
        FIFO(int c){
            capacity = c;
            pagefaults = 0;
        }

        void input()
        {
            int n;
            cout<<"Enter the number of pages\n";
            cin>>n;
            for(int i=0;i<n;i++){
            cout<<"Enter the element\n";
            int p;
            cin>>p;
            v.push_back(p);
            }
        }

        void func()
        {
            for(int i=0;i<v.size();i++){
                if(s.size()<capacity){
                    if(s.find(v[i])==s.end()){
                        s.insert(v[i]);
                        pagefaults++;
                        q.push_back(v[i]);
                    }
                }
                else{
                    if(s.find(v[i])==s.end()){
                        int val = q.front();
                        q.erase(q.begin());
                        s.erase(val);
                        s.insert(v[i]);
                        pagefaults++;
                        q.push_back(v[i]);
                    }
                }
            }
            cout<<"The number of page faults = "<<pagefaults<<"\n";
        }

        void display()
        {
            cout<<"The queue currently is: ";
            for(int i=0;i<capacity;i++){
                cout<<q[i]<<" ";
            }
            cout<<"\n";
        }
};

int main()
{
    cout<<"\n******************************************LRU***********************************************\n\n";
    int c1;
    cout<<"Enter the capacity of the pages\n";
    cin>>c1;

    LRU l(c1);

    l.input();
    l.func();
    l.display();

    cout<<"\n******************************************FIFO***********************************************\n\n";
    int c2;
    cout<<"Enter the capacity of the pages\n";
    cin>>c2;

    FIFO f(c2);

    f.input();
    f.func();
    f.display();

    
    return 0;
}