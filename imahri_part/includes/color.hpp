/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:55:00 by imahri            #+#    #+#             */
/*   Updated: 2023/10/27 11:54:09 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_HPP
#define COLORS_HPP

#define BOLD        "\e[1m"
#define DIM         "\e[2m"
#define UNDERLINED  "\e[4m"
#define BLINK       "\e[5m"
#define REVERSE     "\e[7m"
#define HIDDEN      "\e[8m"

#define RESET_ALL         "\e[0m"
#define RESET_BOLD        "\e[21m"
#define RESET_DIM         "\e[22m"
#define RESET_UNDERLINED  "\e[24m"
#define RESET_BLINK       "\e[25m"
#define RESET_REVERSE     "\e[27m"
#define RESET_HIDDEN      "\e[28m"

#define FG_DEFAULT  "\e[39m"
#define FG_BLACK    "\e[30m"
#define FG_RED      "\e[31m"
#define FG_GREEN    "\e[32m"
#define FG_YELLOW   "\e[33m"
#define FG_BLUE     "\e[34m"
#define FG_MAGENTA  "\e[35m"
#define FG_CYAN     "\e[36m"
#define FG_LGRAY    "\e[37m"
#define FG_DGRAY    "\e[90m"
#define FG_LRED     "\e[91m"
#define FG_LGREEN   "\e[92m"
#define FG_LYELLOW  "\e[93m"
#define FG_LBLUE    "\e[94m"
#define FG_LMAGENTA "\e[95m"
#define FG_LCYAN    "\e[96m"
#define FG_WHITE    "\e[97m"

#define BG_DEFAULT  "\e[49m"
#define BG_BLACK    "\e[40m"
#define BG_RED      "\e[41m"
#define BG_GREEN    "\e[42m"
#define BG_YELLOW   "\e[43m"
#define BG_BLUE     "\e[44m"
#define BG_MAGENTA  "\e[45m"
#define BG_CYAN     "\e[46m"
#define BG_LGRAY    "\e[47m"
#define BG_DGRAY    "\e[100m"
#define BG_LRED     "\e[101m"
#define BG_LGREEN   "\e[102m"
#define BG_LYELLOW  "\e[103m"
#define BG_LBLUE    "\e[104m"
#define BG_LMAGENTA "\e[105m"
#define BG_LCYAN    "\e[106m"
#define BG_WHITE    "\e[107m"

#define Color_Off  "\033[0m"       //# Text Reset

// # Regular Colors
#define  Black  "\033[0;30m"        // # Black
#define  Red  "\033[0;31m"          // # Red
#define  Green  "\033[0;32m"        // # Green
#define  Yellow  "\033[0;33m"       // # Yellow
#define  Blue  "\033[0;34m"         // # Blue
#define  Purple  "\033[0;35m"       // # Purple
#define  Cyan  "\033[0;36m"         // # Cyan
#define  White  "\033[0;37m"        // # White

// # Bold
#define  BBlack  "\033[1;30m"       // # Black
#define  BRed  "\033[1;31m"         // # Red
#define  BGreen  "\033[1;32m"       // # Green
#define  BYellow  "\033[1;33m"      // # Yellow
#define  BBlue  "\033[1;34m"        // # Blue
#define  BPurple  "\033[1;35m"      // # Purple
#define  BCyan  "\033[1;36m"        // # Cyan
#define  BWhite  "\033[1;37m"       // # White

// # Underline
#define  UBlack  "\033[4;30m"       // # Black
#define  URed  "\033[4;31m"         // # Red
#define  UGreen  "\033[4;32m"       // # Green
#define  UYellow  "\033[4;33m"      // # Yellow
#define  UBlue  "\033[4;34m"        // # Blue
#define  UPurple  "\033[4;35m"      // # Purple
#define  UCyan  "\033[4;36m"        // # Cyan
#define  UWhite  "\033[4;37m"       // # White

// # Background
#define  On_Black  "\033[40m"       // # Black
#define  On_Red  "\033[41m"         // # Red
#define  On_Green  "\033[42m"       // # Green
#define  On_Yellow  "\033[43m"      // # Yellow
#define  On_Blue  "\033[44m"        // # Blue
#define  On_Purple  "\033[45m"      // # Purple
#define  On_Cyan  "\033[46m"        // # Cyan
#define  On_White  "\033[47m"       // # White

// # High Intensity
#define  IBlack  "\033[0;90m"       // # Black
#define  IRed  "\033[0;91m"         // # Red
#define  IGreen  "\033[0;92m"       // # Green
#define  IYellow  "\033[0;93m"      // # Yellow
#define  IBlue  "\033[0;94m"        // # Blue
#define  IPurple  "\033[0;95m"      // # Purple
#define  ICyan  "\033[0;96m"        // # Cyan
#define  IWhite  "\033[0;97m"       // # White

// # Bold High Intensity
#define  BIBlack  "\033[1;90m"      // # Black
#define  BIRed  "\033[1;91m"        // # Red
#define  BIGreen  "\033[1;92m"      // # Green
#define  BIYellow  "\033[1;93m"     // # Yellow
#define  BIBlue  "\033[1;94m"       // # Blue
#define  BIPurple  "\033[1;95m"     // # Purple
#define  BICyan  "\033[1;96m"       // # Cyan
#define  BIWhite  "\033[1;97m"      // # White

// # High Intensity backgrounds
#define  On_IBlack  "\033[0;100m"   // # Black
#define  On_IRed  "\033[0;101m"     // # Red
#define  On_IGreen  "\033[0;102m"   // # Green
#define  On_IYellow  "\033[0;103m"  // # Yellow
#define  On_IBlue  "\033[0;104m"    // # Blue
#define  On_IPurple  "\033[0;105m"  // # Purple
#define  On_ICyan  "\033[0;106m"    // # Cyan
#define  On_IWhite  "\033[0;107m"   // # White

#endif