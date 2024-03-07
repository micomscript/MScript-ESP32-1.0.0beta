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

/*
 *	ESPFunction.h
 */

#ifndef __ESPFUNCTION_H__
#define __ESPFUNCTION_H__

//-------------------------------------------------------------------
class SetColor : public AbstructFunction {
public:
	SetColor(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};


class TextSize : public AbstructFunction {
public:
	TextSize(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

//描画系-------------------------------------------------------------
class ClearScreen : public AbstructFunction {
public:
	ClearScreen(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

class FillScreen : public AbstructFunction {
public:
	FillScreen(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class DrawLine : public AbstructFunction {
public:
	DrawLine(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class DrawPixel : public AbstructFunction {
public:
	DrawPixel(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

class DrawString :public AbstructFunction {
public:
	DrawString(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

class DrawRect : public AbstructFunction {
public:
	DrawRect(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

class FillRect : public AbstructFunction {
public:
	FillRect(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

class DrawCircle : public AbstructFunction {
public:
	DrawCircle(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

class FillCircle : public AbstructFunction {
public:
	FillCircle(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class DrawTriangle : public AbstructFunction {
public:
	DrawTriangle(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class FillTriangle : public AbstructFunction {
public:
	FillTriangle(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class DrawFastVLine : public AbstructFunction {
public:
	DrawFastVLine(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class DrawFastHLine : public AbstructFunction {
public:
	DrawFastHLine(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class DrawEllipse : public AbstructFunction {
public:
	DrawEllipse(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class FillEllipse : public AbstructFunction {
public:
	FillEllipse(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class DrawRoundRect : public AbstructFunction {
public:
	DrawRoundRect(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class FillRoundRect : public AbstructFunction {
public:
	FillRoundRect(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class DrawCircleHelper : public AbstructFunction {
public:
	DrawCircleHelper(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
class FillCircleHelper : public AbstructFunction {
public:
	FillCircleHelper(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};
//GPIO関係-----------------------------------------------------------------------------------------
class PinMode : public AbstructFunction {
public:
	PinMode(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

class DigitalWrite : public AbstructFunction {
public:
	DigitalWrite(char *name) : AbstructFunction(name) {}

	Value *evaluate();
};

class AnalogRead :  public AbstructFunction {
public:
	AnalogRead(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class DigitalRead :  public AbstructFunction {
public:
	DigitalRead(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};
//-------------------------------------------------------------------------------------------------
/*class Buzzer :  public AbstructFunction {
public:
	Buzzer(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class StopBuzzer :  public AbstructFunction {
public:
	StopBuzzer(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};*/

class LedcSetup :  public AbstructFunction {
public:
	LedcSetup(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class LedcAttachPin :  public AbstructFunction {
public:
	LedcAttachPin(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class LedcDetachPin :  public AbstructFunction {
public:
	LedcDetachPin(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class LedcWrite :  public AbstructFunction {
public:
	LedcWrite(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class LedcWriteTone :  public AbstructFunction {
public:
	LedcWriteTone(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class LedcRead :  public AbstructFunction {
public:
	LedcRead(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};

class LedcReadFreq :  public AbstructFunction {
public:
	LedcReadFreq(char *name) : AbstructFunction(name){}

	Value *evaluate(); 
};
//-------------------------------------------------------------------------------------------------
// オブジェクト生成クラス

class AbstructObject : public Value{
public:
	void	add(Value *val) {}
	void	sub(Value *val) {}
	void	mul(Value *val) {}
	void	div(Value *val) {}
	void	mod(Value *val) {}
	void	power(Value *val) {}
	void	increment(bool ch) {}
	void	decrement(bool ch) {}
	void	minus() {}
	void	printTree(int s);
	// Implement next method:
	// getInt(), getFloat(), getText(), getBool(), getType()
	// evaluate(), print()
};

class ObjNode {
public:
	Value	*_obj;
	ObjNode	*_next;

	ObjNode(Value *obj, ObjNode *next){
		_obj = obj;
		_next = next;
	}
};

class ObjList {
public:
	ObjNode	*_top;

	ObjList(){
		_top = NULL;
	}

	virtual ~ObjList(){
		clearNodes();
	}

	void	 clearNodes();
	ObjNode	*search(Value *obj);
	void	 add(Value *obj);
	void	 remove(Value *obj);
};

class ButtonList : public ObjList {
public:
	void scan();
};

class TimerList : public ObjList {
public:
	void dispatch();
};

class Output : public AbstructObject{
private:
	uint8_t			_pin;
	uint8_t			_state;

public:
	Output(uint8_t pin, uint8_t state = 0){
		_pin = pin;
		_state = state;
		pinMode(_pin, OUTPUT);
		digitalWrite(_pin, _state);
	}

	long getInt(){
		return _state;
	}

	double getFloat(){
		return (double)_state;
	}

	bool getBool(){
		return _state != 0;
	}
	
	char	*getText();
	char	*getType();
	Value	*evaluate();
	void	 print();
	Value	*methodCall(char *name, List *params);

	void high(){
		_state = 1;
		digitalWrite(_pin, _state);
	}

	void low(){
		_state = 0;
		digitalWrite(_pin, _state);
	}

	void toggle(){
		_state = 1 - _state;
		digitalWrite(_pin, _state);
	}

	uint8_t status(){
		return _state;
	}
};

class OutputGen : public AbstructFunction {
public:
	OutputGen(char *name) : AbstructFunction(name){}

	Value *evaluate();
};

class Button : public AbstructObject{
private:
	uint8_t			_pin;
	FuncName		*_fOnPress;
	FuncName		*_fOnRelease;
	uint8_t			_state;

public:
	Button(uint8_t	pin);
	~Button();
	void	onPress(char *fname);
	void	onRelease(char *fname);
	void	scan();
	void	clear();

	long getInt(){
		return _state;
	}

	double getFloat(){
		return (double)_state;
	}

	bool getBool(){
		return _state != 0;
	}
	
	char	*getText();
	char	*getType();
	Value	*evaluate();
	void	 print();
	Value	*methodCall(char *name, List *params);
};

class ButtonGen : public AbstructFunction {
public:
	ButtonGen(char *name) : AbstructFunction(name){}

	Value *evaluate();
};

class Timer : public AbstructObject{
private:
	FuncName		*_func;
	unsigned long	_lastMils;
	unsigned long	_interval;
	unsigned long	_count;
	bool			_isRunning;

public:
	Timer();
	Timer(unsigned long interval, unsigned long count);
	~Timer(){
		delete _func;
	}
	void	dispatch();
	bool	isRunning();
	
	long getInt(){
		return 0;
	}
	double getFloat(){
		return 0.0;
	}
	bool getBool(){
		return false;
	}
	
	char	*getText();
	char	*getType();
	Value	*evaluate();
	void	 print();
	Value	*methodCall(char *name, List *params);
};

class TimerGen : public AbstructFunction {
public:
	TimerGen(char *name) : AbstructFunction(name){}

	Value *evaluate();
};

class AM2320Obj : public AbstructObject{
private:
	Adafruit_AM2320	_am2320;

public:
	AM2320Obj(){
		_am2320 = Adafruit_AM2320();
	}

	void begin();

	char	*getType(){
		return "AM2320";
	}

	long getInt(){
		return 0;
	}

	double getFloat(){
		return 0.0;
	}

	bool getBool(){
		return false;
	}
	
	char	*getText(){
		return NULL;
	}
	
	Value	*evaluate();

	void	 print();
	Value	*methodCall(char *name, List *params);
};

class AM2320Gen : public AbstructFunction {
public:
	AM2320Gen(char *name) : AbstructFunction(name){}

	Value *evaluate();
};

class Speaker : public AbstructObject{
private:
	uint8_t		_pin;
	uint8_t		_channel;

public:
	Speaker(uint8_t pin, uint8_t ch);

	char	*getType(){
		return "Speaker";
	}

	long getInt(){
		return _pin;
	}

	double getFloat(){
		return (float)_pin;
	}

	bool getBool(){
		return false;
	}
	
	char	*getText(){
		return NULL;
	}
	
	Value	*evaluate();

	void	 print();
	Value	*methodCall(char *name, List *params);
};

class SpeakerGen : public AbstructFunction {
public:
	SpeakerGen(char *name) : AbstructFunction(name){}

	Value *evaluate();
};

#endif
