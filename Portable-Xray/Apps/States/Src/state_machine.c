#include <state_machine_type.h>

static state_machine_t g_state_machine;

inline void SetMainState(main_state_t mainState)
{
	g_state_machine.main_state = mainState;
}

inline uint32_t GetMainState()
{
	return g_state_machine.main_state;
}

inline void SetSubState(main_state_t subState)
{
	g_state_machine.sub_state = subState;

}

inline uint32_t GetSubState()
{
	return g_state_machine.sub_state;
}


