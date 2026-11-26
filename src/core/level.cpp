#include "level.h"
#include "util.h"
#include <iostream>
#include <fstream>
using namespace std;
bool loadBuildingMap(const char* filename,
    char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
    char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
    int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]) {
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
    bool entityline = false;
    char arr1[MAX_LINE_LEN];
    while (file1.getline(arr1, MAX_LINE_LEN)) {
        int length = strlen(arr1);
        int roomcount = -1;
        if (entityline == true) {
            if (arr1[i] == '|') {
                roomcount++;
            }
            roomEntities[floor][room][MAX_ENTITIES_PER_ROOM] = ;

        }
        else {
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
                                    entityline = true;
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    ifstream file1(filename);
    if (!file1.is_open()) {
        return 0;
    }
}
// Modular implementation using primitive arrays for map parsing and verification
