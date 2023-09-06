void activateAlarm()
{
  while (alarmMode)
  {
    char key = keypad.getKey();
    if (key == '*') {homeScr();}  // Terminate and exit 
    B sensorState = digitalRead(sensor);
    if (!sensorState)
    {
      alarmFlag = 1; // Enter in next while loop after detect sensor
      digitalWrite(buzz, 1); digitalWrite(led1, 0);
      lcd.clear(); lcd.print("  ALARMING !!!");
      lcd.setCursor(0, 1); lcd.print("Password>");
    }
    while (alarmFlag) {enterPassword();} // Enter Password loop
  }
}

void enterPassword()
{
  char key = keypad.getKey();
  if (key)
  {
    if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' ||
        key == '6' || key == '7' || key == '8' || key == '9' || key == '0')
    {
      tempPassword += key;  // Store password
      curPos++;
      lcd.setCursor(curPos, 1); lcd.print("*");
    }

    if (curPos == 13 || key == '#') // Clear password 
    {
      curPos = 8; tempPassword = "";
      lcd.setCursor(9, 1); lcd.print("     ");
    }
    if (key == '*')  // Press OK Button
    {
      if (alarmMode) {checkPass = 1; changePass = 0;} // Enter check password loop
      if (changeMode) {checkPass = 0; changePass = 1;}  // Enter change pass loop
      savePassword();  // Save new pass
      checkPassword();  // Varify the entered pass
      changePassword();  // Change old pass
    }
  }
}

void checkPassword()
{
  if (checkPass)
  {
    if (tempPassword == password)  // Deactivate alarm and exit
    {
      digitalWrite(buzz, 0);
      lcd.clear(); lcd.print("Alarm Deactivated");
      delay(700);
      homeScr();
    }
    else  // Back for enter correct password
    {
      curPos = 8; tempPassword = "";  // Clear tempPassword flag
      lcd.setCursor(0, 1); lcd.print("Wrong! Try again");
      delay(600);
      lcd.setCursor(0, 1); lcd.print("Password>       ");
    }
  }
}

void changePassword()
{
  if (changePass)
  {
    if (tempPassword == password)  // If old pass match, enter new pass
    {
      curPos = 8;  passFlag = 1;
      tempPassword = "";   // Clear tempPassword flag
      lcd.clear(); lcd.print("Set New Password");
      lcd.setCursor(8, 1); lcd.print(">");
    }
    else // Back for enter correct password
    {
      curPos = 8; tempPassword = "";  // Clear tempPassword flag
      lcd.setCursor(0, 1); lcd.print("Wrong! Try again");
      delay(600);
      lcd.setCursor(0, 1); lcd.print("        >        ");
    }
  }
}

void savePassword()
{
  if (passFlag) // Save new password and exit
  {
    password = tempPassword;
    lcd.clear(); lcd.print("Password Saved!");
    lcd.setCursor(0, 1); lcd.print("New Pass: "); lcd.print(password);
    delay(2500);
    homeScr();
  }
}

void homeScr()  // When no event happened
{
  curPos = 8; tempPassword = "";  // Clear tempPassword flag
  alarmMode = 0;  alarmFlag = 0;
  changeMode = 0; checkPass = 0; changePass = 0; passFlag = 0;
  digitalWrite(led1, 0);
  lcd.clear(); lcd.print("+ Activate Alarm");
  lcd.setCursor(0, 1); lcd.print("* Change Pasword");
}
