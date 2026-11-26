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
                      cout<<"Player's Floor Number : "<<playerFloor<<endl;
                      cout<<"Player's Room Number : "<<playerRoom<<endl;
                      cout<<"Energy : "<<energy<<endl;
                      cout<<"Time : "<<time<<endl;
                      cout<<"Score : "<<score<<endl;
                      cout<<"Inventory Count : "<<inventoryCount<<endl;
                      cout<<"Emergency Trips Left : "<<emergencyTripsLeft<<endl;
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
                        cout<<"Entity Count : "<<entityCount<<endl;
                        cout<<"Room Entities : ";
                        for(int i=0 ; i<entityCount ; i++)
                        {
                            cout<<roomEntities[floor-1][room-1][i]<<" ";
                        }
                        cout<<endl;
                       }

void renderAsciiBuilding(int playerFloor, int playerRoom)
{
  for(int i=1 ; i<=NUM_FLOORS ; i++)
  {
    for(int j=1 ; j<=ROOMS_PER_FLOOR ; j++)
    {
     if(i==playerFloor && j==playerRoom)
     cout<<"P"<<" ";
     else
     cout<<j<<" ";
    }
    cout<<endl;
  }
}
void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES]){
    string objectiveNames[ ] = { "Master Key", "Clue 4" , "Clue 2" , "clue 7" , "Cabinet Unlocked" , "Train Key" , "Fuse Collected" , "Fuse Installed" , "Lift Pass" , "Lift 2 Active" , "Passenger Rescued" , "Cat Carrier" , "Cat Secured" , "Train Prepared" , "Mission Won" , "Mission Failed" };
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