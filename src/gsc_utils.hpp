#include <ctime>

#if COMPILE_SSL == 1
#include <openssl/evp.h>
#endif

void gsc_utils_file_exists();
void gsc_utils_fopen();
void gsc_utils_fread();
void gsc_utils_fwrite();
void gsc_utils_fclose();

void gsc_utils_sendcommandtoclient();
void gsc_utils_logprintconsole();
void gsc_utils_getsubstr();
void gsc_utils_getascii();
void gsc_utils_toupper();
void gsc_utils_tolower();
void gsc_utils_strtok();
void gsc_utils_replace();
void gsc_utils_getserverstarttime();
void gsc_utils_getsystemtime();
void gsc_utils_strftime();
void gsc_utils_getconfigstring();
void gsc_utils_makelocalizedstring();
void gsc_utils_getlocalizedstringindex();
void gsc_utils_makeupdatedlocalizedstring();
void gsc_utils_ban();
void gsc_utils_unban();
void gsc_utils_strip();
void gsc_utils_strstr();
void gsc_utils_monotone();
void gsc_utils_sendservercommand();
void gsc_utils_seconds();
void gsc_utils_printconsole();

#if COMPILE_SSL == 1
void gsc_utils_hash();
#endif