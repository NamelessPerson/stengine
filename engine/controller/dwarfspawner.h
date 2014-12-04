#ifndef _DWARF_SPAWNER_H_
#define _DWARF_SPAWNER_H_

class DwarfSpawner : public ITickable {
	void pretick(float dt);
	void tick(float dt);
	void posttick(float dt);
};

#endif