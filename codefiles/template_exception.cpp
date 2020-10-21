#include<iostream>
#include<string>
#include<exception>

using namespace std;


template<class T>
class FullQueue : public exception
{
public:
	FullQueue(T t) :exception(" queue is full "), element(t){}
	 T get(){ return element; }
private:
	T element;
};


class EmptyQueue : public exception
{
  public:
	EmptyQueue(void):exception(" queue is empty "){}	
};





const int queue_size=4;

class intQueue
{
public:

	intQueue():queue_start(0),queue_end(queue_size-1),actual_size(0){}

    void enqueue(int a){ if (actual_size == queue_size) throw FullQueue<int>(a);
	QueueArray[++queue_end == queue_size ? queue_end = 0 : queue_end] = a; actual_size++; 
	//dump();
	}
	int dequeue(void){if (actual_size == 0) throw EmptyQueue();
	                  int present_queue_start = queue_start;
					  queue_start = queue_start == queue_size - 1 ? 0 : queue_start + 1;
	                  actual_size--; 
					 // dump();
					  return QueueArray[present_queue_start]; }
	

private:
	void dump(void) 
	{cout << endl << " qs " << queue_start << " qe " << queue_end << " as " << actual_size << endl;}
	int QueueArray[queue_size];
	unsigned int queue_start,queue_end,actual_size;
};

template<class T, int size> 
class Queue
{
public:

	Queue():queue_start(0),queue_end(size-1),actual_size(0){}

    void enqueue(T a){ if (actual_size == size) throw FullQueue<T>(a);
	                   QueueArray[++queue_end == queue_size ? queue_end = 0 : queue_end] = a; actual_size++;
	                 }
	T dequeue(void){ if (actual_size == 0) throw EmptyQueue();
	                 int present_queue_start = queue_start;
	                 queue_start = queue_start == queue_size - 1 ? 0 : queue_start + 1;
	                 actual_size--;
	                 return QueueArray[present_queue_start];
	               }

private:
	T QueueArray[size];
	unsigned int queue_start,queue_end,actual_size;
};

void main(void)
{
	 intQueue queue;
	 Queue<double,4> dq;
	
	 queue.enqueue(4);
	 queue.enqueue(5);
	 cout<<queue.dequeue()<<" "<<endl;
	 cout<<queue.dequeue()<<" "<<endl;
	 queue.enqueue(6);
	 queue.enqueue(7);
	 queue.enqueue(42);
  	 queue.enqueue(43);   
     cout << queue.dequeue() << " " << endl;
	 cout << queue.dequeue() << " " << endl;

	 dq.enqueue(3.3);
	 dq.enqueue(7.7);	 
	 cout<<dq.dequeue()<<" "<<endl;
	 cout<<dq.dequeue()<<" "<<endl;

     try
	 {
	  //cout << dq.dequeue() << " " << endl;
	  dq.enqueue(3.3);
	  dq.enqueue(7.7);
	  dq.enqueue(3.4);
	  dq.enqueue(7.8); dq.dequeue(); dq.dequeue(); dq.dequeue(); dq.dequeue(); dq.dequeue(); dq.dequeue(); dq.dequeue();
	  dq.enqueue(3.9);
	 
	
	 }
	 catch( FullQueue<double> &t)
	 { cout << t.what() << t.get() << " could not be inserted "<< endl;}
	 catch( EmptyQueue &t)
	 { cout << t.what() << endl;}
	 catch( exception &t)
	 { cout << t.what() << endl;}

	 int k;
	 cin >> k;
}


	
