#include <algorithm> 
#include <list>
#include <cctype>
#include <locale>
#include <string>

using namespace std;

class utils{
public:
	utils();
	// trim from start (in place)
	static inline void ltrim(std::string &s) {
	    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
	        return !std::isspace(ch);
	    }));
	}

	// trim from end (in place)
	static inline void rtrim(std::string &s) {
	    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
	        return !std::isspace(ch);
	    }).base(), s.end());
	}

	// trim from both ends (in place)
	static inline void trim(std::string &s) {
	    ltrim(s);
	    rtrim(s);
	}

	// retorna lista de tokens
	static list <string> tokenizeStr(string txt, string delimiter){
		int n = 0, pos;
		string token;
		list <string> myList;

		while ((pos = txt.find(delimiter)) != string::npos) {
			token = txt.substr(0, pos);
			myList.push_back(token);
			txt.erase(0, pos + delimiter.length());
		}
		myList.push_back(txt);

		return myList;
	}

	~utils();
};
