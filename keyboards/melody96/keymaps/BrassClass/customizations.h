// Phrases

// MO(1) + "-" [Sends String]
char Phrase1[] = "---";

// MO(1) + "=" [Sends String, taps CTRL+S, ESC]
char Phrase2[] = " RG";

// MO(1) + Ctrl + d [Sends String, taps Enter]
char Phrase3[] = "";


// RGB Colors
// Syntax: {mode, hue, sat, value}

// Default Layer Color
uint8_t RGB_Def[4] = {1, 45, 255, 240};

// Function Layer Color
uint8_t RGB_Func[4] = {18, 8, 255, 240};

// Media Layer Color
//uint8_t RGB_Media[4] = {14, 128, 255, 240};

// Caps Lock Active Color
uint8_t RGB_Caps[4] = {36, 72, 255, 240};

// Reset Color
uint8_t RGB_Reset[4] = {1, 0, 255, 240};
