#include <vector>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <iostream>
using namespace std;
shared_mutex rw_mutex;//读写锁
int shared_data = 0;//共享数据
//写函数
void writter(int i)
{
	unique_lock<decltype(rw_mutex)> lock(rw_mutex);
	shared_data = i;
	cout << "pid: " << this_thread::get_id() << " write data: " << shared_data << endl;

}
//读函数
void reader()
{
	shared_lock<decltype(rw_mutex)> lock(rw_mutex);
	cout << "pid: " << this_thread::get_id() << " read data: " << shared_data << endl;
}
int main()
{
	vector<thread> thr;
	
	for(int i = 1;i<=5;i++)
	{
		thr.emplace_back(reader);
		thr.emplace_back(writter, i);
	}
	for (auto &t : thr)
	{
		t.join();
	}
	return 0;
}