#include "level.h"
#include "util.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

bool loadBuildingMap(const char* filename,
    char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
    char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
    int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]) {
    ifstream file1(filename);
    if (!file1.is_open()) {
        return 0;
    }
    for (int i = 0;i < NUM_FLOORS;i++) {
        for (int j = 0;j < ROOMS_PER_FLOOR - 1;j++) {
            horizontalConn[i][j] = CONN_NONE;
        }
    }
    for (int i = 0;i < NUM_FLOORS;i++) {
        for (int j = 0;j < ROOMS_PER_FLOOR;j++) {
            for (int k = 0;k < MAX_ENTITIES_PER_ROOM;k++) {
                roomEntities[i][j][k] = ENT_NONE;
            }
            entityCounts[i][j] = 0;
        }
    }
    int floor = -1, room = -1;
    char arr1[MAX_LINE_LEN];
    while (file1.getline(arr1, MAX_LINE_LEN)) {
        if (strlen(arr1) == 0) {
            break;
        }
        int length = strlen(arr1);
            for (int i = 0;i < length;i++) {
                int  remChar = length - i;
                if (remChar >= 5) {
                if ((arr1[i] == 'F') && (arr1[i + 1] >= '1' && arr1[i + 1] <= '5') && (arr1[i + 2] == '-')
                    && (arr1[i + 3] == 'R') && (arr1[i + 4] >= '1' && arr1[i + 4] <= '4')) {
                    floor = arr1[i + 1] - '0';
                    floor = floor - 1;
                    room = arr1[i + 4] - '0';
                    room = room - 1;
                        if (remChar >= 11) {
                            if (room < ROOMS_PER_FLOOR - 1) {
                                char connection = arr1[i + 10];
                                if (connection == CONN_DOOR || connection == CONN_WINDOW || connection == CONN_LOCKED_DOOR || connection == CONN_SOLID_WALL) {
                                    if (remChar >= 12) {
                                        if (connection == CONN_LOCKED_DOOR && arr1[i + 11] == '1') {
                                            continue;
                                        }
                                    }
                                    horizontalConn[floor][room] = connection;
                                
                                   }
                                }
                            }
                        }
                    }      
                }  //for closing
            } //while closing
    file1.clear();
    file1.seekg(0);  //file reading position  begining pey a jai gi 
        while (file1.getline(arr1, MAX_LINE_LEN)) {
            if (strlen(arr1) == 0) {
                break;
            }
        int length = strlen(arr1);
        for (int i = 0;i < length;i++) {
            int remChar = length - i;
            if (remChar >= 5) {
                if ((arr1[i] == 'F') && (arr1[i + 1] >= '1' && arr1[i + 1] <= '5') && (arr1[i + 2] == '-')
                    && (arr1[i + 3] == 'R') && (arr1[i + 4] >= '1' && arr1[i + 4] <= '4')) {
                    floor = arr1[i + 1] - '0';
                    floor = floor - 1;
                    room = arr1[i + 4] - '0';
                    room = room - 1;
                    if (room == 0) {
                        if (file1.getline(arr1, MAX_LINE_LEN)) {
                            int length = strlen(arr1);
                            for (int j = 0;j < ROOMS_PER_FLOOR;j++) {
                                int start = 9 + j * 12;
                                int end = start + 10;
                                for (int k = start;k <= end && k < length;k++) {
                                    if (arr1[k] == ENT_MASTER_KEY || arr1[k] == ENT_ENERGY_PACK
                                        || arr1[k] == ENT_CAT_CARRIER || arr1[k] == ENT_EMERGENCY_TOOLKIT
                                        || arr1[k] == ENT_CLUE_4 || arr1[k] == ENT_FUSE
                                        || arr1[k] == ENT_OBSERVATION_TOKEN || arr1[k] == ENT_CAT
                                        || arr1[k] == ENT_CONTROL_PANEL || arr1[k] == ENT_LIFT_PASS
                                        || arr1[k] == ENT_PASSENGER || arr1[k] == ENT_MEDICAL_KIT
                                        || arr1[k] == ENT_EMERGENCY_CARD || arr1[k] == ENT_CLUE_2
                                        || arr1[k] == ENT_CLUE_7 || arr1[k] == ENT_CABINET_TRAIN_KEY) {
                                        char entity = arr1[k];
                                        if (entityCounts[floor][j] < MAX_ENTITIES_PER_ROOM) {
                                            roomEntities[floor][j][entityCounts[floor][j]] = entity;
                                            entityCounts[floor][j]++;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return true;
} // loadBuildingMap closing bracket
bool loadInitialState(const char* filename,
    int& playerFloor, int& playerRoom,
    int& energy, int& time, int& score,
    char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
    bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft) {
    ifstream file1(filename);
    if (!file1.is_open()) {
        return 0;
    }
    playerFloor = -1;
    playerRoom = -1;
    time = INITIAL_TIME;
    energy = INITIAL_ENERGY;
    score = INITIAL_SCORE;
    inventoryCount = 0;
    emergencyTripsLeft = 0;
    for (int i = 0;i < MAX_INVENTORY_CAPACITY;i++) {
        inventory[i] = ENT_NONE;
    }
    for (int j = 0;j < NUM_OBJECTIVES;j++) {
        objectives[j] = false;
    }
    char line[MAX_LINE_LEN];
    while (file1.getline(line, MAX_LINE_LEN)) {
        int length = strlen(line);
        int colonindex = -1;
        for (int i = 0; i < length; i++) {
            if (line[i] == ':') {
                colonindex = i;
                break;
            }
        }
        if (colonindex == -1) {
            continue;
        }
        char key[MAX_LINE_LEN];
        char value[MAX_LINE_LEN];
        for (int i = 0; i < colonindex; i++) {
            key[i] = line[i];
        }
        key[colonindex] = '\0';
        int j = 0;
        for (int i = colonindex + 1; i < length; i++) {
            value[j] = line[i];
            j++;
        }
        value[j] = '\0';
        trimWhitespace(key);
        trimWhitespace(value);
        if (stringEquals(key, "INITIAL_ENERGY")) {
            energy = atoi(value);    //atoi will convert string to int 
        }
        else if (stringEquals(key, "INITIAL_TIME")) {
            time = atoi(value);
        }
        else if (stringEquals(key, "INITIAL_SCORE")) {
            score = atoi(value);
        }
        else if (stringEquals(key, "START_ROOM")) {
            if (stringEquals(value, "PLAYER_SELECTS")) {
                playerFloor = -1;
                playerRoom = -1;
            }
            else {
                return false;
            }
        }
        else if (stringEquals(key, "PASSENGER_RESCUED")) {
            objectives[OBJ_PASSENGER_RESCUED] =
                stringEquals(value, "YES");
        }
        else if (stringEquals(key, "CAT_RESCUED")) {
            objectives[OBJ_CAT_SECURED] =
                stringEquals(value, "YES");
        }
        else if (stringEquals(key, "CABINET_UNLOCKED")) {
            objectives[OBJ_CABINET_UNLOCKED] =
                stringEquals(value, "YES");
        }
        else if (stringEquals(key, "TRAIN_KEY_COLLECTED")) {
            objectives[OBJ_TRAIN_KEY] =
                stringEquals(value, "YES");
        }
        else if (stringEquals(key, "FUSE_INSTALLED")) {
            objectives[OBJ_FUSE_INSTALLED] =
                stringEquals(value, "YES");
        }
        else if (stringEquals(key, "LIFT_PASS_COLLECTED")) {
            objectives[OBJ_LIFT_PASS] =
                stringEquals(value, "YES");
        }
        else if (stringEquals(key, "TRAIN_PREPARED")) {
            objectives[OBJ_TRAIN_PREPARED] =
                stringEquals(value, "YES");
        }
        else if (stringEquals(key, "INITIAL_INVENTORY")) {
            if (!stringEquals(value, "NONE")) {
                return false;
            }
        }
        else if (stringEquals(key, "CLUES_COLLECTED")) {
            if (!stringEquals(value, "NONE")) {
                return false;
            }
        }
    }
    if (energy < 0 || energy > MAX_ENERGY) {
        return false;
    }
    if (time < 0 || time > MAX_TIME) {
        return false;
    }
    if (score < 0) {
        return false;
    }
     return true;
  }//fucntion closing bracket
 
  bool validateStartingRoom(
      int startFloor, int startRoom,
      const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]) {

      // Check floor and room boundaries
      if (startFloor < 0 || startFloor >= NUM_FLOORS) {
          return false;
      }

      if (startRoom < 0 || startRoom >= ROOMS_PER_FLOOR) {
          return false;
      }

      // Check left connection
      if (startRoom > 0) {
          char left = horizontalConn[startFloor][startRoom - 1];

          if (left == CONN_DOOR || left == CONN_WINDOW) {
              return true;
          }
      }

      // Check right connection
      if (startRoom < ROOMS_PER_FLOOR - 1) {
          char right = horizontalConn[startFloor][startRoom];

          if (right == CONN_DOOR || right == CONN_WINDOW) {
              return true;
          }
      }

      // Check staircase connections
      if (startRoom == 0) {
          return true;
      }

      // Check Lift 1 connections
      if (startFloor == 0 || startFloor == 1) {
          if (startRoom == 1 || startRoom == 2) {
              return true;
          }
      }
      return false;
  } // validateStartingRoom closing bracket

          const char* getEntityName(char entitySymbol) {
              switch (entitySymbol) {
              case ENT_MASTER_KEY:
                  return "Master Key";
              case ENT_ENERGY_PACK:
                  return "Energy Pack";
              case ENT_EMERGENCY_TOOLKIT:
                  return "Emergency tool kit";
              case ENT_CLUE_4:
                      return "Clue 4";
              case ENT_FUSE:
                  return "Fuse";
              case ENT_CAT:
                  return "Cat";
              case ENT_CONTROL_PANEL:
                  return "Control panel";
              case ENT_LIFT_PASS:
                  return "Lift Pass";
              case ENT_PASSENGER:
                  return "Passenger";
              case  ENT_MEDICAL_KIT:
                  return "Medical kit";
              case  ENT_EMERGENCY_CARD:
                  return "Emergency Card";
              case ENT_CLUE_2:
                  return "Clue 2";
              case ENT_CLUE_7:
                  return "Clue 7";
              case  ENT_CABINET_TRAIN_KEY:
                  return "Cabinet Train Key";
              case  ENT_CAT_CARRIER:
                  return "Cat carrier";
              case  ENT_OBSERVATION_TOKEN:
                  return "Observation token";
                  
              default:
                  return "Unknown Entity";
              }
          }

