#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
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

    	outf.open("test.txt");

	getline(inf, s);

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
		cout << i << " "<< end << "\n";
	}

	for (int i = 0; i < s.size(); i+=2) {
		cout<<hex<<*(unsigned short*)&s[i]<<" ";
	}

    		int a = 0;
		unsigned index = 0;
		std::map<unsigned short, unsigned> container;

    	/*while (getline(inf, s) && a == 0) {

		//getline(inf,s);
		//const char* addr = s.c_str();
		//short *addr2 = (short*)addr;

		while (index <= s.size() - 2 && s.size() != 1) {
				//cout<<"1\n";
				unsigned short key = *(unsigned short *)(&s[index]);
				cout << hex << key << "\n";
				char *temp = (char *)&key;
				cout << (int)*temp << (int)*(temp+1) <<"\n";
				if (container.contains(key)) {
					container[key] += 1;
				}
				else {
					container.emplace(key, (unsigned)1);
				}

				index += 2;	
		}

		index = 0;

		for (auto & ite : container) {
			unsigned short temp = ite.first;
		       	char *ptr = (char *)&temp;
			outf << ptr[0] << ptr[1] << "," << ite.second <<'\n';
		}
		
		++a;
		//cout<< s.size() << "  "<< (s[0] == ' ')<<"\n";
 	        //cout << s << endl;
    	}*/

    	inf.close();
    	outf.close();

    	return 0;
}
