#ifndef JOYPAD_H
#define JOYPAD_H

class Joypad;

#include "def.hh"
#include "mmu.hh"

class Joypad{
public:
	Joypad();
	void InitInternal(MMU *m_mmu);
	~Joypad();

	virtual void cycle() = 0;
protected:
	void set_buttons(uint8_t buttons);
private:
	MMU *m_mmu;
};

#endif
