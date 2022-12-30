#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;

int myrand(int min, int max) {
  return rand()%(max-min)+min;
}

void lock(atomic_flag& m) {
  while (m.test_and_set())
    this_thread::sleep_for(chrono::milliseconds(8));
}

void unlock(atomic_flag& m) {
  m.clear();
}

void phil(int ph, atomic_flag& ma, atomic_flag& mb) {
  while(true) {
    int duration=myrand(1000, 2000);
    cout<<ph<<" thinks "<<duration<<"ms\n";
    this_thread::sleep_for(chrono::milliseconds(duration));

    lock(ma);
    cout<<"\t\t"<<ph<<" got ma\n";
    this_thread::sleep_for(chrono::milliseconds(1000));

    lock(mb);
    cout<<"\t\t"<<ph<<" got mb\n";

    duration=myrand(1000, 2000);
    cout<<"\t\t\t\t"<<ph<<" eats "<<duration<<"ms\n";
    this_thread::sleep_for(chrono::milliseconds(duration));

    unlock(mb);
    unlock(ma);
  }
}

int main() {
  cout<<"dp_6\n";
  srand(time(nullptr));

  atomic_flag m1, m2, m3, m4;
  unlock(m1);
  unlock(m2);
  unlock(m3);
  unlock(m4);

  thread t1([&] {phil(1, m1, m2);});
  thread t2([&] {phil(2, m2, m3);});
  thread t3([&] {phil(3, m3, m4);});
  thread t4([&] {phil(4, m1, m4);});

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}