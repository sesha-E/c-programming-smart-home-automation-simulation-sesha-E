#include <stdio.h>

// Function Prototypes
void initializeSystem(int rooms, int lights[], int temp[], int motion[], int locks[]);
void toggleLight(int rooms, int lights[]);
void readTemperature(int rooms, int temp[]);
void detectMotion(int rooms, int motion[]);
void securitySystem(int rooms, int locks[]);
void analyzeHouseStatus(int rooms, int lights[], int temp[], int motion[], int locks[], int *noMotionCounter);

int main() {
    int rooms;
    printf("Enter number of rooms: ");
    scanf("%d", &rooms);

    int lights[rooms], temp[rooms], motion[rooms], locks[rooms];
    int noMotionCounter = 0;
    initializeSystem(rooms, lights, temp, motion, locks);

    int choice;
    do {
        printf("\n===== Smart Home Menu =====\n");
        printf("1. Toggle Light\n2. Read Temperature\n3. Check Motion Sensor\n4. Lock/Unlock Security System\n5. House Status Summary\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: toggleLight(rooms, lights); break;
            case 2: readTemperature(rooms, temp); break;
            case 3: detectMotion(rooms, motion); break;
            case 4: securitySystem(rooms, locks); break;
            case 5: analyzeHouseStatus(rooms, lights, temp, motion, locks, &noMotionCounter); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void initializeSystem(int rooms, int lights[], int temp[], int motion[], int locks[]) {
    printf("Initializing system...\n");
    for (int i = 0; i < rooms; i++) {
        lights[i] = 0;
        temp[i] = 22 + (i % 5); // Assign some default temperatures
        motion[i] = 0;
        locks[i] = 1;
    }
}

void toggleLight(int rooms, int lights[]) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        lights[room - 1] = !lights[room - 1];
        printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
    } else {
        printf("Invalid room number!\n");
    }
}

void readTemperature(int rooms, int temp[]) {
    int room;
    printf("Enter room number to check temperature (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        printf("Room %d Temperature: %d°C\n", room, temp[room - 1]);
        if (temp[room - 1] > 30) {
            printf("Warning: Room %d temperature is too high!\n", room);
        }
    } else {
        printf("Invalid room number!\n");
    }
}

void detectMotion(int rooms, int motion[]) {
    int detected = 0;
    for (int i = 0; i < rooms; i++) {
        if (motion[i]) {
            printf("Motion detected in Room %d!\n", i + 1);
            detected = 1;
        }
    }
    if (!detected) {
        printf("No motion detected.\n");
    }
}

void securitySystem(int rooms, int locks[]) {
    int room;
    printf("Enter room number to toggle lock (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        locks[room - 1] = !locks[room - 1];
        printf("Room %d is now %s.\n", room, locks[room - 1] ? "Locked" : "Unlocked");
    } else {
        printf("Invalid room number!\n");
    }
}

void analyzeHouseStatus(int rooms, int lights[], int temp[], int motion[], int locks[], int *noMotionCounter) {
    printf("\nHouse Status:\n");
    int allLightsOn = 1;
    int noMotion = 1;
    
    for (int i = 0; i < rooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, %s, %s\n",
               i + 1,
               lights[i] ? "ON" : "OFF",
               temp[i],
               motion[i] ? "Motion Detected" : "No Motion",
               locks[i] ? "Locked" : "Unlocked");
        
        if (!lights[i]) allLightsOn = 0;
        if (motion[i]) noMotion = 0;
    }
    
    if (allLightsOn) {
        printf("Warning: All lights are ON for too long. Consider turning some OFF.\n");
    }
    
    if (noMotion) {
        (*noMotionCounter)++;
        if (*noMotionCounter >= 5) {
            printf("Auto-Lock activated: Locking all doors due to inactivity.\n");
            for (int i = 0; i < rooms; i++) {
                locks[i] = 1;
            }
            *noMotionCounter = 0;
        }
    } else {
        *noMotionCounter = 0;
    }
}
