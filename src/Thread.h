/*
 * Thread.cpp
 *
 *  Created on: 2013-5-20
 *      Author: qiong
 */

class Thread {
public:
	virtual ~Thread() {
	}
	//开始线程
	void start() {
		pthread_create(&tid, NULL, hook, this);
	}
	//等待线程结束
	void join(){
		over();
		pthread_join(tid,NULL);
	}
private:
	pthread_t tid;
	static void* hook(void* args) {
		reinterpret_cast<Thread*> (args)->run();
		return NULL;
	}
protected:
	virtual void run() = 0;
	virtual void over() = 0;
};
