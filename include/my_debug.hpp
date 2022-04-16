// To ensure that the file will be included only once
#pragma once

#define MY_DEBUG

//#define D_PRINTMACADD
//#define D_STARTESPNOW
//#define D_ONDATASENT
//#define D_ONDATAREC
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

#ifdef MY_DEBUG
  #define D(x) x
#else
  #define D(x)
#endif

/*
// Uncommit this to debug OnDataSent
// #define ONDATASENT
// Uncommit this to debug OnDataRecv
// #define ONDATARECV
// Uncommit this to debug SendReadings
// #define SENDREADINGS
// Uncommit this to debug updateDisplay
#define SHOWRECEIVINGS
// Debug session
#ifdef MY_DEBUG
#define D(x) x
#else
#define D(x)
#endif
#ifdef ONDATASENT
#define DBG_ODS(x) D(x)
#else
#define DBG_ODS(x)
#endif
#ifdef ONDATARECV
#define DBG_ODR(x) D(x)
#else
#define DBG_ODR(x)
#endif
#ifdef SENDREADINGS
#define DBG_SR(x) D(x)
#else
#define DBG_SR(x)
#endif
#ifdef SHOWRECEIVINGS
#define DBG_SHR(x) D(x)
#else
#define DBG_SHR(x)
#endif*/