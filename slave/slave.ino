#include <RH_ASK.h>

RH_ASK driver;
int last_idx = 0;
char buffer[20];//el char es solo un buffer para meter y sacar el string

void setup()
{
  Serial.begin(9600); // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    // Message with a good checksum received, dump it.
    buf[buflen]=0;
    Serial.print("Received(");
    Serial.print(buflen);
    Serial.print(",");
    int idx=atoi(buf);
    Serial.print(idx>last_idx ? "+" : "-");
    Serial.print(idx-last_idx);
    last_idx=idx;
    Serial.print("}: ");
    driver.printBuffer(buf, buf, buflen);
    sprintf(buffer, "El multiplo es: %d\r\n", idx*2); //se guarda un string con el dato recibido
  //se envia la respuesta
    //const char *buffer = "Hello World!";

    driver.send((uint8_t *)buffer, strlen(buffer)); //Se envia el numero X
    driver.waitPacketSent(); //Se espera a que el numero X sea enviado
  }
}
