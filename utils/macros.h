/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:51:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/21 22:31:56 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# include <unistd.h>
# include <mlx.h>
# include <time.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "/usr/local/include/mlx.h"

# define BUFFER_SIZE 40

# define WIDTH 1600
# define HEIGHT 900

# define EPSILON 0.00001

# define MULT 1
# define ADD 2
# define SUB 3
# define DIV 4
# define OPP 5

# define OPEN_FILE_ERR "  Failed to open file\n"
# define BAD_FILE_TEXTURE "  Failed function 'mlx_xpm_file_to_image'\n"
# define F_MALL "  Allocation failed\n"
# define BAD_TYPE "  Bad type of element in the scene\n"

/*------------------------- err Ambient lightning ---------------------------*/

# define ERR_A "  Declared more then one element 'A' in the scene\n"
# define ERR_A_1 "  Bad identifier information for element 'A' in the scene\n"
# define ERR_A_2 "  ambient lighting of element 'A' \
in the scene out of range [0.0,1.0]\n"
# define ERR_A_3 "  R.G.B for element 'A' in the scene out of range [0-255]\n"

/*------------------------- err camera ---------------------------*/

# define ERR_C "  Declared more then one element 'C' in the scene\n"
# define ERR_C_1 "  Bad identifier information for element 'C' in the scene\n"
# define ERR_C_2 "  Normalized vector of element 'C' \
in the scene out of range [-1.0,1.0]\n"
# define ERR_C_3 "  FOV of element 'A' in the scene out of range [0-180]\n"
# define NORMAL_C "  Vector not normalized for element 'C'\n"

/*------------------------- err light ---------------------------*/

# define ERR_L "  Declared more then one element 'L' in the scene\n"
# define ERR_L_1 "  Bad identifier information for element 'L' in the scene\n"
# define ERR_L_2 "  Light brightness of element 'L' \
in the scene out of range [0.0,1.0]\n"

/*------------------------- err sphere ---------------------------*/

# define ERR_SP_1 "  Bad identifier information for element 'sp' in the scene\n"
# define ERR_SP_2 "  R.G.B for element 'sp' in the scene out of range [0-255]\n"

/*------------------------- err plane ---------------------------*/

# define ERR_PL_1 "  Bad identifier information for element 'pl' in the scene\n"
# define ERR_PL_2 "  Normalized vector of element 'pl' \
in the scene out of range [-1.0,1.0]\n"
# define ERR_PL_3 "  R.G.B for element 'pl' in the scene out of range [0-255]\n"
# define NORMAL_PL "  Vector not normalized for element 'pl'\n"

/*------------------------- err cylinder ---------------------------*/

# define ERR_CY_1 "  Bad identifier information for element 'cy' in the scene\n"
# define ERR_CY_2 "  Normalized vector of element 'cy' \
in the scene out of range [-1.0,1.0]\n"
# define ERR_CY_3 "  R.G.B for element 'cy' in the scene out of range [0-255]\n"
# define NORMAL_CY "  Vector not normalized for element 'cy'\n"

/*------------------------- err cone ---------------------------*/

# define ERR_CO_1 "  Bad identifier information for element 'co' in the scene\n"
# define ERR_CO_2 "  Normalized vector of element 'co' \
in the scene out of range [-1.0,1.0]\n"
# define ERR_CO_3 "  R.G.B for element 'co' in the scene out of range [0-255]\n"
# define NORMAL_CO "  Vector not normalized for element 'co'\n"

#endif
