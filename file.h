#ifndef FILE_H
#define FILE_H

/* file.c functions */

#ifndef MSDOS
void lock_score_file( void );
void unlock_score_file( void );
#endif
FILE* checkfopen( char*, char* );
int filecheck( void );
int test_file_access( char*, char );
void abyss_file( void );
void adeptfile( void );
void checkhigh( char*, int );
void cityguidefile( void );
void combat_help( void );
void commandlist( void );
void copyfile( char* );
void displayfile( char* );
void displaycryptfile( char* );
void extendlog( char*, int );
void filescanstring( FILE*, char* );    /* in util.c if MSDOS defined */
void inv_help( void );
void save_hiscore_npc( int );
void show_license( void );
void showmotd( void );
void showscores( void );
void theologyfile( void );
void user_intro( void );
void wishfile( void );

#endif
