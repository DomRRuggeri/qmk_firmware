// Phrases

// MO(1) + d [Sends String, taps Tab]
char Phrase1[] = "druggeri$$";

// MO(1) + Shift + d [Sends String, taps Tab]
char Phrase2[] = "EAS\\druggeri$$";

// MO(1) + Ctrl + d [Sends String, taps Enter]
char Phrase3[] = "druggeri1@ellsworth.onmicrosoft.com";


// WinOpen

// MO(1) + n [Taps Winkey, Sends String, taps Enter]
char WinOpen1[] = "notepad";

// MO(1) + Shift + n [Taps Winkey, Sends String, taps Enter]
char WinOpen2[] = "";

// MO(1) + Ctrl + n [Taps Winkey, Sends String, taps Enter]
char WinOpen3[] = "";


// RGB Colors
// Syntax: {mode, hue, sat, value}

// Default Layer Color
uint8_t RGB_Def[4] = {30, 224, 255, 240};

// Function Layer Color
uint8_t RGB_Func[4] = {18, 8, 255, 240};

// Media Layer Color
uint8_t RGB_Led[4] = {14, 128, 255, 240};

// Caps Lock Active Color
uint8_t RGB_Caps[4] = {36, 72, 255, 240};

// Reset Color
uint8_t RGB_Reset[4] = {1, 0, 255, 240};
