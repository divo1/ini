#include <exception>
class CIniException : public std::exception {
	private:
		const char* msg;
	public:
		CIniException(const char *m) throw() : std::exception() {
			this->msg = m;
		}
		virtual const char* what() const throw() {
			return this->msg;
		}
};