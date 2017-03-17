#include <iostream>
#include<iomanip>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <stdlib.h>
#include <pthread.h>
#include <sstream>
#include <time.h>
#include <stdint.h>

#include <sys/socket.h>      
#include <netinet/in.h>      
#include <netdb.h> 
#include <event.h>
#include <cmath>

/**********count_max_thread_test***********/
void* foo(void* arg) {
	sleep(1);
	//std::cout << "creat...";
}

int count_max_thread(void) {
    int i = 0;
    pthread_t thread;
    
    while (1) {
        if (pthread_create(&thread, NULL, foo, NULL) != 0) {
			printf("i = %d\n", i);
			return i;
			
		}            
        i++;  
		
    }
	return 0;
}

void count_max_thread_test(void) {
	int count = count_max_thread();
	std::cout << "Max thread:[ " << count << " ]\n";
}
/**********count_max_thread_test***********/ //END

/**********ofstream_put_out ***********/
#define LOG_FILE    file_t

class LOG  {  // :public std::ofstream
	public:
		LOG(const std::ofstream &log_f) {
		//	log_file = log_f;
		}
		LOG(const std::string &file_name) {
			log_file.open(file_name.c_str(), std::ofstream::out);
			if (!log_file.is_open()) {
				std::cout << "Open the LOG_FILE file failure :" << file_name;
			}
		}
		
		
	public:
		friend std::istringstream & operator>>(std::istringstream &is, const LOG &log ); // 
	
		std::ofstream log_file;
};

template<typename T>
 std::istringstream & operator>>(std::istringstream &is, const T log) { // 
	 std::ostringstream str_t;
	 is >> str_t;
			log.log_file << str_t.str();
			if (log.log_file.fail())
			{
				std::cout << "Error writing to test.txt\n";
				log.log_file.clear();
			}
			 return is;		
};



void ofstream_put_out(void) {
	

	
	std::string file_path("test.txt");
	std::ofstream file_t;
	file_t.open(file_path.c_str(), std::ofstream::out);
	if (!file_t.is_open()) {
		std::cout << "Open the LOG_FILE file failure :" << file_path;
	}
	// file_t.close();
	std::cout << "file_t: " << file_t << "\n";
	std::string str;
	std::ostringstream str_t;
	str_t << "key:" << "xxx" << "value:" << 20000 << "\n";
	LOG_FILE << str_t.str();
	std::cout << str_t.str();
	LOG_FILE << "key:" << "xxx" << "value:" << 10000 << "\n";
//	std::cout << (LOG_FILE << "test data\ntest\n " << str) << "\n";
//	std::cout << (LOG_FILE << "test data\ntest\n " << str_t) << "\n";
	if (LOG_FILE.fail())
	{
		std::cout << "Error writing to test.txt\n";
		LOG_FILE.clear();
	}
		file_t.close();
		LOG_FILE << "key:" << "xxx" << "value:" << 10000 << "\n";
	if (LOG_FILE.fail())
	{
		std::cout << "Error writing to test.txt\n";
		LOG_FILE.clear();
	}
	std::istringstream istr_t("aadddddd\n");
	LOG log(std::string("test.txt"));
	// istr_t >> log;
	std::cout << "file_t: " << file_t << "\n";
}


/**********ofstream_put_out***********/ //END

/**********vector_dynamic_operation***********/ 

void vector_dynamic_operation(void) {
	std::vector<std::string> strs;
	std::ostringstream ostr_t;
	for (int i = 0; i < 20; i++) {
		
		ostr_t << "test: " << i << "\n";
		strs.push_back(ostr_t.str());
		ostr_t.str("");
	}
	std::vector<std::string>::iterator it;
	for (it = strs.begin(); it != strs.end(); it++) {
		if ((*it).compare("test: 0\n") == 0) {
			std::cout << "delete operation\n";
			strs.erase(it);
			std::cout << "strs.begin(): " << *(strs.begin()) << "\n";
			std::cout << "(*it): " << (*it) <<"\n";
			
		} 
		if ((*it).compare("test: 18\n") == 0) {
			std::cout << "add operation\n";
			strs.push_back("add new\n");
		}		
	}
	for (it = strs.begin(); it != strs.end(); it++)
    {
		std::cout << *it;
    }
	
	
}
/**********ofstream_put_out***********/ //END

/**********time_operation***********/  
std::string get_currunt_time(void) {
	time_t timep;  
    struct tm *p_tm;  
    timep = time(NULL); 
	timep += 8*60*60;
    p_tm = gmtime(&timep); /*获取GMT时间*/  
	std::ostringstream time_str;
	time_str << "[" 
			<< p_tm->tm_year+1900 << "-" 
			<< p_tm->tm_mon+1 << "-" 
			<< p_tm->tm_mday << " " 
			<< p_tm->tm_hour << ":"
			<< p_tm->tm_min << ":"
			<< p_tm->tm_sec << "] ";
	return time_str.str();
}

std::string get_local_time(void) {
	time_t now;          	//time_t实际为长整形  
    struct tm  *w;          //tm结构体结构化存放时间    
    time(&now);  
    w=localtime(&now);      //获取当前系统时间  
      
    printf("%04d/%02d/%02d\n%02d:%02d:%02d\n",w->tm_year+1900,  
                w->tm_mon+1,w->tm_mday,w->tm_hour,w->tm_min,w->tm_sec); 
	std::ostringstream time_str;
	time_str << "[" 
			<< w->tm_year+1900 << "-" 
			<< w->tm_mon+1 << "-" 
			<< w->tm_mday << " " 
			<< w->tm_hour << ":"
			<< w->tm_min << ":"
			<< w->tm_sec << "] \n";
			
	std::cout << "time()1: " << time(NULL) << "\n";
	sleep(1);
	std::cout << "time()2: " << time(NULL) << "\n";
	
	
	return time_str.str();
}

void time_operation(void) {
	std::cout << get_local_time();
	
	// std::cout << get_currunt_time();
	
}


/**********time_operation***********/ //END
/**********print_test***********/
void print_test(void) {
	std::cout << "\n" << std::left << std::setw(2) << "A" 
			  << std::setw(0) << "Plug status: " 
			  << ((1 == 1) ? 
						"New plug device\n" : "Already plug\n");
	
	
	
}



/**********print_test***********/ //END
/**********struct_destructor_test***********/  


struct person {
		int id;
		static int count;
		int sex;
		int type;
		static int type_count;
		
		person( ) { //:id(0),sex(0),type(0)
			std::cout << "get this struct function 0 \n"; 
			count++;
		}
		person(const struct person &p) {
			std::cout << "get this struct function 1 \n";
			id = p.id ;
			sex = p.sex;
			type = p.type;
			count++;
			if (type == 1) {
				type_count++;
			}	
			
		}
		person(int set_id, int set_sex, int set_type) {
			std::cout << "get this struct function 2 \n";
			id = set_id ;
			sex = set_sex;
			type = set_type;
			count++;
			if (type == 1) {
				type_count++;
			}
		}
		~person (void) {
			std::cout << "get this destruct function 0 \n";
			count--;
			if (type == 1) {
				type_count--;
			}
		}
		
		void print_inf(void) {
			
			std::cout << "count: " << count << "\n";
			std::cout << "type_count: " << type_count << "\n";
			std::cout << "id: " << id << "\n";
			
		}
		
		
	};
int person::count = 0;
int person::type_count = 0;	
void struct_destructor_test(void) {
	
	
	std::map <int, struct person> team;
 
	//team.insert(std::pair<int, person> (3,person(3,1,1)));
	//team[3].print_inf();
	// 
	//team.insert(std::pair<int, person> (5,person(4,1,1)));
	//team[5].print_inf();
	
	for (int i; i< 20;i++) {
		//struct person one(i,1,-1);
		team.insert(std::pair<int, person> (i,person(i,1,1)));
		//team[i]=(person(i,1,-1)) ;
	}
	
	for (int i=20; i< 10+20;i++) {
		//struct person one(i,0,1);
		//team[i] = one;
		//team[i] = struct person(i,1,-1);
		team.insert(std::pair<int, person> (i,person(i,-1,-1)));
	}
	for (int i=0; i< team.size();i++) {
		 
		team[i].print_inf();
		std::cout << "\n";
		
	}
	std::cout << "\nperson.print_inf():\n";
	//struct person::print_inf();
}


/**********print_test***********/ //END




/**********libevent_test***********/
using namespace std;  
      
    // 事件base  
    struct event_base* base;  
      
    // 读事件回调函数  
    void onRead(int iCliFd, short iEvent, void *arg)  
    {  
        int iLen;  
        char buf[1500]; 
      
        iLen = recv(iCliFd, buf, 1500, 0); 
      
        if (iLen <= 0) { 
            cout << "Client Close" << endl; 
      
            // 连接结束(=0)或连接错误(<0)，将事件删除并释放内存空间  
            struct event *pEvRead = (struct event*)arg;  
            event_del(pEvRead);  
            delete pEvRead;  
      
            close(iCliFd);  
            return;  
        }  
      
        buf[iLen] = 0;  
        cout << "Client Info:" << buf << endl;
		char d[] = "hello";
		iLen = send(iCliFd,d,strlen(d),NULL);
		if (iLen <= 0) {  
            cout << "Send error" << endl;
		}
    }  
      
    // 连接请求事件回调函数  
    void onAccept(int iSvrFd, short iEvent, void *arg)  
    {  
        int iCliFd;  
        struct sockaddr_in sCliAddr;  
      
        socklen_t iSinSize = sizeof(sCliAddr);  
        iCliFd = accept(iSvrFd, (struct sockaddr*)&sCliAddr, &iSinSize);  
      
        // 连接注册为新事件 (EV_PERSIST为事件触发后不默认删除)  
        struct event *pEvRead = new event;  
        event_set(pEvRead, iCliFd, EV_READ|EV_PERSIST, onRead, pEvRead);  
        event_base_set(base, pEvRead);  
        event_add(pEvRead, NULL);  
    }

	void libevent_test(void) {
		int iSvrFd;    
        struct sockaddr_in sSvrAddr;  
                    
        memset(&sSvrAddr, 0, sizeof(sSvrAddr));    
        sSvrAddr.sin_family = AF_INET;    
        sSvrAddr.sin_addr.s_addr = inet_addr("10.11.146.219");      
        sSvrAddr.sin_port = htons(8005);     
                                  
        // 创建tcpSocket（iSvrFd），监听本机8888端口    
        iSvrFd = socket(AF_INET, SOCK_STREAM, 0);    
        bind(iSvrFd, (struct sockaddr*)&sSvrAddr, sizeof(sSvrAddr));    
        listen(iSvrFd, 10);  
      
        // 初始化base  
        base = event_base_new();  
          
        struct event evListen;  
        // 设置事件  
        event_set(&evListen, iSvrFd, EV_READ|EV_WRITE|EV_PERSIST, onAccept, NULL);  
        // 设置为base事件  
        event_base_set(base, &evListen);  
        // 添加事件  
        event_add(&evListen, NULL);  
          
        // 事件循环  
        event_base_dispatch(base);
		
		
		
	}

/**********time_operation***********/ //END

/**********exec_cmd***********/
void exec_cmd(void) {
	std::string cmd ;
	cmd = "ls ";
	cmd += "/";
	std::cout << "result: " << system(cmd.c_str());
	std::ostringstream cmd1;
	cmd1 << "cp" << " test.txt" << " test.bak";
	std::cout << "result1: " << system(cmd1.str().c_str());
	
}

/**********time_operation***********/ //END
/**********my_list_test***********/ 
// template <class T>
// class mList {
// 	public:
// 		explicit mList(){
// 			
// 		}
// 	
// }
// 
// void my_list_test(void) {
// 	
// 	
// 	
// 	
// }
/**********my_list_test***********/ //END
/**********max_min_deap_test***********/
 #define LEFT(i) ((i)<<1|1)
#define RIGHT(i) (LEFT(i) + 1)
#define PARENTS(i) ((i)/2)

void swap(int d[], int a, int b) {
	int tmp;
	tmp = d[a];
	d[a] = d[b];
	d[b] = tmp;
	
}

// 最大堆
void max_heapfy(int *a, int i, int size)
{
 int larg;
 int left = LEFT(i);
 int right = RIGHT(i);

 if (left < size && a[left] > a[i]) 
  larg = left;
 else
  larg = i;

 if (right < size && a[right] > a[larg])
  larg = right;

 if (larg != i) {
  swap(a, i, larg);
  max_heapfy(a, larg, size);
 }
}

void max_heapfy_loop(int *a, int i, int size)
{
 int larg;
 int left = LEFT(i);
 int right = RIGHT(i);

 if (left < size && a[left] > a[i]) 
  larg = left;
 else
  larg = i;

 if (right < size && a[right] > a[larg])
  larg = right;

 while (larg != i) {
  swap(a, i, larg);
  i = larg;
  left = LEFT(larg);
  right = RIGHT(larg);

  if (left < size && a[left] > a[i]) 
   larg = left;
  else
   larg = i;

  if (right < size && a[right] > a[larg])
   larg = right;
 }
}


void build_maxheap(int *a, int len)
{
 int i;
 
 for (i = (len+1)/2-1; i>=0; i--) {
  max_heapfy(a, i, len); 
 } 
}

void heap_sort(int *a, int len)
{
 int i;
 int size = len;

 build_maxheap(a, len); 

 for (i=size-1; i>=1; i--) {
  swap(a, 0, i);
  size--;
  max_heapfy_loop(a, 0, size);
 }
}


/*
 * 最小堆
 */
void min_heapfy(int *a, int i, int size)
{
 int min;
 int left = LEFT(i);
 int right = RIGHT(i);

 if (left < size && a[left] < a[i]) 
  min = left;
 else
  min = i;

 if (right < size && a[right] < a[min])
  min = right;

 if (min != i) {
  swap(a, i, min);
  min_heapfy(a, min, size);
 }
}


void build_minheap(int *a, int len)
{
 int i;
 for (i=(len+1)/2-1; i>=0; i--) {
  min_heapfy(a, i, len);
 }
}

/* 按从小到大的顺序排序 */
void heap_sort_min(int *a, int len)
{
 int i;
 int size = len;

 //build_minheap(a, len); 
 
 for (i=size-1; i>=1; i--) {
  swap(a, 0, i);
  size--;
  min_heapfy(a, 0, size);
 }
}

 

/*
 * 最大优先队列
 */
/* 取最大值 */
int heap_maxinum(int *a, int len)
{
 return a[0];
}


/*
 * 1, 取第一个元素，就是最大值
 * 2, 把最后一个元素赋给第一个元素，把堆的大小-1，再最大化堆
 */
int  heap_extract_max(int *a, int *max, int len)
{
 int size = len;

 if (size < 1) return -1;
 *max = a[0];
 a[0] = a[size-1]; 
 size -= 1;
 max_heapfy_loop(a, 0, size); 
 return *max;
}

void printarr(int *a, int len) {
	for (int i = 0; i < len; i++) {
		
		std::cout << a[i] << " -> ";
	}
	std::cout << "\n";
}

int max_min_deap_test(void)
{
 int a[] = {10,2,45,6,6,12,22,0,3,456};
 std::cout << "orignal data: \n";
 printarr(a, sizeof(a)/sizeof(int));
 build_maxheap(a, sizeof(a)/sizeof(int));
 //build_maxheap_useloop(a, 10);
 //printarr(a, 10);
 // heap_sort(a, 10);
 std::cout << "heap_sort data: \n";
 printarr(a, sizeof(a)/sizeof(int));
 //heap_sort_min(a, 10);
 //std::cout << "heap_sort_min data: \n";
 //printarr(a, 10);
 return 0;
} 

template <class T>
class Heap {
	public:
		Heap() {
			data = new std::vector<T>;

		}
		virtual ~Heap() {
			delete data;
		}
		void set_data(const std::vector<T> &d) {
		
			for (int i = 0; i < d.size(); i++) {
				(*data)[i] = d[i];
			}
		}
		void set_data(const T d[], int size) {
		
			for (int i = 0; i < size; i++) {
				data->push_back(d[i]);
			}
		}
		
		void swap(std::vector<T> *d, int index1, int index2) {
			T temp;
			temp = d->at(index1);
			(*d)[index1] = d->at(index2);
			(*d)[index2] = temp;
		}
		
		void creat_max_heap(void) {
			int size = data->size();
			for (int i = (size+1)/2-1; i >= 0; --i) { // (size-2)/2
				max_heap(data, i, size);
			}
			//for (int i = (size-2)/2; i >= 0; --i) { // (size-2)/2
			//	max_heap(data, i, size);
			//}
			
		}
		void print_data(void) {
			std::cout <<  "data:\n";
			for (int i = 0; i < data->size(); i++) {
				std::cout << data->at(i);
				if (i != data->size()-1) 
					std::cout << " -> ";
			}
			std::cout <<  "\n";
		}
	private:
		std::vector<T> *data;
		
		void max_heap(std::vector<T> *d, int index, int size) {
			int i = index;
			T d_index = d->at(index);
			int left_child = i*2+1;
			int right_child = i*2+2;
			int max = left_child;
			if (left_child > size || right_child > size) {
				return;
			}
			while(left_child < size) {
				if (right_child < size) {
					if (d->at(right_child) > d->at(left_child)) {
						max = right_child;
					}
				} 
				
				if (i == 4) {
					std::cout << "p: " << (*d)[i] << " left: " << (*d)[i*2+1] << "\n";
 				}
				if (d->at(max) < d->at(i)) {
					max = i;
				} 
				if (max != i) {
					swap(d, max, i);
					i = max;
					
					left_child = i*2+1;
					right_child = i*2+2;
					max = left_child;
				}
				else {
					
					break;
				}
				
			}
			//(*d)[i] = d_index;
		}
	
};

void class_heap_test(void) {
	Heap<int> heap_test;
	int data[] = {10,2,45,6,6,12,22,0,3,456};
	heap_test.set_data(data, sizeof(data)/sizeof(int));
	heap_test.creat_max_heap();
	heap_test.print_data();
	
}

/**********max_min_deap_test***********/ //END

namespace check_string_char_type {
/**********check_string_char_type***********/
#define CHAR_TYPE  1
#define NUMBER_TYPE  2
#define CHARACTER_TYPE  4

int check_string_char_type(const std::string str) {
	int check_result = 0;
	if (str.size() == 0) {
		return check_result;
	}
	std::cout << str << "\n";
	for (int pos = 0; pos < str.size();) {
		unsigned char key = str[pos];
		
		if (key&0X80) {
			check_result |= CHARACTER_TYPE;
			pos += 3;
		} else if (key >= '0' && key <= '9') {
			check_result |= NUMBER_TYPE;
			pos++;
		} else if((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
			check_result |= CHAR_TYPE;
			pos++;
		} else {
			pos++;
			std::cout << pos << " key: " << key << " ";
		}
		
		if (pos > str.size()-1) {
			break;
		}
		
	}
	return check_result;
}
void check_string_char_type_test(void) {
	std::string str = "你好呀";
	for (int i = 0; i < str.size(); i++) {
		char ch = str[i];
		printf("0x%x ", ch);
		
	}
	std::cout << "\nnext:";
	
	std::cout << "check result: " << check_string_char_type(str) << "\n";
	
}
/**********max_min_deap_test***********/ //END
}
/**********trie_tree_test***********/ 
template <class T1, class T2>
class TrieTreeNode {
	public:
		TrieTreeNode() {
			// children.set_empty_key('\0');
		};
		virtual~TrieTreeNode() {
			// std::map< T1, TrieTreeNode * >::iterator it;
			// for (it = children.begin(); it != children.end(); ++it) {
			// 	delete it->second;
			// }
			children.clear();
		};
	public:	
		typedef std::map<T1, TrieTreeNode *> Map;
		Map children;
		T2 value;
};


/**********trie_tree_test***********/ //END

/**********shfit_test***********/
void shfit_test(void) {
	char c1 = 0X01;
	char c2 = 0X0A;
	char c3 = 0X0d; //
	int va = ((unsigned char)c1);
	//|| ((unsigned char)c2 << 8) || ((unsigned char)c3 << 8);
	va = va << 8 | (unsigned char)c2;
	//va = va << 8 ||(unsigned char)c3;
	
	std::cout << "va= " << std::hex << va << "\n";
	
	
}

/**********shfit_test***********/ //END

/**********test***********/
void test(void) {
	int8_t v = 0x0f;
	
	std::cout.flags ( std::ios::right | std::ios::dec | std::ios::showbase ); 
	std::cout <<  "\nv: " << std::dec << v << "\n";
	std::cout << std::hex << -100 << "\n";
	std::cout.setf(std::ios::dec);
	std::cout << std::dec << v << "\n";
	if ( 1)
		printf("v: %d\n", v);
	
	
}

/**********test***********/ //END

int main(int argc, char **argv) {
	// count_max_thread_test();
	// ofstream_put_out();
	// vector_dynamic_operation();
	 // time_operation();
	// exec_cmd();
	// libevent_test();
	// max_min_deap_test();
	// class_heap_test();
	// check_string_char_type_test();
	// test();
	// struct_destructor_test();
	shfit_test();
    return 0;
}
