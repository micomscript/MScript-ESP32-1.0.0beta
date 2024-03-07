// リソース -------------------------------------------------------

#ifndef __RESOURCE_H__
#define __RESOURCE_H__

class Resource{
private:

public:
	virtual void	 print() = 0;
	virtual void	 printTree() = 0;
	virtual Value	*methodCall(char *name, List *params) = 0;
};

class WiFiRes : public Resource{
private:

public:
	WiFiRes(){
	}

	void	 print();
	void	 printTree();
	void	 printValue(char *s, Value *value);
	Value	*methodCall(char *name, List *params);

	Value	*begin(List *params);
	Value	*status();
	Value	*localIP();
	Value	*macAddress();
	Value	*subnetMask();
	Value	*gatewayIP();
	Value	*dnsIP();
	Value	*disconnect();
	Value	*toText(String s);
};

class WiFi_UDP : public AbstructObject{
private:
	uint16_t	 _localPort;
	WiFiUDP		 _udp;
	FuncName	*_func;

public:
	WiFi_UDP(){
		_localPort = 0;
		_func = NULL;
	}

	~WiFi_UDP(){
		delete _func;
	}
	
	long getInt(){
		return _localPort;
	}

	double getFloat(){
		return (double)_localPort;
	}

	bool getBool(){
		return _localPort != 0;
	}

	char *getText(){
		return getType();
	}

	char *getType(){
		return "WiFiUDP";
	}

	Value *evaluate(){
		return new WiFi_UDP();
	}

	void print();

	void printTree(int s){
		printSpace(s);
		print();
		printf("\n");
	}

	void	 confirmArrival();
	
	Value	*methodCall(char *name, List *params);

	Value	*begin(List *params);
	Value	*send(List *params);
	Value	*available(List *params);
	Value	*read(List *params);
	Value	*onReceive(List *params);
	Value	*remote_ip();
	Value	*remote_port();
	Value	*toText(String s);
};

#endif
