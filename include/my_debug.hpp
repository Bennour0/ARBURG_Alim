// To ensure that the file will be included only once
#pragma once

#define DEBUG
// Uncommit this to debug OnDataSent
// #define ONDATASENT
// Uncommit this to debug OnDataRecv
// #define ONDATARECV
// Uncommit this to debug SendReadings
// #define SENDREADINGS
// Uncommit this to debug updateDisplay
#define SHOWRECEIVINGS
// Uncommit this to chose board ID 1
#define BOARDID1
// Uncommit this to chose board ID 2
// #define BOARDID2
// Debug session
#ifdef DEBUG
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
#endif
#ifdef BOARDID1
#define DBG_BID1(x) D(x)
#else
#define DBG_BID1(x)
#endif
#ifdef BOARDID2
#define DBG_BID2(x) D(x)
#else
#define DBG_BID2(x)
#endif