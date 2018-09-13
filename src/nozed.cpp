#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"

#define ADDRESS "192.168.63.133"	// Broker IP
#define CLIENTID "ODOM ID"
#define TOPIC "diagnostics"
#define QOS 2

int main()
{
  int rc = 0;
  MQTTClient zed;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  MQTTClient_create(&zed, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

  if(rc = MQTTClient_connect(zed, &conn_opts) != MQTTCLIENT_SUCCESS)
  {
    printf("Connection failed. Return code: %d\n", rc);
  }

  MQTTClient_message diag = MQTTClient_message_initializer;
  diag.payload = "ciao!";
  if(MQTTClient_publishMessage(zed, TOPIC, &diag, NULL))
  {
    printf("Message published\n");
  }
  
  return 0;
}
