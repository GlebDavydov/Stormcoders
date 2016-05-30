#ifndef DRIVE_H_INCLUDED
#define DRIVE_H_INCLUDED

int initialize(void);
char *ReadCOM(char *buff);
void move_send(char data);

#endif // DRIVE_H_INCLUDED
