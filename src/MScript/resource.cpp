////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Begin license text.

Copyright 2023- MicomScript Project

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
associated documentation files (the �gSoftware�h), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED �gAS IS�h, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.

End license text.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>
#include "common.h"
#include "lock.h"
#include "expression.h"
#include "logic.h"
#include "varmap.h"
#include "sentence.h"
#include "function.h"
#include "function_m.h"
#include "resource.h"

WiFiRes		_wifi;


// ---------------------------------------------------------
// Resource用メソッドコール

ResMethodCall::ResMethodCall(int res_id, char *mname){
	_resID = res_id;
	_methodName = new char[strlen(mname)+1];
	strcpy(_methodName, mname);
}

ResMethodCall::~ResMethodCall(){
#ifdef DEBUG
	printf("delete ResMethodCall...%d.%s()\n", _resID, _methodName);
#endif
	delete [] _methodName;
	_eList.clear();
}

void ResMethodCall::addParam(Expression *e) {
	_eList.append(e);
}

void ResMethodCall::print() {
	if (_resID == R_WiFi){
		printf("WiFi.");
	} else {
		printf("???.");
	}
	printf("%s(", _methodName);
	_eList.print();
	printf(")");
}

void ResMethodCall::printTree(int depth) {
	printSpace(depth);
	print();
	printf(")\n");
}

Value *ResMethodCall::evaluate() {
	Resource *res;

	if(_resID == R_WiFi){
		res = &_wifi;
	} else {
		printf("Unknown Resource\n");
		return new Integer(0);
	}

	// 引数式→Value
	List *params = new List();
	Expression *e;
	for(e = _eList.top() ; e ; e = _eList.next()){
		params->append(e->evaluate());
	}

	Value *v = res->methodCall(_methodName, params);
	delete params;

	if (v)
		return v;
	return new Integer(0);
}

// WiFiRess:: ----------------------------------------------

void WiFiRes::print(){
	printf("WiFi\n");
	printValue("status", status());
	printValue("local IP address", localIP());
	printValue("subnet mask", subnetMask());
	printValue("gateway IP address", gatewayIP());
	printValue("DNS server", dnsIP());
}

void WiFiRes::printTree(){
	printf("WiFi\n");
}

void WiFiRes::printValue(char *s, Value *value){
	if (value){
		printf("  %s: ", s);
		value->print();
		printf("\n");
		delete value;
	}
}

Value *WiFiRes::methodCall(char *name, List *params){
//	printf("Wifi.%s()\n", name);
	if (strcmp(name, "begin") == 0){
		return begin(params);
	} else if (strcmp(name, "status") == 0){
		return status();
	} else if (strcmp(name, "localIP") == 0){
		return localIP();
	} else if (strcmp(name, "dnsIP") == 0){
		return dnsIP();
	} else if (strcmp(name, "gatewayIP") == 0){
		return gatewayIP();
	} else if (strcmp(name, "subnetMask") == 0){
		return subnetMask();
	} else if (strcmp(name, "macAddress") == 0){
		return macAddress();
	} else if (strcmp(name, "disconnect") == 0){
		return disconnect();
	} else if (strcmp(name, "UDP") == 0){
		return new WiFi_UDP();
	} else if (strcmp(name, "print") == 0){
		print();
		printf("\n");
		return NULL;
	}
	printf("Unknown method name : %s\n", name);
	return NULL;
}

Value *WiFiRes::begin(List *params){
	int nParams = params->size();
	if (nParams < 2){
		printf("Parameter Error\n");
		return new Integer(0);
	}
	char *ssid = params->getElement(0)->getText();
	char *pass = params->getElement(1)->getText();
	int state = WiFi.begin(ssid, pass);
	return new Integer(state);
}

Value *WiFiRes::status(){
	int state = WiFi.status();
	if (state == WL_NO_SHIELD){
		return new Text("NO_SHIELD");
	} else if (state == WL_IDLE_STATUS){
		return new Text("IDLE_STATUS");
	} else if (state == WL_NO_SSID_AVAIL){
		return new Text("NO_SSID_AVAIL");
	} else if (state == WL_SCAN_COMPLETED){
		return new Text("SCAN_COMPLETED");
	} else if (state == WL_CONNECTED){
		return new Text("CONNECTED");
	} else if (state == WL_CONNECT_FAILED){
		return new Text("CONNECT_FAILED");
	} else if (state == WL_CONNECTION_LOST){
		return new Text("CONNECTION_LOST");
	} else if (state == WL_DISCONNECTED){
		return new Text("DISCONNECTED");
	}
	return new Text("UNKNOWN");
}

Value *WiFiRes::localIP(){
	return toText(WiFi.localIP().toString());
}

Value *WiFiRes::subnetMask(){
	return toText(WiFi.subnetMask().toString());
}

Value *WiFiRes::gatewayIP(){
	return toText(WiFi.gatewayIP().toString());
}

Value *WiFiRes::dnsIP(){
	return toText(WiFi.dnsIP().toString());
}

Value *WiFiRes::macAddress(){
	byte mac[6];
	WiFi.macAddress(mac);
	char buff[20];
	sprintf(buff, "%2X:%2X:%2X:%2X:%2X:%2X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	return new Text(buff);
}

Value *WiFiRes::disconnect(){
	bool b = WiFi.disconnect();
	return new Integer(b ? 1 : 0);
}

Value *WiFiRes::toText(String s){
	int len = s.length() + 1;
	char *t = new char[len];
	s.toCharArray(t, len);
	Value *value = new Text(t);
	delete t;
	return value;
}

Value *WiFi_UDP::methodCall(char *name, List *params){
//	printf("Wifi_UDP.%s()\n", name);
	if (strcmp(name, "begin") == 0){
		return begin(params);
	} else if (strcmp(name, "send") == 0){
		return send(params);
	} else if (strcmp(name, "available") == 0){
		return available(params);
	} else if (strcmp(name, "read") == 0){
		return read(params);
	} else if (strcmp(name, "onReceive") == 0){
		return onReceive(params);
	} else if (strcmp(name, "remoteIP") == 0){
		return remote_ip();
	} else if (strcmp(name, "remotePort") == 0){
		return remote_port();
	} else if (strcmp(name, "print") == 0){
		print();
		printf("\n");
		return NULL;
	}
	printf("WiFiUDP:: Unknown method name : %s\n", name);
	return NULL;
}

void WiFi_UDP::print(){
	printf("WiFi_UDP\n");
	printf("  local port = %d\n", _localPort);
	if (_func){
		printf("  onReceive --> ");
		_func->print();
		printf("\n");
	}
}

Value *WiFi_UDP::begin(List *params){
	int nParams = params->size();
	if (nParams == 0){
		printf("Parameter Error\n");
		return NULL;
	}
	_localPort = params->getElement(0)->getInt();
	uint8_t v = _udp.begin(_localPort);
	return new Integer(v);
}

Value *WiFi_UDP::send(List *params){
	int nParams = params->size();
	if (nParams < 3){
		printf("Parameter Error\n");
		return NULL;
	}
	char *ipaddress = params->getElement(0)->getText();
	int port = params->getElement(1)->getInt();
	char *msg = params->getElement(2)->getText();
	_udp.beginPacket(ipaddress, port);
	_udp.print(msg);
	_udp.endPacket();
	return NULL;
}

Value *WiFi_UDP::available(List *params){
	int n = _udp.parsePacket();
	return new Integer(n);
}

Value *WiFi_UDP::read(List *params){
	char buff[256];
	memset(buff, 0, 256);
	_udp.read(buff, 256);
	return new Text(buff);
}

Value *WiFi_UDP::toText(String s){
	int len = s.length() + 1;
	char *t = new char[len];
	s.toCharArray(t, len);
	Value *value = new Text(t);
	delete t;
	return value;
}

Value *WiFi_UDP::remote_ip(){
	return(toText(_udp.remoteIP().toString()));
}

Value *WiFi_UDP::remote_port(){
	return(new Integer(_udp.remotePort()));
}

void WiFi_UDP::confirmArrival(){
	if (_udp.parsePacket() > 0){
		if (_func){
			try{
				Value *v = _func->evaluate();
				delete v;
			}catch(ErrorException e){}
		}
	}
}

// WiFi UDP Observer -------------------------------------------------

class WiFi_UDPList : public ObjList {
public:
	void confirmArrival();
};

WiFi_UDPList		_udpList;
SimpleLocker		_udpList_locker;

void WiFi_UDPList::confirmArrival(){
	ObjNode *node;
	WiFi_UDP *udp;
	for(node = _top; node ; node = node->_next){
		udp = (WiFi_UDP *)node->_obj;
		udp->confirmArrival();
	}
}

void udpObserver(void *args){
	while(1){
		// 排他制御
		if (_udpList_locker.lock(100)){
			_udpList.confirmArrival();
			_udpList_locker.unlock(100);
		}
		delay(1);
	}
}

Value *WiFi_UDP::onReceive(List *params){
	int nParams = params->size();
	if (nParams == 0){
		printf("WiFiUDP::onReceive() : Parameter Error\n");
		return NULL;
	}
	char *fname = params->getElement(0)->getText();
	if (fname == NULL){
		printf("WiFi_UDP::onReceive() : handler name is required.\n");
		return NULL;
	}
	_func = new FuncName(fname);
	
	// 排他制御
	_udpList_locker.waitForUnlock(200);
	_udpList.add(this);
	_udpList_locker.unlock(200);
	
	return NULL;
}
