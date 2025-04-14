// #define __DELAY_BACKWARD_COMPATIBLE__
// #include <avr/io.h>
// #include <usart.h>
// #include <util/delay.h>
// #include <leds.h>
// #include <display.h>
// #include <buttons.h>
// #include <avr/interrupt.h>
// #include <string.h>
// #include <stdlib.h>

// #define MAX_WOORDEN 20  // Maximaal aantal woorden per categorie
// #define WOORD_LENGTE 4   // Lengte van de te raden woorden
// #define MAX_CATEGORIEEN 4 // Aantal categorieën
// #define MAX_POGINGEN 6   // Maximaal aantal pogingen per raadsel

// char *categorien[] = {"DIER", "MENS", "LAND", "DING"};
// const char *dierWoorden[20] = {"HOND", "KAT", "MUIS", "UIL", "VOS", "WOLF", "ZEEH", "BEEH", "HAAN", "UILT", "PAAR", "LEEU", "RAAF", "ZWAAN", "DUIF", "EEND", "GEIT", "HAAI", "TIGR", "ZEBR"};
// const char *mensWoorden[20] = {"MOED", "VADR", "ZOON", "DOCH", "NEEF", "NIGT", "TANT", "MEET", "BABI", "PEET", "BEER", "LIEF", "MOOI", "BOSS", "PRES", "MEID", "KIND", "PAUS", "NARD", "HULK"};
// const char *landWoorden[20] = {"PERU", "CHAD", "IRAN", "OMAN", "FIJI", "MALI", "CUBA", "NEPA", "INDI", "LAOS", "IRAK", "TOGO", "MEXI", "JAPA", "EGYP", "CHIN", "ITAL", "SPAA", "GREE", "TURK"};
// const char *dingWoorden[20] = {"TAFL", "STOE", "LAMP", "BOEK", "KAST", "DEUR", "RAAM", "FIET", "AUTO", "BOOT", "KLUI", "MUUR", "VUUR", "ROOK", "BORD", "KOPJ", "VORK", "BEST", "LEPE", "ZAKK"};

// typedef struct
// {
//   char *categorie;
//   char *woord;
//   //made hiddenword easier to work with
//   char *hiddenWoord;
//   int pogingen;
//   int tijd;
// } Raadsel;

// // globally add on heap
// Raadsel *raadsel = NULL;

// // delay van 1 sec
// #define DELAY 1000

// volatile uint8_t gameState = 0;

// volatile uint8_t categorySelector = 0;

// //startpattern to start game
// void startPattern(){
//   uint8_t numberOfLed = 4;
//   while ( numberOfLed > 0)
//   {
//     lightUpLed(numberOfLed-1);
//     lightUpLed(numberOfLed-2);
//     lightUpLed(numberOfLed-3);
//     lightUpLed(numberOfLed-4);
//     _delay_ms(1000);
//     lightDownLed(numberOfLed-1);
//     lightDownLed(numberOfLed-2);
//     lightDownLed(numberOfLed-3);
//     lightDownLed(numberOfLed-4);
//     _delay_ms(500);
//     numberOfLed--;
//   }
// }

// // timer
// volatile uint8_t sec = 0;
// #define VEELVOUD 250
// volatile uint8_t ctr = 0;

// void initTimer()
// {
//   // CTC mode: (clear timer on compare)
//   TCCR2A |= (1 << WGM21);

//   TIMSK2 |= (1 << OCIE2A);

//   sei();
// }

// void startTimer()
// {
//   printf("started the timer");
//   TCCR2B |= (1 << CS22) | (1 << CS21);
// }

// void resetTimer()
// {
//   printf("reset the timer");
//   sec = 0;
// }

// void tick()
// {
//   OCR2A = 250;
//   sec++;
//   printf("sec: %d",sec);
// }
// // Deze ISR loopt elke 4ms
// ISR(TIMER2_COMPA_vect)
// {
//   // verhoog counter met 1
//   ctr++;
//   // als counter + 1 deelbaar is door VEELVOUD tel één seconde.
//   if (ctr == VEELVOUD)
//   {
//     ctr = 0;
//     tick();
//   }
// }

// char* hiddenWord(char* woord)
// {

//   size_t len = strlen(woord);
//   char *output = (char *)malloc(len + 1);

//   for (uint8_t i = 0; woord[i] != '\0'; i++)
//   {
//     if (woord[i] == 'A' || woord[i] == 'E' || woord[i] == 'I' || woord[i] == 'O' || woord[i] == 'U')
//     {
//       output[i] = woord[i];
//     }
//     else
//     {
//       output[i] = '_';
//     }
//   }
//   output[len] = '\0';  // Null-terminate the string

//   return output;
// }

// void woordSelector()
// {
//   // using string compare
//   if (strcmp(raadsel->categorie, "DIER") == 0)
//   {
//     printf("%s\n", raadsel->categorie);
//     raadsel->woord = dierWoorden[rand() % 20];
//     printf("Woord: %s\n", raadsel->woord);

//     printf("hidden: %s\n", hiddenWord(raadsel->woord));
//     raadsel->hiddenWoord = hiddenWord(raadsel->woord);
//     while (1)
//     {
//       writeString(raadsel->hiddenWoord);
//     }
    
    
//   }
//   if (strcmp(raadsel->categorie, "MENS") == 0)
//   {
//     printf("%s\n", raadsel->categorie);
//     raadsel->woord = mensWoorden[rand() % 20];
//     printf("Woord: %s\n", raadsel->woord);

//     printf("hidden: %s\n", hiddenWord(raadsel->woord));
//     raadsel->hiddenWoord = hiddenWord(raadsel->woord);
//     while (1)
//     {
//       writeString(raadsel->hiddenWoord);
//     }
//   }
//   if (strcmp(raadsel->categorie, "LAND") == 0)
//   {
//     printf("%s\n", raadsel->categorie);
//     raadsel->woord = landWoorden[rand() % 20];
//     printf("Woord: %s\n", raadsel->woord);
    
//     printf("hidden: %s\n", hiddenWord(raadsel->woord));
//     raadsel->hiddenWoord = hiddenWord(raadsel->woord);
//     while (1)
//     {
//       writeString(raadsel->hiddenWoord);
//     }
//   }
//   if (strcmp(raadsel->categorie, "DING") == 0)
//   {
//     printf("%s\n", raadsel->categorie);
//     raadsel->woord = dingWoorden[rand() % 20];
//     printf("Woord: %s\n", raadsel->woord);

//     printf("hidden: %s\n", hiddenWord(raadsel->woord));
//     raadsel->hiddenWoord = hiddenWord(raadsel->woord);
//     while (1)
//     {
//       writeString(raadsel->hiddenWoord);
//     }
//   }
// }



// void selectCategory()
// {
 
//   categorySelector = (categorySelector + 1) % 4; // Wrap around for cyclic selection
//   writeStringAndWait(categorien[categorySelector], DELAY);

// }

// // Function to confirm category selection and start the game
// void confirmCategory()
// {

//   gameState = 1; // Switch to game state
//   startPattern();
//   strcpy(raadsel->categorie, categorien[categorySelector]);
//   woordSelector(); // Choose a random word
//   /* resetTimer(); // Reset timer for the game
//   startTimer(); */
//   startTimer();
//   // Start the timer
  
// }

// // Button interrupt handling
// ISR(PCINT1_vect)
// {
//   if (buttonIsPressed(0))
//   {
//     if (gameState == 0)
//     {
//       selectCategory();
//     }
    
//     if (gameState == 1)
//     {
      
//     }
    
//   }
//   if (buttonIsPressed(1))
//   {
//     if (gameState == 0)
//     {
//       confirmCategory();
//     }
    
//     if (gameState == 1)
//     {
      
//     }
//   }
// }

// int main()
// {
//   initUSART();
//   initDisplay();
//   enableAllButtons();
//   enableAllButtonInterrupt();
//   enableAllLeds();
//   lightDownAllLeds();

//   raadsel = (Raadsel *)malloc(sizeof(Raadsel));


//   initTimer();
//   resetTimer();


//   while (1)
//   {
//     // printf("in loop...");
//     // printf("sec: %d\n",sec);
//     _delay_ms(1000);
//   }
//   return 0;
// }


#define _DELAY_BACKWARD_COMPATIBLE__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <buttons.h>
#include <display.h>
#include <music.h>
#include <stdlib.h>  // To use malloc
#include <string.h>  // To use strcpy
#include <usart.h>
#include <util/delay.h>

#define E5 659.250
#define E4 329.628

// -- VARIABLES
int gameStatus = 1;
//pointer of gameState
int* pGameStatus = &gameStatus;

int numCategories = 0;
//pointer of numCategories
int* pNumCategories = &numCategories;

int currentCategoryIndex = 0;
//pointer of categoryIndex
int* pCurrentCategoryIndex = &currentCategoryIndex;

int buttonPushed = 0;

int* pButtonPushed = &buttonPushed;

char transformedWord[5];
char consonants[] = "bcdfghjklmnpqrstvwxyz";
int numUnderscores = 0;
int underscorePositions[4] = {-1, -1, -1, -1};
int currentConsonantIndex[3] = {0, 0, 0};

int counter = 0;
int* pCounter = &counter;

int seconden = 0;
int* pSeconden = &seconden;
int timerIsDone = 0;

void initTimer()
{
  // CTC mode: (clear timer on compare)
  TCCR2A |= (1 << WGM21);

  TIMSK2 |= (1 << OCIE2A);

  sei();
}

void startTimer()
{
  printf("started the timer");
  TCCR2B |= (1 << CS22) | (1 << CS21);
}

void resetTimer()
{
  printf("reset the timer");
  seconden = 0;
}

typedef struct {
  char* name;     // "dier", "mens", "land", "ding"
  int wordCount;  // hoeveelheid 4 letter woorden in de categorie
  char** words;   // array van de woorden in deze categorie
} CATEGORY;

//make a categories struct equal to NULL
CATEGORY** categories = NULL;



void adjustConsonant(char* transformedWord, int buttonPressed) {
  if (buttonPressed < numUnderscores) {
    int underscoreIndex = underscorePositions[buttonPressed];
    transformedWord[underscoreIndex] = consonants[currentConsonantIndex[buttonPressed]];
    currentConsonantIndex[buttonPressed] = (currentConsonantIndex[buttonPressed] + 1) % strlen(consonants);
  }
}

// showInformation()
// Purpose: Displays welcome and game information.
// Details: Prints welcome messages and waits for button 0 to be pressed to continue.
void showInformation() {
  printf("\nWelcome to the game.\n");
  printf("I hope you are ready for a wordquiz");

  while (!buttonIsPressed(0)) {
    writeString("cat?");
  }
}

// isValidWord(const char* word)
// Purpose: Checks if a given word meets certain criteria.
// Details: Ensures the word is exactly 4 letters long and contains only lowercase letters.
int isValidWord(const char* word) {
  // Alleen 4 letter woorden
  if (strlen(word) != 4) {
    printf("Word '%s' must be exactly 4 letters long.\n", word);
    return 0;
  }

  // Geen hoofdletters
  for (int i = 0; i < 4; i++) {
    if (word[i] < 'a' || word[i] > 'z') {
      printf("Word '%s' must contain only lowercase letters.\n", word);
      return 0;
    }
  }
  return 1;
}

// CATEGORY* createCategory(char* categoryName)
// Purpose: Creates a new category structure.
// Details: Dynamically allocates memory for a new CATEGORY struct and its name.
CATEGORY* createCategory(char* categoryName) {
  if (!isValidWord(categoryName)) {
    printf("Invalid category name: %s\n", categoryName);
    exit(EXIT_FAILURE);
  }

  //* Memorie voor CATEGORY struct
  CATEGORY* category = (CATEGORY*)malloc(sizeof(CATEGORY));

  //* Memorie voor de naam
  category->name = (char*)malloc(5 * sizeof(char));  // 4 characters + 1 for the null terminator
  if (category->name == NULL) {
    printf("Failed to allocate memory for category name");
    free(category);
    exit(EXIT_FAILURE);
  }
  strncpy(category->name, categoryName, 5);
  (*pNumCategories)++;

  category->wordCount = 0;
  category->words = NULL;

  return category;
}

// addWord(CATEGORY* category, const char* word)
// Purpose: Adds a word to a specified category.
// Details: Dynamically reallocates memory for the category's words array and adds the new word.
void addWord(CATEGORY* category, const char* word) {
  if (!isValidWord(word)) {
    printf("Invalid category name: %s\n", word);
    exit(EXIT_FAILURE);
  }

  //* pas memorie aan voor woorden array
  category->words = (char**)realloc(category->words, (category->wordCount + 1) * sizeof(char*));
  if (category->words == NULL) {
    printf("Failed to reallocate memory for words array");
    exit(EXIT_FAILURE);
  }

  //* maak memorie vrij voor het nieuwe woord en voeg het toe
  category->words[category->wordCount] = (char*)malloc(5 * sizeof(char));  // 4 characters + 1 for the null terminator
  if (category->words[category->wordCount] == NULL) {
    printf("Failed to allocate memory for a new word");
    exit(EXIT_FAILURE);
  }

  strncpy(category->words[category->wordCount], word, 4);
  category->words[category->wordCount][4] = '\0'; // null terminator

  category->wordCount++;
}

// removeWord(CATEGORY* category, const char* word)
// Purpose: Removes a word from a specified category.
// Details: Frees memory for the specified word and adjusts the words array accordingly.
void removeWord(CATEGORY* category, const char* word) {
  int index = -1;
  for (int i = 0; i < category->wordCount; i++) {
    if (strncmp(category->words[i], word, 4) == 0) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Word not found in category.\n");
    return;
  }

  // geef memorie van het woord vrij
  free(category->words[index]);

  // verzet de overige woorden in het array
  for (int i = index; i < category->wordCount - 1; i++) {
    category->words[i] = category->words[i + 1];
  }

  // verminder woord count + nieuwe memorie maken die past voor deze nieuwe hoeveelheid woorden
  category->wordCount--;
  category->words = (char**)realloc(category->words, category->wordCount * sizeof(char*));
  if (category->wordCount > 0 && category->words == NULL) {
    printf("Failed to reallocate memory for words array");
    exit(EXIT_FAILURE);
  }
}

// freeCategory(CATEGORY* category)
// Purpose: Frees memory associated with a category.
// Details: Frees memory for all words in the category and then frees memory for the category itself.
void freeCategory(CATEGORY* category) {
  for (int i = 0; i < category->wordCount; i++) {
    free(category->words[i]);
  }
  free(category->words);
  free(category->name);
  free(category);
}

// printCategories(CATEGORY** categories, int numCategories)
// Purpose: Prints all categories and their associated words.
// Details: Iterates through all categories and prints each category's name and its words.
void printCategories(CATEGORY** categories, int numCategories) {
  for (int i = 0; i < numCategories; i++) {
    CATEGORY* category = categories[i];
    printf("Category: %s\n", category->name);
    for (int j = 0; j < category->wordCount; j++) {
      printf("  Word %d: %s\n", j + 1, category->words[j]);
    }
    printf("\n");
  }
}

// char* getRandomWord(CATEGORY* category)
// Purpose: Retrieves a random word from a specified category.
// Details: Selects a random word from the words array of the given category.
char* getRandomWord(CATEGORY* category) {
  if (category->wordCount == 0) {
    printf("This category doesn't have any words in it!");
    exit(EXIT_FAILURE);
  }
  int randomIndex = random() % category->wordCount;
  return category->words[randomIndex];
}

// transformWordWithUnderscores(char* word, char* transformedWord)
// Purpose: Transforms a word into a format with underscores.
// Details: Replaces non-vowel characters in the word with underscores (_).
void transformWordWithUnderscores(char* word, char* transformedWord) {
  const char* vowels = "aeiou";
  for (int i = 0; i < 4; i++) {
    if (strchr(vowels, word[i])) {
      transformedWord[i] = word[i];
    } else {
      transformedWord[i] = '_';
    }
  }
  transformedWord[4] = '\0';
}


// updateTransformedWord(char* transformedWord, const char* targetWord)
// Purpose: Updates the transformed word based on the guessed word.
// Details: Compares each character of transformedWord with targetWord and updates if necessary.
void updateTransformedWord(char* transformedWord, const char* targetWord) {
  for (int i = 0; transformedWord[i] != '\0'; i++) {
    if (transformedWord[i] != targetWord[i]) {
      transformedWord[i] = '_';
    }
  }
}

// identifyUnderscores(char* transformedWord)
// Purpose: Identifies positions of underscores in a transformed word.
// Details: Identifies and stores the positions of underscores (_) in underscorePositions.
void identifyUnderscores(char* transformedWord) {
  numUnderscores = 0;
  for (int i = 0; i < 4; i++) {
    if (transformedWord[i] == '_') {
      underscorePositions[numUnderscores] = i;
      numUnderscores++;
    }
  }
}

// areAllUnderscoresFilled(char* transformedWord)
// Purpose: Checks if all underscores in a transformed word have been filled.
// Details: Returns 1 if there are no underscores left (transformedWord is fully guessed), otherwise 0.
int areAllUnderscoresFilled(char* transformedWord) {
  for (int i = 0; i < 4; i++) {
    if (transformedWord[i] == '_') {
      return 0;  // als er nog "_" aanwezig zijn
    }
  }
  return 1;  // geen "_" meer
}

ISR(TIMER2_COMPA_vect) {
  (*pCounter)++;
  if (counter == 250) {
    (*pSeconden)++;
    printf("seconds = %d\n", seconden);
    counter = 0;
  }

  if (buttonIsPressed(0) || buttonIsPressed(1) || buttonIsPressed(2)) {
    counter = 0;
    seconden = 0;
    resetTimer();
  }

  if (seconden == 5) {
    timerIsDone = 1;
    counter = 0;
    seconden = 0;
    resetTimer();
  }
}

ISR(PCINT1_vect) {
  switch (gameStatus) {
    case 0:
      if (buttonIsPressed(0)) {
        (*pGameStatus)++;
        break;
      }
      break;
    case 1:
      if (buttonIsPressed(0)) {
        (*pButtonPushed)++;
        break;
      } else if (buttonIsPressed(1)) {
        (*pGameStatus)++;
        break;
      }
      break;
    case 2:
      if (buttonIsPressed(0)) {
        adjustConsonant(transformedWord, 0);
        break;
      } else if (buttonIsPressed(1)) {
        adjustConsonant(transformedWord, 1);
        break;
      } else if (buttonIsPressed(2)) {
        adjustConsonant(transformedWord, 2);
        break;
      }
      break;
    case 3:
      if (buttonIsPressed(0)) {
        for (int i = 0; i < numCategories; i++) {
          freeCategory(categories[i]);
        }
        gameStatus = 0;
        main();
        break;
      }
      break;
  }
}
// playIntroSong(), playRightAnswerSong(), playWrongAnswerSong()
// Purpose: Play tones using a buzzer.
// Details: Each function plays a predefined sequence of tones using the playTone() function.
void playIntroSong() {
  playTone(F5,200);
  playTone(C5,100);
  playTone(F5,150);
  playTone(A5,250);
}

void playRightAnswerSong() {
  playTone(G5,300);
  playTone(C5,400);
  playTone(E5,250);
}

void playWrongAnswerSong() {
  playTone(B5,250);
  playTone(G5,300);
  playTone(E4,500);
}

int main() {
  initUSART();
  enableAllButtons();
  enableAllButtonInterrupt();
  initTimer();
  initDisplay();
  enableBuzzer();

  playIntroSong();

  CATEGORY* cDier = createCategory("dier");
  CATEGORY* cMens = createCategory("mens");
  CATEGORY* cLand = createCategory("land");
  CATEGORY* cDing = createCategory("ding");
  //First I was adding everything manual so i Fixeed it
  // const char *dierWoorden[20] = {"HOND", "KAT", "MUIS", "UIL", "VOS", "WOLF", "ZEEH", "BEEH", "HAAN", "UILT", "PAAR", "LEEU", "RAAF", "ZWAAN", "DUIF", "EEND", "GEIT", "HAAI", "TIGR", "ZEBR"};
  addWord(cDier, "eend");
  addWord(cDier, "hond");
  addWord(cDier, "ezel");
  //addWord(cDier, "muis");

  addWord(cMens, "moed");
  addWord(cMens, "vadr");
  addWord(cMens, "zoon");

  addWord(cLand, "peru");
  addWord(cLand, "chad");
  addWord(cLand, "iran");

  addWord(cDing, "tafl");
  addWord(cDing, "stoe");
  addWord(cDing, "lamp");
//   const char *dierWoorden[20] = {
//   "HOND", "KAT", "MUIS", "UIL", "VOS", "WOLF", "ZEEH", "BEEH", 
//   "HAAN", "UILT", "PAAR", "LEEU", "RAAF", "ZWAA", "DUIF", 
//   "EEND", "GEIT", "HAAI", "TIGR", "ZEBR"
//   };

//   // Convert words to lowercase and add only valid words (4-letter words) to the cDier category
//   for (int i = 0; i < 20; i++) {
//       char lowerWord[5];
      
//       // Convert to lowercase
//       for (int j = 0; j < 4; j++) {
//           lowerWord[j] = tolower(dierWoorden[i][j]);
//       }
//       lowerWord[4] = '\0';  // Null-terminate the string

//       // Add the word to the category
//       addWord(cDier, lowerWord);
//   }
//   // const char *mensWoorden[20] = {"MOED", "VADR", "ZOON", "DOCH", "NEEF", "NIGT", "TANT", "MEET", "BABI", "PEET", "BEER", "LIEF", "MOOI", "BOSS", "PRES", "MEID", "KIND", "PAUS", "NARD", "HULK"};
//   // Adding words to cMens category
//   const char *mensWoorden[20] = {
//     "MOED", "VADR", "ZOON", "DOCH", "NEEF", "NIGT", "TANT", "MEET", 
//     "BABI", "PEET", "BEER", "LIEF", "MOOI", "BOSS", "PRES", "MEID", 
//     "KIND", "PAUS", "NARD", "HULK"
//   };

//   for (int i = 0; i < 20; i++) {
//       char lowerWord[5];
      
//       for (int j = 0; j < 4; j++) {
//           lowerWord[j] = tolower(mensWoorden[i][j]);
//       }
//       lowerWord[4] = '\0';  // Null-terminate the string

//       addWord(cMens, lowerWord);
//   }

// // const char *landWoorden[20] = {"PERU", "CHAD", "IRAN", "OMAN", "FIJI", "MALI", "CUBA", "NEPA", "INDI", "LAOS", "IRAK", "TOGO", "MEXI", "JAPA", "EGYP", "CHIN", "ITAL", "SPAA", "GREE", "TURK"};
// // const char *dingWoorden[20] = {"TAFL", "STOE", "LAMP", "BOEK", "KAST", "DEUR", "RAAM", "FIET", "AUTO", "BOOT", "KLUI", "MUUR", "VUUR", "ROOK", "BORD", "KOPJ", "VORK", "BEST", "LEPE", "ZAKK"};
//   const char *landWoorden[20] = {
//     "PERU", "CHAD", "IRAN", "OMAN", "FIJI", "MALI", "CUBA", "NEPA", 
//     "INDI", "LAOS", "IRAK", "TOGO", "MEXI", "JAPA", "EGYP", "CHIN", 
//     "ITAL", "SPAA", "GREE", "TURK"
//   };

//   const char *dingWoorden[20] = {
//     "TAFL", "STOE", "LAMP", "BOEK", "KAST", "DEUR", "RAAM", "FIET", 
//     "AUTO", "BOOT", "KLUI", "MUUR", "VUUR", "ROOK", "BORD", "KOPJ", 
//     "VORK", "BEST", "LEPE", "ZAKK"
//   };

//   // Adding words to cLand category
//   for (int i = 0; i < 20; i++) {
//       char lowerWord[5];
      
//       // Convert to lowercase
//       for (int j = 0; j < 4; j++) {
//           lowerWord[j] = tolower(landWoorden[i][j]);
//       }
//       lowerWord[4] = '\0';  // Null-terminate the string

//       // Add the word to the category
//       addWord(cLand, lowerWord);
//   }

//   // Adding words to cDing category
//   for (int i = 0; i < 20; i++) {
//       char lowerWord[5];
      
//       // Convert to lowercase
//       for (int j = 0; j < 4; j++) {
//           lowerWord[j] = tolower(dingWoorden[i][j]);
//       }
//       lowerWord[4] = '\0';  // Null-terminate the string

//       // Add the word to the category
//       addWord(cDing, lowerWord);
//   }

  



  categories = (CATEGORY**)malloc(numCategories * sizeof(CATEGORY*));
  if (categories == NULL) {
    printf("Failed to allocate memory for categories array\n");
    exit(EXIT_FAILURE);
  }

  categories[0] = cDier;
  categories[1] = cMens;
  categories[2] = cLand;
  categories[3] = cDing;

  showInformation();
  // printCategories(categories, 4);

  while (gameStatus == 1) {
    if (buttonPushed == 1) {
      writeString(categories[currentCategoryIndex]->name);
    } else if (buttonPushed == 2) {
      currentCategoryIndex++;
      if (currentCategoryIndex >= numCategories) {
        currentCategoryIndex = 0;
      }

      buttonPushed = 1;
    }
  }
  buttonPushed = 0;

  char* targetWord = getRandomWord(categories[currentCategoryIndex]);
  transformWordWithUnderscores(targetWord, transformedWord);
  identifyUnderscores(transformedWord);

  int attempts = 1;
  int* pAttempts = &attempts;

  while (gameStatus == 2) {
    writeString(transformedWord);
    if (areAllUnderscoresFilled(transformedWord) && timerIsDone == 0) {
      timerIsDone = 0;
      startTimer();
    }

    if (timerIsDone == 1) {
      if (strcmp(transformedWord, targetWord) == 0) {
        printf("YES!\n");
        printf("In categorie '%s' werd het woord '%s' geraden in %d poginen\n", categories[currentCategoryIndex]->name, targetWord, attempts);
        playRightAnswerSong();
        gameStatus = 3;
        timerIsDone = 0;
        attempts = 0;
      } else {
        printf("NEEN, '%s' boek was niet het juiste aantwoord\n", transformedWord);
        updateTransformedWord(transformedWord, targetWord);  
        gameStatus = 2;
        timerIsDone = 0;
        (*pAttempts)++;
      }
    }
  }

  // Free the category memory
  for (int i = 0; i < numCategories; i++) {
    freeCategory(categories[i]);
  }

  return 0;
}