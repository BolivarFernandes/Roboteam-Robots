#ifndef __MOTOR_H__

#define __MOTOR_H__
#define pin
#define pwmpin
#define val

#endif // __MOTOR_H__


void motor(char pin,char pwmpin,int val)//argument pin is IO import，pwmpin is the IO port of PWM，val is the value of speed from 0 to 255
{
    pinMode(pin, OUTPUT);
  if(val>0)                             //when val >0, rotate clockwise
  {
    analogWrite(pwmpin,val);
    digitalWrite(pin,1);
   }
  else if(val<0)                     //when val <0, rotate counterclockwise
{
   analogWrite(pwmpin,-val);
   digitalWrite(pin,0);
}
else if(val==0)                     //when val = 0, stop
{
    analogWrite(pwmpin,0);
    digitalWrite(pin,0);
}
}
