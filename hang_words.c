#include "hang_words.h"

/* Word libraries */
char anilib[][20] = {"DOG", "FALCON", "TIGER", "ELEPHANT", "LION", "CAT", 
                       "ANTEATER", "SQUIRREL", "EAGLE", "PLATAPUS", "DUCK",
                       "BADGER", "DRAGON", "UNICORN", "RACCOON", "GECKO", 
                       "CHAMELEON", "GORILLA", "GAZELLE", "CHEETAH", "CHEETAL",
                       "PLATYPUS", "PENGUIN", "SPARROW", "MOCKINGBIRD", "CROW",
                       "RAVEN", "SHARK", "WHALE", "TIGERSHARK", "SQUID",
                       "OCTOPUS", "LEEMUR", "CHIMPANZEE", "RINOCEROS", 
                       "IMPALA", "CORVID", "WOODCHUCK", "BEAVER", "ROOSTER",
                       "HORSE", "SHEEP", "GOAT", "COW", "PIG", "HOG", "ROBIN",
                       "NARWHAL", "CHICKEN", "DOVE", "QUAIL", "TIMBERWOLF",
                       "CORGI", "CRAB", "JELLYFISH", "HALIBUT", "TUNA", 
                       "STINGRAY", "FROG", "RATTLESNAKE", "PYTHON", "COBRA",
                       "IGUANA", "MOUSE", "TITMOUSE", "ALPACA", "DEER", 
                       "SASQUATCH", "COD", "SALMON", "FISH", "SHIBE", 
                       "TABBY CAT", "SNOW OWL", "OWL", "BEETLE", "BLACK WIDOW",
                       "SPIDER", "LADYBUG", "HUMMINGBIRD", "HEDGEHOG", 
                       "PORCUPINE", "GUINEA PIG", "BEAR", "BROWN BEAR", 
                       "BLACK BEAR", "ALLIGATOR", "CROCODILE", "SIAMESE CAT", 
                       "RAT", "HUMAN"};

char clib[][25] = {"WCHAR","WCTYPE", "COMPLEX", "FENV", "INTTYPES", "STDBOOL", 
                    "SDTINT", "TGMATH", "ASSERT", "ERRNO", "FLOAT", "LIMITS"
                    "LOCALE", "MATH", "SETJMP", "SIGNAL", "STDARG", "STDINT", 
                    "STDDEF", "STDIO", "STDLIB", "STRING", "TIME", "POSIX", 
                    "NCURSES", "CCV", "CRANIUM", "FANN", "GENANN", "KANN", 
                    "LIBDEEP", "AUTOTOOLS", "CMAKE", "GNUMAKE", "MESON", 
                    "PREMAKE", "SCONS", "XMAKE", "CCACHE", "CLANG", "CPROC", 
                    "PCC", "DISTCC", "FIRM", "GCC", "BLOSC", "BROTLI", "CLZIP",
                    "CROARING", "FINITE STATE ENTROPY", "DENSITY", "HEATSHRINK",
                    "FASTZL", "HANDANDPUFF", "LIZARD", "TURBOPFOR", "SMAZ", 
                    "SIMDCOMP", "SQUASH", "TURBORLE", "ZIP", "ZLIB", 
                    "CHECKEDTHREADS", "CHAN"};
                       
char lwlib[][55] = {"PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS", 
                    "HIPPOPOTOMONSTROSESQUIPPEDALIOPHOBIA",
                    "SUPERCALIFRAGILISTICEXPIALIDOCIOUS",
                    "PSEUDOPSEUDOHYPOPARATHYROIDISM", 
                    "FLOCCINAUCINIHILIPILIFICATION",
                    "ANTIDISESTABLISHMENTARIANISM","HONORIFICABILITUDINITATIBUS",
                    "THYROPARATHYROIDECTOMIZED", "DICHLORODIFLUOROMETHANE",
                    "INCOMPREHENSIBILITIES", "HEPATICOCHOLANGIOGASTROSTOMY",
                    "SPECTROPHOTOFLUOROMETRICALLY", 
                    "PSYCHONEUROENDOCRINOLOGICAL", 
                    "RADIOIMMUNOELECTROPHORESIS",
                    "PNEUMOENCEPHALOGRAPHICALLY", "PSYCHOPHYSICOTHERAPEUTICS",
                    "IMMUNOELECTROPHORETICALLY", "OTORHINOLARYNGOLOGICAL", 
                    "UNCHARACTERISTICALLY"};

char linglib[][25] = {"NOOB", "YEET", "ROFL", "PWNED", "LMGTFY", "LEET", 
                        "SCRUB", "SCRUBLORD", "BUMP", "TROLL", "SIMP",
                        "LURKER", "MEME", "FACEPALM", "FAIL", "ADORBS", 
                        "TOTES", "TBH", "IMHO", "PHOTOBOMB", "SPAM", 
                        "TRENDING", "HANDLE", "NSFW", "TLDR", "OMG", "BRB",
                        "AFK", "TTYL", "STFU", "IDGAF", "AF", "ASF", "HBU",
                        "HMU", "NEWB", "LMAO", "LOL", "NGL", "LMBO", "LEL"};

char capitalslib[][40] = {"MONTGOMERY", "JUNEAU", "PHOENIX", "SACRAMENTO", 
                            "DENVER", "HARTFORD", "DOVER", "TALLAHASSEE",
                            "ATLANTA", "HONOLULU", "BOISE", "SPRINGFIELD", 
                            "INDANAPOLIS", "TOPEKA", "FRANKFORT", "AUGUSTA",
                            "ANNAPOLIS", "BOSTON", "LANSING", "JACKSON", 
                            "HELENA", "LINCOLN", "CONCORD", "TRENTON", 
                            "ALBANY", "RALEIGH", "BISMARCK", "COLUMBUS", 
                            "SALEM", "HARRISBURG", "PROVIDENCE","COLUMBIA", 
                            "PIERRE", "NASHVILLE", "AUSTIN", "MONTPELIER", 
                            "RICHMOND", "OLYMPIA", "CHARLESTON", "MADISON", 
                            "CHEYENNE"};

char prolib[][25] = {"COMPILER", "LINKING", "PREPROCESSOR", "DIRECTIVE", 
                        "PROGRAM", "INCLUDE", "HEADER", "POINTER", "VOID",
                        "STATEMENT", "COMMENT", "VARIABLE", "ASSIGNMENT", 
                        "DECLARATION", "INITIALIZE", "CONSTANT",
                        "IDENTIFIER", "KEYWORD", "LAYOUT", "FORMAT", 
                        "CONVERSION", "SEQUENCE", "ESCAPE", "FUNCTION", 
                        "LIBRARY", "EXPRESSION", "OPERATOR", "IMPLEMENTATION",
                        "PRECEDENCE", "ASSOCIATIVITY", "ASSIGNMENT", "LVALUES",
                        "COMPOUND", "INCREMENT", "DECREMENT", "EVALUATION", 
                        "SUBEXPRESSION", "SELECTION", "RELATIONAL", "EQUALITY",
                        "LOGICAL", "ELSE", "OR", "DO", "XOR", "AND", "WHILE", 
                        "LOOP", "IF", "CASCADED", "BOOLEAN", "VALUE", "SWITCH",
                        "BREAK", "GOTO", "NULL", "UNSIGNED", "INTEGER", 
                        "OCTAL", "HEXIDECIMAL", "DECIMAL", "FLOAT", "DOUBLE", 
                        "ARITHMETIC", "GETCHAR", "PUTCHAR", "CAST", "SIZEOF", 
                        "ARRAY", "INITIALIZATON", "MULTIDIMENSIONAL", 
                        "FUNCTION", "DECLARATION", "ARGUMENT", "RETURN", 
                        "TERMINATION", "RECURSION", "ALGORITHM", "STATIC", 
                        "LOCAL", "GLOBAL", "EXTERNAL", "STACK"};

char countlib[][25] = {"AFGANISTAN", "ALBANIA", "ALGERIA", "ANDORRA", "ANGOLA",
                        "ARGENTINA", "ANTIGUA", "ARMENIA", "AUSTRALIA", 
                        "AUSTRIA", "AZERBAIJAN", "BAHAMAS", "BAHRAIN", 
                        "BANGLADESH", "BARBADOS", "BELARUS", "BELGIUM", 
                        "BELIZE", "BENIN", "BHUTAN", "BOLIVIA", "BOSNIA", 
                        "BOTSWANA", "BRAZIL", "BRUNEI", "BULGARIA", "BURUNDI", 
                        "CAMBODIA", "CAMEROON", "CANADA", "CHAD", "CHILE", 
                        "CHINA", "COLOMBIA", "COMOROS", "CONGO", "CROATIA", 
                        "CUBA", "CYPRUS", "CZECHIA, DENMARK", "DJIBOUTI", 
                        "DOMINICA", "ECUADOR", "EGYPT", "ERITREA", "ESTONIA", 
                        "ESWATINI", "ETHIOPIA", "FIJI", "FINLAND", "FRANCE", 
                        "GABON", "GAMBIA", "GEORGIA", "GERMANY", "GHANA", 
                        "GREECE", "GRENADA", "GUATEMALA", "GUINEA", "GUYANA", 
                        "HAITI", "HONDURAS", "HUNGARY", "ICELAND", "INDIA", 
                        "INDONESIA", "IRAN", "IRAQ", "IRELAND", "ISRAEL", 
                        "ITALY", "JAMACIA", "JAPAN", "JORDAN", "KAZAKHSTAN", 
                        "KENYA", "KRIBATI", "KUWAIT", "KYRGYZSTAN", "LAOS",
                        "LATVIA", "LEBANON", "LESOTHO", "LIBERIA", "LIBYA", 
                        "LIECHTENSTEIN", "LITHUANIA", "LUXEMBOURG", 
                        "MADAGASCAR", "MALAWI", "MALAYSIA", "MALDIVES", "MALI",
                        "MALTA", "MARITANIA", "MAURITIUS", "MEXICO", 
                        "MICRONESIA", "MOLDOVA", "MONACO", "MONGOLIA", 
                        "AMERICA", "MONTENEGRO", "MOROCCO", "MOZAMBIQUE",
                        "MYNAMAR", "NAMBIA", "NAURU", "NEPAL", "NETHERLANDS",
                        "NICARAGUA", "NIGER", "NIGERIA", "NORWAY", "OMAN", 
                        "PAKISTAN", "PALAU", "PALESTINE", "PANAMA", "PARAGUAY",
                        "PERU", "PHILIPPINES", "POLAND", "PORTUGAL", "QATAR", 
                        "ROMANIA", "RUSSIA", "RWANDA", "SAMOA", "SENEGAL", 
                        "SERBIA", "SEYCHELLES", "SINGAPORE", "SLOVAKIA", 
                        "SLOVENIA", "SOMALIA", "SPAIN", "SUDAN", "SURINAME",
                        " SWEEDEN", "SWITZERLAND", "SYRIA", "TAJIKISTAN", 
                        "TANZANIA", "THAILAND", "TOGO", "TONGA", "TUNISIA", 
                        "TURKEY", "TURKMENISTAN", "TUVALU", "UGANDA", 
                        "UKRAINE", "WALES", "ENGLAND", "SCOTLAND", 
                        "UZBEKISTAN", "VANUATU", "VENEZULA", "VIETNAM", 
                        "YEMEN", "ZAMBIA", "ZIMBABWE"};

/* Get size of arrays automatically so you don't need to manually
    change the array size when expanding the library           */
size_t anilib_sz = sizeof(anilib) / sizeof(anilib[0]);
size_t clib_sz = sizeof(clib) / sizeof(clib[0]);
size_t lwlib_sz = sizeof(lwlib) / sizeof(lwlib[0]);
size_t linglib_sz = sizeof(linglib) / sizeof(linglib[0]);
size_t capitalslib_sz = sizeof(capitalslib) / sizeof(capitalslib[0]);
size_t prolib_sz = sizeof(prolib) / sizeof(prolib[0]);
size_t countlib_sz = sizeof(countlib) / sizeof(countlib[0]);

//Loss statements
char gameOver[][100] = {"2020", "It was never meant to be", 
                            "Is life ever fair?", 
                            "We choose our own disappointments", 
                            "React wisely, it's your only life control", 
                            "What time is it?",
                            "Oftentimes, we dig our own grave", 
                            "The coolest part about losing is getting to "
                            "try again", 
                            "Everything has a beginning, and an end", 
                            "Did you mean to lose?",
                            "Someone, somewhere, loves you. Just not me", 
                            "You thought it was going to be easy?", 
                            "The greatest successes come with the biggest"
                            " downfalls",
                            "All of your bases are belong to us", 
                            "I'm a doctor, not a wordsmith", 
                            "Bye Felicia ;)", 
                            "As if", 
                            "Survey says: FAIL"};
size_t gameOver_sz = sizeof(gameOver) / sizeof(gameOver[0]);

//Victory statements
char winEasy[][100] = {"Mastermind?", 
                            "Maybe I picked something too easy for you", 
                            "I'll get you next time", 
                            "Why do you keep winning?", 
                            "Winner winner, chicken dinner", 
                            "I meant it to be easy",
                            "Only an omniscient being could've guessed"
                            " that", 
                            "This game is too easy for you", 
                            "Give me a break, how are you so good at"
                            " this?",
                            "You think you're smart don't you?", 
                            "You're still basic", 
                            "Look at the big brains on Brad", 
                            "Survey says: You won, but did you reaallly?", 
                            "Is this your job?", "Hacks"};
size_t winEasy_sz = sizeof(winEasy) / sizeof(winEasy[0]);

char winMedium[][100] = {"Ok, you win", "Meh, average", 
                        "You're not the first", "Lots of people do that",
                        "Survey says: Winners can't be losers but in your"
                        " case I'm not sure", "Was that really your best?", 
                        "Lame", "Mmmk","Kthxbye", "1337", 
                        "You're just another 99 percent", "Here's a cookie", 
                        "Someone switch the channel this is boring", 
                        "All that and a bag of chips",
                        "You just leveled up", "Power level over 9000", 
                        "\"Final Fantasy Fanfare\""};
size_t winMedium_sz = sizeof(winMedium) / sizeof(winMedium[0]);

char winHard[][100] = {"At last, my patience was really wearing thin", 
                        "How does it take so many tries?", 
                        "That was... a lot of tries", 
                        "You need to get better at this",
                        "My grandma can do better", 
                        "Survey says: I'd say congrats but you probably cheated", 
                        "Finally", "Took you long enough", 
                        "Wake me up when you're done", "Great success", 
                        "*eyeroll*", "You won...for once"};
size_t winHard_sz = sizeof(winHard) / sizeof(winHard[0]);