const static double triggers[] = {
  0,     //0
  1.500, // 1
  3.280, // 2 SA
  3.875, // 3 YUU 
  5.400, // 4 Nochi
  
  7.205, // 5
  8.083, // 6
  8.685, // 7
  8.800, // 8
  10.6,  // 9

  // Da-da-daaa
  11.450, // 10
  11.811, // 11
  12.200, // 12

  13.780, // 13

  15.540, // 14

  // Cresendo
  17.383, // 15

  // More-karoo
  20.679, // 16
  22.238, // 17

  // YE-hii
  24.035, // 18

  27.300, // 19
  28.116, // 20
  28.933, // 21

  30.747, // 22
};

const static size_t len_triggers = sizeof(triggers) / sizeof(*triggers);


// #define OVERRIDE_START_SECS 9
// #define OVERRIDE_END_SECS 17