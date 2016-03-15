#include "logger_base.hpp"

class SimpleLogger : protected LoggerBase {
private:
        
public:
    SimpleLogger();
    ~SimpleLogger();
    
    virtual void BeginLogging(std::ostream& destination, LogLvl level);
	virtual void Log();
    virtual void StopLogging();
};