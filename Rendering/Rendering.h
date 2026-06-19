/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 12:53:28 by lpieck            #+#    #+#             */
/*   Updated: 2026/06/19 14:24:57 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;

typedef struct s_draw_params
{
	int col;
	int line_height;
	int draw_start;
	int draw_end;
}	t_draw_params;

void	 render_frame(t_game *game);


#endif
