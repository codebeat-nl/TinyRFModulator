/*
  Language definition file for TinyRFModulator project.

  CopyLight (c) 2019 codebeat, Erwin Haantjes, http://codebeat.nl

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copylight notice, this
     list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  ATTENTION:
  ---------
  THIS SOFTWARE IS PROVIDED BY THE COPYLIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  VERSION history:
  - Date    : 04-sep-2019 (v1.00)
    updated : 18-sep-2018 


  SUPPORT
  -------
  Love this software? Consider a donation (in future),
  grateful for any kind of support.

  codebeat channels (maybe work in progress):
  - http://www.codebeat.nl             ; Main website
  - http://blog.codebeat.nl            ; Blog website (projects and more)
  - http://youtube.codebeat.nl         ; YouTube channel (shortcut)
  - http://patreon.codebeat.nl         ; Patreon support channel (shortcut)   
  - http://github.codebeat.nl          ; Github (projects)
*/

// -- LANGUAGE STUFF ------------------------------------------------------------------------

// NOTICE:
// ------ 
// o Default language is EN (English)
// o Because of limitation of characters in the font table, not all language specific 
//   characters can be used. Sorry for the inconvenience. 
// o It is possible translations are not that accurate because of missing font 
//   characters or in depth knowledge about a (not natively known) language. 
//   Feel free to rectify possible errors in grammar.
// o Some translations (strings) are stored in program space with use of the 
//   F() macro however this not possible for every string because of:
//   - limited program space
//   - class support, print function

// ADD OR SELECT A LANGUAGE:
// ------------------------- 
// o To add a new language:
//   - Add a new define above the english translation, with a suffix of the name of 
//     language, for example: 
//     #elif defined TRFM_GUI_LANGUAGE_RU // Russian 
//   - Copy all of the defines inside the English block and paste inside the new
//     created block.
//   - Start your translation of all the defines in the created block
// o To activate/select a language:
//   - Copy the define of the language you want; 
//   - Open the TinyRFModulator.config.h file;  
//   - Select the define TRFM_GUI_LANGUAGE_EN and paste clipboard contents;   
//   - Save the file and compile or upload the sketch (no errors = well done!).
 
// TRFM_GUI_LANGUAGE_NL
// --------------------
#ifdef TRFM_GUI_LANGUAGE_NL
 // Dutch
#define TRFM_GUI_LABEL_CHANNEL        "KNL"
#define TRFM_GUI_LABEL_MHZ            "Mhz"
#define TRFM_GUI_LABEL_TESTMODE       "((T))"
#define TRFM_GUI_LABEL_INPUT          "((o))"
#define TRFM_GUI_LABEL_SOUND_CARRIER  "SC" 
#define TRFM_GUI_LABEL_SC_QESTION     "Verbonden tuner"
#define TRFM_GUI_LABEL_ANALOG         "ANALOOG"
#define TRFM_GUI_LABEL_DIGITAL        "DIGITAAL"
#define TRFM_GUI_LABEL_LONG_PRESS     "druk lang"
#define TRFM_GUI_LABEL_SHORT_PRESS    "druk kort"
#define TRFM_GUI_LABEL_OKAY           "OK"
#define TRFM_GUI_LABEL_TUNER          "tuner"
#define TRFM_GUI_LABEL_RESET          "OPNIEUW INSTELLEN"

#define TRFM_GUI_LABEL_SERIAL_COMMAND            F("COMMANDO'S")                      // Command
#define TRFM_GUI_LABEL_SERIAL_UNKNOWN_CMD        F("Onbekend commando opgegeven")     // Unknown command
#define TRFM_GUI_LABEL_SERIAL_SETTINGS_SAVED     F("INSTELLINGEN OPGESLAGEN")         // SETTINGS SAVED
#define TRFM_GUI_LABEL_SERIAL_HELP               F("Geeft deze help weer")            // Shows this help
#define TRFM_GUI_LABEL_SERIAL_LONG_PRESS         F("Voert een lange knopdruk uit")    // Performs a long press
#define TRFM_GUI_LABEL_SERIAL_SHORT_PRESS        F("Voert een korte knopdruk uit")    // Performs a short press
#define TRFM_GUI_LABEL_SERIAL_NEXT_CHANNEL       F("Stelt het volgende kanaal in")    // Set next channel
#define TRFM_GUI_LABEL_SERIAL_PREV_CHANNEL       F("Stelt het vorige kanaal in")      // Set previous channel
#define TRFM_GUI_LABEL_SERIAL_NEXT_SOUND_CARRIER F("Stelt volgende audio carrier in") // Set next sound carrier
#define TRFM_GUI_LABEL_SERIAL_PREV_SOUND_CARRIER F("Stelt vorige audio carrier in")   // Set previous sound carrier 
#define TRFM_GUI_LABEL_SERIAL_TESTMODE           F("Testmodus in-/uitschakelen")      // Toggle testmode 
#define TRFM_GUI_LABEL_SERIAL_RESET              F("Apparaat opnieuw instellen")      // Reset settings/device
#define TRFM_GUI_LABEL_SERIAL_COMMAND            F("COMMANDO")                        // Command
#define TRFM_GUI_LABEL_SERIAL_UNKNOWN_CMD        F("Onbekend commando opgegeven")     // Unknown command
#define TRFM_GUI_LABEL_SERIAL_SETTINGS_SAVED     F("INSTELLINGEN OPGESLAGEN")         // SETTINGS SAVED


// TRFM_GUI_LANGUAGE_DE
// --------------------
#elif defined TRFM_GUI_LANGUAGE_DE
 // German
#define TRFM_GUI_LABEL_CHANNEL        "KNL"
#define TRFM_GUI_LABEL_MHZ            "Mhz"
#define TRFM_GUI_LABEL_TESTMODE       "((T))"
#define TRFM_GUI_LABEL_INPUT          "((o))"
#define TRFM_GUI_LABEL_SOUND_CARRIER  "SC" 
#define TRFM_GUI_LABEL_SC_QESTION     "Angeschl. Tuner"
#define TRFM_GUI_LABEL_ANALOG         "ANALOG"   
#define TRFM_GUI_LABEL_DIGITAL        "DIGITAL"  
#define TRFM_GUI_LABEL_LONG_PRESS     "druck lang"   // Lang drücken
#define TRFM_GUI_LABEL_SHORT_PRESS    "druck kurz"   // Kurz drücken 
#define TRFM_GUI_LABEL_OKAY           "Akzeptiert"   // Akzeptiert
#define TRFM_GUI_LABEL_TUNER          "tuner"
#define TRFM_GUI_LABEL_RESET          "ZURUCKSETZEN" // Zurücksetzen

#define TRFM_GUI_LABEL_SERIAL_COMMAND            F("KOMMANDO")                            // Command
#define TRFM_GUI_LABEL_SERIAL_UNKNOWN_CMD        F("Unbekannter kommando angegeben")      // Unknown command
#define TRFM_GUI_LABEL_SERIAL_SETTINGS_SAVED     F("EINSTELLUNGEN GESPEICHERT")           // SETTINGS SAVED
#define TRFM_GUI_LABEL_SERIAL_HELP               F("Zeigt diese Hilfe")                   // Shows this help
#define TRFM_GUI_LABEL_SERIAL_LONG_PRESS         F("Führt ein langes drücken durch")      // Performs a long press
#define TRFM_GUI_LABEL_SERIAL_SHORT_PRESS        F("Führt ein kurzes drücken durch")      // Performs a short press
#define TRFM_GUI_LABEL_SERIAL_NEXT_CHANNEL       F("Nächsten kanal einstellen")           // Set next channel
#define TRFM_GUI_LABEL_SERIAL_PREV_CHANNEL       F("Vorherigen kanal einstellen")         // Set previous channel
#define TRFM_GUI_LABEL_SERIAL_NEXT_SOUND_CARRIER F("Nächsten audio carrier einstellen")   // Set next sound carrier
#define TRFM_GUI_LABEL_SERIAL_PREV_SOUND_CARRIER F("Vorherigen audio carrier einstellen") // Set previous sound carrier 
#define TRFM_GUI_LABEL_SERIAL_TESTMODE           F("Testmodus umschalten")                // Toggle testmode 
#define TRFM_GUI_LABEL_SERIAL_RESET              F("Institutionen zurücksetzen")          // Reset settings/device


// TRFM_GUI_LANGUAGE_FR
// --------------------
#elif defined TRFM_GUI_LANGUAGE_FR
 // French
#define TRFM_GUI_LABEL_CHANNEL        "CH" // Chaîne
#define TRFM_GUI_LABEL_MHZ            "Mhz"
#define TRFM_GUI_LABEL_TESTMODE       "((T))"
#define TRFM_GUI_LABEL_INPUT          "((o))"
#define TRFM_GUI_LABEL_SOUND_CARRIER  "SC" 
#define TRFM_GUI_LABEL_SC_QESTION     "Tuner connecte" // Tuner connecté
#define TRFM_GUI_LABEL_ANALOG         "ANALOG"         // ANALOGIQUE
#define TRFM_GUI_LABEL_DIGITAL        "DIGITAL"  
#define TRFM_GUI_LABEL_LONG_PRESS     "appui long"
#define TRFM_GUI_LABEL_SHORT_PRESS    "appui brief"    // appuyer brièvement
#define TRFM_GUI_LABEL_OKAY           "D'ACCORD"       // d'accord
#define TRFM_GUI_LABEL_TUNER          "tuner"
#define TRFM_GUI_LABEL_RESET          "REINITIALISER"  // Réinitialiser

#define TRFM_GUI_LABEL_SERIAL_COMMAND            F("COMMANDES")                     // Command
#define TRFM_GUI_LABEL_SERIAL_UNKNOWN_CMD        F("Commande inconnue donnée")      // Unknown command
#define TRFM_GUI_LABEL_SERIAL_SETTINGS_SAVED     F("PARAMÈTRES ENREGISTRÉS")        // SETTINGS SAVED
#define TRFM_GUI_LABEL_SERIAL_HELP               F("Afficher cette aide")           // Shows this help
#define TRFM_GUI_LABEL_SERIAL_LONG_PRESS         F("Effectue une pression longue")  // Performs a long press
#define TRFM_GUI_LABEL_SERIAL_SHORT_PRESS        F("Effectue une pression courte")  // Performs a short press
#define TRFM_GUI_LABEL_SERIAL_NEXT_CHANNEL       F("Définir le canal suivant")      // Set next channel
#define TRFM_GUI_LABEL_SERIAL_PREV_CHANNEL       F("Définir la chaîne précédente")  // Set previous channel
#define TRFM_GUI_LABEL_SERIAL_NEXT_SOUND_CARRIER F("Le carrier sonore suivant")     // Set next sound carrier
#define TRFM_GUI_LABEL_SERIAL_PREV_SOUND_CARRIER F("Le carrier sonore précédent")   // Set previous sound carrier 
#define TRFM_GUI_LABEL_SERIAL_TESTMODE           F("Basculer le mode de test")      // Toggle testmode 
#define TRFM_GUI_LABEL_SERIAL_RESET              F("Réinitialiser")                 // Reset settings/device


// TRFM_GUI_LANGUAGE_IT
// --------------------
#elif defined TRFM_GUI_LANGUAGE_IT
  // Italian
#define TRFM_GUI_LABEL_CHANNEL        "CN" // Canale
#define TRFM_GUI_LABEL_MHZ            "Mhz"
#define TRFM_GUI_LABEL_TESTMODE       "((T))"
#define TRFM_GUI_LABEL_INPUT          "((o))"
#define TRFM_GUI_LABEL_SOUND_CARRIER  "SC" 
#define TRFM_GUI_LABEL_SC_QESTION     "Tuner collegato"
#define TRFM_GUI_LABEL_ANALOG         "ANALOG"  // analogico
#define TRFM_GUI_LABEL_DIGITAL        "DIGITAL" // digitale
#define TRFM_GUI_LABEL_LONG_PRESS     "press. lunga"      // pressione lunga
#define TRFM_GUI_LABEL_SHORT_PRESS    "press. brev."      // pressione brevemente
#define TRFM_GUI_LABEL_OKAY           "VA BENE"
#define TRFM_GUI_LABEL_TUNER          "tuner"
#define TRFM_GUI_LABEL_RESET          "DI NUOVO IMPOSTARE" 

#define TRFM_GUI_LABEL_SERIAL_COMMAND            F("COMMANDI")                            // Command
#define TRFM_GUI_LABEL_SERIAL_UNKNOWN_CMD        F("Comando sconosciuto dato")            // Unknown command
#define TRFM_GUI_LABEL_SERIAL_SETTINGS_SAVED     F("IMPOSTAZIONI SALVATE")                // SETTINGS SAVED
#define TRFM_GUI_LABEL_SERIAL_HELP               F("Mostra questo aiuto")                 // Shows this help
#define TRFM_GUI_LABEL_SERIAL_LONG_PRESS         F("Esegue una pressione prolungata")     // Performs a long press
#define TRFM_GUI_LABEL_SERIAL_SHORT_PRESS        F("Esegue una breve pressione")          // Performs a short press
#define TRFM_GUI_LABEL_SERIAL_NEXT_CHANNEL       F("Imposta il canale successivo")        // Set next channel
#define TRFM_GUI_LABEL_SERIAL_PREV_CHANNEL       F("Imposta il canale precedente")        // Set previous channel
#define TRFM_GUI_LABEL_SERIAL_NEXT_SOUND_CARRIER F("Imposta il prossimo carrier audio")   // Set next sound carrier
#define TRFM_GUI_LABEL_SERIAL_PREV_SOUND_CARRIER F("Imposta il precedente carrier audio") // Set previous sound carrier 
#define TRFM_GUI_LABEL_SERIAL_TESTMODE           F("Attiva/disattiva modalità test")      // Toggle testmode 
#define TRFM_GUI_LABEL_SERIAL_RESET              F("Ripristina impostazioni/dispositivo") // Reset settings/device
#else
// TRFM_GUI_LANGUAGE_EN
// --------------------
// Default is English
#define TRFM_GUI_LABEL_CHANNEL        "CH"
#define TRFM_GUI_LABEL_MHZ            "Mhz"
#define TRFM_GUI_LABEL_TESTMODE       "((T))"
#define TRFM_GUI_LABEL_INPUT          "((o))"
#define TRFM_GUI_LABEL_SOUND_CARRIER  "SC" 
#define TRFM_GUI_LABEL_SC_QESTION     "Connected tuner"
#define TRFM_GUI_LABEL_ANALOG         "ANALOG"
#define TRFM_GUI_LABEL_DIGITAL        "DIGITAL"
#define TRFM_GUI_LABEL_LONG_PRESS     "long press"
#define TRFM_GUI_LABEL_SHORT_PRESS    "short press"
#define TRFM_GUI_LABEL_OKAY           "OK"
#define TRFM_GUI_LABEL_TUNER          "tuner"
#define TRFM_GUI_LABEL_RESET          "RESET"

#define TRFM_GUI_LABEL_SERIAL_COMMAND            F("COMMANDS")                      
#define TRFM_GUI_LABEL_SERIAL_UNKNOWN_CMD        F("Unknown command") 
#define TRFM_GUI_LABEL_SERIAL_SETTINGS_SAVED     F("SETTINGS SAVED") 
#define TRFM_GUI_LABEL_SERIAL_HELP               F("Shows this help")
#define TRFM_GUI_LABEL_SERIAL_LONG_PRESS         F("Performs a long press")
#define TRFM_GUI_LABEL_SERIAL_SHORT_PRESS        F("Performs a short press")
#define TRFM_GUI_LABEL_SERIAL_NEXT_CHANNEL       F("Set next channel")
#define TRFM_GUI_LABEL_SERIAL_PREV_CHANNEL       F("Set previous channel")
#define TRFM_GUI_LABEL_SERIAL_NEXT_SOUND_CARRIER F("Set next sound carrier")
#define TRFM_GUI_LABEL_SERIAL_PREV_SOUND_CARRIER F("Set previous sound carrier")
#define TRFM_GUI_LABEL_SERIAL_TESTMODE           F("Toggle testmode") 
#define TRFM_GUI_LABEL_SERIAL_RESET              F("Reset settings/device")

#endif
