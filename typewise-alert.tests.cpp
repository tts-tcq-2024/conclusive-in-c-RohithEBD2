#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    ASSERT_EQ(inferBreach(12, 20, 30), TOO_LOW);
    ASSERT_EQ(inferBreach(25, 20, 30), NORMAL);
    ASSERT_EQ(inferBreach(35, 20, 30), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    ASSERT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    ASSERT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    ASSERT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);
    ASSERT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 20), NORMAL);
}

TEST(TypeWiseAlertTestSuite, SendsAlertToController) {
    // Redirect stdout to capture output
    testing::internal::CaptureStdout();
    sendToController(TOO_HIGH);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "feed : 2\n");
}

TEST(TypeWiseAlertTestSuite, SendsAlertToEmail) {
    testing::internal::CaptureStdout();
    sendToEmail(TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");

    testing::internal::CaptureStdout();
    sendToEmail(TOO_HIGH);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");
}

TEST(TypeWiseAlertTestSuite, CheckAndAlert) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};

    // Test alert to controller
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 50);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "feed : 2\n");

    // Test alert to email
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, -1);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");
}
