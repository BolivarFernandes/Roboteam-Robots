#ifndef __SELECTOR_H__

#define __SELECTOR_H__
#define pin


#endif // __SELECTOR_H__


void selector(void)//
{
    int pin = analogRead(A0);
    if(pin>=0&&pin<=100) return 0;
    else if(pin>100&&pin<=200) return 1;
    else if(pin>200&&pin<=200) return 2;
    else if(pin>300&&pin<=400) return 3;
    else if(pin>400&&pin<=500) return 4;
    else if(pin>500&&pin<=600) return 5;
    else if(pin>600&&pin<=700) return 6;
    else if(pin>700&&pin<=800) return 7;
    else if(pin>800&&pin<=900) return 8;
    else return 9;

}
