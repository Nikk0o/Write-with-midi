#ifndef NERR_H
#define NERR_H

    /*
    * Error macros for different types of errors.
    */

    /*
    * File errors
    */
    
    #define ERR_DATANULL -1
    #define ERR_FILENOTOPEN -2
    #define ERR_NULLVEC -3
    #define ERR_READERROR -4
    #define ERR_NEGFD -5
    #define ERR_WRITEERROR -6
    #define ERR_GEN -7

    /*
    * Memory allocation errors
    */

    #define ERR_NOMEM -8

#endif