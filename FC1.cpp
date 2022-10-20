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
    	inf.open("Ci.txt");
    
    	if (!inf) {
        	cout << "error\n";
    	}

    	outf.open("1gram.csv");

    		int a = 0;
		unsigned index = 0;
		std::map<unsigned short, unsigned> container;

		vector<string> SC;

    	while (getline(inf, s)) {

		//getline(inf,s);
		//const char* addr = s.c_str();
		//short *addr2 = (short*)addr;
		if (*(unsigned short*)&s[0] == 0xf5a1) {
			continue;
		}

		SC.push_back(s);

	}

	for (auto &ite : SC) {
		if (ite.size() != 1) {

			while (index < ite.size() - 2) {
				//cout<<"1\n";
				char *asc_prof = &ite[index];
				if (*(unsigned char *)asc_prof < 0x81 /*|| *(short *)(asc_prof+1) < 0x40*/) {
					index += 1;
				}

				else {
					unsigned short key = *(unsigned short*)asc_prof;
					if (container.contains(key)) {
						container[key] += 1;
					}

					else {
						container.emplace(key, (unsigned)1);
					}
					index += 2;
				}

			}
		}

		index = 0;
	}

	for (auto & ite : container) {
			unsigned short temp = ite.first;
		       	char *ptr = (char *)&temp;
			outf << ptr[0] << ptr[1] << "," << ite.second <<'\n';
	}


    	inf.close();
    	outf.close();

    	return 0;
}
