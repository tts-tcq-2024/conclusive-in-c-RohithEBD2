#include "sendToEmailControllerMock.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

int lower_limit[] = {0,0,0};
int upper_limit[] = {35,45,40};

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit = lower_limit[coolingType];
  int upperLimit = upper_limit[coolingType];

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

BreachType (*classifyTemperatureBreachPtr)(CoolingType, double) = classifyTemperatureBreach;


BreachType breachTypeMock;
void checkAndAlertMock(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC){
    breachTypeMock = classifyTemperatureBreachPtr(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachTypeMock);
      break;
    case TO_EMAIL:
      sendToEmail(breachTypeMock);
      break;
  }
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreachPtr(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printtocontroller(header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recepient = "a.b@c.com";
    const char* messages[] = {"","Hi, the temperature is too low\n","Hi, the temperature is too high\n"};
    
    if (breachType == TOO_LOW || breachType == TOO_HIGH) {
        printToMessage(recepient);
        printMessage(messages[breachType]);
    }
}

