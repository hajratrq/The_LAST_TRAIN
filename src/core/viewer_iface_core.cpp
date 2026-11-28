#include "viewer_iface.h"
#include "util.h"
#include<iostream>
#include<string>
using namespace std;

// Terminal UI and dashboard rendering using primitive parameters
void renderDashboard(int playerFloor, int playerRoom, int energy, int time, int score,
                     const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                     int emergencyTripsLeft)
                     {
                      printHeader("Player Dashboard");
                      if(playerFloor<1 || playerFloor>5)
                      {
                        cout<<"Invalid floor Number";
                        return;
                      }
                      cout<<"Player's Floor Number : "<<playerFloor<<endl;
                       if(playerRoom<1 || playerRoom>4)
                      {
                        cout<<"Invalid room Number";
                        return;
                      }
                      cout<<"Player's Room Number : "<<playerRoom<<endl;
                       if(energy<0 || energy>MAX_ENERGY)
                      {
                        cout<<"Invalid energy";
                        return;
                      }
                      cout<<"Energy : "<<energy<<endl;
                       if(time<0 || time>MAX_TIME)
                      {
                        cout<<"Invalid time";
                        return;
                      }
                      cout<<"Time : "<<time<<endl;
                      cout<<"Score : "<<score<<endl;
                       if(inventoryCount>MAX_INVENTORY_CAPACITY || inventoryCount<0)
                      {
                        cout<<"Invalid Inventory Count!!!";
                        return ;
                      }
                      cout<<"Inventory Count : "<<inventoryCount<<endl;
                      if(emergencyTripsLeft<0)
                      {
                        cout<<"Invalid emergency trips";
                        return;
                      }
                      cout<<"Emergency Trips Left : "<<emergencyTripsLeft<<endl;
                      printHeader("Inventory");
                      cout<<"Inventory : ";
                      for(int i=0 ; i<inventoryCount ; i++)
                      {
                       cout<<inventory[i]<<" ";
                      }
                      cout<<endl;
                     }

void renderRoomDetails(int floor, int room,
                       const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                       int entityCount)
                       {
                        if(floor<1 || floor>5)
                      {
                        cout<<"Invalid floor Number";
                        return;
                      }
                       if(room<1 || room>4)
                      {
                        cout<<"Invalid room Number";
                        return;
                      }
                      if(entityCount<0 || entityCount>MAX_ENTITIES_PER_ROOM)
                      {
                        cout<<"invalid entity count";
                        return;
                      }
                        cout<<"Entity Count : "<<entityCount<<endl;
                        if(entityCount==0)
                        {
                          cout<<"No entities in this room";
                        }
                        else 
                        {
                        cout<<"Room Entities : ";
                        for(int i=0 ; i<entityCount ; i++)
                        {
                            cout<<roomEntities[floor-1][room-1][i]<<" ";
                        }
                      }
                       cout<<endl;
                    }

void renderAsciiBuilding(int playerFloor, int playerRoom)
{
   if(playerFloor<1 || playerFloor>5)
                      {
                        cout<<"Invalid floor Number";
                        return;
                      }
  if(playerRoom<1 || playerRoom>4)
                      {
                        cout<<"Invalid room Number";
                        return;
                      } 
   cout<<"         Rooms"<<endl;                           
  for(int i=NUM_FLOORS ; i>=1 ; i--)
  {
    cout<<"Floor "<<i<<" : ";
    for(int j=1 ; j<=ROOMS_PER_FLOOR ; j++)
    {
     if(i==playerFloor && j==playerRoom)
      cout<<"P"<<" ";
     else
      cout<<"F"<<i<<"-R"<<j<<" ";
    }
    cout<<endl;
  }
}
void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES]){
    string objectiveNames[ ] = { "Master Key", "Clue 4" , "Clue 2" , "Clue 7" , "Cabinet Unlocked" , "Train Key" , "Fuse Collected" , "Fuse Installed" , "Lift Pass" , "Lift 2 Active" , "Passenger Rescued" , "Cat Carrier" , "Cat Secured" , "Train Prepared" , "Mission Won" , "Mission Failed" };
    for(int i=0 ; i<NUM_OBJECTIVES ; i++)
    {
      if(objectives[i]==1)
      {
        cout<<"[done] "<<objectiveNames[i]<<" "<<endl;
      }
      else
      {
        cout<<"[  ] "<<objectiveNames[i]<<" "<<endl;
      }
    }

}