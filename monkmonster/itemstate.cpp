/*************************************************************************
    > File Name: itemstate.cpp
    > Created Time: Tue 02 Feb 2016 12:30:51 AM PST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<deque>
#include<vector>
#include<assert.h>
#include<map>
#include<algorithm>
using namespace std;

enum BoatLocation 
{
	LOCAL = 0,
	REMOTE,
};

enum ActionName
{
	ONE_MONSTER_GO = 0,
    TWO_MONSTER_GO,
    ONE_MONK_GO,
    TWO_MONK_GO,
    ONE_MONSTER_ONE_MONK_GO,
    ONE_MONSTER_BACK,
    TWO_MONSTER_BACK,
	ONE_MONK_BACK,
	TWO_MONK_BACK,
    ONE_MONSTER_ONE_MONK_BACK,
    INVALID_ACTION_NAME,
};

typedef struct tagActionDescription
{
	ActionName act;
	const char *description; //相应动作的人类语言描述
}ACTION_DESCRIPTION;

ACTION_DESCRIPTION actDesc[] = 
{
    { ONE_MONSTER_GO ,            "One monster go over river"              },
    { TWO_MONSTER_GO ,            "Two monster go over river"              },
    { ONE_MONK_GO ,               "One monk go over river"                 },
    { TWO_MONK_GO ,               "Two monk go over river"                 },
    { ONE_MONSTER_ONE_MONK_GO ,   "One monster and one monk go over river" },
    { ONE_MONSTER_BACK ,          "One monster go back"                    },
    { TWO_MONSTER_BACK ,          "Two monster go back"                    },
    { ONE_MONK_BACK ,             "One monk go back"                       },
    { TWO_MONK_BACK ,             "Two monk go back"                       },
    { ONE_MONSTER_ONE_MONK_BACK , "One monster and one monk go back"       }
};

typedef struct ActionEffect_s
{
	ActionName act;
	BoatLocation boat_to; //船移动的方向
	int move_monster; //此次移动的妖怪数量
	int move_monk; //此次移动的和尚数量
}ActionEffect;

ActionEffect acteffect[]=
{
	{ ONE_MONSTER_GO, REMOTE, -1, 0},
	{ TWO_MONSTER_GO, REMOTE, -2, 0},
	{ ONE_MONK_GO, REMOTE, 0, -1},
	{ TWO_MONK_GO, REMOTE, 0, -2},
	{ ONE_MONSTER_ONE_MONK_GO, REMOTE, -1, -1},

	{ ONE_MONSTER_BACK, LOCAL, 1, 0},
	{ TWO_MONSTER_BACK, LOCAL, 2, 0},
	{ ONE_MONK_BACK, LOCAL, 0, 1},
	{ TWO_MONK_BACK, LOCAL, 0, 2},
	{ ONE_MONSTER_ONE_MONK_BACK, LOCAL, 1, 1}
};


struct ItemState
{
	int local_monster;
	int local_monk;
	int remote_monster;
	int remote_monk;
	BoatLocation boat;	//local or remote
	ActionEffect curAction;
	
	ItemState(){}
	ItemState(int lms,int lm,int rms,int rm, BoatLocation location);
	bool IsSameState(ItemState nestate);
	bool IsFinalState();
	bool CanTakeAction(ActionEffect action);
	bool TakeAction(ActionEffect action, ItemState &next);
	void SetAction(ActionEffect action);
};

ItemState init_state(3,3,0,0,LOCAL);
ItemState final_state(0,0,3,3,REMOTE);

ItemState::ItemState(int lms,int lm,int rms,int rm, BoatLocation location)
{
	local_monster = lms;
	local_monk = lm;
	remote_monster = rms;
	remote_monk = rm;
	boat = location;
	ActionEffect init_action = {INVALID_ACTION_NAME,LOCAL,0,0};
	SetAction(init_action);
}

bool ItemState::IsSameState(ItemState newstate)
{
	return (local_monster == newstate.local_monster &&
		local_monk == newstate.local_monk &&
		remote_monster == newstate.remote_monster &&
		remote_monk == newstate.remote_monk &&
		boat == newstate.boat);
}

bool ItemState::IsFinalState()
{
	return IsSameState(final_state);
}

bool ItemState::CanTakeAction(ActionEffect action)	//剪枝
{
	//boat是船的当前位置，boat_to是船要移动到的方向，二者不能相同
	if(boat == action.boat_to) return false;
	if(local_monster + action.move_monster < 0 || local_monster + action.move_monster>3)
		return false;
	if(local_monk + action.move_monk < 0||local_monk + action.move_monk >3)
		return false;
	return true;
}

void ItemState::SetAction(ActionEffect action)
{
	curAction = action;
}

bool ItemState::TakeAction(ActionEffect action, ItemState &next)
{
	next.local_monster = local_monster + action.move_monster;
	next.local_monk = local_monk + action.move_monk;
	next.remote_monster = remote_monster - action.move_monster;
	next.remote_monk = remote_monk - action.move_monk;
	
	next.boat = action.boat_to;
	
	next.SetAction(action);
	if(next.local_monster > next.local_monk && next.local_monk > 0)
		return false;
	if(next.remote_monster > next.remote_monk && next.remote_monk >0)
		return false;
	return true;
}

bool IsSameState(ItemState state1, ItemState state2)
{
	return state1.IsSameState(state2);
}

bool IsProcessedState(deque<ItemState> &state,ItemState next)
{
	deque<ItemState>::iterator it = state.begin();
	it = find_if(state.begin(),state.end(),bind2nd(ptr_fun(IsSameState),next));
	return it!=state.end();
}

const char *GetActionDescription(ActionName act)
{
    int actCount = sizeof(actDesc) / sizeof(actDesc[0]);
    for(int i = 0; i < actCount; ++i)
    {
        if(actDesc[i].act == act)
        {
            return actDesc[i].description;
        }
    }
    return "Unknown action";
}

void PrintResult(deque<ItemState> &state)
{
	cout<<"RESULT:"<<endl;
	deque<ItemState>::iterator it = state.begin();
	it++;
	while( it!= state.end())
	{
		cout<<GetActionDescription(it->curAction.act)<<endl;
		it++;
	}
	cout<<endl;
}

void SearchState(deque<ItemState>& state);

void SearchStateOnAction(deque<ItemState>& state, ItemState current, ActionEffect action)
{
	if(current.CanTakeAction(action))
	{
		ItemState next;
		bool rst = current.TakeAction(action,next);
		if(rst && !IsProcessedState(state,next))
		{
			state.push_back(next);
			SearchState(state);
			state.pop_back();
		}
	}
}
void SearchState(deque<ItemState>& state)
{
	ItemState current = state.back();
	if(current.IsFinalState())
	{
		PrintResult(state);
		return;
	}
	else
	{
		for(int i=0; i< sizeof(acteffect)/sizeof(acteffect[0]); i++)
		{
			SearchStateOnAction(state, current, acteffect[i]);
		}
	}
}

int main()
{
	deque<ItemState> state;
	state.push_back(init_state);
	SearchState(state);
	return 0;
}

