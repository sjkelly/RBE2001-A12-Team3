
driveMotor(int16_t speed, motor side)
{
 if(speed > 0)
 {
  digitalWrite(HBRIDGE1, 0);
  digitalWrite(HBRIDGE2, 1);
 }
 else
 {
  speed *= -1;
  digitalWrite(HBRIDGE2, 0);
  digitalWrite(HBRIDGE1, 1);
 }
 analogWrite(side ,speed);
}
