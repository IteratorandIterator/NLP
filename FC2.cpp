#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	string s;
    	ofstream outf;
    	ifstream inf;
    	inf.open("Ci1.txt");
    
    	if (!inf) {
        	cout << "error\n";
    	}

    	outf.open("2gram.csv");

    		int a = 0;
		unsigned index = 0;
		std::map<unsigned int, unsigned> container;

		vector<string> SC;

    	while (getline(inf, s)) {

		//getline(inf,s);
		//const char* addr = s.c_str();
		//short *addr2 = (short*)addr;
		++a;
		SC.push_back(s);

	int end = s.size();

	for (int i = 0; i < end;) {
		if (*(unsigned char *)(&s[i]) < 0x81) {
			s.erase(i, 1);
			//cout << "100" << '\n';
		}

		else if (*(unsigned short*)(&s[i]) == 0xaca3 || 
			*(unsigned short*)(&s[i]) == 0xa3a1 ||
				*(unsigned short*)(&s[i]) == 0xa2a1) {
			s.erase(i, 2);
		}

		else {
			i += 2;
		}
		end = s.size();
	}

	}

	for (auto &ite : SC) {
		if (ite.size() != 1) {

			while (ite.size() - index >= 4 && ite.size() >= 4) {
				//cout<<"1\n";
				unsigned int key = *(unsigned int *)(&ite[index]);
				if (container.contains(key)) {
					container[key] += 1;
				}
				else {
					container.emplace(key, (unsigned)1);
				}

				index += 4;	
			}

			if (ite.size() == 2 || (ite.size() - index < 4 /*&& index != ite.size() - 1*/)) {
				unsigned short key = *(unsigned short *)(&ite[index]);
				if (container.contains((unsigned int)key)) {
					container[(unsigned int)key] += 1;
				}
				else {
					container.emplace((unsigned int)key, (unsigned)1);
				}
			}
		}

		index = 0;
	}

	for (auto & ite : container) {
			unsigned short temp = ite.first;
		       	char *ptr = (char *)&temp;
			outf << ptr[0] << ptr[1] << ptr[2] << ptr[3] << "," << ite.second <<'\n';
	}


    	inf.close();
    	outf.close();

    	return 0;
}
