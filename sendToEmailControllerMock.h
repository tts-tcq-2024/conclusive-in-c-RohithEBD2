#include "typewise-alertUtils.h"
#include "printMessage.h"

void sendToControllerMock(BreachType breachType) {
  const unsigned short headerMock = 0xfeed;
  printtocontroller(headerMock, breachType);
}

void sendToEmailMock(BreachType breachType) {
    const char* recepientMock = "a.b@c.com";
    const char* messagesMock[] = {"","Hi, the temperature is too low","Hi, the temperature is too high"};
    
    if (breachType == TOO_LOW || breachType == TOO_HIGH) {
        printToMessage(recepientMock);
        printMessage(messagesMock[breachType]);
    }
}
