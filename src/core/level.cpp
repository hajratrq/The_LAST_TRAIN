#include "level.h"
#include "util.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
bool findflooroomIndex(char arr1[], int i,int& floor,int &room) {
        int length = strlen(arr1);
            int  remChar = length - i;
            if (remChar >= 5) {
                if ((arr1[i] == 'F') && (arr1[i + 1] >= '1' && arr1[i + 1] <= '5') && (arr1[i + 2] == '-')
                    && (arr1[i + 3] == 'R') && (arr1[i + 4] >= '1' && arr1[i + 4] <= '4')) {
                    floor = arr1[i + 1] - '0';
                    floor = floor - 1;
                    room = arr1[i + 4] - '0';
                    room = room - 1;
                    return true;
                }
            }
            return false;
}
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
        int length = strlen(arr1);
            for (int i = 0;i < length;i++) {
                int  remChar = length - i;
                if (findflooroomIndex(arr1,i,floor,room)){
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
                }  //for closing
            } //while closing
    file1.clear();
    file1.seekg(0);  //file reading position  begining pey a jai gi 
    while (file1.getline(arr1, MAX_LINE_LEN)) {
        int length = strlen(arr1);
        for (int i = 0;i < length;i++) {
            if (findflooroomIndex(arr1, i, floor, room) && (room == 0)) {
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
     return true;
  }