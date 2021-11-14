#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

using namespace std;

static mutex mtx;

class pcout
{
public:
    pcout(){
        mtx.lock();
    }
    ~pcout()
    {
        mtx.unlock();
    }

    template<typename T>
    pcout operator<<(const T& t)
    {
        {
            cout<< t;
            return *this;
        }
    }
};


void prnt(string s)
{
    this_thread::sleep_for(2s);
    pcout() << s;
}

void task1()
{
    cout<<"Task 1"<<endl;
    thread th1(prnt,"Thread 1\n");
    thread th2(prnt,"Thread 2\n");
    thread th3(prnt,"Thread 3\n");
    thread th4(prnt,"Thread 4\n");
    th1.join();
    th2.join();
    th3.join();
    th4.join();
}

void simple(uint32_t n,int &res)
{
    res = 0;
    uint32_t i;
    for (i=2;i<=n/2;i++)
    {
        if(n%i == 0)
        {
            res = 0;
            return;
        }
    }
    res = n;
}

void countsimple(int num)
{
    int current = 1;
    int ans = 0;
    for (uint32_t i=2;current<=num;i++)
    {
        thread th1(simple,i,ref(ans));
        th1.join();
        if(ans)
        {
            cout<<ans<<" is "<<current<<" simple number"<<endl;
            current++;
        }
    }
    cout<<"Your simple is = "<<ans<<endl;
}

void task2()
{
    cout<<"Task 2"<<endl;
    int num;
    cout<<"Enter the number ";
    cin>> num;
    countsimple(num);
}

void worker(vector<int> &house, int &res)
{
    for(int i=0;i<10;i++)
    {
        int k = rand()%100+1;
        house.push_back(k);
        cout<<"+Worker brings thing wich costs "<<k<<endl;
        this_thread::sleep_for(1s);
    }
}

void thief(vector<int> &house, int &res)
{
    for(int i=0;i<10;i++)
    {
        auto max = house.begin();
        for(auto it = house.begin();it!=house.end();it++)
        {
            if (*max<*it)
                max=it;
        }
        res = *max;
        house.erase(max);
        cout<<"-Thief stole thing wich costs "<<res<<endl;
        this_thread::sleep_for(2s);
    }
}

void task3()
{
    cout<<"Task 3"<<endl;
    vector<int> house;
    int res;
    thread th1(worker,ref(house),ref(res));
    thread th2(thief,ref(house),ref(res));
    th1.join();
    th2.join();
}

int main()
{
    task1();
    task2();
    task3();
    return 0;
}
