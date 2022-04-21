#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11

//#define DHT_SENSOR_TYPE DHT_TYPE_21 
//#define DHT_SENSOR_TYPE DHT_TYPE_22

static const int DHT_SENSOR_PIN = 6; 

DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

void setup( ) 
{ 
  Serial.begin(9600); 
} 
void loop( ) 
{ 
  float temperature; 
  float humidity;
  float temperature_F;
  
  if(dht_sensor.measure(&temperature, &humidity)){ 
    temperature_F = temperature*1.8 + 32;
    
    Serial.print( "T = " ); 
    Serial.print( temperature_F, 1 );
    Serial.print( " deg. F, H = " ); 
    Serial.print( humidity, 1 ); 
    Serial.println( "%" );
  } 
}
