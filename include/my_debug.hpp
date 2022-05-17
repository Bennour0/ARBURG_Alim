// To ensure that the file will be included only once
#pragma once

#define MY_DEBUG

//#define D_PRINTMACADD
//#define D_STARTESPNOW
//#define D_ONDATASENT
//#define D_ONDATAREC
#define D_SHOWQUEUE
#define D_INT_FEEDMAX
#define D_INT_ARBURG
#define D_INT_FEEDMAX_LVL

#ifdef MY_DEBUG
  #define D(x) x
#else
  #define D(x)
#endif

#ifdef D_STARTESPNOW
  #define D_SESPNOW(x)  D(x)
#else
  #define D_SESPNOW(x)
#endif

#ifdef D_PRINTMACADD
  #define D_PMA(x)  D(x)
#else
  #define D_PMA(x)
#endif

#ifdef D_ONDATAREC
  #define D_ODR(x)  D(x)
#else
  #define D_ODR(x)
#endif

#ifdef D_ONDATASENT
  #define D_ODS(x)  D(x)
#else
  #define D_ODS(x)
#endif

#ifdef ESP32SERVER
//#define D_BROADCAST
//#define D_SEND2CLIENT

#ifdef D_SEND2CLIENT
  #define D_S2C(x)  D(x)
#else
  #define D_S2C(x)
#endif

#ifdef D_BROADCAST
  #define D_BRCAST(x)  D(x)
#else
  #define D_BRCAST(x)
#endif
#endif

#ifdef ESP32CLIENT

#define D_CLIENT2SERVER
#ifdef D_CLIENT2SERVER
  #define D_C2S(x)  D(x)
#else
  #define D_C2S(x)
#endif

#endif

#ifdef D_SHOWQUEUE
  #define D_SHQ(x)  D(x)
#else
  #define D_SHQ(x)
#endif

#ifdef D_INT_FEEDMAX
  #define D_INTF(x)  D(x)
#else
  #define D_INTF(x)
#endif

#ifdef D_INT_ARBURG
  #define D_INTA(x)  D(x)
#else
  #define D_INTA(x)
#endif

#ifdef D_INT_FEEDMAX_LVL
  #define D_INTFL(x)  D(x)
#else
  #define D_INTFL(x)
#endif

#define PRINT_STATUS(x) ((x)?"Up":"Down")