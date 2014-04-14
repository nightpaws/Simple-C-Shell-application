/***************************************************************************************************************
 *
 * Filename: ace4.h
 *
 * Synopsis: Simple Shell Application Header
 *
 * This is the header file containing the crucial values for the operation of ace
 * 
 * Authors:
 *      Craig Morrison, Reg no: 201247913
 *	Stewart Key, Reg no: 201240385
 *	Adam McGhie, Reg no: 201240207
 *	Liam Diamond, Reg no: 201210681
 *
 * Group:
 *     Thursday Group 6
 *
 * Promise: I confirm that this submission is all my own work.
 *
 *            (Craig Morrison)	__________________________________________
 *               (Stewart Key)	__________________________________________
 *               (Adam McGhie)	__________________________________________
 *              (Liam Diamond)	__________________________________________
 *
 * Version: See ace4.c Revision History
 *
 **************************************************************************************************************/

/*defining boolean values*/
#define true 0
#define false 1
typedef int bool;

/*declare max size of input*/
#define inputval 512
/*declare max size of input plus one for null value*/
#define in_size inputval+1

/* Max size of arg array */
#define max_args 50
/* Define number of chars per arg in array */
#define max_chars 512

/*Define maximum size of history*/
#define max_hist 20

/*Define maximum number of aliases*/
#define max_alias 10
