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

namespace heapsort {
	template<class Type>
	class HeapSort {
		private:
			int get_left(int i) {
				
				return 2*i+1;
			}
			int get_right(int i) {
				
				return 2*i+2;
			}
			void value_swap(Type &a, Type &b) {
				Type tmp;
				tmp = a;
				a = b;
				b = tmp;
			}
			void max_heapify(std::vector<Type> &values, int k, int len);
			void min_heapify(std::vector<Type> &values, int k, int len);
			void max_build(std::vector<Type> &values, int len);
			void min_build(std::vector<Type> &values, int len);
		public:
			void heap_sort_max(std::vector<Type> &values);
			void print_result(std::vector<Type> &values,  int len);
		
	};
	
	template<class Type>
	void HeapSort<Type>::max_heapify(std::vector<Type> &values, int k, int len) {
		if (k>len || len > values.size()) {
			return;
		}
		while (k<len) {
			
			int max_index = k;
			
			int l = get_left(k);
			if (l<len && values[l]>values[k]) {
				max_index = l;
			}
			int r = get_right(k);
			if (r<len && values[r]>values[k]) {
				max_index = r;
			}
			if (k!=max_index) {
				value_swap(values[k], values[max_index]);
				k = max_index;
			} else {
				break;
			}
	
		}
		print_result(values, values.size());
		
	}
	
	template<class Type>
	void HeapSort<Type>::min_heapify(std::vector<Type> &values, int k, int len) {
		if (k>len || len > values.size()) {
			return;
		}
		while (k<len) {
			
			int min_index = k;
			
			int l = get_left(k);
			if (l<len && values[l]<values[k]) {
				min_index = l;
			}
			int r = get_right(k);
			if (r<len && values[r]<values[k]) {
				min_index = r;
			}
			if (k!=min_index) {
				value_swap(values[k], values[min_index]);
				k = min_index;
			} else {
				break;
			}
			
		}
	}
	
	template<class Type>
	void HeapSort<Type>::max_build(std::vector<Type> &values, int len) {
		if (len > values.size()) {
			return;
		}
		for (int i = (len-1)/2; i >= 0; --i) {
			max_heapify(values, i, len);
		}
 
	}
	
	template<class Type>
	void HeapSort<Type>::min_build(std::vector<Type> &values, int len) {
		if (len > values.size()) {
			return;
		}
		for (int i = (len-1)/2; i >= 0; --i) {
			min_heapify(values, i, len);
		}
	}
	
	template<class Type>
	void HeapSort<Type>::heap_sort_max(std::vector<Type> &values) {
		
		int len = values.size();
		std::cout << "len:" << len << "\n";
		max_build(values, len);
		for (int i = len-1;i>=0;i--) {
			std::cout << "i= " << i << " \n";
			
			value_swap(values[0], values[i]);
			max_build(values, i+1);
			print_result(values, values.size());
		}
		//print_result(values, len);
		
		
	}
	template<class Type>
	void HeapSort<Type>::print_result(std::vector<Type> &values, int len) {
		
		for (int i = 0; i < len;i++) {
			std::cout << values[i] << ",";
		}
		std::cout << std::endl;
	}
	
	void heap_application(void) {
		HeapSort<int> heap_sort;
		int values[] = {12,4,35,20,33,50,23,200};
		std::vector<int> valus;
		for (int i=0;i<sizeof(values)/sizeof(int);i++) {
			valus.push_back(values[i]);
		}
		heap_sort.print_result(valus, valus.size());
		heap_sort.heap_sort_max(valus);
	}
	
	
}
 

int main(int argc, char **argv) {
	
	heapsort::heap_application();
	
	
	
	
	
	
}