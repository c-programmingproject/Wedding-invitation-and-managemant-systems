#ifndef UI_H
#define UI_H

/* ================================================================
   MODULE 5 : User Interface (Advanced Console)  –  Header
   PKFIE Yaoundé  |  2025-2026
   ================================================================ */

/* ---------------------------------------------------------------
   Platform-specific clear command
   --------------------------------------------------------------- */
#ifdef _WIN32
    #define CLEAR_CMD "cls"
#else
    #define CLEAR_CMD "clear"
#endif

/* ---------------------------------------------------------------
   ANSI colour / style codes
   (defined here so every module that includes ui.h gets them)
   --------------------------------------------------------------- */
#define RESET    "\033[0m"
#define BOLD     "\033[1m"
#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define CYAN     "\033[36m"
#define MAGENTA  "\033[35m"
#define WHITE    "\033[37m"

/* ---------------------------------------------------------------
   Layout constant
   --------------------------------------------------------------- */
#define CONSOLE_WIDTH 60

/* ---------------------------------------------------------------
   Low-level display helpers
   --------------------------------------------------------------- */

/** clear_screen : call system("clear") / system("cls") */
void clear_screen(void);

/** print_line : print character c repeated n times then newline */
void print_line(char c, int n);

/** print_centered : centre text within CONSOLE_WIDTH columns */
void print_centered(const char *text);

/** print_header : clear screen then print the standard WIGMS banner */
void print_header(const char *title);

/** press_enter : display prompt and consume input until '\n' */
void press_enter(void);

/* ---------------------------------------------------------------
   Feedback helpers
   --------------------------------------------------------------- */
void display_error_message  (const char *msg);
void display_success_message(const char *msg);
void display_warning_message(const char *msg);
void display_info_message   (const char *msg);

/* ---------------------------------------------------------------
   Input helpers  (validated)
   --------------------------------------------------------------- */

/**
 * confirm_action
 * Prints question (Y/N) and returns 1 if user presses Y/y, else 0.
 */
int confirm_action(const char *question);

/**
 * read_int
 * Prompts until the user enters an integer in [min, max].
 */
int read_int(const char *prompt, int min, int max);

/**
 * read_float
 * Prompts until the user enters a float in [min, max].
 */
float read_float(const char *prompt, float min, float max);

/**
 * read_string
 * Prompts until the user enters a non-empty string.
 * Writes at most max_len-1 characters into buf.
 */
void read_string(const char *prompt, char *buf, int max_len);

/* ---------------------------------------------------------------
   Screen layouts
   --------------------------------------------------------------- */
void display_splash_screen(void);
void display_main_menu    (void);

/* ---------------------------------------------------------------
   Module menus  (called from run_application)
   --------------------------------------------------------------- */
void person_menu  (void);
void category_menu(void);
void priority_menu(void);
void gift_menu    (void);
void about_menu   (void);

/* ---------------------------------------------------------------
   Application entry point
   --------------------------------------------------------------- */
void run_application(void);

#endif /* UI_H */
