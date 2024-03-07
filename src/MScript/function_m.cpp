////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Begin license text.

Copyright 2023- MicomScript Project

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
associated documentation files (the “Software”), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.

End license text.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include <string.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>
#include "common.h"
#include "lock.h"
#include "command.h"
#include "expression.h"
#include "logic.h"
#include "varmap.h"
#include "sentence.h"
#include "function.h"
#include "function_m.h"

extern Command	_command;

TFT_eSPI _tft = TFT_eSPI();

int _gColor = TFT_WHITE;
int _bColor = TFT_BLACK;	//文字の背景色
int textSize = 1;			//文字のサイズ
//------------------------------------------------------
extern VarMapStack _varMap;

/*　Input
Value *Input::evaluate(){
// for ESP32
	char buff[IN_BUFF_SIZE];
	_command.readLine(buff, IN_BUFF_SIZE, false);
	return new Text(buff);
}
*/


Value *SetColor::evaluate(){
	int color,back;
	color = _list -> getElement(0) -> getInt();
	if(_list->size() == 2){
		back = _list -> getElement(1) -> getInt();
		_bColor = back;
	}
	_gColor = color;
	
	_tft.setTextColor(_gColor,_bColor);
	return NULL;
}

Value *TextSize::evaluate(){
	textSize = _list -> getElement(0) -> getInt();
	_tft.setTextSize(textSize);
	return NULL;
}

Value *ClearScreen::evaluate(){
	_tft.fillScreen(_bColor);
	return NULL;
}

Value *FillScreen::evaluate(){
	_tft.fillScreen(_gColor);
	return NULL;
}

Value *DrawLine::evaluate() {
	int x1,x2,y1,y2;
	x1 = _list-> getElement(0)->getInt();
	y1 = _list-> getElement(1)->getInt();
	x2 = _list-> getElement(2)->getInt();
	y2 = _list-> getElement(3)->getInt();

	_tft.drawLine(x1,y1,x2,y2,_gColor);
	return NULL;
}

Value *DrawPixel::evaluate() {
	int x,y;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	_tft.drawPixel(x,y,_gColor);
	return NULL;
}

Value *DrawString::evaluate() {
	int x,y;
	char *str;
	str = _list->getElement(0)->getText();
	x = _list-> getElement(1)->getInt();
	y = _list-> getElement(2)->getInt();
		
	_tft.drawString(str,x,y);
	return NULL;
}

Value *DrawRect::evaluate() {
	int x,y,w,h;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	w = _list-> getElement(2)->getInt();
	h = _list-> getElement(3)->getInt();
	_tft.drawRect(x,y,w,h,_gColor);
	return NULL;
}

Value *FillRect::evaluate() {
	int x,y,w,h;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	w = _list-> getElement(2)->getInt();
	h = _list-> getElement(3)->getInt();
	_tft.fillRect(x,y,w,h,_gColor);
	return NULL;
}

Value *DrawCircle::evaluate() {
	int x,y,r;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	r = _list-> getElement(2)->getInt();
	_tft.drawCircle(x,y,r,_gColor);
	return NULL;
}

Value *FillCircle::evaluate() {
	int x,y,r;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	r = _list-> getElement(2)->getInt();
	_tft.fillCircle(x,y,r,_gColor);
	return NULL;
}

Value *DrawTriangle::evaluate() {
	int x0,y0,x1,y1,x2,y2;
	x0 = _list-> getElement(0)->getInt();
	y0 = _list-> getElement(1)->getInt();
	x1 = _list-> getElement(2)->getInt();
	y1 = _list-> getElement(3)->getInt();
	x2 = _list-> getElement(4)->getInt();
	y2 = _list-> getElement(5)->getInt();
	_tft.drawTriangle(x0,y0,x1,y1,x2,y2,_gColor);
	return NULL;
}
Value *FillTriangle::evaluate() {
	int x0,y0,x1,y1,x2,y2;
	x0 = _list-> getElement(0)->getInt();
	y0 = _list-> getElement(1)->getInt();
	x1 = _list-> getElement(2)->getInt();
	y1 = _list-> getElement(3)->getInt();
	x2 = _list-> getElement(4)->getInt();
	y2 = _list-> getElement(5)->getInt();
	_tft.fillTriangle(x0,y0,x1,y1,x2,y2,_gColor);
	return NULL;
}
Value *DrawFastVLine::evaluate(){
	int x,y,v;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	v = _list-> getElement(2)->getInt();
	_tft.drawFastVLine(x,y,v,_gColor);
	return NULL;
}

Value *DrawFastHLine::evaluate(){
	int x,y,h;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	h = _list-> getElement(2)->getInt();
	_tft.drawFastHLine(x,y,h,_gColor);
	return NULL;
}
Value *DrawEllipse::evaluate(){
	int x,y,rx,ry;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	rx = _list-> getElement(2)->getInt();
	ry = _list-> getElement(3)->getInt();
	_tft.drawEllipse(x,y,rx,ry,_gColor);
	return NULL;
}
Value *FillEllipse::evaluate(){
	int x,y,rx,ry;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	rx = _list-> getElement(2)->getInt();
	ry = _list-> getElement(3)->getInt();
	_tft.fillEllipse(x,y,rx,ry,_gColor);
	return NULL;
}
Value *DrawRoundRect::evaluate(){
	int x,y,w,h,r;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	w = _list-> getElement(2)->getInt();
	h = _list-> getElement(3)->getInt();
	r = _list-> getElement(4)->getInt();
	_tft.drawRoundRect(x,y,w,h,r,_gColor);
	return NULL;
}
Value *FillRoundRect::evaluate(){
	int x,y,w,h,r;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	w = _list-> getElement(2)->getInt();
	h = _list-> getElement(3)->getInt();
	r = _list-> getElement(4)->getInt();
	_tft.fillRoundRect(x,y,w,h,r,_gColor);
	return NULL;
}
Value *DrawCircleHelper::evaluate(){
	int x,y,r,c;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	r = _list-> getElement(2)->getInt();
	c = _list-> getElement(3)->getInt();
	_tft.drawCircleHelper(x,y,r,c,_gColor);
	return NULL;
}
Value *FillCircleHelper::evaluate(){
	int x,y,r,c,d;
	x = _list-> getElement(0)->getInt();
	y = _list-> getElement(1)->getInt();
	r = _list-> getElement(2)->getInt();
	c = _list-> getElement(3)->getInt();
	d = _list-> getElement(4)->getInt();
	_tft.fillCircleHelper(x,y,r,c,d,_gColor);
	return NULL;
}
//GPIO関数----------------------------------------
Value *PinMode::evaluate(){
	int pin,io;
	pin = _list->getElement(0)->getInt();
	io = _list->getElement(1)->getInt();
	if(io==0){
		pinMode(pin,OUTPUT);
	}else if(io==1){
		pinMode(pin,INPUT);
	}else if(io==2){
		pinMode(pin,INPUT_PULLUP);
	}else{
		printf("エラー\n");
	}
	
	return NULL;
}

Value *DigitalWrite::evaluate(){
	int pin,HL;
	pin = _list-> getElement(0)->getInt();
	HL = _list-> getElement(1)->getInt();
	if(HL == 0){
		digitalWrite(pin,LOW);
	}else if(HL == 1){
		digitalWrite(pin,HIGH);
	}else{
		printf("エラー：HIGHは1、LOWは0\n");
	}
	return NULL;
}

Value *AnalogRead::evaluate(){
	int pin;
	pin = _list-> getElement(0) ->getInt();
	int analogValue = analogRead(pin);
	return new Integer(analogValue);
}

Value *DigitalRead::evaluate(){
	int pin;
	pin = _list-> getElement(0) ->getInt();
	int digitalValue = digitalRead(pin);
	return new Integer(digitalValue);
}
//--------------------------------------------------
/*Value *Buzzer::evaluate(){
	int pin;
	unsigned int tones;
	pin = _list-> getElement(0)->getInt();
	tones = _list-> getElement(1)->getInt();
	ledcSetup(1,tones,16);
	ledcAttachPin(pin,1);
	ledcWrite(1,tones);
	return NULL;
}

Value *StopBuzzer::evaluate(){
	int ch;
	ch = _list-> getElement(0)->getInt();
	ledcWrite(ch,0);
	return NULL;
}*/

Value *LedcSetup::evaluate(){
	int ch,bits;
	unsigned int freq;
	ch = _list-> getElement(0)->getInt();
	freq = _list-> getElement(1)->getInt();
	bits = _list-> getElement(2)->getInt();
	ledcSetup(ch,freq,bits);
	return NULL;
}

Value *LedcDetachPin::evaluate(){
	int pin;
	pin = _list-> getElement(0)->getInt();
	ledcDetachPin(pin);
	return NULL;
}

Value *LedcAttachPin::evaluate(){
	int ch,pin;
	pin = _list-> getElement(0)->getInt();
	ch = _list-> getElement(1)->getInt();
	ledcAttachPin(pin,ch);
	return NULL;
}

Value *LedcWrite::evaluate(){
	int ch;
	unsigned int tones;
	ch = _list-> getElement(0)->getInt();
	tones = _list-> getElement(1)->getInt();
	ledcWrite(ch,tones);
	return NULL;
}

Value *LedcWriteTone::evaluate(){
	int ch;
	unsigned int freq;
	ch = _list-> getElement(0)->getInt();
	freq = _list-> getElement(1)->getInt();
	ledcWriteTone(ch,freq);
	return NULL;
}

Value *LedcRead::evaluate(){
	int ch;
	ch = _list-> getElement(0)->getInt();
	int readDuty = ledcRead(ch);
	return new Integer(readDuty);
}

Value *LedcReadFreq::evaluate(){
	int ch;
	ch = _list-> getElement(0)->getInt();
	int readFreq = ledcReadFreq(ch);
	return new Integer(readFreq);
}
//--------------------------------------------------

void AbstructObject::printTree(int s){
	printSpace(s);
	print();
	printf("\n");
}

//--------------------------------------------------
char _high[] = "HIGH";
char _low[] = "LOW";

char *Output::getText() {
	return _state ? _high : _low;
}

char *Output::getType() {
	return "Output";
}

Value *Output::evaluate() {
	return new Output(_pin);
}

void Output::print() {
	printf("{Output(%d) state = %d}", _pin, _state);
}

Value *Output::methodCall(char *name, List *params) {
#ifdef DEBUG
	printf("Output::methodCall(%s)\n", name);
#endif
	if (strcmp(name, "high") == 0) {
		high();
		return new Integer(1);
	} else if (strcmp(name, "low") == 0) {
		low();
		return new Integer(0);
	} else if (strcmp(name, "toggle") == 0) {
		toggle();
		return new Integer(_state);
	} else if (strcmp(name, "status") == 0){
		return new Integer(_state);
	} else {
		printf("Undefined function: %s\n", name);
	}
	return NULL;
}

Value *OutputGen::evaluate() {
	int n = _list->size();
	if (n == 0){
		printf("Insufficient number of parameters\n");
		throw ErrorException();
	}
	int port = _list->getElement(0)->getInt();
	uint8_t state = 0;
	if (n >= 2){
		state = _list->getElement(1)->getInt();
	}
	return new Output(port, state);
}

//--------------------------------------------------

ButtonList		_buttonList;
TimerList		_timerlist;
SimpleLocker	_timerlist_locker;
SimpleLocker	_buttonlist_locker;

char _timerName[] = "Timer";

void buttonObserver(void *args){
	while(1){
		if (_buttonlist_locker.lock(400)){
			_buttonList.scan();
			_buttonlist_locker.unlock(400);
		}
		delay(10);
	}
}

void timeObserver(void *args){
	while(1){
		if (_timerlist_locker.lock(300)){
			_timerlist.dispatch();
			_timerlist_locker.unlock(300);
		}
		delay(1);
	}
}

void ObjList::clearNodes(){
	ObjNode *node, *next;
	for(node = _top; node ; node = next){
		next = node->_next;
		delete node;
	}
}

ObjNode *ObjList::search(Value *obj){
	ObjNode *node;
	for(node = _top; node ; node = node->_next){
		if (node->_obj == obj)
			return node;
	}
	return NULL;
}

void ObjList::add(Value *obj){
	ObjNode *node = search(obj);
	if (node == NULL){
		_top = new ObjNode(obj, _top);
	}
}

void ObjList::remove(Value *obj){
	ObjNode *node, *next, *prev;
	prev = NULL;
	for(node = _top; node ; node = next){
		next = node->_next;
		if (node->_obj == obj)
			break;
		prev = node;
	}
	if (node){
		if (node == _top){	// or if (prev == NULL)
			_top = _top->_next;
		} else {
			prev->_next = node->_next;
		}
		delete node;
	}
}

void ButtonList::scan(){
	ObjNode *node;
	Button *button;
	for(node = _top; node ; node = node->_next){
		button = (Button *)node->_obj;
		button->scan();
	}
}

Button::Button(uint8_t	pin) {
	_pin = pin;
	pinMode(_pin, INPUT_PULLUP);
	_state = digitalRead(_pin);
	_fOnPress = NULL;
	_fOnRelease = NULL;
}

Button::~Button(){
	delete _fOnPress;
	delete _fOnRelease;
}

char *Button::getText() {
	static char high[] = "HIGH";
	static char low[] = "LOW";
	return _state ? high : low;
}

char *Button::getType() {
	return "Button";
}
Value *Button::evaluate() {
	return new Button(_pin);
}

void Button::print() {
	printf("Button(%d)", _pin);
}

Value *Button::methodCall(char *name, List *params) {
#ifdef DEBUG
	printf("Button::methodCall(%s)\n", name);
#endif
	int n = params->size();
	if (strcmp(name, "onPress") == 0) {
		if (n == 0){
			onPress(NULL);
		} else {
			Value *v = params->getElement(0);
			onPress(v->getText());
		}
	} else if (strcmp(name, "onRelease") == 0){
		if (n == 0){
			onRelease(NULL);
		} else {
			Value *v = params->getElement(0);
			onRelease(v->getText());
		}
	} else {
		printf("Undefined function: %s\n", name);
	}
	return NULL;
}

void Button::onPress(char *fname) {
	if (_fOnPress){
		delete _fOnPress;
		_fOnPress = NULL;
	}
	if (fname == NULL){
		if (_fOnRelease == NULL){
			_buttonlist_locker.waitForUnlock(410);
			_buttonList.remove(this);
			_buttonlist_locker.unlock(410);
		}
	} else {
		_fOnPress = new FuncName(fname);
		_buttonlist_locker.waitForUnlock(420);
		_buttonList.add(this);
		_buttonlist_locker.unlock(420);
	}
}

void Button::onRelease(char *fname) {
	if (_fOnRelease){
		delete _fOnRelease;
		_fOnRelease = NULL;
	}
	if (fname == NULL){
		if (_fOnPress == NULL){
			_buttonlist_locker.waitForUnlock(430);
			_buttonList.remove(this);
			_buttonlist_locker.unlock(430);
		}
	} else {
		_fOnRelease = new FuncName(fname);
		_buttonlist_locker.waitForUnlock(440);
		_buttonList.add(this);
		_buttonlist_locker.unlock(440);
	}
}

void Button::scan() {
	Value *v;
	uint8_t state = digitalRead(_pin);
	if (_state == HIGH && state == LOW) {			// Press
		if (_fOnPress) {
			try{
				v = _fOnPress->evaluate();
				delete v;
			}catch(ErrorException e){}
		}
	} else if (_state == LOW && state == HIGH) {		// Release
		if (_fOnRelease) {
			try{
				v = _fOnRelease->evaluate();
				delete v;
			}catch(ErrorException e){}
		}
	}
	_state = state;
}

void Button::clear() {
	_fOnPress = NULL;
	_fOnRelease = NULL;
//	_btnlist.remove(this);
}

Value *ButtonGen::evaluate() {
	int n = _list->size();
	if (n == 0){
		printf("Insufficient number of parameters\n");
		throw ErrorException();
	}
	int port = _list->getElement(0)->getInt();
	return new Button(port);
}

//----------------------------------------------------------------

void TimerList::dispatch(){
	ObjNode *node;
	Timer *timer;
	for(node = _top; node ; node = node->_next){
		timer = (Timer *)node->_obj;
		timer->dispatch();
	}
}

Timer::Timer(){
	_func = NULL;
	_lastMils = millis();
	_interval = 0;
	_count = 0;
	_isRunning = false;
}

Timer::Timer(unsigned long interval, unsigned long count){
	_func = NULL;
	_lastMils = millis();
	_interval = interval;
	_count = count;
	_isRunning = false;
}

bool Timer::isRunning(){
	return _isRunning;
}

void Timer::dispatch(){
	if (_isRunning){
		unsigned long now = millis();
		if (now - _lastMils >= _interval){
			_lastMils = now;
			try{
				Value *v = _func->evaluate();
				delete v;
			}catch(ErrorException e){}
		}
	}
}

char *Timer::getText() {
	return _timerName;
}

char *Timer::getType() {
	return _timerName;
}

Value *Timer::evaluate() {
	return new Timer(_interval, _count);
}

void Timer::print() {
	printf("Timer: interval = %d\n", _interval);
}

Value *Timer::methodCall(char *name, List *params) {
#ifdef DEBUG
	printf("Timer::methodCall(%s)\n", name);
#endif
	int n = params->size();
	if (strcmp(name, "setTimer") == 0) {
		if (n < 2){
			printf("Insufficient number of parameters.\n");
			throw ErrorException();
		}
		char *fname = params->getElement(0)->getText();
		if (fname == NULL){
			printf("Invalid function name.\n");
			throw ErrorException();
		}
		_func = new FuncName(fname);
		_interval = params->getElement(1)->getInt();
		if (n >= 3){
			_count = params->getElement(2)->getInt();
		}
		if (_func && _interval > 0){
			_isRunning = true;
			_timerlist_locker.waitForUnlock(310);
			_timerlist.add(this);
			_timerlist_locker.unlock(310);
		} else {
			printf("Invalid parameter.\n");
		}
	} else if (strcmp(name, "stop") == 0){
		_timerlist_locker.waitForUnlock(320);
		_timerlist.remove(this);
		_timerlist_locker.unlock(320);
		_isRunning = false;
	} else if (strcmp(name, "resume") == 0){
		if (_isRunning){
			printf("Already running.\n");
			return NULL;
		}
		if (_func && _interval > 0){
			_isRunning = true;
			_timerlist_locker.waitForUnlock(330);
			_timerlist.add(this);
			_timerlist_locker.unlock(330);
		} else {
			printf("Invalid parameter.\n");
		}
	} else {
		printf("Undefined function: %s\n", name);
	}
	return NULL;
}

Value *TimerGen::evaluate() {
	return new Timer();
}

//--------------------------------------------------

void AM2320Obj::print(){
	printf("AM2320");
}

Value *AM2320Obj::methodCall(char *name, List *params) {
#ifdef DEBUG
	printf("AM2320Obj::methodCall(%s)\n", name);
#endif
	if (strcmp(name, "humidity") == 0) {
		float humid = _am2320.readHumidity();
		return new Float(humid);
	} else if (strcmp(name, "temperature") == 0) {
		float temp = _am2320.readTemperature();
		return new Float(temp);
	} else {
		printf("Undefined function: %s\n", name);
	}
	return NULL;
}

Value *AM2320Obj::evaluate(){
	return NULL;
}

void AM2320Obj::begin(){
	_am2320.begin();
}

Value *AM2320Gen::evaluate(){
	AM2320Obj *am2320 = new AM2320Obj();
	am2320->begin();
	return am2320;
}

//--------------------------------------------------

Speaker::Speaker(uint8_t pin, uint8_t ch){
	_pin = pin;
	_channel = ch;
	ledcSetup(_channel, 8192, 12);
	ledcAttachPin(_pin, _channel);
}
void Speaker::print(){
	printf("Speaker");
}

Value *Speaker::evaluate(){
	return NULL;
}

Value *Speaker::methodCall(char *name, List *params){
#ifdef DEBUG
	printf("Speaker::methodCall(%s)\n", name);
#endif
	if (strcmp(name, "tone") == 0) {
		int n = params->size();
		if (n == 0){
			printf("Invalid parameter\n");
			return NULL;
		}
		uint32_t freq = params->getElement(0)->getInt();
		ledcWriteTone(_channel, freq);
		return NULL;
	} else if (strcmp(name, "stop") == 0){
		ledcWriteTone(_channel, 0);
	} else {
		printf("Undefined function: %s\n", name);
	}
	return NULL;
}

Value *SpeakerGen::evaluate(){
	int n = _list->size();
	int pin = 21, ch = 0;
	if (n >= 1){
		pin = _list->getElement(0)->getInt();
	}
	if (n >= 2){
		ch = _list->getElement(1)->getInt();
	}
	return new Speaker(pin, ch);
}
