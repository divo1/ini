#include <exception>

using namespace std;

class CIniException : public exception {
	private:
		const char* msg;
	public:
		CIniException(const char *m) throw() : exception() {
			this->msg = m;
		}
		virtual const char* what() const throw() {
			return this->msg;
		}
};