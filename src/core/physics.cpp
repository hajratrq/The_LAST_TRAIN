#include "physics.h"
#include "util.h"
#include "config.h"
// Movement validation and resource adjustments without structures
bool isDirectlyConnected(int fromF, int fromR, int toF, int toR,
                         const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                         char& outConnType)
{
outConnType=CONN_NONE;
if(fromF!=toF)
 return 0;
if(toR!=(fromR+1) && toR!=(fromR-1))
 return 0;
int floor_index=fromF-1;
int smaller_room;
if(fromR<toR)
{
   smaller_room=fromR;
}
else
smaller_room=toR;
int connection_index=smaller_room-1;
outConnType=horizontalConn[floor_index][connection_index];
if(outConnType==CONN_NONE)
return 0;
else
return 1;
}

bool canTraverse(int targetFloor, int targetRoom, char connType,
                 const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                 int emergencyTripsLeft, bool lift2Operational)
                 {
                   if(connType==CONN_DOOR)
    return true;
    else if(connType==CONN_WINDOW)
    return true;
    else if(connType==CONN_LOCKED_DOOR)
    {
    if(hasItem(inventory,inventoryCount, ENT_MASTER_KEY)==1)
    return true;
    else
    return false;
    }
    else if(connType==CONN_SOLID_WALL)
    return false;
    else 
    return false;
                 }

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime)
{
  energy+=deltaEnergy;
  time+=deltaTime;
}
void applyScoreDelta(int& score, int deltaScore)
{
  score+=deltaScore;
}
 bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol)
{
 for(int i=0 ; i<inventoryCount ; i++)
  {
    if(inventory[i]==itemSymbol)
    return true;
  }
return false;
}
bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol)
{
    if(inventoryCount==MAX_INVENTORY_CAPACITY)
    return false;
    else
    {
    inventory[inventoryCount]=itemSymbol;
    inventoryCount+=1;
    return true;
    }
}
bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol)
{
    for(int i=0 ; i<inventoryCount ; i++)
    {
        if(inventory[i]==itemSymbol)
        {
            for(int j=i ; j<(inventoryCount-1) ; j++)
            {
                inventory[j]=inventory[j+1];
            }
            inventoryCount-=1;
            return true;
        }
    }
    return false;
}