    #include <linux/input-event-codes.h>

    int get_char_note(unsigned int note_num)
    {
        int note = KEY_RESERVED; // 0 will be nothing
        switch (note_num)
        {
            case 21:
                // SUPER key
                note = KEY_LEFTMETA;
                break;
            case 22:
                // Ctrl
                note = KEY_LEFTCTRL;
                break;
            case 23:
                // Shift
                note = KEY_LEFTSHIFT;
                break;
            case 24:
                // tab
                note = KEY_TAB;
                break;
            case 25:
                // Capslock
                note = KEY_CAPSLOCK;
                break;
            case 48 ... 73: 
                // for the alphabet letters
                switch(note_num)
                {
                    case 48:
                        note = KEY_A;
                        break;
                    case 49:
                        note = KEY_B;
                        break;
                    case 50:
                        note = KEY_C;
                        break;
                    case 51:
                        note = KEY_D;
                        break;
                    case 52:
                        note = KEY_E;
                        break;
                    case 53:
                        note = KEY_F;
                        break;
                    case 54:
                        note = KEY_G;
                        break;
                    case 55:
                        note = KEY_H;
                        break;
                    case 56:
                        note = KEY_I;
                        break;
                    case 57:
                        note = KEY_J;
                        break;
                    case 58:
                        note = KEY_K;
                        break;
                    case 59:
                        note = KEY_L;
                        break;
                    case 60:
                        note = KEY_M;
                        break;
                    case 61:
                        note = KEY_N;
                        break;
                    case 62:
                        note = KEY_O;
                        break;
                    case 63:
                        note = KEY_P;
                        break;
                    case 64:
                        note = KEY_Q;
                        break;
                    case 65:
                        note = KEY_R;
                        break;
                    case 66:
                        note = KEY_S;
                        break;
                    case 67:
                        note = KEY_T;
                        break;
                    case 68:
                        note = KEY_U;
                        break;
                    case 69:
                        note = KEY_V;
                        break;
                    case 70:
                        note = KEY_W;
                        break;
                    case 71:
                        note = KEY_X;
                        break;
                    case 72:
                        note = KEY_Y;
                        break;
                    case 73:
                        note = KEY_Z;
                        break;
                }
                break;
            case 74:
                // space
                note = KEY_SPACE;
                break;
            case 75:
                note = KEY_ENTER;
                break;
            case 77:
                // backspace
                note = KEY_BACKSPACE;
                break;
            case 108: 
                note = KEY_ESC;
                break;
        }

        return note;
    }