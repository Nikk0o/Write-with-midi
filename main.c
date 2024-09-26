// Define the usleep() function 
#define _DEFAULT_SOURCE

#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <linux/uinput.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "Error.h"

enum state { pressed, released };
typedef char __8bit;

/*
* This struct is used to store the raw data read from the 
* device 
*/
struct _midi_data
{
    __8bit note;
    __8bit time; // i still don't quite get what the time means, and since it isn't relevant to this program, i'll just ignore it
    enum state state;
};

/*
* Lists all devices avalible
* (probably will need different implementations depending on the user's OS)
*/
void list_devices();

/*
* Return a char that corresponds to a given note value
* This function is defined in the getcharnote.c to make this file cleaner
*/
int get_char_note(unsigned int note_num);

/*
* reads the midi input from the file specified by the file descriptor fp
*/
int read_midi_input(int fd, struct _midi_data *midi_read, __8bit *buf);

/*
* Opens the file located at the specified path in read or write mode
* and returns its file descriptor.
* If it fails, returns -1
*/
int open_device(const char path[], int mode, int append);

/*
* Writes the character *chr in the file fd
*/
int write_keyb_char(struct _midi_data chr, int fd);


void list_devices()
{
    return;
}

int open_device(const char path[], int mode, int block)
{
    if (block == -1) return open(path, mode);
    return open(path, mode | block);
}

int read_midi_input(int fd, struct _midi_data *midi_read, __8bit *buf)
{
    if (buf == NULL) return ERR_NULLVEC;

    int didread = read(fd, buf, 3);

    if (didread == -1)
    {
        perror("Could not read midi data");
        return ERR_READERROR;
    }
    else if (didread == 0)
    {
        // if it reaches feof, return
        return 0;
    }

        if (buf == NULL)
        {
            perror("read returned NULL");
            return ERR_DATANULL;
        }

        // 144 is the code for a pressed key
        if (buf[0] == (__8bit) 144)
        {
            // Assigns the data read to the note
            midi_read->state = pressed;
            midi_read->note = buf[1];
            midi_read->time = buf[2];

            return 1;
        }
        // 128 is the code for a released key
        else if (buf[0] == (__8bit) 128)
        {
            midi_read->state = released;
            midi_read->note = (char) buf[1];
            midi_read->time = (char) buf[2];

            return 1;
        }
        return 1;
    }

    /*
    * This function is copied from https://www.kernel.org/doc/html/v4.14/input/uinput.html
    * I did not create it
    */
    int emit(int fd, int type, int code, int val)
    {
        struct input_event ie;

        ie.type = type;
        ie.code = code;
        ie.value = val;
        /* timestamp values below are ignored */
        ie.time.tv_sec = 0;
        ie.time.tv_usec = 0;

        // Just for debugging
        printf("%hu, %hu, %hu\n", ie.value, ie.type, ie.code);

        return write(fd, &ie, sizeof(ie));
    }


    int create_keyboard(struct uinput_setup *setup, int fd)
    {
        if (ioctl(fd, UI_SET_EVBIT, EV_KEY) == -1) return ERR_GEN;

        ioctl(fd, UI_SET_KEYBIT, KEY_SPACE);
        ioctl(fd, UI_SET_KEYBIT, KEY_LEFTCTRL);
        ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT);
        ioctl(fd, UI_SET_KEYBIT, KEY_LEFTMETA);
        ioctl(fd, UI_SET_KEYBIT, KEY_CAPSLOCK);
        ioctl(fd, UI_SET_KEYBIT, KEY_TAB);
        ioctl(fd, UI_SET_KEYBIT, KEY_BACKSPACE);
        ioctl(fd, UI_SET_KEYBIT, KEY_ENTER);
        ioctl(fd, UI_SET_KEYBIT, KEY_A);
        ioctl(fd, UI_SET_KEYBIT, KEY_B);
        ioctl(fd, UI_SET_KEYBIT, KEY_C);
        ioctl(fd, UI_SET_KEYBIT, KEY_D);
        ioctl(fd, UI_SET_KEYBIT, KEY_E);
        ioctl(fd, UI_SET_KEYBIT, KEY_F);
        ioctl(fd, UI_SET_KEYBIT, KEY_G);
        ioctl(fd, UI_SET_KEYBIT, KEY_H);
        ioctl(fd, UI_SET_KEYBIT, KEY_I);
        ioctl(fd, UI_SET_KEYBIT, KEY_J);
        ioctl(fd, UI_SET_KEYBIT, KEY_K);
        ioctl(fd, UI_SET_KEYBIT, KEY_L);
        ioctl(fd, UI_SET_KEYBIT, KEY_M);
        ioctl(fd, UI_SET_KEYBIT, KEY_N);
        ioctl(fd, UI_SET_KEYBIT, KEY_O);
        ioctl(fd, UI_SET_KEYBIT, KEY_P);
        ioctl(fd, UI_SET_KEYBIT, KEY_Q);
        ioctl(fd, UI_SET_KEYBIT, KEY_R);
        ioctl(fd, UI_SET_KEYBIT, KEY_S);
        ioctl(fd, UI_SET_KEYBIT, KEY_T);
        ioctl(fd, UI_SET_KEYBIT, KEY_U);
        ioctl(fd, UI_SET_KEYBIT, KEY_V);
        ioctl(fd, UI_SET_KEYBIT, KEY_W);
        ioctl(fd, UI_SET_KEYBIT, KEY_X);
        ioctl(fd, UI_SET_KEYBIT, KEY_Y);
        ioctl(fd, UI_SET_KEYBIT, KEY_Z);

        memset(setup, 0, sizeof(*setup));
        setup->id.bustype = BUS_USB;
        setup->id.vendor = 0x1234;
        setup->id.product = 0x1235;
        strcpy(setup->name, "Generic Keyboard");

        if (ioctl(fd, UI_DEV_SETUP, setup) == -1) return ERR_GEN;
        if (ioctl(fd, UI_DEV_CREATE) == -1) return ERR_GEN;

        return 0;
    }


    int write_keyb_char(struct _midi_data chr, int fd)
    {
        if (fd < 0) return ERR_NEGFD;

        int val;
        if (chr.state == pressed) val = 1;
        else val = 0;

        /* Write the output to the virtual keyboard */
        emit(fd, EV_KEY, get_char_note(chr.note), val);
        emit(fd, EV_SYN, SYN_REPORT, 0);

        return 0;
    }



int main(void)
{
    const char midipath[] = "/dev/midi1";
    const char keybpath[] = "/dev/uinput";
    
    struct _midi_data note;
    int fd_midi, fd_keyb;
    __8bit *buf;

    fd_midi = open_device(midipath, O_RDONLY, -1);
    fd_keyb = open_device(keybpath, O_WRONLY, -1);
    if (fd_midi < 0 || fd_keyb < 0) return ERR_FILENOTOPEN;

    printf("midi's fd: %d, keyboard's fd: %d\n", fd_midi, fd_keyb);

    if ((buf = (__8bit *) malloc(sizeof(__8bit)*3)) == NULL) { close(fd_keyb); close(fd_midi); return ERR_NOMEM; }

    // Create a virtual keyboard with uinput
    // and wait a bit just to make sure the device is ready
    struct uinput_setup setup;
    if (create_keyboard(&setup,fd_keyb) != 0) return ERR_GEN; 
    sleep(1);


    /* Main loop */
    while (1)
    {
        int succ;
        if ((succ = read_midi_input(fd_midi, &note, buf)) < 0) continue;

        // apparently it never returns 0, but i'll keep this here just in case
        else if (succ == 0) continue;
        // printf("%d\n", succ);

        int ac_chr = get_char_note(note.note);
        printf("%u\n", note.note);

        // the program closes if the character is KEY_ESC
        // I will probably change this key
        if (ac_chr == KEY_ESC) break;
        else if (ac_chr == KEY_RESERVED) continue; // maybe change this key, idk what it is

        succ = write_keyb_char(note, fd_keyb);
        if (succ < 0) { printf("Could not write character to keyboard\n"); }
    }

    sleep(1);
    free(buf);
    ioctl(fd_keyb, UI_DEV_DESTROY);
    close(fd_keyb);
    close(fd_midi);
    return 0;
}