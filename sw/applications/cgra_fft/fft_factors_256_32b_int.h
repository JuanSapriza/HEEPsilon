#ifndef _FFT_FACTORS_H_
#define _FFT_FACTORS_H_

#include "defines.h"

const fxp f_real[FFT_SIZE/2] = {

 32768,  32758,  32728,  32679,  32610,  32521,  32413,  32285,  32138,  31971,  31785,  31581,  31357,  31114,  30852,  30572, 
 30273,  29956,  29621,  29269,  28898,  28511,  28106,  27684,  27245,  26790,  26319,  25832,  25330,  24812,  24279,  23732, 
 23170,  22594,  22005,  21403,  20787,  20159,  19519,  18868,  18204,  17530,  16846,  16151,  15446,  14732,  14010,  13278, 
 12539,  11793,  11039,  10278,   9512,   8739,   7961,   7179,   6392,   5602,   4808,   4011,   3211,   2410,   1607,    804, 
     0,   -804,  -1607,  -2410,  -3211,  -4011,  -4808,  -5602,  -6392,  -7179,  -7961,  -8739,  -9512, -10278, -11039, -11793, 
-12539, -13278, -14010, -14732, -15446, -16151, -16846, -17530, -18204, -18868, -19519, -20159, -20787, -21403, -22005, -22594, 
-23170, -23732, -24279, -24812, -25330, -25832, -26319, -26790, -27245, -27684, -28106, -28511, -28898, -29269, -29621, -29956, 
-30273, -30572, -30852, -31114, -31357, -31581, -31785, -31971, -32138, -32285, -32413, -32521, -32610, -32679, -32728, -32758, };

const fxp f_imag[FFT_SIZE/2] = {

     0,   -804,  -1607,  -2410,  -3211,  -4011,  -4808,  -5602,  -6392,  -7179,  -7961,  -8739,  -9512, -10278, -11039, -11793, 
-12539, -13278, -14010, -14732, -15446, -16151, -16846, -17530, -18204, -18868, -19519, -20159, -20787, -21403, -22005, -22594, 
-23170, -23732, -24279, -24812, -25330, -25832, -26319, -26790, -27245, -27684, -28106, -28511, -28898, -29269, -29621, -29956, 
-30273, -30572, -30852, -31114, -31357, -31581, -31785, -31971, -32138, -32285, -32413, -32521, -32610, -32679, -32728, -32758, 
-32768, -32758, -32728, -32679, -32610, -32521, -32413, -32285, -32138, -31971, -31785, -31581, -31357, -31114, -30852, -30572, 
-30273, -29956, -29621, -29269, -28898, -28511, -28106, -27684, -27245, -26790, -26319, -25832, -25330, -24812, -24279, -23732, 
-23170, -22594, -22005, -21403, -20787, -20159, -19519, -18868, -18204, -17530, -16846, -16151, -15446, -14732, -14010, -13278, 
-12539, -11793, -11039, -10278,  -9512,  -8739,  -7961,  -7179,  -6392,  -5602,  -4808,  -4011,  -3211,  -2410,  -1607,   -804, };

const fxp A_r[FFT_SIZE] = {
 16384,  16182,  15981,  15780,  15580,  15379,  15178,  14978,  14778,  14578,  14378,  14179,  13979,  13781,  13582,  13385, 
 13187,  12990,  12794,  12598,  12403,  12208,  12014,  11820,  11627,  11435,  11244,  11054,  10864,  10675,  10487,  10300, 
 10114,   9928,   9744,   9561,   9378,   9197,   9017,   8838,   8660,   8483,   8308,   8134,   7960,   7789,   7618,   7449, 
  7281,   7115,   6949,   6786,   6624,   6463,   6304,   6146,   5990,   5835,   5682,   5530,   5381,   5233,   5086,   4941, 
  4798,   4657,   4517,   4380,   4244,   4110,   3977,   3847,   3718,   3592,   3467,   3345,   3224,   3105,   2988,   2873, 
  2761,   2650,   2541,   2435,   2330,   2228,   2128,   2030,   1934,   1840,   1749,   1660,   1573,   1488,   1405,   1325, 
  1247,   1171,   1097,   1026,    957,    891,    826,    765,    705,    648,    593,    541,    491,    443,    398,    355, 
   314,    276,    241,    208,    177,    149,    123,     99,     78,     60,     44,     30,     19,     11,      4,      1, 
     0,      1,      4,     11,     19,     30,     44,     60,     78,     99,    123,    149,    177,    208,    241,    276, 
   314,    355,    398,    443,    491,    541,    593,    648,    705,    765,    826,    891,    957,   1026,   1097,   1171, 
  1247,   1325,   1405,   1488,   1573,   1660,   1749,   1840,   1934,   2030,   2128,   2228,   2330,   2435,   2541,   2650, 
  2761,   2873,   2988,   3105,   3224,   3345,   3467,   3592,   3718,   3847,   3977,   4110,   4244,   4380,   4517,   4657, 
  4798,   4941,   5086,   5233,   5381,   5530,   5682,   5835,   5990,   6146,   6304,   6463,   6624,   6786,   6949,   7115, 
  7281,   7449,   7618,   7789,   7960,   8134,   8308,   8483,   8660,   8838,   9017,   9197,   9378,   9561,   9744,   9928, 
 10114,  10300,  10487,  10675,  10864,  11054,  11244,  11435,  11627,  11820,  12014,  12208,  12403,  12598,  12794,  12990, 
 13187,  13385,  13582,  13781,  13979,  14179,  14378,  14578,  14778,  14978,  15178,  15379,  15580,  15780,  15981,  16182, };

const fxp A_i[FFT_SIZE] = {
-16384, -16382, -16379, -16372, -16364, -16353, -16339, -16323, -16305, -16284, -16260, -16234, -16206, -16175, -16142, -16107, 
-16069, -16028, -15985, -15940, -15892, -15842, -15790, -15735, -15678, -15618, -15557, -15492, -15426, -15357, -15286, -15212, 
-15136, -15058, -14978, -14895, -14810, -14723, -14634, -14543, -14449, -14353, -14255, -14155, -14053, -13948, -13842, -13733, 
-13622, -13510, -13395, -13278, -13159, -13038, -12916, -12791, -12665, -12536, -12406, -12273, -12139, -12003, -11866, -11726, 
-11585, -11442, -11297, -11150, -11002, -10853, -10701, -10548, -10393, -10237, -10079,  -9920,  -9759,  -9597,  -9434,  -9268, 
 -9102,  -8934,  -8765,  -8594,  -8423,  -8249,  -8075,  -7900,  -7723,  -7545,  -7366,  -7186,  -7005,  -6822,  -6639,  -6455, 
 -6269,  -6083,  -5896,  -5708,  -5519,  -5329,  -5139,  -4948,  -4756,  -4563,  -4369,  -4175,  -3980,  -3785,  -3589,  -3393, 
 -3196,  -2998,  -2801,  -2602,  -2404,  -2204,  -2005,  -1805,  -1605,  -1405,  -1205,  -1004,   -803,   -603,   -402,   -201, 
     0,    201,    402,    603,    803,   1004,   1205,   1405,   1605,   1805,   2005,   2204,   2404,   2602,   2801,   2998, 
  3196,   3393,   3589,   3785,   3980,   4175,   4369,   4563,   4756,   4948,   5139,   5329,   5519,   5708,   5896,   6083, 
  6269,   6455,   6639,   6822,   7005,   7186,   7366,   7545,   7723,   7900,   8075,   8249,   8423,   8594,   8765,   8934, 
  9102,   9268,   9434,   9597,   9759,   9920,  10079,  10237,  10393,  10548,  10701,  10853,  11002,  11150,  11297,  11442, 
 11585,  11726,  11866,  12003,  12139,  12273,  12406,  12536,  12665,  12791,  12916,  13038,  13159,  13278,  13395,  13510, 
 13622,  13733,  13842,  13948,  14053,  14155,  14255,  14353,  14449,  14543,  14634,  14723,  14810,  14895,  14978,  15058, 
 15136,  15212,  15286,  15357,  15426,  15492,  15557,  15618,  15678,  15735,  15790,  15842,  15892,  15940,  15985,  16028, 
 16069,  16107,  16142,  16175,  16206,  16234,  16260,  16284,  16305,  16323,  16339,  16353,  16364,  16372,  16379,  16382, };

const fxp B_r[FFT_SIZE] = {
 16384,  16585,  16786,  16987,  17187,  17388,  17589,  17789,  17989,  18189,  18389,  18588,  18788,  18986,  19185,  19382, 
 19580,  19777,  19973,  20169,  20364,  20559,  20753,  20947,  21140,  21332,  21523,  21713,  21903,  22092,  22280,  22467, 
 22653,  22839,  23023,  23206,  23389,  23570,  23750,  23929,  24107,  24284,  24459,  24633,  24807,  24978,  25149,  25318, 
 25486,  25652,  25818,  25981,  26143,  26304,  26463,  26621,  26777,  26932,  27085,  27237,  27386,  27534,  27681,  27826, 
 27969,  28110,  28250,  28387,  28523,  28657,  28790,  28920,  29049,  29175,  29300,  29422,  29543,  29662,  29779,  29894, 
 30006,  30117,  30226,  30332,  30437,  30539,  30639,  30737,  30833,  30927,  31018,  31107,  31194,  31279,  31362,  31442, 
 31520,  31596,  31670,  31741,  31810,  31876,  31941,  32002,  32062,  32119,  32174,  32226,  32276,  32324,  32369,  32412, 
 32453,  32491,  32526,  32559,  32590,  32618,  32644,  32668,  32689,  32707,  32723,  32737,  32748,  32756,  32763,  32766, 
 32768,  32766,  32763,  32756,  32748,  32737,  32723,  32707,  32689,  32668,  32644,  32618,  32590,  32559,  32526,  32491, 
 32453,  32412,  32369,  32324,  32276,  32226,  32174,  32119,  32062,  32002,  31941,  31876,  31810,  31741,  31670,  31596, 
 31520,  31442,  31362,  31279,  31194,  31107,  31018,  30927,  30833,  30737,  30639,  30539,  30437,  30332,  30226,  30117, 
 30006,  29894,  29779,  29662,  29543,  29422,  29300,  29175,  29049,  28920,  28790,  28657,  28523,  28387,  28250,  28110, 
 27969,  27826,  27681,  27534,  27386,  27237,  27085,  26932,  26777,  26621,  26463,  26304,  26143,  25981,  25818,  25652, 
 25486,  25318,  25149,  24978,  24807,  24633,  24459,  24284,  24107,  23929,  23750,  23570,  23389,  23206,  23023,  22839, 
 22653,  22467,  22280,  22092,  21903,  21713,  21523,  21332,  21140,  20947,  20753,  20559,  20364,  20169,  19973,  19777, 
 19580,  19382,  19185,  18986,  18788,  18588,  18389,  18189,  17989,  17789,  17589,  17388,  17187,  16987,  16786,  16585, };

const fxp B_i[FFT_SIZE] = {
 16384,  16382,  16379,  16372,  16364,  16353,  16339,  16323,  16305,  16284,  16260,  16234,  16206,  16175,  16142,  16107, 
 16069,  16028,  15985,  15940,  15892,  15842,  15790,  15735,  15678,  15618,  15557,  15492,  15426,  15357,  15286,  15212, 
 15136,  15058,  14978,  14895,  14810,  14723,  14634,  14543,  14449,  14353,  14255,  14155,  14053,  13948,  13842,  13733, 
 13622,  13510,  13395,  13278,  13159,  13038,  12916,  12791,  12665,  12536,  12406,  12273,  12139,  12003,  11866,  11726, 
 11585,  11442,  11297,  11150,  11002,  10853,  10701,  10548,  10393,  10237,  10079,   9920,   9759,   9597,   9434,   9268, 
  9102,   8934,   8765,   8594,   8423,   8249,   8075,   7900,   7723,   7545,   7366,   7186,   7005,   6822,   6639,   6455, 
  6269,   6083,   5896,   5708,   5519,   5329,   5139,   4948,   4756,   4563,   4369,   4175,   3980,   3785,   3589,   3393, 
  3196,   2998,   2801,   2602,   2404,   2204,   2005,   1805,   1605,   1405,   1205,   1004,    803,    603,    402,    201, 
     0,   -201,   -402,   -603,   -803,  -1004,  -1205,  -1405,  -1605,  -1805,  -2005,  -2204,  -2404,  -2602,  -2801,  -2998, 
 -3196,  -3393,  -3589,  -3785,  -3980,  -4175,  -4369,  -4563,  -4756,  -4948,  -5139,  -5329,  -5519,  -5708,  -5896,  -6083, 
 -6269,  -6455,  -6639,  -6822,  -7005,  -7186,  -7366,  -7545,  -7723,  -7900,  -8075,  -8249,  -8423,  -8594,  -8765,  -8934, 
 -9102,  -9268,  -9434,  -9597,  -9759,  -9920, -10079, -10237, -10393, -10548, -10701, -10853, -11002, -11150, -11297, -11442, 
-11585, -11726, -11866, -12003, -12139, -12273, -12406, -12536, -12665, -12791, -12916, -13038, -13159, -13278, -13395, -13510, 
-13622, -13733, -13842, -13948, -14053, -14155, -14255, -14353, -14449, -14543, -14634, -14723, -14810, -14895, -14978, -15058, 
-15136, -15212, -15286, -15357, -15426, -15492, -15557, -15618, -15678, -15735, -15790, -15842, -15892, -15940, -15985, -16028, 
-16069, -16107, -16142, -16175, -16206, -16234, -16260, -16284, -16305, -16323, -16339, -16353, -16364, -16372, -16379, -16382, };

#endif // _FFT_FACTORS_H_
