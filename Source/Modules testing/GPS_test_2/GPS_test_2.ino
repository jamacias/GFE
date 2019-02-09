#include <TinyGPS.h>

float latitude, longitude;
unsigned long fix_age;

float latitude_command = 28.307271;
float longitude_command = -16.398117;
float heading_command = 0;

TinyGPS gps;

void setup(){
    Serial.begin(115200);
    Serial1.begin(9600);
}

void loop(){
    // while (Serial1.available()){
    //     int c = Serial1.read();
    //     if (gps.encode(c)){
    //         // retrieves +/- lat/long in 100000ths of a degree
    //         gps.f_get_position(&latitude, &longitude, &fix_age);
    //     }
    // }
    get_location(gps);

    /*
    Remember to divide the GPS values by a factor of 10 so that they fall
    within the GPS range. Example: if your serial monitor value is printing
    37664939 and -121234543 for your latitude and longitude values respectively,
    then divide each by 1000000 to get the real value.
    */

    Serial.print("latitude_command = ");
    Serial.print((float)latitude_command, 6);
    Serial.print(" ");
    Serial.print("longitude_command = ");
    Serial.println((float)longitude_command, 6);

    Serial.print("latitude = ");
    Serial.print((float)latitude, 6);
    Serial.print(" ");
    Serial.print("longitude = ");
    Serial.println((float)longitude, 6);

    heading_command = gps.course_to(latitude, longitude, 81.3, -110.8); // Magnetic north
    Serial.print("heading_command = ");
    Serial.println(heading_command);

    if(goal_is_reached(latitude, longitude, latitude_command, longitude_command)){
        Serial.println("Goal is reached!");
        delay(1000);
    }
    else{
        delay(100);
    }
}

static void get_location(TinyGPS &gps){
    while (Serial1.available()){
        int c = Serial1.read();
        if (gps.encode(c)){
            // retrieves +/- lat/long in 100000ths of a degree
            gps.f_get_position(&latitude, &longitude, &fix_age);
        }
    }
}

// Check if current location is close enough to the objective
int goal_is_reached(float latitude, float longitude, float latitude_command, float longitude_command){
    // Error of one square meter is considered succesful
    if(abs(latitude - latitude_command) <= 0.00001 && abs(longitude - longitude_command) <= 0.00001){
        return 1;
    }
    else{
        return 0;
    }
}
