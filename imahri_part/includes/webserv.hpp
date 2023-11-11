/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:18:09 by imahri            #+#    #+#             */
/*   Updated: 2023/10/27 11:50:27 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include <iostream>
#include "color.hpp"

typedef enum type_config
{
    WORLD ,
    TILDE ,     //  >> ~ <<
    OPEN_CB ,   //  >> { <<
    CLOSED_CB , //  >> } <<
    SLASH ,     //  >> / <<
    COMMENT ,   //  >> # <<
    SEMI ,      //  >> ; <<
    SINGLE_Q ,  //  >> ' <<
    DOUBLE_Q ,  //  >> " <<
    BACKSLASH   //  >> \ <<
    
    
}   t_config;