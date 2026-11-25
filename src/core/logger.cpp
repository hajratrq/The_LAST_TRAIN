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
                            file<<playerFloor<<endl;
                            file<<playerRoom<<endl;
                            file<<energy<<endl;
                            file<<time<<endl;
                            file<<score<<endl;
                            file<<inventoryCount<<endl;
                            file<<emergencyTripsLeft<<endl;
                             for(int i=0 ; i<inventoryCount ; i++)
                             {
                              file<<inventory[i]<<endl;
                              }
                              for(int i=0 ; i<NUM_OBJECTIVES ; i++)
                               {
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
                              for(int i=0 ; i<NUM_FLOORS ; i++)
                              {
                             for(int j=0 ; j<ROOMS_PER_FLOOR ; j++)
                             {
                             for(int k=0 ; k<entityCounts[i][j] ; k++)
                             {
                             file<<roomEntities[i][j][k]<<endl;
                              }
                               }
                               }
                              }
                            file.close();
                            return 1;
                           }

bool loadGameStateFromFile(const char* filename,
                           int& playerFloor, int& playerRoom,
                           int& energy, int& time, int& score,
                           char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                           bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft,
                           char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                           int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
                           {
                             ifstream file(filename);
                             if (!file)
                              return 0;
                             file>>playerFloor;
                             file>>playerRoom;
                             file>>energy;
                             file>>time;
                             file>>score;
                             file>>inventoryCount;
                             if(inventoryCount>=0 && inventoryCount<=MAX_INVENTORY_CAPACITY)
                              return 0;
                             file>>emergencyTripsLeft;
                              for(int i=0 ; i<inventoryCount ; i++)
                             {
                              file>>inventory[i];
                              }
                               for(int i=0 ; i<NUM_OBJECTIVES ; i++)
                               {
                               file>>objectives[i];
                                 }
                                  for(int i=0 ; i<NUM_FLOORS ; i++ )
                              {
                              for(int j=0 ; j<ROOMS_PER_FLOOR ; j++)
                               { 
                             file>>entityCounts[i][j];
                             if(entityCounts>=0 && entityCounts<=MAX_ENTITIES_PER_ROOM)
                               return 0;
                               }
                              } 
                              for(int i=0 ; i<NUM_FLOORS ; i++)
                              {
                             for(int j=0 ; j<ROOMS_PER_FLOOR ; j++)
                             {
                             for(int k=0 ; k<entityCounts[i][j] ; k++)
                             {
                             file>>roomEntities[i][j][k];
                              }
                               }
                               }
                             file.close();
                             return 1;
                           }

void writeGameSummaryReport(const char* filename,
                            int score, int remainingEnergy, int remainingTime,
                            const bool objectives[NUM_OBJECTIVES], bool victory)
                            {
                             ofstream file(filename);
                             if (!file)
                              return ;
                             file<<"Final score : "<<score<<endl;
                             file<<"Remaining Energy : "<<remainingEnergy<<endl;
                             file<<"Remaining Time : "<<remainingTime<<endl;
                             for(int i=0 ; i<NUM_OBJECTIVES ; i++)
                               {
                               if(objectives[i]==1)
                                file<<"Completed"<<endl;
                               else
                                file<<"Not Completed"<<endl;
                                 }
                              if(victory==0)
                              file<<"You Failed!!"<<endl;
                              else
                              file<<"VICTORYYYYY!!!!"<<endl;
                              file.close();
                            }