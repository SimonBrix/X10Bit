#pragma once

class X10
{
public:
	X10();
	~X10();
	void write(Data bitData);
	virtual void onRecieve(bool bit) const;
};
