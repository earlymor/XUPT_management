#ifdef WIN32
#include <winodws.h>
#endif

#ifdef linux
#include <unistd.h>
#endif

void wcsleep(int sleepSec) {
#ifdef WIN32
    Sleep(sleepSec * 1000);
#endif

#ifdef linux
    sleep(sleepSec);
#endif
}

void wcclear(){
#ifdef WIN32
    system("cls");
#endif

#ifdef linux
    system("clear");
#endif

}