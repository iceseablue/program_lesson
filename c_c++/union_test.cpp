#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <memory.h>
#include <string.h> 
#include <arpa/inet.h>
#include <fstream> 
#include <stdlib.h>

#define arg_len  11
#define buf_len  21
#define BUFF_LEN  30


std::vector<std::string> usb_flash_iserial_white_list;
std::vector<std::string> server_mac_white_list;

int parse_config_file(int argc, char **argv) {
	
	char buff[BUFF_LEN];
	if (argc >= 2) {
		std::ifstream config_file;
		config_file.open(argv[1],  std::ifstream::in);
		if (!config_file.is_open()) {
			std::cout << "Open the file failure :" << argv[1];
		}
		while (config_file.getline(buff,BUFF_LEN)) {
			if (strstr(buff,"[usb flash white list]") != NULL) {
				std::cout << buff << std::endl;
				memset(buff,'\0', BUFF_LEN);
				std::string iserial_number;
				while (config_file.getline(buff,BUFF_LEN)) {
					std::cout << buff << std::endl;
					if (strstr(buff,"[end]") != NULL) {
						break;
					} else {
						iserial_number.append(buff);
						usb_flash_iserial_white_list.push_back(iserial_number);
						iserial_number.clear();
						memset(buff,'\0', BUFF_LEN);
					}
				}
			} else if (strstr(buff,"[server MAC white list]") != NULL){
				memset(buff,'\0', BUFF_LEN);
				std::string mac;
				while (config_file.getline(buff,BUFF_LEN)) {
					if (strstr(buff,"[end]") != NULL) {
						break;
					} else {
						mac.append(buff);
						server_mac_white_list.push_back(mac);
						mac.clear();
						memset(buff,'\0', BUFF_LEN);
					}
				}
				
			}
		}
		for (int i = 0; i < usb_flash_iserial_white_list.size(); i++) {
			std::cout << i <<" :[" << usb_flash_iserial_white_list[i] << ']' << std::endl;
		}
		for (int i = 0; i < server_mac_white_list.size(); i++) {
			std::cout << i <<" :[" << server_mac_white_list[i] << ']' << std::endl;
		}
	} else {
		std::cout << "please input usb flash white list file!\n";
		exit(1);
	}
}


int find_string_in_vector(const std::vector<std::string> &str_list,
						  const std::string &value) {
	if (str_list.size() == 0) {
		return -1;
	}
	for (int i = 0; i < str_list.size(); i++) {
		if (str_list[i].compare(value) == 0) {
			return i;
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	#pragma pack (1)
	struct Data {
		int id;
		unsigned char mod;
		int len;
		char arg[11];
		unsigned char end;
	}data;
	#pragma pack ()
	printf("sizeof(struct Data): %d\n",sizeof(struct Data));
	
	#pragma pack (1)
	union dataBuf {
		unsigned char send_buf[21];
		struct Data user_data;
	}datab_uf;
	#pragma pack ()
	printf("sizeof(union dataBuf ): %d\n",sizeof(union dataBuf));
	
	data.id = htonl(0XAABBCCDD);
	data.mod = 't';
	data.len = htonl(255);
	//data.arg = {"this a Ta!"};
	memset(datab_uf.send_buf, '0', 21);
	strcpy(data.arg, "tabcdefghi");
	data.end = 0xFF;
	
	unsigned char *ch_buf;
	ch_buf = (unsigned char *)&data;
	//ch_buf = static_cast<unsigned char *> (data);
	char *s = "tabcdefghi";
	printf("str:\n");
	for (int i = 0; i < strlen(s); i++) {
		printf(" 0x%x", s[i]);
	}
	std::cout << std::endl;
	
	datab_uf.user_data = data;
	printf("datab_uf.send_buf:\n");
	for (int i = 0; i < 21; i++) {
		printf(" 0x%x", datab_uf.send_buf[i]);
	}
	std::cout << std::endl;
	
	printf("ch_buf:\n");
	for (int i = 0; i < 21; i++) {
		printf(" 0x%x", ch_buf[i]);
	}
	std::cout << std::endl;
	
	parse_config_file(argc, argv);
	
	std::cout << "\nfing result: " << find_string_in_vector(usb_flash_iserial_white_list, std::string(argv[2])) 
				<< std::endl;
	
	char buff[30] = {'\0'}; //{"SK",0x01,0x0C,"00197D721E07001636D69799"};
	sprintf(buff, "%s%c%c%c%s","SK",0x01,0x0C,0X02, "00197D721E07001636D69799");
	printf("type:%x  Len: %x MAC_size: 0x%x\n", buff[2],buff[3], buff[4]);
	std::vector<std::string> keys;
	std::cout << "buff:[" << buff  << "]\n";
	for (int i = 0; i < buff[4]; i++) {
		keys.push_back(std::string(buff+5+i*12, 12));
		std::cout << i << ":[" << keys[i] << "]\n";
	}
	//std::cout << 0 << ":[" << keys[0] << "]\n";
	//std::cout << 1 << ":[" << keys[1] << "]\n";
	// 00197D721E07001636D69799
	return 0;
}