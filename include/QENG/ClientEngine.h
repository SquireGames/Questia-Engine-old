#ifndef CLIENTENGINE_H
#define CLIENTENGINE_H

#include <string>
#include <functional>

class ClientEngine
{
public:
	ClientEngine();
	/* void setSettings(); */
	/* void registerState(std::string tag, std::function<State()> state); */
	int run( /* std::string stateTag */ );
private:
};

#endif // CLIENTENGINE_H
