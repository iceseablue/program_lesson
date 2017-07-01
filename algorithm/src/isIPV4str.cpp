#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

bool isNumStr(string &str) {
	if (&str == NULL || str.size() == 0) {
		return false;
	}
	int i = 0;
	if (str[0] == '-' || str[0] == '+') {
		i++;
	}
	for(;i<str.size();i++) {
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
	}
	return true;
}

bool isIPV4Str(string &ip) {
  if (ip.size() < 7 || ip.size() > 15) {
    return false;
  }
  cout << "ip:" << ip << endl;	
	int len = ip.size();
	int seg_n = 0;
	for (int  i=0;i <ip.size();) {
		int pos = i;
		cout << "i: " << i << endl;
		while (ip[pos] != '.'&&pos < ip.size()) {
			pos++;
		}
		cout << "pos: " << pos << endl;
		seg_n++;
		if ((pos == len && seg_n  < 4)||seg_n > 4 || pos-i == 0 || pos-i > 3) {
			return false;
		}
		string seg_str = ip.substr(i, pos-i); 
		cout << "seg_str:" << seg_str << endl;
		if (!isNumStr(seg_str)) {
			return false;
		}
		int val = atoi(seg_str.c_str());
		cout << "val = " << val <<endl;
		if (val < 0 || val > 255) {
			return false;
		}
		i = pos+1;
	}
	return true;
}

int main(int argc, char *argv[]) {
	if (argc <2){
		return 1;
	}
	string ip(argv[1]);
	if (isIPV4Str(ip)){
		cout << "This string is a valid IP" << endl;
	} else {
		cout << "This string is a invalid IP" << endl;
	}
	return 0;
}


