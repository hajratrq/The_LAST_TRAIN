#include "logger.h"
#include "util.h"
#include<fstream>
using namespace std;

// File persistence for savegame.txt and game_summary.txt using primitive variables
bool saveGameStateToFile(const char* filename,
                         int playerFloor, int playerRoom,
                         int energy, int time, int score,
                         const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                         const bool objectives[NUM_OBJECTIVES], int emergencyTripsLeft,
                         const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                         const int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
                         {
                          ofstream file(filename);
                          if (!file)
                            return 0;
                          else
                           {
                            file<<"Player's current floor is : "<<playerFloor<<endl;
                            file<<"Player's current room is : "<<playerRoom<<endl;
                            file<<"Player's current energy is : "<<energy<<endl;
                            file<<"Current time is : "<<time<<endl;
                            file<<"Player's current scores are : "<<score<<endl;
                            file<<"Player's current inventory count is : "<<inventoryCount<<endl;
                            file<<"Player's left emergency trips are : "<<emergencyTripsLeft<<endl;
                             for(int i=0 ; i<inventoryCount ; i++)
                             {
                              file<<inventory[i];
                              }
                              for(int i=0 ; i<NUM_OBJECTIVES ; i++)
                               {
                               objectives[i];
                               if(objectives[i]==1)
                                file<<1<<endl;
                               else
                                file<<0<<endl;
                                 }
                               for(int i=0 ; i<NUM_FLOORS ; i++ )
                              {
                              for(int j=0 ; j<ROOMS_PER_FLOOR ; j++)
                               { 
                             file<<entityCounts[i][j]<<endl;
                               }
} 
                              }
                           }

bool loadGameStateFromFile(const char* filename,
                           int& playerFloor, int& playerRoom,
                           int& energy, int& time, int& score,
                           char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                           bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft,
                           char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                           int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
                           {

                           }

void writeGameSummaryReport(const char* filename,
                            int score, int remainingEnergy, int remainingTime,
                            const bool objectives[NUM_OBJECTIVES], bool victory)
                            {

                            }