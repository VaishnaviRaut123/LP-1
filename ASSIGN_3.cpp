#include<iostream>
#include<mutex>
#include<queue>
using namespace std;

struct semaphore{
    int value;
    queue<int> q;     
};

class Semaphore{
    semaphore s;
    int currItemNum;
public:
    Semaphore(){
        // 0 because initially item can be produced
        s.value = 0;
        currItemNum = 0;
    }

    void produce(){
        char ch;
        do{
            s.value = s.value - 1;

            if(s.value < 0){
                s.q.push(currItemNum);
                currItemNum++;
                cout << "Item " << currItemNum << " produced" << "\n";
            }
            else{
                cout << "All threads busy" << "\n";
                return;
            }

            cout << "Do you want to continue producing ? (y/n)" << "\n";
            cin >> ch; 
        }while(ch == 'y');
        
    }

    void consume(){
        char ch;
        do{
            if(currItemNum <= 0){
                cout << "No item available" << "\n";
                return;
            }

            s.value = s.value + 1;

            if(s.value < 0){
                int item = s.q.front();
                s.q.pop();
                cout << "Item " << item << " consumed" << "\n";
                currItemNum--;
            }
            else{
                cout << "All threads busy" << "\n";
                return;
            }

            cout << "Do you want to continue consuming ? (y/n)" << "\n";
            cin >> ch; 
        }while(ch == 'y');
    }

    void itemsAvailable(){
        cout << "Total :- " << currItemNum << " items available" << "\n";
        return;
    }

    void giveLockValue(){
        cout << "Lock value :- " << s.value << "\n";
    }

};

class Mutex{
    // 0 -> Unlock state;
    // 1 -> Locked state 
    int lockState; 
    int currItemNum;
    mutex m;
public:
    Mutex(){
        // 0 because initially item can be produced
        lockState = 0;
        currItemNum = 0;
    }

    void setLockState(){
        lockState = 1;
    }

    void unSetLockState(){
        lockState = 0;
    }

    void produce(){
        if(lockState == 1){
            cout << "Thread is busy" << "\n";
            return; 
        }

        m.lock();

        currItemNum++;
        cout << "Item " << currItemNum << " produced" << "\n";

        m.unlock(); 

        lockState = 0;
        return;
    } 

    void consume(){
        if(lockState == 1){
            cout << "Thread is busy" << "\n";
            return;
        }

        m.lock();

        if(currItemNum <= 0){
            cout << "!!! No item available !!!" << "\n";
            m.unlock();
            return;
        }

        cout << "Item " << currItemNum << " consumed" << "\n";
        currItemNum--;

        m.unlock(); 

        lockState = 0;
        return;
    }

    void itemsAvailable(){
        cout << "Total :- " << currItemNum << " items available" << "\n";
        return;
    }

};

int main(){

    cout << "------------MUTEX--------------" << "\n";    
    Mutex mt;

    mt.produce();
    mt.produce();
    mt.consume();
    mt.consume();
    mt.setLockState();
    mt.unSetLockState();
    mt.produce();

    cout << "---------------SEMAPHORE------------" << "\n";
    Semaphore sp;

    sp.produce();
    sp.giveLockValue();
    sp.consume();
    sp.giveLockValue();

    return 0;
}