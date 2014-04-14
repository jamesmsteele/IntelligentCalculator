#include <vector>
#include <string>
using namespace std;

class History{
	private:
		vector<string> history;
	public:
		History();
		void print();
		void print(int start, int end);
		void print(int start);
		void printAll();
		void add(string hist);
		string ans();
		string ans(int n);
};
