#include "logger.h"
#include "util.h"
#include<fstream>

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