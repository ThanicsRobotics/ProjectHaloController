#ifndef RADIO_H
#define RADIO_H

////Radio protocol coefficients
//{"Link Request": 0x01, "Link Acknowledge": 0x02, "Throttle": 0x03, "Roll": 0x04, "Pitch": 0x05,
//                "Yaw": 0x06, "X_Velocity": 0x07, "Y_Velocity": 0x08, "Z_Velocity": 0x09, "X_Acceleration": 0x0A,
//                "Y_Acceleration": 0x0B, "Z_Acceleration": 0x0C, "Drone_GPS_Latitude": 0x0D, "Drone_GPS_Longitude": 0x0E,
//                "Controller_GPS_Latitude": 0x0F, "Controller_GPS_Longitude": 0x10, "Altitude": 0x11, "Fail": 0x12}

#define LINK_REQ 0x01
#define LINK_ACK 0x02

void setupRadio();
void radioSend();

#endif // RADIO_H
